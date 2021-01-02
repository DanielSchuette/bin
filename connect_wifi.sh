#!/bin/sh
sudo killall dhcpcd
sudo ip link set down wlan0 # might be another interface
sudo wifi-menu
