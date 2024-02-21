#!/usr/bin/tclsh
# All user defined data types must be ended with `_t`

foreach f [getSourceFileNames] {
    set lineNumber 1
    foreach line [getAllLines $f] {

        if [regexp {\}\s*[a-zA-Z0-9]+\;} $line] {
            report $f $lineNumber "User defined data types must be ended with `_t`"
        } 
        incr lineNumber
    }
}