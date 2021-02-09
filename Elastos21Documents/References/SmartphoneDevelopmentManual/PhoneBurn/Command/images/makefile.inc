#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.gif $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\SmartphoneDevelopmentManual\PhoneBurn\command\images\$(SPECIAL_TARGET)
	$(V)touch $@
