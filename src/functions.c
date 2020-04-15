

/* 
 * File:   functions.c
 * Author: Goodluck
 * Author: Riya
 * Author: Ritwik
 * Created on April 9, 2018, 3:41 PM
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "H" {
#endif




#ifdef __cplusplus
}
#endif


#define SPACE ' '
//Function used by libcurl to allocate memory to data received from the HTTP response

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {

    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);

    if (mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

static size_t WriteFunct(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct string *s = (struct string *) userp;
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    printf("%s", s->ptr);
    size_t realsize = size*nmemb;
    return realsize;
}

int find_restaurants() {
    char *encoded_address, *url;
    char *api_key = "AIzaSyAjfVvnaDMYiR9i2DjeCSjZ76PR4qRCNTM";
    char address[1000];
    CURL *curl = NULL;
    CURLcode result;
    int i, len;
    int j, head_length, length; //variables for output formatting
    char location[1000];
    struct json_object *jobj, *obj1, *obj2, *obj3, *obj4, *lat, *lng; //Geocoding API json objects
    struct json_object *pl1, *pl2, *idx, *name, *price, *vic, *rate, *open, *hrs; //Google Place API json Objects
    struct MemoryStruct geo, places;
    geo.memory = malloc(4096);
    geo.size = 0;
    places.memory = malloc(4096);
    places.size = 0;


    curl = curl_easy_init();

    system("say Please enter your area/locality");
    printf("Please enter your area/locality\n\n");
    fgets(address, 1000, stdin);

    //-----------------------Google Geocoding API to convert Area name into co-ordinates needed by Places API------------------------	

    if (curl) {
        encoded_address = curl_easy_escape(curl, address, 0);
        if (!encoded_address) {
            fprintf(stderr, "Could not encode address\n");
            curl_easy_cleanup(curl);
            return -1;
        }

        url = malloc(strlen(encoded_address) + 200);
        if (!url) {
            fprintf(stderr, "Could not allocate memory for url\n");
            free(encoded_address);
            curl_easy_cleanup(curl);
            return -1;
        }

        //url for geocoder api
        sprintf(url, "https://maps.googleapis.com/maps/api/geocode/json?key=%s&address=%s", api_key, encoded_address);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_CAPATH, "/usr/ssl/certs/crt");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &geo);


        result = curl_easy_perform(curl);

        if (result != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

        }

        //---------------Parsing JSON result from geocoding API----------------------------------------------------------------
        jobj = json_tokener_parse(geo.memory);
        json_object_object_get_ex(jobj, "results", &obj1);
        obj2 = json_object_array_get_idx(obj1, 0);
        json_object_object_get_ex(obj2, "geometry", &obj3);
        json_object_object_get_ex(obj3, "location", &obj4);
        json_object_object_get_ex(obj4, "lat", &lat);
        json_object_object_get_ex(obj4, "lng", &lng);

        //-----------------------------JSON Parsed-------------------------------------------------------------------------------
        sprintf(location, "%s,%s", json_object_get_string(lat), json_object_get_string(lng));

        //------------------------------Google Places API---------------------------------------------------------------------

        sprintf(url, "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=%s&radius=500&type=restaurant&key=%s", location, api_key);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_CAPATH, "/usr/ssl/certs/crt");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &places);



        result = curl_easy_perform(curl);

        if (result != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

        }



        pl1 = json_tokener_parse(places.memory);
        json_object_object_get_ex(pl1, "results", &pl2);
        len = json_object_array_length(pl2);

        system("say Here are some restaurants in the area");
        printf("Here are some restaurants in the area\n\n");
        for (i = 0; i < len && i <= 7; i++) {
            idx = json_object_array_get_idx(pl2, i);
            json_object_object_get_ex(idx, "name", &name);

            json_object_object_get_ex(idx, "rating", &rate);
            json_object_object_get_ex(idx, "vicinity", &vic);
            json_object_object_get_ex(idx, "opening_hours", &hrs);
            json_object_object_get_ex(hrs, "open_now", &open);
            json_object_object_get_ex(idx, "price_level", &price);

            //------------------- Code to display output in tables---------------------------------------
            head_length = strlen("Restaurant Name:") + strlen(json_object_get_string(vic)) + 40;

            for (j = 0; j < head_length; j++)
                printf("-");


            printf("\n| ");
            printf("Restaurant Name:");
            length = strlen("Restaurant Name:");
            for (j = length; j <= 40; j++)
                printf(" ");
            printf("|");

            printf(" %s", json_object_get_string(name));
            length = length + (40 - length) + strlen(json_object_get_string(name));
            for (j = length; j < head_length - 4; j++)
                printf(" ");

            printf("|\n");

            for (j = 0; j < head_length; j++)
                printf("-");

            printf("\n| ");
            printf("Address:");
            length = strlen("Address:");
            for (j = length; j <= 40; j++)
                printf(" ");
            printf("|");

            printf(" %s", json_object_get_string(vic));
            length = length + (40 - length) + strlen(json_object_get_string(vic));
            for (j = length; j < head_length - 4; j++)
                printf(" ");
            printf("|\n");
            for (j = 0; j < head_length; j++)
                printf("-");

            printf("\n| ");

            if (json_object_get_double(rate) > 0.0) {
                printf("Rating:");
                length = strlen("Rating:");
                for (j = length; j <= 40; j++)
                    printf(" ");
                printf("|");
                printf(" %.1f", json_object_get_double(rate));
                length = length + (40 - length) + 3;
                for (j = length; j < head_length - 4; j++)
                    printf(" ");

                printf("|\n");
                for (j = 0; j < head_length; j++)
                    printf("-");

                printf("\n| ");

            }
            if (json_object_get_double(price) > 0.0) {
                printf("Price Rating:");
                length = strlen("Price Rating:");
                for (j = length; j <= 40; j++)
                    printf(" ");
                printf("|");
                printf(" %.1f", json_object_get_double(rate));
                length = length + (40 - length) + 3;
                for (j = length; j < head_length - 4; j++)
                    printf(" ");

                printf("|\n");
                for (j = 0; j < head_length; j++)
                    printf("-");

                printf("\n| ");
            }
            if (json_object_get_boolean(open)) {
                printf("open now");
                length = strlen("Open now");
                for (j = length; j < head_length - 1; j++)
                    printf(" ");
                printf("|\n");
            } else {
                printf("closed now");
                length = strlen("Closed now");
                for (j = length; j < head_length - 1; j++)
                    printf(" ");
                printf("|\n");
            }
            for (j = 0; j < head_length; j++)
                printf("-");
            printf("\n\n");

        }


        free(places.memory);
        free(geo.memory);
        free(url);
        free(encoded_address);
        curl_easy_cleanup(curl);

    }


    return 0;

}

int show_weather(char* weather) {
    CURL *curl_weather = NULL;
    CURLcode result_weather;
    curl_weather = curl_easy_init();
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl_weather, CURLOPT_URL, weather);
    curl_easy_setopt(curl_weather, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl_weather, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl_weather, CURLOPT_USERAGENT, "curl");
    curl_easy_setopt(curl_weather, CURLOPT_WRITEFUNCTION, &WriteFunct);
    curl_easy_setopt(curl_weather, CURLOPT_WRITEDATA, (void *) &s);
    result_weather = curl_easy_perform(curl_weather);
    return 0;
}

int max(int v1, int v2){
    if(v1 > v2) return v1;
    else return v2; 
}

#endif /* FUNCTIONS_C */

