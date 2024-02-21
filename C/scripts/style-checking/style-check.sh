# !/bin/bash
# sh style-check.sh path-to-root-of-source-files path to vera rules

if [ $# -lt 2 ]; then
    echo "Usage: $0 <Path to root directory of source and header files> <path to vera rules>"
    exit 1
fi

FILES=$(find $1 -name "*.c" -o -name "*.h")

vera++ -R L001 -R L003 -R L004 -R L005 -R L006 -R F001 -R F002 -R T001 -R T003 -R T004 -R T005 -R T006 -R T007\
       -R T008 -R T009 -R T010 -R T011 -R T012 -R T015 -R T016 -R T017 -R T018 -R T019 -R B001 -R B002 -R B003\
       -R B004\
       -P max-line-length=80\
       -e\
       -S\
       -s\
       --root ${2}\
        ${FILES}