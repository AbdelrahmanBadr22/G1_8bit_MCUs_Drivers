#!/usr/bin/tclsh
# All defined macros should be upper case and value is surrounded by parentheses
# #define MACRO_NAME (value)

foreach f [getSourceFileNames] {
    set lineNumber 1
    foreach line [getAllLines $f] {

        if [regexp {\#define\s+[a-z]+} $line] {
            report $f $lineNumber "All defined macros should be uppercase"
        }
        if [regexp {\#define\s+[A-Z0-9\_]+\s+[0-9a-zA-z\_]+} $line] {
            report $f $lineNumber "Macro value should be surrounded by parentheses"
        }
        incr lineNumber
    }
}