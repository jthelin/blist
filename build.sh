#!/usr/bin/env bash

CMD_DIR=$(dirname "$0")

BLD_DIR=${CMD_DIR}/cmake-build

mkdir -p "${BLD_DIR}" && pushd "${BLD_DIR}" || exit 1

# Exit immediately if a command exits with a non-zero status.
set -e
set -o pipefail

echo "---- cmake generate ----"
cmake .. &&
  echo "---- cmake build ----" &&
  set -x &&
  cmake --build . "$@"
