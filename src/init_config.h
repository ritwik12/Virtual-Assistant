/**
 *  Define configuration functions
 * */

#include "stdio.h"
#include "string.h"
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