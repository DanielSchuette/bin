#!/bin/sh
primary='eDP1'
secondary='HDMI2'
xrandr --output "$primary" --primary --auto --output "$secondary" --right-of "$primary" --auto
