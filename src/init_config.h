/**
 *  Define configuration functions
 * */
#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H
#include "stdio.h"
#include "string.h"

char str[1000], *start, pv, location[1000], youtube[1000], songs[1000], cal[100], search[100];

/***"Init funtions"***/
FILE *get_Config_File();
char *set_HomeDir_Var(FILE *conf);
char *set_MediaPlayer_Var(FILE *conf);
char *set_WebBrowser_Var(FILE *conf);
int config_Cleanup_Status(FILE *conf);
/***Configuration variables**/
char HOMEDIR[1000];
char WebBrowser[1000];
char MediaPlayer[1000];
/***Interface to other modules***/
char* getVar(char *varName);
#endif /*INIT_CONFIG H*/