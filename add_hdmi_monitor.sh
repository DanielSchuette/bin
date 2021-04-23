#!/bin/sh
primary='eDP1'
secondary='HDMI2'
xrandr --output "$primary" --primary --auto --output "$secondary" --left-of "$primary" --auto
