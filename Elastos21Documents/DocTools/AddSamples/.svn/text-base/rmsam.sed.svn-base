#=========================================================================
# File:    rmsam.sed
# Purpose: Remove <example> and <result> tags of a .xml file
# Usage:   <STDOUT> | sed -f rmsam.sed
# Date:    2006-12-22
#
# Depends: GNU sed 4.1.4 (GNUWin32)
#=========================================================================
# Example:
# 
# D:\>cat frag1.tst
# ...
#         </routine>
#     </requirements>
# 
#     <example>
#         <pre>
# /* hello.cpp
#  */
# 
# #include &lt;stdio.h&gt;
# 
# int main(void)
# {
#     printf(&quot;%s\n&quot;, &quot;Hi, buddy. What&apos;s up?&quot;);
#     return 0;
# }
#         </pre>
#     </example>
#     <result>
# Hi, buddy. What&apos;s up?
#     </result>
# 
#     <references>
# ...
# 
# D:\>cat frag1.tst | sed -f e:\mytools\rmsam.sed
# ...
#         </routine>
#     </requirements>
# 
#     <example>
#     </example>
# 
#     <references>
# ...
# 
# D:\>
#=========================================================================
# Pseudo code:
#
# if (current line contains <example>) {
#     while (current line does not contains </example>)
#         concatenate next line to current line
#     remove all contents between <example> and </example>
# }
#
# if (current line contains <result>) {
#     while (current line does not contains </result>)
#         concatenate next line to current line
#     remove the <result> tag and all contents between <result> and </result>
# }
#=========================================================================

/<example>/ {
    :loop1
    /<\/example>/! {
        N
        b loop1
    }
    s/\( *\)<example>.*<\/example>/\1<example>\n\1<\/example>/
}

/<result>/ {
    :loop2
    /<\/result>/! {
        N
        b loop2
    }
    /^ *<result>.*<\/result> *$/d
    s/ *<result>.*<\/result>//
}
