#ifndef _QUESTS_H_
#define _QUESTS_H_

typedef struct q_Node q_Node;
typedef struct q_List q_List;

void createQuestList();
q_Node* createQuestNode(char* name,int step,int type,void* data,int rewType,int reward);
bool pushQuestNode(/*q_Node* list,*/char* name,int step,int type,void* data,int rewType,int reward);
void removeQuestNode(int nb);
void purgeQuestList();

bool isQuestActive(char* name);
bool isQuestCompleted(char* name);
void questIsNowCompleted(char* name);
#define cleanCompletedQuestList() free(completedQuests)
#define wasQuestAlreadyLoaded(name)   ( isQuestCompleted(name) || isQuestActive(name) )

void updateQuests();

int loadQuest(char* name,int step);
void freeQuest(void* data,int type);
void fsaveQuests(FILE* file);
void floadQuests(FILE* file);
void cleanQuests();

#define Q_END   0
#define Q_KILL  1
#define Q_TALK  2
#define Q_GOTO  3
#define Q_TEXT  4
#define Q_QUEST 5

#define QR_NONE 0
#define QR_EXP  1
#define QR_LIFE 2
#define QR_MANA 3
#define QR_WPON 4   //activate waypoint
typedef struct q_dataKill q_dataKill;
typedef struct q_dataTalk q_dataTalk;
typedef struct q_dataGoto q_dataGoto;
typedef struct q_dataText q_dataText;
typedef struct q_dataQuest q_dataQuest;

struct q_dataKill
{
    int dataID,target,total;
};

struct q_dataTalk
{
    char* npc;
};

struct q_dataGoto
{
    char* map;
    int x,y,u,v;
};

struct q_dataText
{
    char* text;
};

struct q_dataQuest
{
    char* name;
    int step;
};

bool updateQuestKill(q_dataKill *data);
bool updateQuestTalk(q_dataTalk *data);
bool updateQuestGoto(q_dataGoto *data);
bool updateQuestText(q_dataText *data);
bool updateQuestQuest(q_dataQuest *data);


void q_reward(q_Node* quest);
#endif
