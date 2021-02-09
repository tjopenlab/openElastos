#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\SmartphoneDevelopmentManual\PhoneBurn\Common\OSBurn\images\$(SPECIAL_TARGET)
	$(V)touch $@
