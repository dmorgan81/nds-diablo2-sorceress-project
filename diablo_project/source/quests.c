#include <nds.h>
#include <filesystem.h>
#include <stdlib.h>
#include <stdio.h>
#include "quests.h"
#include "defines.h"
#include "top_screen.h"
#include "ulScreenDisplay.h"
int texty=45;
extern u32 killedMobs[MAX_DATA];
char* completedQuests=NULL;

struct q_Node
{
    char *name;
    int type,step,rewType,reward,done;
    void* data;
    q_Node *next;
};

struct q_List
{
    q_Node *start;
    int length;
};

q_List questList;

void createQuestList()
{
    questList.start=NULL;
    questList.length=0;
}
q_Node* createQuestNode(char* name,int step,int type,void* data,int rewType,int reward)
{
    q_Node *temp=malloc(sizeof(*temp));
    if(temp)
    {
        temp->name=malloc((strlen(name)+1) *sizeof(char) );
        sprintf(temp->name,"%s",name);
        temp->step=step;
        temp->type=type;
        temp->data=data;
        temp->rewType=rewType;
        temp->reward=reward;
        temp->next=NULL;
    }
    return temp;
}

//add new quest at the beginning
bool pushQuestNode(/*q_Node* list,*/char* name,int step,int type,void* data,int rewType,int reward)
{
    q_Node *temp=createQuestNode(name,step,type,data,rewType,reward);
    if(temp!=NULL)
    {
        temp->next=questList.start;//or list if allow multiple quest lists
        temp->done=0;
        questList.start=temp;
        questList.length++;
        return 1;
    }
    return 0;
}

void removeQuestNode(int nb)//remember, we the first element is 1 and not 0 as in an array
{
    if(nb>questList.length)return;//cant supress void
    if(nb>1)//if not the first element
    {
        q_Node *temp=questList.start,*ptemp=NULL;
        int i;
        for(i=1; i<nb; i++)
        {
            ptemp=temp;
            temp=temp->next;
        }
        ptemp->next=temp->next;
        freeQuest(temp->data,temp->type);
        if(temp->name)free(temp->name);
        free(temp);
        questList.length--;
    }
    if(nb==1 && questList.start!=NULL)
    {
        q_Node *temp=questList.start;
        questList.start=questList.start->next;
        free(temp->data);
        free(temp);
        questList.length--;
    }
}

void purgeQuestList()
{
    while(questList.length)
    {
        removeQuestNode(1);
    }
}
// TODO (Clement#1#): Add other quest types with their respective functions (npc dialog is important, have to do it fast..)

bool isQuestActive(char* name)
{
    int i=0;
    q_Node* tmp=questList.start;
    while(tmp!=NULL)
    {
        if(strcmp(name,tmp->name)==0)return 1;
        tmp=tmp->next;
        i+=8;

    }
    return 0;
}

bool isQuestCompleted(char* name)
{
    return strstr(completedQuests,name)!=NULL;
}

void questIsNowCompleted(char* name)
{
    if(!completedQuests)
    {
        completedQuests=malloc( (strlen(name)+1) * sizeof(char) );
        sprintf(completedQuests,"%s",name);
    }
    else
    {
        char* buffer=NULL;
        buffer=malloc( (strlen(completedQuests)+strlen(name)+2)*sizeof(char) );
        if(buffer)
        {
            sprintf(buffer,"%s%s",completedQuests,name);
            if(completedQuests)free(completedQuests);
            completedQuests=buffer;
        }
    }
}

