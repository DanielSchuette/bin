#!/bin/sh
# Create a new tmux session with a bunch of windows.
SESSIONNAME='dev0'
LABDIR="$HOME"/lab
CODEDIR="$LABDIR"/code/project-ponder-lung/project-ponder-lung/daniel

tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? != 0 ]; then
    tmux new-session -d -s $SESSIONNAME -n home
    tmux new-window -t $SESSIONNAME -n lab -c "$LABDIR"
    tmux new-window -t $SESSIONNAME -n code -c "$CODEDIR"
fi

tmux attach -t $SESSIONNAME
