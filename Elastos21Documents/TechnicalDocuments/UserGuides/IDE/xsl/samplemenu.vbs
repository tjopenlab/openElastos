'==========================================================================
' Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
'==========================================================================
function b_ReadPath
on error resume next
set wshshell=CreateObject("WScript.Shell")
elapath = "D:\Elastos20.SDK\"
if elapath = "" then
    alert("��û�а�װElastos.SDK���ֹ��ActiveX�ؼ����У���ˢ�º����ԡ�")
    elaexist = false
end if
b_ReadPath = elaexist
end function

sub b_RunSample (cmdline)
on error resume next
set wshshell=CreateObject("WScript.Shell")
WshShell.Run cmdline
end sub