#!/bin/sh

set -e

CFLAGS="-Os -Wall -ansi -pedantic -nostdinc -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables"
LDFLAGS="-nostdlib -static"

cc -o librt00.a $CFLAGS $LDFLAGS -c rt00.c
cc -o hello $CFLAGS $LDFLAGS librt00.a main.c
