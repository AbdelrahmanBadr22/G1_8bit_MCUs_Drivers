#!/bin/bash

EXIT=0
main_C_test_directory=regression-tests/regression-tests

if [ -d "$main_C_test_directory" ]; then
  test_files_dirs=$(ls "$main_C_test_directory")
else
  echo "Directory not found: $main_C_test_directory"
  exit 1 
fi

# Loop over the tests directories
for test_file_dir in $test_files_dirs
do
    if sh ../scripts/testing/run-regressions.sh -d $main_C_test_directory/$test_file_dir 
    then
        :   # NOP command
    else 
        EXIT=1 #Once we are get here then we have to exit with error
    fi
done

exit $EXIT