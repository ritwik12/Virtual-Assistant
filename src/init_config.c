
/* 
 * File:   init_config.c
 *
 * Created on April 10, 2018, 9:18 AM
 */
#include "init_config.h"

FILE *get_Config_File()
{
    FILE *fp;
    fp = fopen("config", "rw");
    
    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open config file\n");
        return NULL;
    }
    else
    {
        return fp;
    }
}
char *set_HomeDir_Var(FILE *conf)
{
    //Getting home directory out of configuration file
    int i = 0;
    char cfg_line[1000];
    cfg_line[i] = fgetc(conf);
    char *pos;
    i++;
    while (cfg_line[i - 1] != '\n' && cfg_line[i - 1] != EOF)
    {
        cfg_line[i] = fgetc(conf);
        i++;
    }
    cfg_line[i - 1] = '\0';
    pos = strchr(cfg_line, '=');

    pos = pos + 2;
    strcpy(HOMEDIR, pos);
#ifdef DEBUG
    printf("%s is home dir\r\n", HOMEDIR);
#endif
    return HOMEDIR;
}
char *set_MediaPlayer_Var(FILE *conf)
{
    //Get preferred media player from config file
    int i = 0;
    MediaPlayer[i] = fgetc(conf);
    i++;
    while (MediaPlayer[i - 1] != '\n' && MediaPlayer[i - 1] != EOF)
    {
        MediaPlayer[i] = fgetc(conf);
        i++;
    }

    MediaPlayer[i - 1] = '\0';
    char *M_P = strchr(MediaPlayer, '=');
    M_P = M_P + 2;
    strcpy(MediaPlayer, M_P);
#ifdef DEBUG
    printf("%s is MediaPlayer\r\n", MediaPlayer);
#endif
    return MediaPlayer;
}
char *set_WebBrowser_Var(FILE *conf)
{
    //Get preferred Webbrowser out of config file
    int i = 0;
    char *pos;
    WebBrowser[i] = fgetc(conf);
    i++;
    while (WebBrowser[i - 1] != '\n' && WebBrowser[i - 1] != EOF)
    {
        WebBrowser[i] = fgetc(conf);
        i++;
    }

    WebBrowser[i - 1] = '\0';
    pos = strchr(WebBrowser, '=');
    pos = pos + 2;
    strcpy(WebBrowser, pos);
#ifdef DEBUG
    printf("%s is webbrowser\r\n", WebBrowser);
#endif
    return WebBrowser;
}
//Clean up file pointer

int config_Cleanup_Status(FILE *conf)
{
    int status = 0;
    if (conf != NULL)
    {
        status = fclose(conf);
    }
    else
    {
        return 1;
    }
    return status;
}
char *getVar(char *varName)
{
    if (!strcmp(WebBrowser, varName))
    {
        return WebBrowser;
    }
    else if (!strcmp(MediaPlayer, varName))
    {
        return MediaPlayer;
    }
    else if (!strcmp(HOMEDIR, varName))
    {
        return HOMEDIR;
    }
    else
    {
        return NULL;
    }
}
