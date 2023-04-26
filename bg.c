#include "headers.h"

node *NodeInit(pid_t procId, char *com)
{
    node *n = (node *)malloc(sizeof(node));
    n->commmand = (char *)malloc(sizeof(char) * 2048);
    strcpy(n->commmand, com);
    n->pid = procId;
    n->next = NULL;
    return n;
}

linklist *ListInit()
{
    linklist *n = (linklist *)malloc(sizeof(linklist));
    n->head = NULL;
    n->size = 0;
    return n;
}

void insert(char *com, pid_t procID)
{
    node *n = NodeInit(procID, com);

    if (list->head == NULL)
    {
        list->head = n;
        list->size++;
        return;
    }
    node *temp = list->head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    return;
}

void delete (char *com, pid_t procID)
{
    if (list->size == 0)
        return;

    node *temp = list->head;

    if (temp->pid == procID)
    {
        list->size--;
        list->head = NULL;
        free(temp);
        return;
    }

    while (temp->next != NULL && procID != temp->next->pid)
        temp = temp->next;

    if (temp->next == NULL)
        return;

    node *temp2 = temp->next;
    temp->next = temp->next->next;
    list->size--;
    free(temp2);
    return;
}

void bg(int argc, char *argv[])
{
    for(int i=0;i<argc;i++) printf("%s", argv[i]);
    fginit = 0;
    int n = fork();
    if (n == 0)
    {
        setpgid(0, 0);
        argv[argc] = NULL;
        for (int i = 0; i < argc; i++)
            printf("%s", argv[i]);
        int valid = execvp(argv[0], argv);

        if (valid == -1)
        {
            printf("%s: command not found\n", argv[0]);
            exit(1);
        }

        pid_t p = getpid();
        char *com = (char *)malloc(sizeof(char) * MAX_COMMAND_LENGTH);
        strcpy(com, argv[0]);
        insert(com, p);
    }
    else if (n == -1)
    {
        perror("Error");
        return;
    }

}
