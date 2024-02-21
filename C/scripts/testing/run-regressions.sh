#!/bin/bash

# Run this script at G1_AVR_Drivers/C
# sh run-regressionn.sh path/to/elf/dir

# Define ANSI color codes
RED='\033[0;31m'
BOLD_RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
Magenta='\033[1;35m'
RESET='\033[0m'  # Reset color to default
OK='\033[1;34m [---- OK  ----]:\033[0m'
OPS='\033[0;31m [--- Ooops ---]:\033[0m'

main_C_test_directory=regression-tests/regression-tests
KEEP_MODE=0
DIR=0
# Parse command-line options
while getopts ":d:k:help:" opt; do
  case $opt in
    d)
      DIR="$OPTARG"
      ;;
    k)
      KEEP_MODE="$OPTARG"
      ;;
    help)
      echo "d: Specify test directory"
      echo "k: Keep result.output file"
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

BASE_DIR=$(basename "$DIR")
# -- Check for passed arguments
if [ $# -lt 1 ]
then 
    echo "$RED[run-regression]:$RESET Usage run-regression -d path/to/elf/dir -k 1 or Usage run-regression all to run all tests"
    exit 1
fi

rm -rf $test_dir/results.output

if [ -d "$DIR" ]
then
  echo "$YELLOW[-- RUNNING --]: $DIR $RESET"
  echo "$OK Directory has been found successfully: $DIR"
  echo "$OK Linking with test: $DIR"

  make compile-test src="$DIR/main.c" target="$DIR/$BASE_DIR"
  echo "$OK Linking has been finished successfully"
  
  test_file=$(find "$DIR" -type f -name "*.testelf")
  
  if [ -s "$test_file" ]
  then
    echo "$OK $RESET Test-elf file has been found : $test_file" 
  else
    echo "$OPS No testelf file found in the directory "
    exit 1
  fi
else
  echo "$OPS :$RESET Directory not found $DIR"
  exit 1 
fi

test_dir=$(dirname "$test_file")
echo "\033[1;36m [-- TESTING --]:$RESET $test_file $RESET" 

if [ -s "$test_dir/results.expected" ]
then
  echo "$OK Expected results file have been found : $test_dir/results.expected"
else
  echo "$OPS No results.expected file found in the directory: $test_dir"
  exit 1
fi

simulavr -d atmega32 -f $test_file -W 0x20,- -R 0x22,- -T exit > $test_dir/resultss.output
head -n -1 $test_dir/resultss.output > $test_dir/results.output
rm -rf $test_dir/resultss.output

if [ -s "$test_dir/results.output" ]
then
  echo "$OK Output file has been generated successfully : $test_dir/results.output"
fi

diff $test_dir/results.output $test_dir/results.expected

if [ $? -eq 0 ]
then  
    echo "$GREEN[--- PASS  ---] $RESET: $test_file" >> $main_C_test_directory/summary
    echo "$GREEN[--- PASS  ---] $RESET: $test_file" 
    if [ $KEEP_MODE -ne 1 ]
    then
    rm -rf $test_dir/results.output
    fi
    rm -rf $DIR/*.testelf
    echo "\n"
    exit 0
else
    echo "$BOLD_RED[--- FAIL  ---] $RESET: $test_file" >> $main_C_test_directory/summary
    echo "$BOLD_RED[--- FAIL  ---] $RESET: $test_file" 
    if [ $KEEP_MODE -ne 1 ]
    then
    rm -rf $test_dir/results.output
    fi
    rm -rf $DIR/*.testelf
    echo "\n"
    exit 1
fi
