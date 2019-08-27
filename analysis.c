
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
scores.weather_score = w;

//For Greeting-----------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(greeting_class[b][c], split[v]) == 0) {
                g++;
            }
        }
    }
scores.greeting_score = g;


//For Google-------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(google_class[b][c], split[v]) == 0) {
                go++;
            }
        }
    }
scores.google_score = go;


//For Media---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(media_class[b][c], split[v]) == 0) {
                me++;
            }
        }
    }
scores.media_score = me;

//For Email---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(email_class[b][c], split[v]) == 0) {
                em++;
            }
        }
    }
scores.email_score = em;


//For Restaurant-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(restaurant_class[b][c], split[v]) == 0) {
                res++;
            }
        }
    }
scores.restaurant_score = res;

int score = 0;
score = max_five_values(scores.weather_score, scores.greeting_score, scores.media_score, scores.google_score, scores.email_score);
score = max_five_values(score, scores.calendar_score, scores.youtube_score, scores.help_score, scores.restaurant_score);

if(score == 0) strcpy(result,"");
else if(score == scores.greeting_score) strcpy(result,"greeting");
else if(score == scores.weather_score) strcpy(result,"weather");
else if(score == scores.media_score) strcpy(result,"media");
else if(score == scores.restaurant_score) strcpy(result,"restaurant");
else if(score == scores.calendar_score) strcpy(result,"calendar");
else if(score == scores.email_score) strcpy(result,"email");
else if(score == scores.youtube_score) strcpy(result,"youtube");
else if(score == scores.help_score) strcpy(result,"help");
else if(score == scores.google_score) strcpy(result,"google");
