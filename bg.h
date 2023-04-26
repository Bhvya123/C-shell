#ifndef _BG__H_
#define _BG__H_

typedef struct linklist linklist;
typedef struct node node;
struct node
{
    node *next;
    char *commmand;
    pid_t pid;
};

struct linklist
{
    node *head;
    unsigned int size;
};

linklist *ListInit();
node *NodeInit(pid_t procId, char* com);
void insert(char *com, pid_t procID);
void delete(char *com, pid_t procID);

void bg(int argc, char *argv[]);

#endif