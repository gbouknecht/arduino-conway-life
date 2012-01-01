This is going to be an implementation of [Conway's Game of Life][1] for the
[Arduino][6].

# Introduction

The idea is to use a Nintendo Nunchuk controller to configure the initial state
and the [TVout library][3] to display the two-dimensional Life grid on a TV
screen.

This project was inspired by [Make Your Own Video Game System][4], an article
found in the August 2011 issue of the [PragPub magazines][5].

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
