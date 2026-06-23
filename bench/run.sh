#!/bin/sh
# run.sh — benchmark ft_ping against the reference inetutils ping on loopback,
# across four metrics: footprint, startup, CPU per packet, flood throughput.
# Wall-clock at the default 1 s interval is identical by design (and required),
# so "faster" is measured only on overhead. Needs sudo (perf) and a setcap'd
# ./ft_ping; the reference ping is already setuid.
#   sh bench/run.sh
set -u
unset CDPATH 2>/dev/null || true

ROOT="$(cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$ROOT/ft_ping"
REF="$(command -v ping)"
RES="$ROOT/bench/results"
HOST=127.0.0.1

taskclock() {
	label="$1"
	reps="$2"
	shift 2
	LC_ALL=C sudo perf stat -r "$reps" -- "$@" >/dev/null 2>"$RES/$label.txt"
	awk '/task-clock/ {gsub(/,/, "", $1); print $1; exit}' "$RES/$label.txt"
}

throughput() {
	secs="$1"
	shift
	"$@" 2>/dev/null | tr -d '.\b' | awk -v s="$secs" \
		'/packets transmitted/ {printf "%.0f", $1 / s; exit}'
}

rss() {
	/usr/bin/time -v "$@" >/dev/null 2>"$RES/rss.txt"
	awk '/Maximum resident/ {print $NF; exit}' "$RES/rss.txt"
}

verdict() {
	awk -v a="$1" -v b="$2" -v m="$3" 'BEGIN {
		if (a == 0 || b == 0) { print "n/a"; exit }
		if (m == "lo") r = b / a; else r = a / b;
		if (r > 1.03) printf "ft_ping %.2fx better", r;
		else if (r < 0.97) printf "ft_ping %.2fx worse", 1 / r;
		else printf "within noise (<3%%)";
	}'
}

row() {
	printf '| %-20s | %14s | %14s | %s |\n' "$1" "$2" "$3" "$(verdict "$4" "$5" "$6")"
}

main() {
	[ -x "$BIN" ] || { printf 'build first: make\n' >&2; exit 1; }
	mkdir -p "$RES"
	fsz=$(stat -c%s "$BIN")
	rsz=$(stat -c%s "$REF")
	frss=$(rss "$BIN" -c 5 -i 0.02 "$HOST")
	rrss=$(rss "$REF" -c 5 -i 0.02 "$HOST")
	fst=$(taskclock ft_start 20 "$BIN" -c 1 "$HOST")
	rst=$(taskclock ref_start 20 "$REF" -c 1 "$HOST")
	fcpu=$(taskclock ft_cpu 5 "$BIN" -c 100 -i 0.02 "$HOST")
	rcpu=$(taskclock ref_cpu 5 "$REF" -c 100 -i 0.02 "$HOST")
	ftp=$(throughput 2 "$BIN" -f -w 2 "$HOST")
	rtp=$(throughput 2 "$REF" -f -w 2 "$HOST")
	printf '\n# ft_ping vs %s — loopback, %s\n\n' "$REF" "$(date 2>/dev/null)"
	printf '| %-20s | %14s | %14s | %s |\n' metric ft_ping ping verdict
	printf '|%s|%s|%s|%s|\n' '----------------------' \
		'----------------' '----------------' '----------------'
	row "binary size (B)" "$fsz" "$rsz" "$fsz" "$rsz" lo
	row "peak RSS (KB)" "$frss" "$rrss" "$frss" "$rrss" lo
	row "startup -c1 (ns)" "$fst" "$rst" "$fst" "$rst" lo
	row "CPU/100pkt (ns)" "$fcpu" "$rcpu" "$fcpu" "$rcpu" lo
	row "flood (pkt/s)" "$ftp" "$rtp" "$ftp" "$rtp" hi
	printf '\nArtifacts in %s\n' "$RES"
}

main "$@"
