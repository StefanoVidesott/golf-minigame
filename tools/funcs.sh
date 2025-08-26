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

SYMB_CHECK="\xE2\x9C\x94"
SYMB_CROSS="\xE2\x9D\x8C"

function _echo {
    echo -en "$@"
}
