#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying gdb1.jpg ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\sdk\development_guides\images\$(SPECIAL_TARGET)
	$(V)touch $@