int loadQuest(char* name,int step)
{
    FILE* file=NULL;
    char buffer[30], textbuffer[500];
    sprintf(buffer,"/quests/%s.dat",name);
    file=fopen(buffer, "rb");
    int type=0,parsedstep=0,rewardType=0,reward=0;
    void* data;
    if(file==NULL)topPrintf(130,40,"Error loading quest data %s step:%i",buffer,step);
    else
    {
        char c=1;
        int i=0;
        do//reach the [step]
        {
            c=fgetc(file);
            if(c=='[')i++;
        }
        while(i<step && c!=EOF);

        if(!fscanf(file,"%i]\n",&parsedstep) || !fscanf(file,"type=%i\n",&type)) PARSERROR;
        if(parsedstep!=step)
        {
            PARSERROR;    //problem in the file, or end of quest data
        }
        else
        {
            switch (type)
            {

            case Q_END:
                questIsNowCompleted(name);
                break;

            case Q_KILL:
                data=malloc(sizeof(q_dataKill));
                if( !fscanf(file,"data=%i\n",&(((q_dataKill*)data)->dataID)) || !fscanf(file,"total=%i\n",&(((q_dataKill*)data)->total)) ) PARSERROR;
                else
                {
                    ((q_dataKill*)data)->target=killedMobs[((q_dataKill*)data)->dataID]+((q_dataKill*)data)->total;
                    if(fscanf(file,"rewardType=%i\nvalue=%i\n\n",&rewardType,&reward)) pushQuestNode(name,step,Q_KILL,(q_dataKill*)data,rewardType,reward);
                    else PARSERROR;
                }
                break;

            case Q_TALK:
                data=malloc(sizeof(q_dataTalk));
                break;

            case Q_GOTO:
                data=malloc(sizeof(q_dataGoto));
                if( !fscanf(file,"mapname=<%29[a-z A-Z]>\n",buffer) || !fscanf(file,"x=%i\ny=%i\nu=%i\nv=%i\n",&(((q_dataGoto*)data)->x),&(((q_dataGoto*)data)->y),&(((q_dataGoto*)data)->u),&(((q_dataGoto*)data)->v)) ) PARSERROR;
                else
                {
                    ((q_dataGoto*)data)->map=malloc((strlen(buffer)+1)*sizeof(char));//allocate amount of memory for the string
                    sprintf(((q_dataGoto*)data)->map,"%s",buffer);                  //copy the name of the map from buffer
                    if(fscanf(file,"rewardType=%i\nvalue=%i\n\n",&rewardType,&reward)) pushQuestNode(name,step,Q_GOTO,(q_dataGoto*)data,rewardType,reward);
                    else PARSERROR;
                }

                break;
            case Q_TEXT:
                data=malloc(sizeof(q_dataText));
                if(!fscanf(file,"text=<%499[^>]>\n",textbuffer))PARSERROR;
                else
                {
                    ((q_dataText*)data)->text=malloc((strlen(textbuffer)+1)*sizeof(char));
                    sprintf(((q_dataText*)data)->text,"%s",textbuffer);
                    i=0;
                    int len=strlen(textbuffer);
                    while(i<len)//replace "end of line" character by a space
                    {
                        if( (((q_dataText*)data)->text)[i]  ==13)(((q_dataText*)data)->text)[i]=' ';
                        i++;
                    }
                    if(fscanf(file,"rewardType=%i\nvalue=%i\n\n",&rewardType,&reward)) pushQuestNode(name,step,Q_TEXT,(q_dataText*)data,rewardType,reward);
                    else PARSERROR;
                }
                break;
            case Q_QUEST:
                data=malloc(sizeof(q_dataQuest));
                if( !fscanf(file,"name=<%[a-z A-Z0-9]>\nstep=%i\n",textbuffer,&(((q_dataQuest*)data)->step)) )PARSERROR;
                else
                {
                    ((q_dataQuest*)data)->name=malloc((strlen(textbuffer)+1)*sizeof(char));
                    sprintf(((q_dataQuest*)data)->name,"%s",textbuffer);
                    if(fscanf(file,"rewardType=%i\nvalue=%i\n\n",&rewardType,&reward))
                    {
                        pushQuestNode(name,step,Q_QUEST,(q_dataQuest*)data,rewardType,reward);
                    }
                    else PARSERROR;
                }
                break;
            default:
                break;
            }

            fclose(file);
            return type;
        }
    }
    fclose(file);
    return 0;
}

void freeQuest(void* data,int type)
{
    switch(type)
    {
    case Q_KILL:
        if((q_dataKill*)data)free((q_dataKill*)data);
        break;
    case Q_TALK:
        if((q_dataTalk*)data)
        {
            if( ((q_dataTalk*)data)->npc ) free(((q_dataTalk*)data)->npc);
            free((q_dataTalk*)data);
        }
        break;
    case Q_GOTO:
        if((q_dataGoto*)data)
        {
            if( ((q_dataGoto*)data)->map ) free(((q_dataGoto*)data)->map);
            free((q_dataGoto*)data);
        }
        break;
    case Q_TEXT:
        if((q_dataText*)data)
        {
            if( ((q_dataText*)data)->text ) free(((q_dataText*)data)->text);
            free((q_dataText*)data);
        }
        break;
    case Q_QUEST:
        if((q_dataQuest*)data)
        {
            if( ((q_dataQuest*)data)->name ) free(((q_dataQuest*)data)->name);
            free((q_dataQuest*)data);
        }
        break;
    }
}
//save quest data and completed quests list
void fsaveQuests(FILE* file)
{
    int stringlen=0;
    fprintf(file,"BeginningOfQuestsData");
    q_Node* temp=questList.start;
    stringlen=strlen(completedQuests);
    fwrite(&stringlen,sizeof(int),1,file);
    fwrite(completedQuests,sizeof(char),stringlen,file);
    fwrite(&questList.length,sizeof(int),1,file);
    while(temp!=NULL)
    {
        stringlen=strlen(temp->name);
        fwrite(&stringlen,sizeof(int),1,file);
        fwrite(temp->name,sizeof(char),stringlen,file);
        fwrite(&temp->step,sizeof(int),1,file);
        fwrite(&temp->type,sizeof(int),1,file);
        switch(temp->type)
        {
        case Q_KILL:
            fwrite(& ((q_dataKill*)(temp->data))->target,sizeof(int),1,file);
            break;
        default:
            break;//other quests types only have constant values
        }
        temp=temp->next;
    }
    fprintf(file,"EndOfQuestsData");
}


