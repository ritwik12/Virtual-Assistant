
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

//For Reminder-----------------------------------
for (int v = 0; v <= k; v++)
    for (int b = 0; b < 2; b++) {
        for (int c = 0; c < 4; c++) {
            if (strcmp(reminder_class[b][c], split[v]) == 0) {
                rem++;
            }
        }
    }
reminder_score = rem;

if (weather_score == 0 && greeting_score == 0 && media_score == 0 && restaurant_score == 0 && google_score == 0 && reminder_score == 0)
	strcpy(result, "google");
else
if (weather_score > greeting_score)
{
	if (weather_score > media_score)
	{
		if (weather_score > restaurant_score)
		{
			if (weather_score > google_score)
			{
				if (weather_score > reminder_score)
					strcpy(result, "weather");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
		else
		{
			if (restaurant_score > google_score)
			{
				if (restaurant_score > reminder_score)
					strcpy(result, "restaurant");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
	}
	else
	{
		if (media_score > restaurant_score)
		{
			if (media_score > google_score)
			{
				if (media_score > reminder_score)
					strcpy(result, "media");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
		else
		{
			if (restaurant_score > google_score)
			{
				if (restaurant_score > reminder_score)
					strcpy(result, "restaurant");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
	}
}
else
{
	if (greeting_score > media_score)
	{
		if (greeting_score > restaurant_score)
		{
			if (greeting_score > google_score)
			{
				if (greeting_score > reminder_score)
					strcpy(result, "greeting");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
		else
		{   
			if (restaurant_score > google_score)
			{
				if (restaurant_score > reminder_score)
					strcpy(result, "restaurant");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
	}
	else
	{
		if (media_score > restaurant_score)
		{
			if (media_score > google_score)
			{
				if (media_score > reminder_score)
					strcpy(result, "media");
				else
					strcpy(result, "reminder");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
		else
		{
			if (restaurant_score > google_score)
			{
				if (restaurant_score > reminder_score)
					strcpy(result, "restaurant");
				else
					strcpy(result, "google");
			}
			else
			{
				if (google_score > reminder_score)
					strcpy(result, "google");
				else
					strcpy(result, "reminder");
			}
		}
	}
}
