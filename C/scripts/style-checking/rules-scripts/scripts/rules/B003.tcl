#!/usr/bin/tclsh
# We have to use std types such as uint16_t, int32_t, ..

foreach f [getSourceFileNames] {
    set lineNumber 1
    foreach line [getAllLines $f] {

        if [regexp {\b(int(?! main)|unsigned|signed|short|long|long long|float|double)\b} $line] {
            report $f $lineNumber "Using non-standard datatype not recommended"
        }
        incr lineNumber
    }
}