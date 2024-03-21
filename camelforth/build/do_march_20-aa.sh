#!/bin/sh

export PICO_SDK_PATH=../../pico-sdk
export SOME_BIN_DIR=$HOME/dev/bin

# change this line to point to the dev toolchain:

cmake .. -D"PICO_BOARD=pico" -D"PICO_TOOLCHAIN_PATH=$SOME_BIN_DIR"

exit 0

#END.
