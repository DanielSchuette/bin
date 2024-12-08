#!/bin/sh
# The following SSH tunnel might not always be correctly configured, sometimes
# CHEOPS provides different instructions regarding ports or node names.
PORT="$1"
ssh -o ProxyJump=dialog.rrz.uni-koeln.de -vnNT -L "$PORT":cheops11801:"$PORT" dschuet7@cheops1.rrz.uni-koeln.de
