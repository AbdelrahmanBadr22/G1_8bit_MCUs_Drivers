#!/usr/bin/tclsh
# Check if the variables : (1) Doesn't contain underscores   (2) Variable begin with lowercase and function name start with uppercase (3) To ignore use //IGNORE-STYLE-CHECK[B004]

set pattern {\/\/IGNORE\-STYLE\-CHECK\[B004\]}

foreach f [getSourceFileNames] {
    set lineNumber 1
    foreach line [getAllLines $f] {
        # TODO : We may use uint16 not uint16_t so we have to modify script
        set isMatch [regexp $pattern $line]
        if {$isMatch == 0} {
            if {[regexp {(char|([a-zA-Z0-9]+_t))\s+[a-zA-Z0-9]+\_+[a-zA-Z0-9]*\s*(\;|\=|\))} $line]} {
                report $f $lineNumber "Variables names shouldn't contain underscores"
            }
        }
        if [regexp {(char|([a-zA-Z0-9]+_t))\s+[A-Z][a-zA-Z0-9]+\s*(\;|\=|\))} $line] {
            report $f $lineNumber "Variables names should start with lowercase"
        }
        if [regexp {(char|([a-zA-Z0-9]+_t)|void)\s+[a-z][a-zA-Z0-9]+\s*(\()} $line] {
            report $f $lineNumber "Functions names should start with uppercase"
        }
        incr lineNumber
    }
}