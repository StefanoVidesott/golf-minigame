#!/bin/bash

# ====== STYLE ======
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

function _echo {
    echo -en "$@"
}

# ====== SETUP ======
_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export PATH="$_DIR:$PATH"

# ====== BANNER ======
_echo "${NL}${COL_LCYN}${RVON}${BOLD} SV ENGINE ENVIRONMENT ${NORM}${COL_LYEL} by Stefano Videsott${NORM}${COL_DFLT}${NL2}"
_echo "${SYMB_CHECK} Environment loaded${NL}"
_echo " use '${BOLD}svdev <command>${NORM}' to work with the engine${NL2}"

# ==== AUTOCOMPLETE ====
_svdev_completions() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    local cmds="build run encode clean"
    COMPREPLY=( $(compgen -W "${cmds}" -- "$cur") )
}
complete -F _svdev_completions svdev
