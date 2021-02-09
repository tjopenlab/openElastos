#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying gdb1.jpg ...
	$(V)$(COPY) /y $(MAKEDIR)\*.bmp $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\SoftwareDevelopmentManual\development_guides\images\$(SPECIAL_TARGET)
	$(V)touch $@
