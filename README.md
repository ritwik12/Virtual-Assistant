# Virtual-Assistant
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-17-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->
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

### Compile

To compile with make:
```
sudo make install
```

then execute using `virtual_assistant` from any location

To remove all build files
```
make clean
```

To remove the changes
```
sudo make uninstall
```

To compile with gcc:
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

Access the gmail service using `emails`. You will be prompted for your email address and email password. Once you have input those, your email will be saved and you can choose what actions you would like to use. Currently you can only choose to write and send emails. Once you are done writing your message use `finish` and the email will save and send.

![56217042-d4841c00-6062-11e9-9d98-71f7bda8a1d4](https://user-images.githubusercontent.com/20038775/56322188-fde99880-6185-11e9-932b-d2f4a7115cd8.png)

# Reminder and Schedule

You can schedule your appointments and work using Virtual-Assistant. It will remind you of the appointments you have on a particular day. You can also access your schedule for any other day by just using the correct words.

In order to add a reminder simply say `Add a reminder` or `Add an appointment` or `Make a schedule` and other things like that. Once there, just enter the required details like date, time and event description.

Every time you run the Virtual-Assistant you will receive notifications of your schedule for that day. If you wish to access schedule for any other day you can say  `my schedule` or `what's my appointments`.

![notification](https://user-images.githubusercontent.com/65824687/96662367-d0c60980-136b-11eb-9cf7-fa98ce06a411.png)

![addreminder](https://user-images.githubusercontent.com/65824687/96662418-f18e5f00-136b-11eb-9f77-3ca879d5002b.png)

![schedule](https://user-images.githubusercontent.com/65824687/96662448-02d76b80-136c-11eb-9a31-32bea79637e7.png)


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
This project intitiated with contributions by [Riya](https://github.com/riya-17) and [Ritwik](https://github.com/ritwik12).
The project is much better and improving with the help of some awesome contributors.

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://riya-17.github.io/"><img src="https://avatars2.githubusercontent.com/u/25060937?v=4" width="100px;" alt=""/><br /><sub><b>Riya</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=riya-17" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=riya-17" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/Rushikesh22"><img src="https://avatars1.githubusercontent.com/u/22569462?v=4" width="100px;" alt=""/><br /><sub><b>Rushikesh Nagle</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=Rushikesh22" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=Rushikesh22" title="Documentation">📖</a> <a href="#infra-Rushikesh22" title="Infrastructure (Hosting, Build-Tools, etc)">🚇</a></td>
    <td align="center"><a href="https://github.com/GaelleMarais"><img src="https://avatars0.githubusercontent.com/u/14167172?v=4" width="100px;" alt=""/><br /><sub><b>GaelleMarais</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=GaelleMarais" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=GaelleMarais" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/vnksnkr"><img src="https://avatars1.githubusercontent.com/u/65824687?v=4" width="100px;" alt=""/><br /><sub><b>Vinayak Sankar</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=vnksnkr" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=vnksnkr" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/mcavazotti"><img src="https://avatars2.githubusercontent.com/u/27312683?v=4" width="100px;" alt=""/><br /><sub><b>Matheus</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=mcavazotti" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/omerdagan84"><img src="https://avatars0.githubusercontent.com/u/8275697?v=4" width="100px;" alt=""/><br /><sub><b>Omer Dagan</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=omerdagan84" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/jackycodes"><img src="https://avatars0.githubusercontent.com/u/8866892?v=4" width="100px;" alt=""/><br /><sub><b>Jacky Lui</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=jackycodes" title="Documentation">📖</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/pavan-pan"><img src="https://avatars3.githubusercontent.com/u/13458012?v=4" width="100px;" alt=""/><br /><sub><b>pavan-pan</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=pavan-pan" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/hardikpnsp"><img src="https://avatars3.githubusercontent.com/u/19833489?v=4" width="100px;" alt=""/><br /><sub><b>hardikpnsp</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=hardikpnsp" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/Eldart95"><img src="https://avatars2.githubusercontent.com/u/57401083?v=4" width="100px;" alt=""/><br /><sub><b>Eldar Takach</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=Eldart95" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=Eldart95" title="Documentation">📖</a></td>
    <td align="center"><a href="http://www.royscodeventure.com"><img src="https://avatars2.githubusercontent.com/u/52980739?v=4" width="100px;" alt=""/><br /><sub><b>Roy Mattar</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=RoyMattar" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/jayadevvasudevan"><img src="https://avatars2.githubusercontent.com/u/35390314?v=4" width="100px;" alt=""/><br /><sub><b>Jayadev V</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=jayadevvasudevan" title="Documentation">📖</a></td>
    <td align="center"><a href="http://www.nummikallio.com"><img src="https://avatars1.githubusercontent.com/u/15906373?v=4" width="100px;" alt=""/><br /><sub><b>A. Nummikallio</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=aurochs-angels" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/igo4Jesus"><img src="https://avatars2.githubusercontent.com/u/37935466?v=4" width="100px;" alt=""/><br /><sub><b>igo4Jesus</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=igo4Jesus" title="Code">💻</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/speedy-software-ch"><img src="https://avatars2.githubusercontent.com/u/12483531?v=4" width="100px;" alt=""/><br /><sub><b>speedy-software-ch</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=speedy-software-ch" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/anindyasen"><img src="https://avatars2.githubusercontent.com/u/7093145?v=4" width="100px;" alt=""/><br /><sub><b>Anindya</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=anindyasen" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/LilyaMel"><img src="https://avatars1.githubusercontent.com/u/47354050?v=4" width="100px;" alt=""/><br /><sub><b>LilyaMel</b></sub></a><br /><a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=LilyaMel" title="Code">💻</a> <a href="https://github.com/ritwik12/Virtual-Assistant/commits?author=LilyaMel" title="Documentation">📖</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!
