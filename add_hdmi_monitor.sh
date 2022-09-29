#!/bin/sh
primary='eDP1'
secondary='HDMI2'
xrandr --output "$primary" --primary --output "$secondary" --mode 1920x1200 --right-of "$primary" --auto
