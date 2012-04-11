#include <nds.h>
#include <filesystem.h>
#include "quests.h"
#include "defines.h"
#include "top_screen.h"
int texty=45;
extern u32 killedMobs[MAX_DATA];
struct q_Node
{
    char *name;
    int type,step,rewType,reward;
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
        temp->name=name;
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
        free(temp->data);
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

// NOTE (Clement#1#): definir /*Q_kills*/, la fonction etc...
bool loadQuest(char* name,int step)
{
    FILE* file=NULL;
    char buffer[30];
    sprintf(buffer,"/quests/%s.dat",name);
    file=fopen(buffer, "rb");
    int type=0,parsedstep=0,rewardType=0,reward=0;
    void* data;
    if(file==NULL)topPrintf(130,40,"Error loading quest data");
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
                //delete quest nodes, free ptr to name etc
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
void updateQuests()
{
    q_Node* temp=questList.start;
    q_Node* temp2=NULL;
    int i=1;
    bool done=0;
    while(temp!=NULL)
    {
        switch(temp->type)
        {
        case Q_KILL:
            done=updateQuestKill((q_dataKill*)temp->data);
            break;
        case Q_TALK:
            done=updateQuestTalk((q_dataTalk*)temp->data);
            break;
        case Q_GOTO:
            done=updateQuestGoto((q_dataGoto*)temp->data);
            break;
        }
        temp2=temp;
        temp=temp->next;
        if(done)
        {
            q_reward(temp2);
            if(loadQuest(temp2->name,temp2->step+1))removeQuestNode(i+1);
            else removeQuestNode(i);
        }
        else i++;
    }
}

bool updateQuestKill(q_dataKill *data)
{
    if(killedMobs[data->dataID] >= data->target)
    {

        topPrintf(128,texty,"Quest completed:%i",data->total);
        //texty+=10;
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
    return 0;
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
        break;
    case QR_MANA:
        hero.stats.manaMax+=quest->reward;
        break;

    default:
        break;
    }
}
