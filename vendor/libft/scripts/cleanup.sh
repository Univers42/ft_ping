#!/bin/bash

SPIN_FILE="$1"

if [ -f "$SPIN_FILE" ]; then
	pid=$(cat "$SPIN_FILE" 2>/dev/null)
	if [ -n "$pid" ]; then
		kill -TERM $pid 2>/dev/null || true
		wait $pid 2>/dev/null || true
	fi
	rm -f "$SPIN_FILE"
	printf "\r\033[K"
fi