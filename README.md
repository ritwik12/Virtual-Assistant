# Virtual-Assistant
A virtual assistant is a software agent that can perform tasks or services for an individual. The term
”chatbot” is also used to refer to virtual assistants. Remember the time, when you were watching Iron Man and wondered to yourself, how cool it would be if you had your own J.A.R.V.I.S? Well, It's time to make that dream into a reality.

Artificial intelligence is the next gen. Imagine how cool it would be if you had your friends over at your house, and all of a sudden you go, "Hey JARVIS, show me some memes.", and JARVIS goes "Sure, sir. Here are the latest Italian memes.", whilst showing you the funniest Italian memes. Cool right?

Well, this is not exactly a chatbot nor JARVIS but to understand it better it is good to know about both.

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
<li>Send emails using your Gmail account</li>  
<li>Arithmetic Calculations</li>  
</ul>

![screenshot from 2017-11-04 23 13 18](https://user-images.githubusercontent.com/20038775/32407915-c80e1a72-c1b5-11e7-83f4-efafcf7d3c85.png)

# How it all works?

The user's sentence is read and passed through our Natural Language Processing (NLP) code for processing. After the sentence is processed, it's redirected to the action to be performed based on the meaning of the sentence. Our NLP code uses a simplified version of the Multinomial Naive Bayes Algorithm.

The following actions can be performed:
<ul>
<li>Play audio and media files
<li>Display weather forecasts based on specified location
<li>Display the calendar of a specified year
<li>Perform YouTube video searches
<li>Perform Google searches
<li>Display restaurant recommendations
<li>Send emails
</ul>

**If the virtual assistant does not understand the user’s sentence, a Google search performed.**

# Artificial Intelligence

**Simplified Multinomial Naive Bayes Algorithm**

Each classification contains a set of sentences that inputs are matched to. Scores are assigned based on the occurrence of words of an input sentence for each of the classifications. Scores measure the commonality of an input sentence to a classification. The commonality between words and the classifications are important. For example, matching the word “it” is considerably less meaningful than a match for the word “cheese”. The input sentence is assigned the classification of the highest score. This is a simplification as words need to be reduced to their stems.

A sample training set:


![ai sample](https://user-images.githubusercontent.com/20038775/32407882-50b9dc54-c1b5-11e7-9b61-5617e1c849ba.png)

Let’s classify a few sample input sentences:

![screenshot from 2017-11-04 23 08 21](https://user-images.githubusercontent.com/20038775/32407872-1df10b26-c1b5-11e7-988b-d6ec965761f7.png)

Notice that the classification for “What’s it like outside” found a term in another class but the term similarities to the desired class produced a higher score. By using an equation we are looking for word matches given some sample sentences for each class, and we avoid having to identify every pattern.

# Setup

### For Ubuntu (Debian-based Linux)
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
$ sudo apt-get install libjson-c-dev
$ sudo apt-get install libssl0.9.8

```
### For Fedora (RHEL-based Linux)

This program uses <b>Espeak</b> for the purpose of text to speech.

espeak converts text to audible speech.

```
$ espeak "hello"
```
Firefox is needed to perform browser tasks such as opening google and youtube.

```
$ sudo yum install firefox
```
In addition to this, following commands are needed to install the necessary packages.

```
$ sudo yum install libcurl libcurl-devel
$ sudo yum install json-c json-c-devel
$ sudo dnf install openssl
$ sudo dnf install openssl-devel

```

### For macOS

GNUstep can be cross-compiled from Linux to run on Apple's macOS, (See: http://wiki.gnustep.org/index.php/Cross_Compiling).

```
brew install curl
brew install json-c
brew install openssl
```

Compile
```
gcc main.c src/init_config.c $(pkg-config --libs --cflags libcurl) -lssl -lcrypto -ljson-c -std=gnu11

```
# Restaurant
  Virtual Assistant can find restaurants in an area.

![restaurants](https://user-images.githubusercontent.com/20038775/33029445-9b05b482-ce3e-11e7-8ed4-5782fe468530.png)



# Weather

This feature requires curl. To use this feature you need to first install curl as follows-

```
$ sudo apt-get install curl
```
Or
```
$ sudo yum install curl
```
![weather](https://user-images.githubusercontent.com/20038775/37968392-9af5446a-31eb-11e8-8008-14b5e935571d.png)

# Media

Virtual assistant can play any audio or video files of your choice.
For playing media files vlc is needed.
Get it here
```
$ sudo apt-get install vlc
```
Or
```
$ sudo dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
$ sudo dnf install vlc
```
Or
```
sudo rpm -Uvh http://li.nux.ro/download/nux/dextop/el7/x86_64/nux-dextop-release-0-5.el7.nux.noarch.rpm
sudo yum install vlc
```
```
Please configure your working directory location before using this feature in config file (value of HOME_DIR)
```
![media](https://user-images.githubusercontent.com/20038775/37968146-fbd9a416-31ea-11e8-8215-9a7ca5259ec3.png)

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

![gsearch](https://user-images.githubusercontent.com/20038775/37968140-fa07a8d6-31ea-11e8-9ad2-97fe5527bc25.png)

# Calendar

Virtual assistant can show calendar of any year.

```
open calendar
```
![calendar](https://user-images.githubusercontent.com/20038775/33027865-4b6d5f28-ce3a-11e7-8376-ac16e9da8606.png)
# Emails

In order to send emails using Virtual-Assistant, you need to allow access from less secure apps on your gmail account.
Open your gmail account on any browser, click on profile pick and then `Google account`. In the tab `Security` you have to activate the parameter `Allow access from less secure apps`.
<p>
Access the gmail service using `emails`. You will be prompted for your email address and email password. Once you have input those, your email will be saved and you can choose what actions you would like to use. Currently you can only choose to write and send emails. Once you are done writing your message use `finish` and the email will save and send.



![56217042-d4841c00-6062-11e9-9d98-71f7bda8a1d4](https://user-images.githubusercontent.com/20038775/56322188-fde99880-6185-11e9-932b-d2f4a7115cd8.png)
# Arithmetic Calculations
Virtual assistant can perform calculations for you, use `math` to calculate expressions in the command line using GNUs command line calculator. When you're done, just use `quit`. 

Use `man bc` on terminal (outside Virtual Assistant) to learn about the command line calculator capabilities.

For long arithmetic expressions, the assistant can bring up the calculator for you by using `calculator`.
![math_demo](https://user-images.githubusercontent.com/57401083/79321003-5d05f880-7f13-11ea-99db-8ec7e8c2343a.png)

  
# Help

Don't know how to use?
Here use help command

```
help
```
![help](https://user-images.githubusercontent.com/20038775/33027895-5eb1a80a-ce3a-11e7-9410-dd1c0b2d21a1.png)

# Contributing Guide
<ul>
<li>This repository is strictly based on C language. No contributions other than C will be accepted.</li>
<li>When contributing to this repository, please first inform or discuss the change(s) you wish to make via an issue. This helps in letting   others know what you're working on.</li>
<li>Before you push your changes to GitHub, make sure that your code compiles and runs without any errors or warnings.</li>
<li>New features are always welcome.</li>
</ul>

# Want to ask something?
Please ask on [FAQ](https://github.com/ritwik12/Virtual-Assistant/issues/41) or mail me at [ritwik.1204@gmail.com](ritwik.1204@gmail.com)

# License

ritwik12/Virtual-Assistant is licensed under the
GNU General Public License v3.0

Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. Rebranding or renaming this software misguides users about the origin of the original software and should not be done.

# Credits
This project is developed with contributions by [Riya](https://github.com/riya-17)
