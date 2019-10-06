#!/usr/bin/env bash

BLD_DIR=build

mkdir -p "${BLD_DIR}" && pushd "${BLD_DIR}" || return

echo "---- cmake generate ----"
set -x
cmake .. && \
\
echo "---- cmake build ----" && \
cmake --build . "$@"
