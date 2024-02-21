#!/usr/bin/tclsh
# Line cannot be too long < NOTE : USE //IGNORE-STYLE-CHECK[L004] to ignore checking >
set maxLength [getParameter "max-line-length" 100]
set pattern {\/\/IGNORE\-STYLE\-CHECK\[L004\]}

foreach f [getSourceFileNames] {
    set lineNumber 1
    foreach line [getAllLines $f] {
        set isMatch [regexp $pattern $line]
        if {$isMatch == 0} {
            if {[string length $line] > $maxLength} {
                report $f $lineNumber "line is longer than ${maxLength} characters"
            }
        }
        incr lineNumber
    }
}
