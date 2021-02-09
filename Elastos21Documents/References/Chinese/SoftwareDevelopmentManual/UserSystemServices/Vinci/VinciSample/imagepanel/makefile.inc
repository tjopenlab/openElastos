#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copycss: $(TARGET)
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.* $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\SoftwareDevelopmentManual\UserSystemServices\Vinci\VinciSample\imagepanel 2>nul
	$(V)touch $@
