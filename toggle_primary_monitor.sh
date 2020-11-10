#!/bin/sh
# Toggle back to the primary monitor of this device
# (might not work, check which one's actually the
# primary device via `` $ xrandr '').
primary='eDP1'
xrandr --output "$primary" --primary
