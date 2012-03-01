#include <nds.h>
#include <filesystem.h>
#include "quests.h"
#include "defines.h"
#include "top_screen.h"
extern u32 killedMobs[MAX_DATA];
struct q_Node
{
    char *name;
    int type,step;
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
q_Node* createQuestNode(char* name,int type,void* data)
{
    q_Node *temp=malloc(sizeof(*temp));
    if(temp)
    {
        temp->name=name;
        temp->type=type;
        temp->data=data;
        temp->next=NULL;
    }
    return temp;
}

//add new quest at the beginning
bool pushQuestNode(/*q_Node* list,*/char* name,int type,void* data)
{
    q_Node *temp=createQuestNode(name,type,data);
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
    int type=0,parsedstep=0;
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
                if( !fscanf(file,"data=%i\n",&(((q_dataKill*)data)->dataID)) || !fscanf(file,"total=%i\n\n",&(((q_dataKill*)data)->total)) ) PARSERROR;
                else    ((q_dataKill*)data)->target=killedMobs[((q_dataKill*)data)->dataID]+((q_dataKill*)data)->total;
                pushQuestNode(name,Q_KILL,(q_dataKill*)data);
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
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void updateQuests()
{
    q_Node* temp=questList.start;
    int i=1;
    bool remove=0;
    while(temp!=NULL)
    {
        switch(temp->type)
        {
        case Q_KILL:
            remove=updateQuestKill((q_dataKill*)temp->data);
            break;
        case Q_TALK:
            remove=updateQuestTalk((q_dataTalk*)temp->data);
            break;
        case Q_GOTO:
            remove=updateQuestGoto((q_dataGoto*)temp->data);
            break;
        }
        temp=temp->next;
        if(remove)
        {
                removeQuestNode(i);
        }
        else i++;
    }
}

bool updateQuestKill(q_dataKill *data)
{
    if(killedMobs[data->dataID] >= data->target)
    {
        topPrintf(128,45,"Quest completed");
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
