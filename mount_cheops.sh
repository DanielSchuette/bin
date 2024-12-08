#!/bin/sh
sudo sshfs -o allow_other,ProxyJump=dschuet7@dialog.rrz.uni-koeln.de,debug,ssh_command='ssh -vvv' dschuet7@cheops.rrz.uni-koeln.de:/ /mnt/cheops/
