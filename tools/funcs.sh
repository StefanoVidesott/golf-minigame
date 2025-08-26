#!/bin/bash

NL="\n"; NL2="${NL}${NL}"
ESC="\033"

NORM="${ESC}[0m"
BOLD="${ESC}[1m"
RVON="${ESC}[7m"
RVOFF="${ESC}[27m"

COL_DFLT="${ESC}[39m"
COL_LGRN="${ESC}[92m"
COL_LYEL="${ESC}[93m"
COL_LMAG="${ESC}[95m"
COL_LCYN="${ESC}[96m"

function _echo {
    echo -en "$@"
}
