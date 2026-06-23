#!/usr/bin/env bash
# Benchmark libft allocation-bound workloads: libc vs ft_malloc, side by side.
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

FT_LIB="build/test/ft/lib/libft.a"
LIBC_LIB="build/test/libc/lib/libft.a"
FTM_INC="srcs/memory/ft_malloc/include"
BIN_DIR="build/bin/test"
SRC="tests/bench/bench_libft.c"
CYN=$'\033[1;36m'; GRN=$'\033[1;32m'; RST=$'\033[0m'
mkdir -p "$BIN_DIR"

echo "${CYN}▸ building archives…${RST}"
make -s BUILD_DIR=build/test/ft   EXTRA_CFLAGS=-DXALLOC_NO_CONFIG "$FT_LIB"   || exit 3
make -s BUILD_DIR=build/test/libc FTM_SRCS= EXTRA_CFLAGS=-DXALLOC_NO_CONFIG "$LIBC_LIB" || exit 3

cc -O3 -DXALLOC_NO_CONFIG -I. -Iinclude "$SRC" "$LIBC_LIB" -lm -o "$BIN_DIR/bench_libc" || exit 4
cc -O3 -DXALLOC_NO_CONFIG -DHAVE_FT_MALLOC -I"$FTM_INC" -I. -Iinclude "$SRC" "$FT_LIB" -pthread -lm -o "$BIN_DIR/bench_ft" || exit 4

echo "${GRN}── libc ──${RST}";        "$BIN_DIR/bench_libc"
echo "${GRN}── ft_malloc ──${RST}";   "$BIN_DIR/bench_ft"
