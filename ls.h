#ifndef _LS_H__
#define _LS_H__
#include "headers.h"
void ls(int argc, char *argv[]);
char *Perms(struct stat sb);
char *formatdate(char *str, time_t val);
void Printls(int l_flag, int a_flag, int n, int numlist);


#endif