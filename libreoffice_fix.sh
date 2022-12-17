#!/bin/sh
# Because the long-standing bug that occurs when using LO in conjunction with
# GTK3 (and probably some compositor, but the internet isn't sure about that),
# we just force libreoffice to use another UI toolkit that works properly.
SAL_USE_VCLPLUGIN=gen soffice "$1"
