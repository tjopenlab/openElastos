#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\sdk\setup_and_administration\images\$(SPECIAL_TARGET)
	$(V)touch $@