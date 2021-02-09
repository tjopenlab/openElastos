#=========================================================================
# File:    getres.sed
# Purpose: Extract contents of output section from sample files
# Usage:   cat foo.cpp | sed -n -f getres.sed
# Date:    2006-12-22
#
# Depends: GNU sed 4.1.4 (GNUWin32)
#
# Test:    test/getres.sed/dotest.bat
#=========================================================================
# Formats of output section:
#
# 1. C style
#
# /*
# Output
#     Hi, buddy. What's up?
# */
#
# 2. C++ Style
#
# //=========================
# // Output:
# //
# //  Sleep for 1 second.
# //  End sleep.
# //
# //=========================
#
#=========================================================================

/\/\*/ {
    :loop1
    /\/\*.*\*\//! {
        N
        b loop1
    }
    s/^.*\/\*[ \n]*Output:\?[ \n]*\(.*\)[ \n]*\*\/.*$/\1/I
    T fail1             # if not matched
    s/^ *//             # remove indent of 1st line
    s/\n */\n/g         # remove indent of the other lines
    s/[ \n]*$//
    p
    :fail1
}

/\/\/ *==*/ {
    :loop2
    /\/\/ *==*.*\/\/ *==*/! {
        N
        b loop2
    }
    s/^.*\/\/ *==*[ \n]*\/\/ *Output:\?[ \n]*\(.*\)\n[ \n]*\/\/ *==*[ \n]*$/\1/I
    T fail2
    s/^\/\/ *//
    s/\n *\/\/ */\n/g
    s/[ \n]*$//
    p
    :fail2
}