//load back quest data and completed quests list
void floadQuests(FILE* file)
{
    char* name=NULL;
    char buffer[1000];
    int step,type,length,i,stringlen;
    q_Node* temp=NULL;
    if(fscanf(file,"BeginningOfQuestsData")==EOF)ERROR("error loading quests save.");
    else
    {
        fread(&stringlen,sizeof(int),1,file);
        fread(buffer,sizeof(char),stringlen,file);
        buffer[stringlen]=0;
        cleanCompletedQuestList();
        questIsNowCompleted(buffer);
        fread(&length,sizeof(int),1,file);
        purgeQuestList();
        for(i=0;i<length;i++)
        {
            fread(&stringlen,sizeof(int),1,file);
            fread(buffer,sizeof(char),stringlen,file);
            buffer[stringlen]=0;
            if(name)free(name);
            name=malloc((strlen(buffer)+1) *sizeof(char));
            sprintf(name,"%s",buffer);
            fread(&step,sizeof(int),1,file);
            fread(&type,sizeof(int),1,file);
            loadQuest(name,step); //push the quest data
            temp=questList.start;
            switch(temp->type)
            {
            case Q_KILL:
                fread(& ((q_dataKill*)(temp->data))->target,sizeof(int),1,file);
                break;
            default:
                break;//other quests types only have constant values
            }
        }
    }
    if(fscanf(file,"EndOfQuestsData") == EOF)
    {
        ERROR("error loading quest save.");
        cleanCompletedQuestList();
        purgeQuestList();
    }
}

void updateQuests()
{
    q_Node* temp=questList.start;
    while(temp!=NULL)
    {
        switch(temp->type)
        {
        case Q_KILL:
            temp->done=updateQuestKill((q_dataKill*)temp->data);
            break;
        case Q_TALK:
            temp->done=updateQuestTalk((q_dataTalk*)temp->data);
            break;
        case Q_GOTO:
            temp->done=updateQuestGoto((q_dataGoto*)temp->data);
            break;
        case Q_TEXT:
            temp->done=updateQuestText((q_dataText*)temp->data);
            break;
        case Q_QUEST:
            temp->done=updateQuestQuest((q_dataQuest*)temp->data);
            break;
        }
        if(temp->done)loadQuest(temp->name,temp->step+1);
        temp=temp->next;
    }
    cleanQuests();
}

void cleanQuests()
{
    q_Node* temp=questList.start;
    int i=1;
    while(temp!=NULL)
    {
        if(temp->done)
        {
            q_reward(temp);
            removeQuestNode(i);
            i--;
        }
        i++;
        temp=temp->next;
    }
}

bool updateQuestKill(q_dataKill *data)
{
    if(killedMobs[data->dataID] >= data->target)
    {
        texty+=10;
        return 1;//quest completed
    }
    //print on top screen how many mobs still need to be killed
    return 0;
}

bool updateQuestTalk(q_dataTalk *data)
{
    return 0;
}

bool updateQuestGoto(q_dataGoto *data)
{
    if(ISINBOX(fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y,data->x,data->y,data->u,data->v))
    {
        texty+=10;
        return 1;//quest completed
    }
    return 0;
}

bool updateQuestQuest(q_dataQuest *data)
{
    if(loadQuest(data->name,data->step))   return 1;
    else return 0;
}

bool updateQuestText(q_dataText *data)
{
    int i;
    UL_IMAGE *box = ulLoadImageFilePNG("/gfx/textbox_png.png",0, UL_IN_RAM, UL_PF_PAL4);

    ulStartDrawing2D();
    myulDrawDialogBox(box,0);
    ulDrawTextBox(3,5,253,190,data->text,0);
    ulEndDrawing();
    i=120;
    while(!ul_keys.pressed.value || i>0)
    {
        WaitForVBL();
        i--;
    }
    WaitForVBL();
    return 1;
}

void q_reward(q_Node* quest)
{
    switch (quest->rewType)
    {
    case QR_NONE:
        break;
    case QR_EXP:
        hero.stats.experience+=quest->reward;
        break;
    case QR_LIFE:
        hero.stats.lifeMax+=quest->reward;
        hero.stats.lifeBonus+=quest->reward;
        break;
    case QR_MANA:
        hero.stats.manaMax+=quest->reward;
        hero.stats.manaBonus+=quest->reward;
        break;
    case QR_WPON:
        //read from a file with waypoints names
        //activatewpnumber(quest->reward)
        //the following function is here temporally
        switch(quest->reward)
        {
        case 0:
            activateWaypoint("Dry Hills");
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
