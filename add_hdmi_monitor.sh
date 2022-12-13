#!/bin/sh
resolution='2560x1440' # discover via `xrandr'
primary='eDP1'
secondary='HDMI2'
xrandr --output "$primary" --primary --output "$secondary" --mode "$resolution" --right-of "$primary" --auto
