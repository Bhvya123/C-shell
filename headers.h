#ifndef HEADER_SS
#define HEADER_SS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<netdb.h>
#include<pwd.h>
#include<time.h>
#include<grp.h>
#include<dirent.h>
#include<time.h>
#include<fcntl.h>
#include "prompt.h"
#include "pwdd.h"
#include "echo.h"
#include "comSelector.h"
#include "cd.h"
#include "history.h"
#include "discovery.h"
#include "ls.h"
#include "pinfo.h"
#include "fg.h"
#include "bg.h"
#define MAX_PATH_LENGTH 1024
#define MAX_COMMAND_LENGTH 2048
#define MAX_FILE_NAME 100
int HistLen; 
long int tt;
int fginit;
char HOME[MAX_PATH_LENGTH];
char CURR_DIR[MAX_PATH_LENGTH];
char PREV_DIR[MAX_PATH_LENGTH];
dequeue *hist;
linklist *list;

#endif