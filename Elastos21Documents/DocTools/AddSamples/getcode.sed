#=========================================================================
# File:    getres.sed
# Purpose: Delete contents of output section from sample files
# Usage:   cat foo.cpp | sed -f getcode.sed
# Date:    2006-12-22
#
# Depends: GNU sed 4.1.4 (GNUWin32)
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
    s/\/\*[ \n]*Output:\?[ \n]*.*[ \n]*\*\/[ \n]*//I
}

/\/\/ *==*/ {
    :loop2
    /\/\/ *==*.*\/\/ *==*/! {
        N
        b loop2
    }
    s/\/\/ *==*[ \n]*\/\/ *Output:\?[ \n]*.*\n[ \n]*\/\/ *==*[ \n]*//I
}
