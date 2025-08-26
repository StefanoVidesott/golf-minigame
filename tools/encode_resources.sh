#!/bin/bash
set -e

VERBOSE=false
while [[ $# -gt 0 ]]; do
    case "$1" in
        -v|--verbose) VERBOSE=true ;;
    esac
    shift
done

OUTDIR="./build/bin/res"
mkdir -p "$OUTDIR"

find ./res ./src/engine/res -type f ! -name "*.enc" | while read -r file; do
    relpath=$(realpath --relative-to="$(pwd)" "$file")
    encoded=$(echo -n "$relpath" | base64 | tr -d '\n')
    outfile="$OUTDIR/$encoded"

    if [ "$VERBOSE" = true ]; then
        echo "Encoding $relpath -> $outfile"
    fi

    base64 "$file" > "$outfile"
done
