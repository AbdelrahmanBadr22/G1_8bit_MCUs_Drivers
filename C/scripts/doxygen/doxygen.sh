# !/bin/bash

# We have to call this script and specifying the way of treating the error
# sh doxygen.sh doxygen_config_file YES  --> This will treat the warning as an error (useful in pipeline to exit with error)
# sh doxygen.sh doxygen_config_file NO   --> This will treat the warning as an warning (useful for daily use)

( cat $1 ; echo "WARN_AS_ERROR = $2" ) | doxygen -