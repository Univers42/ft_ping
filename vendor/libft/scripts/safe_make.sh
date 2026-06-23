#!/bin/bash

# Cleanup function
cleanup() {
    SPIN_FILE="build/obj/.spin_state"
    if [ -f "$SPIN_FILE" ]; then
        pid=$(cat "$SPIN_FILE" 2>/dev/null)
        if [ -n "$pid" ]; then
            kill -9 $pid 2>/dev/null || true
            wait $pid 2>/dev/null || true
        fi
        rm -f "$SPIN_FILE"
        printf "\r\033[K"
    fi
    exit 130
}

# Set trap
trap cleanup INT TERM

# Run make with all arguments
make "$@"
EXIT_CODE=$?

# Normal cleanup
if [ -f "build/obj/.spin_state" ]; then
    pid=$(cat "build/obj/.spin_state" 2>/dev/null)
    [ -n "$pid" ] && kill -9 $pid 2>/dev/null || true
    wait $pid 2>/dev/null || true
    rm -f "build/obj/.spin_state"
fi

exit $EXIT_CODE