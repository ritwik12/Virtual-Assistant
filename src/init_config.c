
/* 
 * File:   init_config.c
 *
 * Created on April 10, 2018, 9:18 AM
 */
//Getting home directory out of configuration file

char str[1000], *start, pv, location[1000], youtube[1000], songs[1000], cal[100], search[100];
int c, d, len = 0;

FILE *fp;
fp = fopen("config", "rw");
if (fp == NULL) {
    fprintf(stderr, "Unable to open config file\n");
    return 1;
}
int i = 0;
char cfg_line[1000];
cfg_line[i] = fgetc(fp);
i++;
while (cfg_line[i - 1] != '\n' && cfg_line[i - 1] != EOF) {
    cfg_line[i] = fgetc(fp);
    i++;
}
cfg_line[i - 1] = '\0';
char * HOME_DIR = strchr(cfg_line, '=');
HOME_DIR = HOME_DIR + 2;

//Get preferred media player from config file
i = 0;
char media_player[1000];
media_player[i] = fgetc(fp);
i++;
while (media_player[i - 1] != '\n' && media_player[i - 1] != EOF) {
    media_player[i] = fgetc(fp);
    i++;
}

media_player[i - 1] = '\0';
char * M_P = strchr(media_player, '=');
M_P = M_P + 2;
//-----------------------
//Get preferred Webbrowser out of config file
i = 0;
char webbrowser[1000];
webbrowser[i] = fgetc(fp);
i++;
while (webbrowser[i - 1] != '\n' && webbrowser[i - 1] != EOF) {
    webbrowser[i] = fgetc(fp);
    i++;
}

webbrowser[i - 1] = '\0';
char * WebBrowser = strchr(webbrowser, '=');
WebBrowser = WebBrowser + 2;



fclose(fp);
