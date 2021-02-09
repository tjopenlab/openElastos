#==========================================================================
# Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
AStringBuf:
	@echo copying *.jpg ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\car_technology\fundamental\development_environment\car\data_type\AStringBuf\images\$(SPECIAL_TARGET)
	$(V)touch $@
	$(V)touch $@
