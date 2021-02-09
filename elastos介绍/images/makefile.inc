#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
copyimg:
	@echo copying ...
	$(V)$(COPY) /y $(MAKEDIR)\*.jpg $(ELASTOS_DUMP)\$(ELASTOS_BUILD_KIND)\Elastos20.Hlp\Chinese\preface\elastos_technic\images\$(SPECIAL_TARGET)
	$(V)touch $@
