#==========================================================================
# Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.gif $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\car_technology\fundamental\development_environment\car\Create_CarDemo\Client\images\$(SPECIAL_TARGET)
	$(V)touch $@