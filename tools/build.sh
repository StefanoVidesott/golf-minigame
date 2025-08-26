#!/bin/bash
set -e

# ==== PATH & FUNCS ====
_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source "${_DIR}/funcs.sh"

# ==== INFO ====
E_NAME="SV ENGINE"
CREDITS="by ${BOLD}Stefano Videsott${NORM}"

# ==== FLAGS ====
VERBOSE=false
SKIP_RUN=false
ONLY_ENCODE=false
RUN_ONLY=false

function usage {
    echo -e "${BOLD}Usage:${NORM} $0 [options]"
    echo
    echo "Options:"
    echo "  -v, --verbose     Show detailed logs (cmake + encoding)"
    echo "  -e, --encode      Only encode resources (skip build & run)"
    echo "  -s, --skip-run    Build + encode, but do not run the app"
    echo "  -r, --run-only    Skip build & encode, only run the app"
    echo "  -h, --help        Show this help message"
    echo
}

# ==== PARSE ARGS ====
while [[ $# -gt 0 ]]; do
    case "$1" in
        -v|--verbose) VERBOSE=true ;;
        -s|--skip-run) SKIP_RUN=true ;;
        -e|--encode) ONLY_ENCODE=true ;;
        -r|--run-only) RUN_ONLY=true ;;
        -h|--help) usage; exit 0 ;;
        *) echo "Unknown option: $1"; usage; exit 1 ;;
    esac
    shift
done

# ==== LOGGING HELPERS ====
function title {
    _echo "${NL}${COL_LMAG}${RVON}${BOLD} $1 ${NORM}${COL_DFLT}"
}

function step {
    _echo " ${BOLD}${COL_LGRN}$1${NORM}${COL_DFLT}${NL}"
}

# ==== MAIN ====
title "$E_NAME"
_echo "${COL_LYEL} ${CREDITS}${COL_DFLT}${NL2}"

# --- build ---
if [ "$ONLY_ENCODE" = false ] && [ "$RUN_ONLY" = false ]; then
    step "BUILDING PROJECT"
    if [ "$VERBOSE" = true ]; then
        cmake -B build -DCMAKE_VERBOSE_MAKEFILE=ON
        cmake --build build -- VERBOSE=1
    else
        cmake -B build -DCMAKE_VERBOSE_MAKEFILE=OFF
        cmake --build build
    fi
    _echo "${NL}"
fi

# --- encode resources ---
if [ "$RUN_ONLY" = false ]; then
    step "ENCODING RESOURCES"
    if [ "$VERBOSE" = true ]; then
        . "${_DIR}/encode_resources.sh" --verbose
    else
        . "${_DIR}/encode_resources.sh"
    fi
    _echo "${NL}"
    step "DONE"
fi

# --- run ---
if [ "$SKIP_RUN" = false ]; then
    step "STARTING APPLICATION"
    _echo "${COL_LCYN}"
    cd "${_DIR}/../build/bin"
    ./golf-minigame
    _echo "${COL_DFLT}${NL}"
    step "APPLICATION TERMINATED"
fi
