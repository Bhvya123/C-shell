#include "headers.h"

struct dirent *lis;
void printAll(char *targetDir, int d, int f)
{
    DIR *dirr = opendir(targetDir);
    if(dirr == NULL) return;
    while((lis = readdir(dirr)) != NULL)
    {
        if(lis->d_name[0] == '.') continue;
        if(lis->d_type != DT_DIR)
        {
            if((d == 0 && f == 0) || (f == 1 && d == 1) || (f == 1 && d == 0))
            {
                printf("%s/%s\n", targetDir, lis->d_name);
            }
        }
        else
        {
            if((d == 0 && f == 0) || (f == 1 && d == 1) || (f == 0 && d == 1))
            {
                printf("%s/%s\n", targetDir, lis->d_name);
            }
            char *path = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
            sprintf(path, "%s/%s", targetDir, lis->d_name);
            printAll(path, d, f);
        }
    }    
    closedir(dirr);
    return;    
}

void findFile(char *targ, char *filename, int d, int f, int *p)
{
    DIR *dirr = opendir(targ);
    if(dirr == NULL) return;
    // struct dirent *lis;
    while((lis = readdir(dirr)) != NULL)
    {        
        // if(strcmp(lis->d_name, ".") == 0) continue;
        // if(strcmp(lis->d_name, "..") == 0) continue;
        if(lis->d_name[0] == '.') continue;
        if(lis->d_type != DT_DIR)
        {
            if((d == 0 && f == 0) || (f == 1 && d == 1) || (f == 1 && d == 0))
            {
                if(strcmp(filename, lis->d_name) == 0) 
                {
                    printf("%s/%s\n", targ, lis->d_name);
                    *p = 1;
                    return;
                }
            }
        }
        else
        {
            if((d == 0 && f == 0) || (f == 1 && d == 1) || (f == 0 && d == 1))
            {
                if(strcmp(filename, lis->d_name) == 0) 
                {
                    printf("%s/%s\n", targ, lis->d_name);
                    *p = 1;
                    return;
                }
            }
            char path[MAX_PATH_LENGTH];
            sprintf(path, "%s/%s", targ, lis->d_name);
            findFile(path, filename, d, f, p);
        }
    }
    closedir(dirr);
    return;
}

void discover(int argc, char *argv[])
{
    int printed = 0;
    if(argc == 1)
    {
        printAll(".", 0, 0);
        return;
    }
    if(argc > 5)
    {
        printf("discover: Too many arguements\n");
        return;
    }
    int d = 0, f = 0;
    for(int i=0;i<argc;i++)
    {
        if(strcmp(argv[i], "-d") == 0) d = 1;
        if(strcmp(argv[i], "-f") == 0) f = 1;
    }
    char *targetDir = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    char *fileName = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
    strcpy(fileName, "");
    strcpy(targetDir, ".");
    int dirNum = 0;
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "-f") != 0)
        {
            if(argv[i][0] == '\"' && argv[i][strlen(argv[i])-1] == '\"')
            {
                char *token = strtok(argv[i], "\"");
                strcpy(fileName, token);
                token = strtok(NULL, "\"");
            }
            else 
            {
                dirNum++;
                if(dirNum > 1)
                {
                    printf("Multiple directories as arguement\n");
                    return;
                }
                int n = chdir(argv[i]);
                if(n == -1)
                {
                    printf("discover: '%s': No such file or directory\n", argv[i]);
                    return;
                }
                chdir(CURR_DIR);
                strcpy(targetDir, argv[i]);
            }
        }
    }
    if(strcmp(fileName, "") != 0)
    {
        findFile(targetDir, fileName, d, f, &printed);
        if(printed == 0) printf("discover: :::::'%s': No such file or directory\n", fileName);
    }
    else printAll(targetDir, d, f);
    return;
}