#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct DeQueue dequeue;
typedef struct QueueNode Qnode;

struct QueueNode
{
    char *data;
    Qnode *next;
    Qnode *prev;
};

struct DeQueue
{
    Qnode *front;
    Qnode *back;
    unsigned int size;
};

Qnode *QnodeInit();
dequeue *DeQueueInit();
void pop_front(dequeue *dq);
void pop_back(dequeue *dq);
void push_front(dequeue *dq, char *x);
void push_back(dequeue *dq, char *x);
char *front(dequeue *dq);
char *back(dequeue *dq);
int isEmpty(dequeue *dq);
int size(dequeue *dq);

void PrintHistory(int argc, char *argv[]);
void writeToFile();
void readPrevHist();

#endif