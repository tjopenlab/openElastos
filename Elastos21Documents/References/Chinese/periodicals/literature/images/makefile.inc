#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.bmp $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\periodicals\literature\images\$(SPECIAL_TARGET)
	$(V)touch $@
