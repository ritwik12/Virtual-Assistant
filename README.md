# Virtual-Assistant
A virtual assistant is a software agent that can perform tasks or services for an individual.The term
”chatbot” is also used to refer to virtual assistants.

Virtual assistants use Artificial Intelligence to match user text input to executable commands.
It can provide a wide variety of services, These includes:

<ul>
<li>Weather forecast of any place</li> 
<li>Play multimedia files such as audio songs and video songs</li> 
<li>Open Applications such as Web browsers, Media players(like vlc), text editors, etc</li>
<li>Open directories in linux, Date and time</li> 
<li>Search anything on Google</li> 
<li>Open websites of user’s choice</li>
<li>Search anything on Youtube</li>
<li>Open Calendar of any year</li>
<li>Find Restaurants in an area</li>  
</ul>

![screenshot from 2017-11-04 23 13 18](https://user-images.githubusercontent.com/20038775/32407915-c80e1a72-c1b5-11e7-83f4-efafcf7d3c85.png)

# How it all works?

We are reading user’s sentence and passing it through our Natural Language Processing code i.e “ Simplified Multinomial Naive Bayes Algorithm “. NLP code processes the sentence and redirects it to the action that should be performed based on the meaning of the sentence.

The functionality is executed such as 
<ul>
<li>A media file (such as audio and media files) is played.
<li>Weather forecast is shown after the user enters the location.
<li>Calendar is shown of the desired year.
<li>Youtube search is performed for the desired content.
<li>Google search is performed for whatever the user wants to.
<li>Restaurants in the given area/locality are shown.  
</ul>

**If the virtual assistant have no idea about the user’s sentence, it will simply search that sentence on Google.**

# Artificial Intelligence

**Simplified Multinomial Naive Bayes Algorithm**

Given a set of sentences, each belonging to a class, and a new input sentence, we can count the occurrence of each word in each class, account for its commonality and assign each class a score. Factoring for commonality is important: matching the word “it” is considerably less meaningful than a match for the word “cheese”. The class with the highest score is the one most likely to belong to the input sentence. This is a slight oversimplification as words need to be reduced to their stems, but you get the basic idea.

A sample training set:


![ai sample](https://user-images.githubusercontent.com/20038775/32407882-50b9dc54-c1b5-11e7-9b61-5617e1c849ba.png)

Let’s classify a few sample input sentences:

![screenshot from 2017-11-04 23 08 21](https://user-images.githubusercontent.com/20038775/32407872-1df10b26-c1b5-11e7-988b-d6ec965761f7.png)

Notice that the classification for “What’s it like outside” found a term in another class but the term similarities to the desired class produced a higher score. By using an equation we are looking for word matches given some sample sentences for each class, and we avoid having to identify every pattern.

# Setup

This program uses <b>GNUstep speech engine</b> for the purpose of text to speech.
To use this feature few commands are needed:

say converts text to audible speech using the GNUstep speech engine.

```
$ sudo apt-get install gnustep-gui-runtime
$ say "hello"
```
Firefox is needed to perform browser tasks such as opening google and youtube.

```
$ sudo apt-get install firefox
```
In addition to this, following commands are needed to install the necessary packages.

```
$ sudo apt-get install libcurl4-openssl-dev

$ sudo apt-get install libjson0 libjson0-dev

```
# Restaurant
  Virtual Assistant can find restaurants in an area.
  
  ![restaurant](https://user-images.githubusercontent.com/22569462/32977453-8dfb20fc-cc53-11e7-91aa-ff43bed7173b.png)



# Weather

This feature requires curl.To use this feature you need to first install curl as follows-

```
$ sudo apt-get install curl
```

![weather](https://user-images.githubusercontent.com/20038775/32407551-c93bc9b2-c1b0-11e7-8daf-51ee917136c6.PNG)

# Media

Virtual assistant can play any audio or video files of your choice.
For playing media files vlc is needed.
Get it here 
```
$ sudo apt-get install vlc
```
```
Please configure your working directory location before using this feature in config file (value of HOME_DIR)
```
![video](https://user-images.githubusercontent.com/20038775/32407550-c8dfc766-c1b0-11e7-8f29-65233b7d1861.PNG)

# Youtube Search

Virtual assistant can search anything on youtube.
```
search youtube for Artificial Intelligence
```
This will show all the videos on youtube related to Artificial Intelligence.
Artificial Intelligence is an example here, you can use anything you want to search.

![youtube](https://user-images.githubusercontent.com/20038775/32407552-c986ec44-c1b0-11e7-9be2-d3a80426207c.PNG)

# Google Search

Virtual assistant can search anything on Google.

![googlesearch](https://user-images.githubusercontent.com/20038775/32407547-c85a9352-c1b0-11e7-9a48-32bd2c94a332.PNG)

# Calendar

Virtual assistant can show calendar of any year.

```
open calendar
```

![calendar](https://user-images.githubusercontent.com/20038775/32407545-c8026a06-c1b0-11e7-81b5-31a089fd5b65.PNG)

# Help

Don't know how to use?
Here use help command

```
help
```

![help](https://user-images.githubusercontent.com/20038775/32407549-c89d5cd2-c1b0-11e7-867a-d5032922315a.PNG)

# Contributing Guide
<ul>
<li>This repository is strictly based on C language. No contributions other than C will be accepted.</li>
<li>When contributing to this repository, please first inform or discuss the change(s) you wish to make via an issue. This helps in letting   others know what you're working on.</li>
<li>Before you push your changes to GitHub, make sure that your code compiles and runs without any errors or warnings.</li>
<li>New features are always welcome and as of now this project is under development.</li>
</ul>


# License

ritwik12/Virtual-Assistant is licensed under the
GNU General Public License v3.0

Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.



