
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

//For Calendar-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(calendar_class[b][c], split[v]) == 0) {
                ca++;
            }
        }
    }
calendar_score = ca;



if (weather_score > greeting_score) {
    if (weather_score > media_score) {
        if (weather_score > restaurant_score) {
            if (weather_score > google_score)
                if (weather_score > calendar_score)
                    strcpy(result, "weather");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        } else {
            if (restaurant_score > google_score)
                if (restaurant_score > calendar_score)
                    strcpy(result, "restaurant");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        }
    } else {
        if (media_score > restaurant_score) {
            if (media_score > google_score)
                if (media_score > calendar_score)
                    strcpy(result, "media");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        } else {
            if (restaurant_score > google_score)
                if (restaurant_score > calendar_score)
                    strcpy(result, "restaurant");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        }
    }
} else {
    if (greeting_score > media_score) {
        if (greeting_score > restaurant_score) {
            if (greeting_score > google_score)
                if (greeting_score > calendar_score)
                    strcpy(result, "greeting");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        } else {
            if (restaurant_score > google_score)
                if (restaurant_score > calendar_score)
                    strcpy(result, "restaurant");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        }
    } else {
        if (media_score > restaurant_score) {

            if (media_score > google_score)
                if (media_score > calendar_score)
                    strcpy(result, "media");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        } else {
            if (restaurant_score > google_score)
                if (restaurant_score > calendar_score)
                    strcpy(result, "restaurant");
                else
                    strcpy(result, "calendar");
            else
                if (google_score > calendar_score)
                    strcpy(result, "google");
                else
                    strcpy(result, "calendar");
        }
    }
}
