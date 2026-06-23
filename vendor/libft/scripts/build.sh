#!/bin/bash

cleanup() {
    # Kill all sleep processes associated with spinners
    pkill -9 -P $$ 2>/dev/null
    pkill -9 -f "sleep 0.1" 2>/dev/null
    pkill -9 -f "spinner" 2>/dev/null
    
    # Kill PIDs from file
    if [ -f "build/obj/.spinner_pids" ]; then
        while read pid; do 
            kill -9 $pid 2>/dev/null
            kill -9 $(pgrep -P $pid) 2>/dev/null
        done < "build/obj/.spinner_pids"
        rm -f "build/obj/.spinner_pids"
    fi
    
    # Nuclear option: kill all background jobs
    jobs -p | xargs -r kill -9 2>/dev/null
    
    printf "\r\033[K"
}

trap cleanup INT TERM EXIT

make "$@"
EXIT_CODE=$?

cleanup
exit $EXIT_CODE