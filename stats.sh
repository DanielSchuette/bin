#!/bin/sh
HISTFILE=~/.bash_history
set -o history
stats=$(history | awk '{ CMD[$2]++; count++; }END { for (a in CMD) print CMD[a] " " CMD[a]/count*100 "% " a; }' | grep -v "./" | column -c 3 -s " " -t | sort -nr | nl |  head -n 20)
echo "$stats"