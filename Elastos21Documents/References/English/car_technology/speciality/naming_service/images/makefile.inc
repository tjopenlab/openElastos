#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
naming:
	@echo copying naming.jpg ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\car_technology\speciality\naming_service\images\$(SPECIAL_TARGET)
	$(V)touch $@