#!/usr/bin/env bash

CMD_DIR=$(dirname "$0")

BUILD_DIR=${CMD_DIR}/cmake-build
INSTALL_DIR=_install

mkdir -p "${BUILD_DIR}" && pushd "${BUILD_DIR}" || exit 1
mkdir -p "${INSTALL_DIR}" || exit 1

# Exit immediately if a command exits with a non-zero status.
set -e
set -o pipefail

echo "---- cmake generate ----"
cmake ..

echo "---- cmake build ----" &&
set -x
cmake --build . "$@"

echo "---- cmake install ----" &&
cmake --install . --prefix "${INSTALL_DIR}"
ls -lhR "${PWD}/${INSTALL_DIR}"
