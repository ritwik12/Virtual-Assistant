
/*
 * File:   analysis.c
 *
 * Created on April 10, 2018, 9:56 AM
 */

//request analysis

struct class_score {
    char * name;
    int score;
};

struct class_score * create_class_score(char * p_name, int p_score) {

    struct class_score * ret = malloc(sizeof(struct class_score));

    ret->name = p_name;
    ret->score = p_score;

    return ret;
}

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

struct class_score * scores[5];

//For Weather---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {

        for (int c = 0; c < 4; c++) {
            if (strcmp(weather_class[b][c], split[v]) == 0) {
                w++;

            }
        }
    }

struct class_score * weathr = create_class_score("weather", w);

scores[0] = weathr;

//For Greeting-----------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(greeting_class[b][c], split[v]) == 0) {
                g++;
            }
        }
    }

struct class_score * greeting = create_class_score("greeting", g);

scores[1] = greeting;

//For Google-------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(google_class[b][c], split[v]) == 0) {
                go++;
            }
        }
    }

struct class_score * google = create_class_score("google", go);

scores[2] = google;

//For Media---------------------------------------

for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(media_class[b][c], split[v]) == 0) {
                me++;
            }
        }
    }

struct class_score * media = create_class_score("media", me);

scores[3] = media;

//For Restaurant-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(restaurant_class[b][c], split[v]) == 0) {
                res++;
            }
        }
    }

struct class_score * restaurant = create_class_score("restaurant", res);

scores[4] = restaurant;

int max_score = scores[0]->score;
char * max_name = scores[0]->name;
int matching_classes = 0;
int ambiguous_flag = 0;
for(int i = 1; i < 5; i++) {

    int temp = scores[i]->score;

    if(temp > max_score) {
        max_score = temp;
        max_name = scores[i]->name;
    }
    else if (temp == max_score) {
        matching_classes++;
    }
}

if(matching_classes >= 2) {
    ambiguous_flag = 1;
}

for (int i = 0; i < 5; i++) {
    struct class_score * temp = scores[i];
    free(temp);
}

if(ambiguous_flag) {
    printf("I didn't understand your request, please rephrase.\n");
    goto get_request;
}
strcpy(result, max_name);
