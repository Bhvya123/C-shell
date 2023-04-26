#include "headers.h"

void CheckStat()
{
    if(list->size == 0) return;
    int status;
    int p = waitpid(-1, &status, WNOHANG);

    if(p > 0)
    {
        node *temp = list->head;
        while(temp != NULL && temp->pid != p)
        {
            temp = temp->next;
        }
        if(temp == NULL) return;

        if(WIFSTOPPED(status)) return;

        printf("%s with pid = %d exited ", temp->commmand, temp->pid);
        if(WIFEXITED(status)) printf("normally\n");
        else printf("abnormally\n");
        delete(temp->commmand, temp->pid);    
    }
}

int main()
{
    getcwd(HOME, MAX_PATH_LENGTH);
    strcpy(CURR_DIR, HOME);
    strcpy(PREV_DIR, HOME);
    int exiter = 0;
    HistLen = 0;
    hist = DeQueueInit();
    FILE *fd = fopen("history.txt", "a");
    fclose(fd);
    readPrevHist();

    Qnode* temp = hist->back;
    list = ListInit();
    tt = 0;
    fginit = 0;
    while(1)
    {
        CheckStat();
        prompt();
        char *inp = (char*)malloc(sizeof(char)*MAX_COMMAND_LENGTH);
        char *inpt = (char*)malloc(sizeof(char)*MAX_COMMAND_LENGTH);
        
        fgets(inp, MAX_COMMAND_LENGTH, stdin);
        strcpy(inpt, inp);
        char *tok = strtok(inpt, " \t\n\r");
        if(strlen(inp) == 0 || tok == NULL) continue;
        if(size(hist) >= 20)
        {
            if(strcmp(front(hist), inp) != 0)
            {
                pop_back(hist);
                push_front(hist, inp);
            }
        }
        else 
        {
            if(front(hist) == NULL) push_front(hist, inp);
            else if(strcmp(front(hist), inp) != 0)
            {
                push_front(hist, inp);
            }
        }
        writeToFile();

        char *token = strtok(inp, ";");
        char *commands[20];
        int numCommands = 0;
        while(token != NULL)
        {
            commands[numCommands++] = token;
            token = strtok(NULL, ";");
        }
        for(int i=0;i<numCommands;i++)
        {
            int argc = 0;
            char *argv[20];
            char *token2 = strtok(commands[i], " \t\r\n");

            while(token2 != NULL)
            {
                argv[argc++] = token2;
                token2 = strtok(NULL, " \t\r\n");
            }
            if(strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "logout") == 0) 
            {
                exiter = 1;
                break;
            }
            if(strcmp(argv[0], "clear") == 0)
            {
                system("clear");
                continue;
            }
            selector(argc, argv);
        }
        if(exiter) break;
    }
    return 0;
}