#!/bin/sh
# Open the remote origin of this repository in a web browser.
printf "Opening repository at %s in browser.\n" "$(pwd)"
url=$(git remote -v | awk '{ print $2 }' | sed -n -e 's/git@//p' | sed -n -e 's/\.git//p' | sed -n -e 's/:/\//p' | sed 1q)
fox -t "$url"
