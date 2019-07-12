#!/bin/sh
# Open surf without an annoying top bar.
nohup surf >/dev/null 2>/dev/null &
sleep 2 # annoying but necessary
pid=$(ps aux | awk '{ print $2,$11; }' | sed -n 's/surf$/surf/p' | awk '{ print $1; }')
wid=$(wmctrl -lp | grep "$pid" | awk '{ print $1; }')
xprop -id "$wid" -f _MOTIF_WM_HINTS 32c -set _MOTIF_WM_HINTS "0x2, 0x0, 0x0, 0x0, 0x0"
