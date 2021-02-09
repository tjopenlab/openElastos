#==========================================================================
# Copyright (c) 2000-2009,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.* $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\SoftwareDevelopmentManual\UserSystemServices\HttpRequest\image\$(SPECIAL_TARGET)
	$(V)touch $@
