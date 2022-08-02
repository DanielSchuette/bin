#!/bin/sh
# The SSH password is the one that you use with the University's webmailer.
DEFAULT_USER=dschuet7
CLUSTER_ADDR=cheops.rrz.uni-koeln.de

USER="$DEFAULT_USER"
if [ -n "$1" ]; then
    USER="$1"
fi

printf "Connecting user %s to %s\n" "$USER" "$CLUSTER_ADDR"
ssh -Y "${USER}@${CLUSTER_ADDR}"
