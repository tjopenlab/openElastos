#=========================================================================
# File:    xmlesc.sed
# Purpose: Make the content xml-holdable
# Usage:   <STDOUT> | sed -f xmlesc.sed
# Date:    2006-12-15
#
# Depends: Tested on GNU sed version 4.1.4
#=========================================================================
# Example:
#
# C:\>cat t.c
# #include <stdio.h>
# int main(void)
# {
#     char c = 'A';
#     char *pc = &c;
#     printf("%c\n", *pc);
#     return 0;
# }
# 
# C:\>cat t.c | sed -f xmlesc.sed
# #include &lt;stdio.h&gt;
# int main(void)
# {
#     char c = &apos;A&apos;;
#     char *pc = &amp;c;
#     printf(&quot;%c\n&quot;, *pc);
#     return 0;
# }
# C:\>
#=========================================================================
# The problem was arosed when we want to add sample codes in "Elastos20Chs.chm"
# So we have to make the sources codes holdable in XML file. Then using XSLT's
# document() function to import the XMLized sources code.
#
# Table: The special characters have to be escaped in an XML file:
#
# +--------------+--------------+
# | Char in .cpp | Char in xml  |
# +--------------+--------------+
# |      &       |   &amp;      |
# |      "       |   &quot;     |
# |      '       |   &apos;     |
# |      <       |   &lt;       |
# |      >       |   &gt;       |
# ---------------+--------------+
#
# Technical Note: Escape Characters for XML/HDF5
#   http://hdf.ncsa.uiuc.edu/HDF5/XML/xml_escape_chars.htm
#=========================================================================

s/&/\&amp;/g
s/"/\&quot;/g
s/'/\&apos;/g
s/</\&lt;/g
s/>/\&gt;/g
