# !/bin/bash

# Comment/uncommnet all needed and unneeded commands according to your system

# INSTALL `Makefile`
#sudo apt-get install make

# INSTALL AVR-GCC COMPILER
sudo apt update
sudo apt-get install gcc-avr binutils-avr avr-libc
avr-gcc --version # this must show message like : avr-gcc (GCC) 5.4.0

# INSTALL AVR-DUDE
sudo apt install avrdude