
/* 
 * File:   analysis.c
 *
 * Created on April 10, 2018, 9:56 AM
 */

//request analysis

for (int i = 0; i < strlen(example); i++) {
    if (example[i] == ' ') {
        if (example[i + 1] != ' ') {
            split[k][j] = '\0';
            j = 0;
            k++;
        }
        continue;
    } else {
        split[k][j++] = example[i];
    }
}

split[k][j] = '\0';


//For Weather---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {

        for (int c = 0; c < 4; c++) {
            if (strcmp(weather_class[b][c], split[v]) == 0) {
                w++;

            }
        }
    }
weather_score = w;

//For Greeting-----------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(greeting_class[b][c], split[v]) == 0) {
                g++;
            }
        }
    }
greeting_score = g;


//For Google-------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(google_class[b][c], split[v]) == 0) {
                go++;
            }
        }
    }
google_score = go;


//For Media---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(media_class[b][c], split[v]) == 0) {
                me++;
            }
        }
    }
media_score = me;

//For Email---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(email_class[b][c], split[v]) == 0) {
                em++;
            }
        }
    }
email_score = em;


//For Restaurant-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(restaurant_class[b][c], split[v]) == 0) {
                res++;
            }
        }
    }
restaurant_score = res;

int score = 0;
score = max_five_values(weather_score, greeting_score, media_score, google_score, email_score);
score = max_five_values(score, calendar_score, youtube_score, help_score, restaurant_score);

if(score == 0) strcpy(result,"");
else if(score == greeting_score) strcpy(result,"greeting");
else if(score == weather_score) strcpy(result,"weather");
else if(score == media_score) strcpy(result,"media");
else if(score == restaurant_score) strcpy(result,"restaurant");
else if(score == calendar_score) strcpy(result,"calendar");
else if(score == email_score) strcpy(result,"email");
else if(score == youtube_score) strcpy(result,"youtube");
else if(score == help_score) strcpy(result,"help");
else if(score == google_score) strcpy(result,"google");
