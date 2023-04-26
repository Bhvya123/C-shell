#include "headers.h"

void fg(int argc, char *argv[])
{   
    int n = fork();
    if(n == 0)
    {
        setpgid(0,0);
        argv[argc] = NULL;
        int valid = execvp(argv[0], argv);

        if(valid == -1)
        {
            fginit = -1;
            printf("%s: command not found\n", argv[0]);
            exit(1);
        }
        fginit = 1;
    }
    else if(n == -1)
    {
        perror("Error");
        fginit = -1;
        return;
    }
    else
    {
        if(fginit != -1) fginit = 1;
        int status;
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0,n);
        waitpid(n, &status, WUNTRACED);
        tcsetpgrp(0, getpgid(0));
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
    return;
}