#==========================================================================
# Copyright (c) 2000-2009,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.bmp $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\car_technology\fundamental\development_environment\car\others\images\$(SPECIAL_TARGET)
	$(V)touch $@
