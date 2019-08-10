#!/usr/bin/env bash

pushd _build && ctest --output-on-failure "$@"
