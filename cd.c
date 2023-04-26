#include "headers.h"

void cd(int argc, char *argv[])
{
    if(argc > 2)
    {
        printf("bash: cd: too many arguements\n");
        return;
    }

    char *temp = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    strcpy(temp, CURR_DIR);

    if(strcmp(argv[1], HOME) == 0)
    {
        int n = chdir(HOME);
        if(n == -1)
        {
            printf("bash: cd: %s: No such file or directory\n", argv[1]);
            return;
        }
        strcpy(PREV_DIR, temp);
        strcpy(CURR_DIR, HOME);
        return;
    }
    if(argc == 1) 
    {
        int n = chdir(HOME);
        if(n == -1)
        {
            printf("bash: cd: %s: No such file or directory\n", argv[1]);
            return;
        }
        strcpy(PREV_DIR, temp);
        strcpy(CURR_DIR, HOME);
        return;
    }
    if(argv[1][0] == '-')
    {
        int n = chdir(PREV_DIR);
        if(n == -1)
        {
            printf("bash: cd: %s: No such file or directory\n", argv[1]);
            return;
        }
        printf("%s\n", PREV_DIR);
        strcpy(PREV_DIR, temp);
        getcwd(CURR_DIR, MAX_PATH_LENGTH);
        return;
    }
    if(argv[1][0] == '~')
    {
        if(strlen(argv[1]) > 1)
        {
            char *direc = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
            strcpy(direc, HOME);
            strcat(direc, argv[1]+1);
            int n = chdir(direc);
            if(n == -1)
            {
                printf("bash: cd: %s: No such file or directory\n", argv[1]);
                return;
            }
            strcpy(PREV_DIR, temp);
            getcwd(CURR_DIR, MAX_PATH_LENGTH);
        }
        else 
        {
            chdir(HOME);
            getcwd(CURR_DIR, MAX_PATH_LENGTH);
        }
        return;
    }
    else
    {
        int fex = 0;
        if(access(argv[1], F_OK) == 0) fex = 1;
        int n = chdir(argv[1]);
        if(n == -1)
        {
            if(fex == 1)
            {
                printf("bash: cd: %s: Not a directory\n", argv[1]);
                return;
            }
            printf("bash: cd: %s: No such file or directory\n", argv[1]);
            return;
        }
        strcpy(PREV_DIR, CURR_DIR);
        getcwd(CURR_DIR, MAX_PATH_LENGTH);
    }
    return;
}