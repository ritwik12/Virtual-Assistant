
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
score_array[WEATHER_SCORE] = w;

//For Greeting-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(greeting_class[b][c], split[v]) == 0) {
                g++;
            }
        }
    }
score_array[GREETING_SCORE] = g;


//For Google-------------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(google_class[b][c], split[v]) == 0) {
                go++;
            }
        }
    }
score_array[GOOGLE_SCORE] = go;


//For Media---------------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(media_class[b][c], split[v]) == 0) {
                me++;
            }
        }
    }
score_array[MEDIA_SCORE] = me;

//For Restaurant-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(restaurant_class[b][c], split[v]) == 0) {
                res++;
            }
        }
    }
score_array[RESTAURANT_SCORE] = res;

int max_index = 10, max_score = 0;
char max_score_name[10];

for (int i=0 ; i< SIZE; i++){
	if (score_array[i] > max_score){
		max_index = i;
		max_score = score_array[i];
		strcpy (max_score_name, score_names[i]);
	}
}

if (max_score == 0)
	strcpy(result, "google");
else
{
	strcpy(result, max_score_name);
}

