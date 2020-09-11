#!/usr/bin/env bash

CMD_DIR=$(dirname "$0")

BLD_DIR=${CMD_DIR}/cmake-build

pushd "${BLD_DIR}" || exit 1

ctest --output-on-failure "$@"
