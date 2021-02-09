#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
xsl:
	echo copying files ...
	$(V)$(COPY) /y $(MAKEDIR)\*.css $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\Repot\xsl\$(SPECIAL_TARGET)
	$(V)$(COPY) /y $(MAKEDIR)\*.js $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\Repot\xsl\$(SPECIAL_TARGET)
	$(V)$(COPY) /y $(MAKEDIR)\*.vbs $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\Repot\xsl\$(SPECIAL_TARGET)
	-$(V)mkdir xsl_c 2>nul
	$(V)$(COPY) /y $(MAKEDIR)\xsl_c\*.xsl $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\Chinese\Repot\xsl\xsl_c\$(SPECIAL_TARGET)
	$(V)touch $@
