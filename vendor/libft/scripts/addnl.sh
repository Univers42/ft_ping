#!/bin/bash

find ../ -type f \( -iname "*.c" -o -iname "*.h" \) -exec bash -c '[[ "$(tail -c 1 "$1")" != "" ]] && echo "" >> "$1"' _ {} \;
