hello_i.c: $(MAKEDIR)\hello.odl
    midl -nologo -h hello.h -I$(ELASTOS_ROOT)\extern\winsdk\inc -I. $**

regdll: $(TARGET)
    regcom.exe /l $(TARGET)
    @echo. > $@
