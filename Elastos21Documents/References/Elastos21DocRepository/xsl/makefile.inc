#==========================================================================
# Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
xsl:
	echo copying files ...
	$(V)$(COPY) /y $(MAKEDIR)\*.css $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\xsl
	$(V)$(COPY) /y $(MAKEDIR)\*.js $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\xsl
	$(V)$(COPY) /y $(MAKEDIR)\*.vbs $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\xsl
	-$(V)mkdir xsl_e 2>nul
	$(V)$(COPY) /y $(MAKEDIR)\xsl_e\*.xsl $(XDK_USER_OBJ)\$(XDK_BUILD_KIND)\Documents\References\English\xsl\xsl_e
	$(V)touch $@
