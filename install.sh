#!/bin/bash

if [[ $1 != "" ]]; then
    ARGS="-D$1"
else
    ARGS="-DDISPLAY=yes"
fi

cmake -B build $ARGS && cmake --build build && sudo cmake --install build

