#!/bin/sh
# On Arch, `dig' requires prior installation of extra/bind.
echo 'IPv4:'
dig +short txt ch whoami.cloudflare @1.0.0.1
echo 'IPv6:'
dig -6 TXT +short o-o.myaddr.l.google.com @ns1.google.com
