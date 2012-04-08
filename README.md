This is an implementation of [Conway's Game of Life][1] for the [Arduino][6].

# Introduction

The Nintendo Nunchuk controller is used to configure the initial state and to
start/stop the creation of next generations. The [TVout library][3] is used to
display the two-dimensional Life grid on a TV screen.

This project was inspired by [Make Your Own Video Game System][4], an article
found in the August 2011 issue of the [PragPub magazines][5].

# How everything is wired together

The following picture shows how everything is wired together:

![][7]

# Makefile

The Arduino IDE is nice, but the text editor it provides is not what I am used
to. I rather use [Vim][2] from a terminal window. Now, to edit, verify, compile
and upload a 'sketch', I had to switch back and forth between the terminal
window and the Arduino IDE. This is less than satisfactory. Therefore, I
created a `Makefile`. Now I enter `make` from the command line and the `.hex`
file will be built and uploaded to the Arduino.

Note that it was not my intention to make the `Makefile` generic for all kinds
of environments. It is fine when it just works for me:

* Mac OS X Lion
* Arduino 1.0 software installed in /Applications/Arduino.app
* Arduino Uno

[1]: http://www.conwaylife.com/
[2]: http://www.vim.org/
[3]: http://code.google.com/p/arduino-tvout/
[4]: http://pragprog.com/magazines/2011-08/make-your-own-video-game-system
[5]: http://pragprog.com/magazines
[6]: http://arduino.cc/
[7]: http://gbouknecht.github.com/arduino-conway-life/images/wired-together.jpg "How everything is wired together"
