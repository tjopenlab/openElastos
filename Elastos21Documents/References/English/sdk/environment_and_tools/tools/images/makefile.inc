#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
tfs:
	@echo copying tfs.jpg ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\sdk\environment_and_tools\tools\images\$(SPECIAL_TARGET)
	$(V)touch $@
