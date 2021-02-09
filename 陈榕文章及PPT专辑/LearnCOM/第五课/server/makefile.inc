regdll: $(TARGET)
    $(WINDIR)\system32\regsvr32.exe /s $(TARGET)
    @echo. > $@
