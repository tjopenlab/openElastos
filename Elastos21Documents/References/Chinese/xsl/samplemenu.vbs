'==========================================================================
' Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
'==========================================================================
function b_ReadPath
on error resume next
set wshshell=CreateObject("WScript.Shell")
elapath = "D:\Elastos21\"
if elapath = "" then
    alert("您没有安装Elastos XDK或禁止了ActiveX控件运行，请刷新后重试。")
    elaexist = false
end if
b_ReadPath = elaexist
end function

sub b_RunSample (cmdline)
on error resume next
set wshshell=CreateObject("WScript.Shell")
WshShell.Run cmdline
end sub