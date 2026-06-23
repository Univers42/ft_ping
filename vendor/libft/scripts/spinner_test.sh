#!/bin/bash

syms=(⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏)
end_time=$((SECONDS + 5))
i=0

while [ $SECONDS -lt $end_time ]; do
    sym=${syms[i % ${#syms[@]}]}
    printf "\r%s Spinning..." "$sym"
    ((i++))
    sleep 0.2
done

printf "\nDone!\n"
