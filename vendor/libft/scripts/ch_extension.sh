find . -type f -name '*.c' -print0 | \
  xargs -0 -I{} bash -c 'f="$1"; mv -- "$f" "${f%.c}.bak"' _ {}