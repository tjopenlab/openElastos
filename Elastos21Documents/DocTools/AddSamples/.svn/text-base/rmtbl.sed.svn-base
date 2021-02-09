#=========================================================================
# File:    rmtbl.sed
# Purpose: Delete all trailing blank lines at the end of file
# Usage:   <STDOUT> | sed -f rmtbl.sed
# Author:  Adopted from http://sed.sourceforge.net/sed1line.txt
# Date:    2006-12-27
#
# Depends: GNU sed 4.1.4 (GNUWin32)
#=========================================================================

:loop
# if blank line matched (which may contains spaces, tabs and newlines only)
/^[ \t\n]*$/ {
    $ d     # if meet the last line (trailing blank lines found), remove it
    N       # append the next line and increase lineno
    b loop  # loop
}
