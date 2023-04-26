#include "headers.h"

void pinfo(pid_t pid)
{
    char *p = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    pid_t procID;
    if(pid == -10) procID = getpid();
    else procID = pid;
    sprintf(p, "/proc/%d/stat", procID);

    FILE *fd = fopen(p, "r");

    char state;
    int pgrp, tpgid;
    long unsigned int virtualMem;

    if(fd)
    {
        for(int i=1;i<24;i++)
        {
            if(i == 3)
            {
                fscanf(fd, "%c", &state);
                continue;
            }
            if(i == 5)
            {
                fscanf(fd, "%d", &pgrp);
                continue;
            }
            if(i == 8)
            {
                fscanf(fd, "%d", &tpgid);
                continue;
            }
            if(i == 23)
            {
                fscanf(fd, "%lu", &virtualMem);
                continue;
            }
            fscanf(fd ," %*s ");
        }
    }
    else
    {
        perror("Error");
        return;
    }

    printf("pid : %d\nprocess status : %c\nmemory : %lu\n", procID, state, virtualMem);
    fclose(fd);

    strcpy(p, "");
    sprintf(p, "/proc/%d/exe", procID);

    char *execpath = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    int execpathlen = readlink(p, execpath, MAX_PATH_LENGTH);
    execpath[execpathlen] = '\0';

    if(execpathlen >= strlen(HOME))
    {
        int flag = 0;
        for(int i=0;i<strlen(HOME);i++)
        {
            if(execpath[i] != HOME[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            strcpy(p, "~");
            strcat(p, execpath+strlen(HOME));
        }
        else
        {
            strcpy(p, execpath);
        }
    }
    else strcpy(p, execpath);

    printf("executable path : %s\n", p);
    free(p);
    return;
}