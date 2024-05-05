Toby's DWM config
=================

Enjoy a small window manager with actual sane defaults.

Added features
--------------
Base:
    fibonacci layout
    bottom stack layout
    attach window in 6 different ways
    actual full screen
    status monitor on all screens
    show the current selected monitor even with no windows
    self restart
    auto start programs
    get colors from xresources
    push window up or down
    window gaps
Autostart:
    picom
    xbanish
    xwallpaper --zoom ~/.config/wallpaper
    xrdb -set ~/Xresources
External:
    mod + e : Emoji picker script
    mod + shift + b : background picker
    

Default Programs
------------------

Kitty, dmenu, picom, xwallpaper, xbanish, xrdb 

Read the original README below


dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.
You also need a c compiler such as gcc


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local/bin/ namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
