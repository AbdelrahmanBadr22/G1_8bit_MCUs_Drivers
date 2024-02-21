#!/bin/bash

simulavr -d atmega32 -f $1 -W 0x20,- -R 0x22,- -T exit 