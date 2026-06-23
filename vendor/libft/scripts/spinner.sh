#!/bin/bash
trap "exit 0" TERM INT

OBJ_DIR="$1"
TOTAL="$2"

syms=(⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏)
i=0

while true; do
	count=$(find "$OBJ_DIR" -name "*.o" 2>/dev/null | wc -l)
	sym=${syms[i % ${#syms[@]}]}
	printf "\r\033[96m%s\033[2m Compiling: %d/%d files\033[0m" "$sym" "$count" "$TOTAL"
	i=$((i+1))
	sleep 0.1
done