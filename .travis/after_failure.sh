#!/usr/bin/env bash

shopt -s nullglob
export LC_ALL=C
for i in /tmp/core*.*; do
    gdb -q ~/.phpenv/versions/$(phpenv version-name)/bin/php "$i" <<EOF
set pagination 0
backtrace full
info registers
thread apply all backtrace
quit
EOF
done