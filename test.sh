#!/usr/bin/env bash

BLD_DIR=_build

pushd "${BLD_DIR}" || return

ctest --output-on-failure --extra-verbose "$@"
