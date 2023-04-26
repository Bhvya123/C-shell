#include "headers.h"

struct dirent **nlist;

char *Perms(struct stat sb)
{
    char *permissions = (char*)malloc(sizeof(char)*10);  
    strcpy(permissions, "");  
    (S_ISDIR(sb.st_mode)) ? strcat(permissions,"d") : strcat(permissions,"-");
    (sb.st_mode & S_IRUSR) ? strcat(permissions,"r") : strcat(permissions,"-");
    (sb.st_mode & S_IXUSR) ? strcat(permissions,"x") : strcat(permissions,"-");
    (sb.st_mode & S_IRGRP) ? strcat(permissions,"r") : strcat(permissions,"-");
    (sb.st_mode & S_IWUSR) ? strcat(permissions,"w") : strcat(permissions,"-");
    (sb.st_mode & S_IWGRP) ? strcat(permissions,"w") : strcat(permissions,"-");
    (sb.st_mode & S_IXGRP) ? strcat(permissions,"x") : strcat(permissions,"-");
    (sb.st_mode & S_IROTH) ? strcat(permissions,"r") : strcat(permissions,"-");
    (sb.st_mode & S_IWOTH) ? strcat(permissions,"w") : strcat(permissions,"-");
    (sb.st_mode & S_IXOTH) ? strcat(permissions,"x") : strcat(permissions,"-");
    return permissions;
}

char* formatdate(char* str, time_t val)
{
    strftime(str, 36, "%b %d %H:%M", localtime(&val));    
    return str;
}

void Printls(int l_flag, int a_flag, int n, int numlist)
{
    long int total = 0;
    for(int i=0;i<n;i++)
    {
        struct stat ts;
        int tts = stat(nlist[i]->d_name, &ts);
        if(a_flag == 0)
        {
            // if(strcmp(nlist[i]->d_name, ".") == 0 || strcmp(nlist[i]->d_name, "..") == 0)
            // {
            //     continue;
            // }
            if(nlist[i]->d_name[0] == '.') continue;
        }
        total += ts.st_blocks; 
    }
    if(l_flag) printf("total %ld\n", total/2);
    for(int i=0;i<n;i++)
    {
        if(a_flag == 0)
        {
            // if(strcmp(nlist[i]->d_name, ".") == 0 || strcmp(nlist[i]->d_name, "..") == 0)
            // {
            //     continue;
            // }
            if(nlist[i]->d_name[0] == '.') continue;
        }
        struct stat sb;
        stat(nlist[i]->d_name, &sb);

        struct group *g = getgrgid(sb.st_gid); //group name
        struct passwd *pw = getpwuid(sb.st_uid); //user name
        char date[36];
        formatdate(date, sb.st_mtim.tv_sec);
        if(l_flag)
        {
            printf("%s\t%ld\t%s\t%s\t%ld\t%s\t ", Perms(sb), sb.st_nlink, pw->pw_name, g->gr_name, sb.st_size, date);
            if(S_ISDIR(sb.st_mode)) 
            {
                printf("\033[0;34m%s\033[0m\n", nlist[i]->d_name);
            }
            else if(sb.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\033[0m\n", nlist[i]->d_name);
            }
            else 
            {
                printf("%s\n", nlist[i]->d_name);
            }
        }
        else
        {
            if(S_ISDIR(sb.st_mode)) 
            {
                printf("\033[0;34m%s\033[0m\t", nlist[i]->d_name);
            }
            else if(sb.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\033[0m\t", nlist[i]->d_name);
            }
            else 
            {
                printf("%s\t", nlist[i]->d_name);
            }
        }
        // free(nlist[n]);
    }
    if(l_flag == 0) printf("\n");
    // free(nlist);
    if(numlist > 1) printf("\n");
    while(n--) free(nlist[n]);
    free(nlist);
    chdir(CURR_DIR);
    return;
}

void ls(int argc, char *argv[])
{
    int a_flag = 0, l_flag = 0;
    if(argc == 1)
    {
        // struct dirent **nlist;
        int n = scandir(".", &nlist, NULL, alphasort);
        for(int i=0;i<n;i++)
        {
            if(strcmp(nlist[i]->d_name, ".") == 0) continue;
            if(strcmp(nlist[i]->d_name, "..") == 0) continue;
            struct stat sb;
            int tt = stat(nlist[i]->d_name, &sb);
            if(tt != 0)
            {
                perror("Error");
            }
            if(S_ISREG(sb.st_mode) == 0) 
            {
                printf("\033[0;34m%s\033[0m\t", nlist[i]->d_name);
            }
            else if(sb.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\033[0m\t", nlist[i]->d_name);
            }
            else 
            {
                printf("%s\t", nlist[i]->d_name);
            }
            // free(nlist[n]);
        }
        // free(nlist);
        while(n--) free(nlist[n]);
        free(nlist);
        printf("\n");
        return;
    }
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i], "-l") == 0) l_flag = 1;
        if(strcmp(argv[i], "-a") == 0) a_flag = 1;
        if(strcmp(argv[i], "-la") == 0 || strcmp(argv[i], "-al") == 0)
        {
            l_flag = 1;
            a_flag = 1;
        }
    }
    char **list = (char**)malloc(sizeof(char*)*20);
    int numlist = 0;
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "-la") != 0 && strcmp(argv[i], "-al") != 0)
        {
            list[numlist] = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
            strcpy(list[numlist++], argv[i]);
        }
    }

    if(numlist == 0)
    {
        // struct dirent **nlist;
        int n = scandir(".", &nlist, NULL, alphasort);
        Printls(l_flag, a_flag, n, numlist);
        return;
    }

    for(int i=0;i<numlist;i++)
    {
        // struct dirent **nlist;
        char *path = (char*)malloc(sizeof(char)*MAX_PATH_LENGTH);
        if(list[i][0] == '~')
        {
            if(strlen(list[i]) == 1) strcpy(path, HOME);
            else
            {
                strcpy(path, HOME);
                strcat(path, &list[i][1]);
            }
        }
        else strcpy(path, list[i]);
        struct stat sb;
        int nn = stat(path, &sb);
        if(nn == -1) 
        {
            printf("ls: cannot access '%s': No such file or directory\n", path);
            continue;
        }
        if(S_ISDIR(sb.st_mode)) 
        {
            if(numlist > 1) printf("%s:\n", path);
        }
        else if(sb.st_mode & S_IXUSR)
        {
            struct group *g = getgrgid(sb.st_gid); //group name
            struct passwd *pw = getpwuid(sb.st_uid); //user name
            char date[36];
            formatdate(date, sb.st_mtim.tv_sec);
            if(l_flag) printf("%s %ld %s %s %ld %s ", Perms(sb), sb.st_nlink, pw->pw_name, g->gr_name, sb.st_size, date);
            printf("\033[0;32m%s\033[0m\n\n", path);
            continue;
        }
        else
        {
            struct group *g = getgrgid(sb.st_gid);
            struct passwd *pw = getpwuid(sb.st_uid); 
            char date[36];
            formatdate(date, sb.st_mtim.tv_sec);
            if(l_flag) printf("%s %ld %s %s %ld %s ", Perms(sb), sb.st_nlink, pw->pw_name, g->gr_name, sb.st_size, date);
            printf("%s\n\n", path);
            continue;
        }
        chdir(path);
        int n = scandir(".", &nlist, NULL, alphasort);
        Printls(l_flag, a_flag, n, numlist);
    }
    return;
}