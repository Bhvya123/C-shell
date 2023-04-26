#include "headers.h"

void prompt()
{
    char *buff2 = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    getcwd(CURR_DIR, MAX_PATH_LENGTH);
    
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    
    gethostname(buff2, MAX_PATH_LENGTH);
    
    printf("\033[0;32m");
    printf("%s@%s", pw->pw_name, buff2);
    printf("\033[0m:");
    printf("\033[0;34m");
    if(strcmp(CURR_DIR, HOME) == 0) 
    {
        if(fginit == 1)
        {
            printf("~ took %lds>\033[0m", tt);
            fginit = 0;
        }
        else printf("~>\033[0m");
    }
    else
    {
        int flag = 0;
        for(int i=0;i<strlen(HOME);i++)
        {
            if(HOME[i] != CURR_DIR[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag) 
        {
            if(fginit == 1)
            {
                printf("%s took %lds>\033[0m", CURR_DIR, tt);
                fginit = 0;
            }
            else printf("%s>\033[0m", CURR_DIR);
        }
        else
        {
            char dir[MAX_PATH_LENGTH];
            int j = 0;
            for(int i = strlen(HOME);i<strlen(CURR_DIR);i++) 
            { 
                dir[j] = CURR_DIR[i];
                j++;
            }
            dir[j] = '\0';
            if(fginit == 1)
            {
                printf("~%s took %lds>\033[0m", dir, tt);
                fginit = 0;
            }
            else printf("~%s>\033[0m", dir);
        }
    }
    
    free(buff2);
    return;
}