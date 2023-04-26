#include "headers.h"

void selector(int argc, char *argv[])
{
    if(strcmp(argv[0], "echo") == 0) echo(argc, argv);
    else if(strcmp(argv[0], "pwd") == 0) pwdd();
    else if(strcmp(argv[0], "cd") == 0) cd(argc, argv);
    else if(strcmp(argv[0], "history") == 0) PrintHistory(argc, argv);
    else if(strcmp(argv[0], "discover") == 0) discover(argc, argv);
    else if(strcmp(argv[0], "ls") == 0) ls(argc, argv);
    else if(strcmp(argv[0], "pinfo") == 0) 
    {
        if(argc == 1) pinfo(-10);
        else pinfo(atoi(argv[1]));
    }
    else 
    {
        int numand = 0;
        for(int i=0;i<argc;i++)
        {
            if(strcmp(argv[i], "&") == 0)
            {
                numand++;
                continue;
            }
            for(int j=0;j<strlen(argv[i]);j++)
            {
                if(argv[i][j] == '&') numand++;
            }
        }
        if(numand == 0)
        {
            time_t ts = time(NULL); 
            fg(argc, argv);
            time_t te = time(NULL);
            tt = te - ts;
            if(fginit == -1)
            {
                tt = 0;
                fginit = 0;
                return;
            }
        }    
        else
        {   
            for(int i=0;i<argc;i++)
            {
                char *tok = strtok(argv[i], "&");
                char *a[20];
                int ac = 0;
                while(tok != NULL)
                {
                    a[ac++] = tok;
                    tok = strtok(NULL, "&");
                }
                for(int j=0;j<ac;j++)
                {
                    int aac = 0;
                    char *aa[20];
                    char *token = strtok(a[j], " \t\r\n");
                    while(token != NULL)
                    {
                        aa[aac++] = token;
                        printf("%s, ", aa[aac-1]);
                        token = strtok(NULL, " \t\r\n");
                    }
                    if(numand > 0) 
                    {
                        numand--;
                        bg(aac, aa);
                    }
                    else selector(aac, aa);
                }
            }
        }
    }

    return;
}