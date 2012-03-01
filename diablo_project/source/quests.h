#ifndef _QUESTS_H_
#define _QUESTS_H_

typedef struct q_Node q_Node;
typedef struct q_List q_List;

void createQuestList();
q_Node* createQuestNode(char* name,int type,void* data);
bool pushQuestNode(/*q_Node* list,*/char* name,int type,void* data);
void removeQuestNode(int nb);
void updateQuests();
bool loadQuest(char* name,int step);

#define Q_END   0
#define Q_KILL  1
#define Q_TALK  2
#define Q_GOTO  3
typedef struct q_dataKill q_dataKill;
typedef struct q_dataTalk q_dataTalk;
typedef struct q_dataGoto q_dataGoto;

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
    int x1,y1,x2,y2;
};

bool updateQuestKill(q_dataKill *data);
bool updateQuestTalk(q_dataTalk *data);
bool updateQuestGoto(q_dataGoto *data);
#endif
