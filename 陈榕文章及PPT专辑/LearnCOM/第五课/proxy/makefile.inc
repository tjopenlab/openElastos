dlldata.c: $(MAKEDIR)\hello.idl
    midl -nologo -Oicf -I$(ELASTOS_ROOT)\extern\winsdk\inc -I. $(MAKEDIR)\hello.idl

regdll: $(TARGET)
    $(WINDIR)\system32\regsvr32.exe /s $(TARGET)
    @echo. > $@

