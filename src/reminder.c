char cur_date[10];
char sc_date[10];
int notification_count=0;

//Checks if valid date is entered
int valid_date(char * date)
{
int i =0;
while(date[i]!='\0')
{
if((i==2||i==5)){
if(date[i]!=47)
return 0;
}
else if(date[i] < 48 || date[i] > 57){
return 0;
}
i++;
}
return 1;
}


//gets the events of the current day if any
int cur_schedule()
{
    int events = 0;
    struct tm * cur_time;
    event search_event;
    time_t cur_timer;
    cur_timer = time(NULL);
    cur_time = localtime( &cur_timer );
    strftime(cur_date,10,"%x", cur_time);
    FILE * fp;
    fp = fopen("/usr/bin/events.dat","r");
    if(fp == NULL)
    {
    	fp = fopen("events.dat","r");
	if(fp == NULL){
    	    printf("Error opening schedule\n");
       	    return 0;
	}
    }
    while(fread(&search_event,sizeof(event),1,fp))
    {
    	if(!strcmp(search_event.date,cur_date)){
    		events += 1;
    	}
    }
    fclose(fp);
return events;
}

//displays schedule of date passed to function
int show_schedule(char * sc_date)
{
int events;
FILE * fp;
event search_event;
fp = fopen("events.dat","r");
if(fp == NULL)
{
printf("Error opening schedule\n");
return 0;
}
while(fread(&search_event,sizeof(event),1,fp))
{
if(!strcmp(search_event.date,sc_date)){
printf("You have %s on %s at %s \n", search_event.desc,search_event.date,search_event.time);
events += 1;
}
}
fclose(fp);
if(events == 0)
printf("You have no appointments on %s\n",sc_date);
return 0; 
}


//adds new events to schedule
int add_reminder()
{
FILE *fp;
struct event cur_event,read;
printf("What is the Event?(Max 50 chars):\n");
fgets(cur_event.desc,50,stdin);
*strchr(cur_event.desc,'\n')='\0';
printf("When do you want to schedule(mm/dd/yy):\n");
fgets(cur_event.date,10,stdin);
*strchr(cur_event.date,'\n')='\0';
if(!valid_date(cur_event.date)){
printf("Please enter a valid date\n");
add_reminder();
}
printf("Time?(hh:mm):\n");
fgets(cur_event.time,6,stdin);

fp = fopen("events.dat","a");
if(fp == NULL)
{
printf("Error opening Schedule\n");
return 0;
}
fwrite(&cur_event,sizeof(struct event),1,fp);
fclose(fp);
printf("Scheduled %s on %s at %s\n",cur_event.desc,cur_event.date,cur_event.time);
return 0;
}


//reminds the user of daily schedule whenever program run
int daily_reminder()
{
int daily_events;
char response;
daily_events = cur_schedule();
if(daily_events)
{
printf("\nYou have %d appointments today.Would you like to see them?(Y/n)",daily_events);
response = getchar();
getchar();
if(response == 'y' || response == 'Y'){
show_schedule(cur_date);
}	
notification_count += 1;
return 0;
}
}

//gets schedule of the date mentioned by user
int schedule()
{
getchar();
daily_reminder();
printf("Enter the schedule date.(mm/dd/yy):\n");
fgets(sc_date,10,stdin);
*strchr(sc_date,'\n')='\0';
show_schedule(sc_date);
}


