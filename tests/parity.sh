#!/bin/sh
# parity.sh — prove ft_ping matches the reference inetutils ping byte-for-byte
# (except the RTT line + reverse-DNS line, per the subject) and never leaks or
# crashes. Run as root: the raw ICMP socket needs CAP_NET_RAW.
#   sudo sh tests/parity.sh [host]
set -u
unset CDPATH 2>/dev/null || true

HOST="${1:-127.0.0.1}"
ROOT="$(cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$ROOT/ft_ping"
REF="$(command -v ping)"
PASS=0
FAIL=0

# Strip the bits the subject exempts: RTT value and the whole round-trip line.
normalize() {
	sed -E -e 's/time=[0-9.]+ ms/time=/' -e '/^round-trip /d' \
		-e '/^rtt /d'
}

check() {
	if [ "$2" = "$3" ]; then
		printf 'PASS  %s\n' "$1"
		PASS=$((PASS + 1))
	else
		printf 'FAIL  %s\n' "$1"
		printf '  --- reference ---\n%s\n  --- ft_ping ---\n%s\n' "$2" "$3"
		FAIL=$((FAIL + 1))
	fi
}

parity_count() {
	a="$($REF -c "$1" -i 0.2 "$HOST" 2>&1 | normalize)"
	b="$($BIN -c "$1" -i 0.2 "$HOST" 2>&1 | normalize)"
	check "parity -c $1 $HOST" "$a" "$b"
}

parity_size() {
	a="$($REF -c 2 -i 0.2 -s "$1" "$HOST" 2>&1 | normalize)"
	b="$($BIN -c 2 -i 0.2 -s "$1" "$HOST" 2>&1 | normalize)"
	check "parity -s $1 $HOST" "$a" "$b"
}

flood_smoke() {
	out="$($BIN -f -c 200 "$HOST" 2>&1 | tr -d '\b.')"
	if printf '%s' "$out" | grep -q '200 packets transmitted, 200 packets'; then
		check "flood -f 200" "ok" "ok"
	else
		check "flood -f 200" "ok" "$out"
	fi
}

run_valgrind() {
	# valgrind cannot exec a setcap'd binary, so run sudo valgrind on an
	# uncapped copy (plain cp drops file caps); root then grants the raw socket.
	command -v valgrind >/dev/null 2>&1 || return 0
	cp "$BIN" "$ROOT/.ftping_vg"
	if sudo valgrind --leak-check=full --error-exitcode=42 --quiet \
		"$ROOT/.ftping_vg" -c 3 -i 0.2 "$HOST" >/dev/null 2>"$ROOT/.vg"; then
		check "valgrind clean" "ok" "ok"
	else
		check "valgrind clean" "ok" "$(cat "$ROOT/.vg")"
	fi
	rm -f "$ROOT/.vg" "$ROOT/.ftping_vg"
}

run_sigint() {
	"$BIN" -i 0.2 "$HOST" >"$ROOT/.si" 2>&1 &
	pid=$!
	sleep 1
	kill -INT "$pid" 2>/dev/null
	wait "$pid" 2>/dev/null
	if grep -q 'packets transmitted' "$ROOT/.si"; then
		check "SIGINT prints stats" "ok" "ok"
	else
		check "SIGINT prints stats" "ok" "$(cat "$ROOT/.si")"
	fi
	rm -f "$ROOT/.si"
}

[ -x "$BIN" ] || { printf 'build first: make\n' >&2; exit 1; }
parity_count 1
parity_count 3
parity_size 16
parity_size 100
flood_smoke
run_valgrind
run_sigint
printf '\n%d passed, %d failed\n' "$PASS" "$FAIL"
[ "$FAIL" -eq 0 ]
