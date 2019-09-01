
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

printf("classifier: %s", classifier[0][0][0]);
//For Weather---------------------------------------

for (int class = 0 ; class < LAST_FIELD ; class++) {
	for (int v = 0; v <= k; v++) {
		for (int b = 0; b < 3; b++) {

			for (int c = 0; c < 4; c++) {
				if (strcmp(classifier[class][b][c], split[v]) == 0) {
					w++;
				}
			}
		}
	}
	scores[class] = w;
}
printf("CHECK 2");
/*
//For Greeting-----------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(classifier[GREETING][b][c], split[v]) == 0) {
                g++;
            }
        }
    }
scores[GREETING] = g;


//For Google-------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(classifier[GOOGLE][b][c], split[v]) == 0) {
                go++;
            }
        }
    }
scores[GOOGLE] = go;


//For Media---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(classifier[MEDIA][b][c], split[v]) == 0) {
                me++;
            }
        }
    }
scores[MEDIA] = me;

//For Email---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(classifier[EMAIL][b][c], split[v]) == 0) {
                em++;
            }
        }
    }
scores[EMAIL] = em;


//For Restaurant-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(classifier[RESTAURANT][b][c], split[v]) == 0) {
                res++;
            }
        }
    }
scores[RESTAURANT] = res;
*/
int score = 0;
for (int i; i < LAST_FIELD; i++) {
	if (scores[i] > score) {
		score = scores[i];
	}
}

if(score == 0) strcpy(result,"");
else if(score == scores[GREETING]) strcpy(result,"greeting");
else if(score == scores[WEATHER]) strcpy(result,"weather");
else if(score == scores[MEDIA]) strcpy(result,"media");
else if(score == scores[RESTAURANT]) strcpy(result,"restaurant");
else if(score == scores[CALENDAR]) strcpy(result,"calendar");
else if(score == scores[EMAIL]) strcpy(result,"email");
else if(score == scores[YOUTUBE]) strcpy(result,"youtube");
else if(score == scores[HELP]) strcpy(result,"help");
else if(score == scores[GOOGLE]) strcpy(result,"google");
