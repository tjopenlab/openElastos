<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" standalone="yes" omit-xml-declaration="no"
    encoding="gb2312" media-type="text/html" indent="yes"/>

<xsl:variable name="is_callback" select="concat(substring-before(normalize-space(/manpage/interface),'Events'),'Events')=normalize-space(/manpage/interface)"/>
<xsl:variable name="is_synccallback" select="concat(substring-before(normalize-space(/manpage/interface),'Errands'),'Errands')=normalize-space(/manpage/interface)"/>
<xsl:variable name="is_new" select="concat(substring-before(normalize-space(/manpage/method),'::New'),'::New')=normalize-space(/manpage/method)"/>

<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE>
        <xsl:choose>
            <xsl:when test="manpage/interface[.!='']"><xsl:value-of select="manpage/interface"/>::</xsl:when>
            <xsl:when test="manpage/class[.!='']"><xsl:value-of select="manpage/class"/>::</xsl:when>
            <xsl:when test="manpage/macro[.!='']"> Macro </xsl:when>
        </xsl:choose>
        <xsl:value-of select="manpage/method|manpage/macro"/>
    </TITLE>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <SCRIPT LANGUAGE="VBSCRIPT" src="/xsl/samplemenu.vbs"></SCRIPT>
</HEAD>
<BODY>
    <xsl:apply-templates select="manpage/sample[@url]"/>
    <div id="nsbanner">
        <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
            <TR class="titlebar">
                <TD><xsl:value-of select="manpage/volume"/></TD>
            </TR>
        </TABLE>
    </div>
    <DIV id="nstext" valign="bottom">
        <xsl:apply-templates select="manpage/c_or_cpp"/>
        <div>
            <xsl:apply-templates select="manpage/method|manpage/macro"/>
            <p></p>
        </div>

<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/syntax"/>
    <xsl:apply-templates select="manpage/syntax_nopara"/>
    <xsl:choose>
        <xsl:when test="manpage/syntax_nopara/NoArguments">
        <h4>参  数</h4>
        </xsl:when>
        <xsl:when test="manpage/syntax/NoArguments">
        <h4>参  数</h4>
        </xsl:when>
        <xsl:when test="manpage/syntax/parameters">
        <h4>参  数</h4>
        </xsl:when>
    </xsl:choose>
    <xsl:apply-templates select="manpage/syntax_nopara/NoArguments"/>
    <xsl:apply-templates select="manpage/syntax/NoArguments"/>
    <xsl:apply-templates select="manpage/syntax/parameters"/>
    <xsl:apply-templates select="manpage/return"/>
    <xsl:apply-templates select="manpage/return/NoReturnValue"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:apply-templates select="manpage/example"/>
    <xsl:apply-templates select="manpage/callback"/>
    <xsl:apply-templates select="manpage/result"/>
    <xsl:apply-templates select="manpage/references"/>
    <script>footer("KoreTide")</script>
<!--===========================  End of Chinese Edition =================================-->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="c_or_cpp">
    <div id="c_or_cpp">
    <A><xsl:attribute name="href"><xsl:value-of select="."/>.htm</xsl:attribute>
    <xsl:apply-templates />
    </A>
    </div>
</xsl:template>

<xsl:template match="c_style|cpp_style">
    <xsl:attribute name="title">See the <xsl:choose><xsl:when test="c_style">C Style</xsl:when><xsl:when test="cpp_style">C++ style</xsl:when></xsl:choose> usages of <xsl:value-of select="/manpage/method"/>.</xsl:attribute><xsl:choose>
    <xsl:when test="c_style">
    C Style Page
    </xsl:when>
    <xsl:when test="cpp_style">
    C++ Style
    </xsl:when>
    </xsl:choose>
</xsl:template>

<xsl:template match="method">
    <h3>
    	  <xsl:choose>
            <xsl:when test="/manpage/interface">
                <a class="method"><xsl:attribute name="href">../<xsl:value-of select="/manpage/interface"/>.htm</xsl:attribute><xsl:value-of select="/manpage/interface"/></a>::
            </xsl:when>
            <xsl:when test="/manpage/class">
                <a class="method"><xsl:attribute name="href">../../<xsl:value-of select="/manpage/class"/>.htm</xsl:attribute><xsl:value-of select="/manpage/class"/></a>::
            </xsl:when>
        </xsl:choose>
        <xsl:value-of select="."/>
    </h3>
</xsl:template>

<xsl:template match="macro">
    <h3><xsl:attribute name="title">This is a macro defined in <xsl:value-of select="/manpage/interface"/></xsl:attribute>
        <xsl:value-of select="."/>
    </h3>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="i|b|red|link|text()|table"/></p>
</xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="method"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
</xsl:template>

<xsl:template match="b">
    <b><xsl:apply-templates select="red|i|link|text()"/></b>
</xsl:template>

<xsl:template match="i">
    <i><xsl:apply-templates select="red|b|link|text()"/></i>
</xsl:template>

<xsl:template match="red">
    <font color="red"><xsl:apply-templates select="i|b|link|text()"/></font>
</xsl:template>


<xsl:template match="table">
    <p><table class="agility_table" cellspacing="0" cellpadding="0">
        <xsl:apply-templates select="tr|th"/>
    </table></p>
</xsl:template>

<xsl:template match="th">
    <THEAD class="head"><xsl:apply-templates select="td"/></THEAD>
</xsl:template>

<xsl:template match="tr">
    <TR><xsl:apply-templates select="td"/></TR>
</xsl:template>

<xsl:template match="td">
    <TD class="cell"><xsl:apply-templates select="link|text()|b"/></TD>
</xsl:template>

<xsl:template match="/manpage//description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="syntax">
    <h4>写  法</h4>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <xsl:choose>
                <xsl:when test="$is_callback">
                    <tr><td colspan="5"><u>CAR（声明）</u></td></tr>
                </xsl:when>
                <xsl:when test="$is_synccallback">
                    <tr><td colspan="5"><u>CAR（声明）</u></td></tr>
                </xsl:when>
                <xsl:when test="$is_new">
                    <tr><td colspan="5"><u>C++（声明）</u></td></tr>
                </xsl:when>
                <xsl:otherwise>
                    <tr><td colspan="5"><u>CAR（声明），C++（声明）</u></td></tr>
                </xsl:otherwise>
            </xsl:choose>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="/manpage/method | /manpage/macro"/>
                    </xsl:otherwise>
                </xsl:choose>
            (</TD>
            </TR>
            <xsl:for-each select="parameters/api_param">
                <TR valign="top">
                    <TD width="8%"></TD>
                    <xsl:choose>
                        <xsl:when test="param_type">
                            <TD><xsl:if test="param_inout[.!='']">/*<xsl:value-of select="param_inout"/>*/</xsl:if><xsl:apply-templates select="param_type"/></TD>
                        </xsl:when>
                    </xsl:choose>
                    <xsl:choose>
                        <xsl:when test="param_func">
                            <TD><xsl:apply-templates select="param_func"/></TD>
                        </xsl:when>
                        <xsl:otherwise>
                            <TD class="param"><xsl:value-of select="param_name"/>
                            <xsl:if test="position()!=last()">
                            <!-- original test is here, i don't know whether new test is right -->
                            <!-- <xsl:if test="context()[not(param_default)]"> -->
                            <xsl:if test="not(param_default)">
                            <span style="color:black; font-size:110%">,</span>
                            </xsl:if>
                            </xsl:if></TD>
                        </xsl:otherwise>
                    </xsl:choose>
                    <xsl:choose>
                        <xsl:when test="param_default">
                            <TD> = <xsl:value-of select="param_default"/>
                            <xsl:if test="position()!=last()">,</xsl:if>
                            </TD>
                       </xsl:when>
                    </xsl:choose>
                </TR>
            </xsl:for-each>
            <TR>
                <TD colspan="5" class="datatype">)
                    <xsl:if test="modifier[.!='']">
                    <xsl:value-of select="modifier"/>
                    </xsl:if>
                ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
    <xsl:if test="$is_synccallback">
        <xsl:call-template name="cpp_style_synccallback">
            <xsl:with-param name="action">Assign</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="cpp_style_synccallback">
            <xsl:with-param name="action">Revoke</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_synccallback">
            <xsl:with-param name="action">Assign</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_synccallback">
            <xsl:with-param name="action">Revoke</xsl:with-param>
        </xsl:call-template>
    </xsl:if>
    <xsl:if test="$is_callback">
        <xsl:call-template name="cpp_style_callback">
            <xsl:with-param name="action">Add</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="cpp_style_callback">
            <xsl:with-param name="action">Remove</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_callback">
            <xsl:with-param name="action">Add</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_callback">
            <xsl:with-param name="action">Remove</xsl:with-param>
        </xsl:call-template>
    </xsl:if>
</xsl:template>

<!-- C++ prototype -->
<xsl:template name="cpp_style_callback">
    <xsl:param name="action"/>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <tr><td colspan="5"><u>C++（声明）</u></td></tr>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                template &lt;class T&gt;
            </TD>
            </TR>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                static
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>()
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$action"/><xsl:value-of select="normalize-space(/manpage/method|/manpage/macro)"/>Callback(
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:if test="modifier[.!='']">
                <xsl:value-of select="modifier"/>
                </xsl:if>
            </TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PInterface</TD>
                <TD class="param">pServerObj<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>T</TD>
                <TD class="param">*pThis<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>ECode</TD>
                <TD class="param">(CARAPICALLTYPE T::*pFunc)(
                    <font class="datatype">PInterface</font>
                    pServerObj
                    <xsl:for-each select="/manpage/syntax/parameters/api_param">
                        <span style="color:black; font-size:110%">,</span>
                        <font class="datatype">
                            <xsl:value-of select="param_type"/>
                        </font>
                        <xsl:value-of select="param_name"/>
                    </xsl:for-each>
                    )
                </TD>
                <TD></TD>
            </TR>
            <TR>
                <TD colspan="5" class="datatype">)
                    <xsl:if test="modifier[.!='']">
                    <xsl:value-of select="modifier"/>
                    </xsl:if>
                ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<!-- C prototype -->
<xsl:template name="c_style_callback">
    <xsl:param name="action"/>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <tr><td colspan="5"><u>C（声明）</u></td></tr>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                static
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>()
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$action"/><xsl:value-of select="normalize-space(/manpage/method|/manpage/macro)"/>Callback(
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:if test="modifier[.!='']">
                <xsl:value-of select="modifier"/>
                </xsl:if>
            </TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PInterface</TD>
                <TD class="param">pServerObj<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>ECode</TD>
                <TD class="param">(*pFunc)(
                    <font class="datatype">PVoid</font>
                    pUserData
                    <span style="color:black; font-size:110%">,</span>
                    <font class="datatype">PInterface</font>
                    pServerObj
                    <xsl:for-each select="/manpage/syntax/parameters/api_param">
                        <span style="color:black; font-size:110%">,</span>
                        <font class="datatype"><xsl:value-of select="param_type"/></font>
                        <xsl:value-of select="param_name"/>
                    </xsl:for-each>
                    )
                </TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PVoid</TD>
                <TD class="param">pUserData</TD>
                <TD>=NULL</TD>
            </TR>
            <TR>
                <TD colspan="5" class="datatype">)
                    <xsl:if test="modifier[.!='']">
                    <xsl:value-of select="modifier"/>
                    </xsl:if>
                ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template name="cpp_style_synccallback">
    <xsl:param name="action"/>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <tr><td colspan="5"><u>C++（声明）</u></td></tr>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                template &lt;class T&gt;
            </TD>
            </TR>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                static
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>()
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$action"/><xsl:value-of select="normalize-space(/manpage/method|/manpage/macro)"/>Delegate(
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:if test="modifier[.!='']">
                <xsl:value-of select="modifier"/>
                </xsl:if>
            </TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PInterface</TD>
                <TD class="param">pServerObj<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>T</TD>
                <TD class="param">*pThis<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>ECode</TD>
                <TD class="param">(CARAPICALLTYPE T::*pFunc)(
                    <font class="datatype">PInterface</font>
                    pServerObj
                    <xsl:for-each select="/manpage/syntax/parameters/api_param">
                        <span style="color:black; font-size:110%">,</span>
                        <font class="datatype">
                            <xsl:value-of select="param_type"/>
                        </font>
                        <xsl:value-of select="param_name"/>
                    </xsl:for-each>
                    )
                </TD>
                <TD></TD>
            </TR>
            <TR>
                <TD colspan="5" class="datatype">)
                    <xsl:if test="modifier[.!='']">
                    <xsl:value-of select="modifier"/>
                    </xsl:if>
                ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template name="c_style_synccallback">
    <xsl:param name="action"/>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <tr><td colspan="5"><u>C（声明）</u></td></tr>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                static
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>()
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$action"/><xsl:value-of select="normalize-space(/manpage/method|/manpage/macro)"/>Delegate(
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:if test="modifier[.!='']">
                <xsl:value-of select="modifier"/>
                </xsl:if>
            </TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PInterface</TD>
                <TD class="param">pServerObj<span style="color:black; font-size:110%">,</span></TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>ECode</TD>
                <TD class="param">(*pFunc)(
                    <font class="datatype">PVoid</font>
                    pUserData
                    <span style="color:black; font-size:110%">,</span>
                    <font class="datatype">PInterface</font>
                    pServerObj
                    <xsl:for-each select="/manpage/syntax/parameters/api_param">
                        <span style="color:black; font-size:110%">,</span>
                        <font class="datatype"><xsl:value-of select="param_type"/></font>
                        <xsl:value-of select="param_name"/>
                    </xsl:for-each>
                    )
                </TD>
                <TD></TD>
            </TR>
            <TR valign="top">
                <TD width="8%"></TD>
                <TD>PVoid</TD>
                <TD class="param">pUserData</TD>
                <TD>=NULL</TD>
            </TR>
            <TR>
                <TD colspan="5" class="datatype">)
                    <xsl:if test="modifier[.!='']">
                    <xsl:value-of select="modifier"/>
                    </xsl:if>
                ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template match="syntax/NoArguments">
    <p>（无）</p>
</xsl:template>

<xsl:template match="syntax/parameters">
    <DL><xsl:for-each select="api_param">
    <xsl:if test="param_note[.!='']">
        <xsl:choose>
            <xsl:when test="param_name">
                <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="param_name"/></DT>
            </xsl:when>
            <xsl:when test="param_func">
                <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="param_func/func_name"/></DT>
            </xsl:when>
        </xsl:choose>
        <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="param_inout"/><xsl:apply-templates select="param_note/para|param_note/para_table"/></font></DD>
    </xsl:if>
    </xsl:for-each></DL>
</xsl:template>

<xsl:template match="param_func">
    <TABLE style="font-size:90%">
        <TR>
            <TD>(
                <xsl:if test="func_return">
                    <xsl:value-of select="func_return"/>
                </xsl:if>
            </TD>
            <TD>
                <xsl:if test="func_name">
                    <font class="param"><xsl:value-of select="func_name"/></font>
                </xsl:if>) (
            </TD>
        </TR>
        <xsl:for-each select="func_param">
            <TR valign="top">
                <xsl:if test="fp_type">
                    <TD>/* <xsl:value-of select="fp_inout"/> */<xsl:value-of select="fp_type"/></TD>
                </xsl:if>
                <!-- bug here: a func_param follows a param, will not gen a , -->
                <xsl:if test="fp_name">
                    <TD><xsl:value-of select="fp_name"/><xsl:if test="position()!=last()"><span style="color:black; font-size:110%">,</span></xsl:if></TD>
                </xsl:if>
            </TR>
        </xsl:for-each>
        <TR>
            <TD>)</TD>
        </TR>
    </TABLE>
</xsl:template>

<xsl:template match="param_note/para">
    <xsl:apply-templates select="red|i|b|link|text()"/><BR/><BR/>
</xsl:template>

<xsl:template match="param_type">
    <font class="datatype"><xsl:apply-templates select="link|text()"/></font>
</xsl:template>

<xsl:template match="para_table">
    <table class="agility_table" cellspacing="0" cellpadding="0">
        <xsl:apply-templates select="tr|th"/>
    </table><br/>
</xsl:template>

<xsl:template match="syntax_nopara">
    <h4>写  法</h4>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <xsl:choose>
                <xsl:when test="$is_callback">
                    <tr><td colspan="5"><u>CAR（声明）</u></td></tr>
                </xsl:when>
                <xsl:when test="$is_new">
                    <tr><td colspan="5"><u>C++（声明）</u></td></tr>
                </xsl:when>
                <xsl:otherwise>
                    <tr><td colspan="5"><u>CAR（声明），C++（声明）</u></td></tr>
                </xsl:otherwise>
            </xsl:choose>
            <TR valign="top">
            <TD colspan="5" class="datatype">
                <xsl:if test="return_val[.!='']">
                    <xsl:value-of select="return_val"/>
                </xsl:if>
                <xsl:choose>
                    <xsl:when test="method_name[.!='']">
                        <xsl:value-of select="method_name"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="/manpage/method | /manpage/macro"/>
                    </xsl:otherwise>
                </xsl:choose>()
                <xsl:if test="modifier[.!='']">
                <xsl:value-of select="modifier"/>
                </xsl:if>
            ;</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
    <xsl:if test="$is_callback">
        <xsl:call-template name="cpp_style_callback">
            <xsl:with-param name="action">Add</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="cpp_style_callback">
            <xsl:with-param name="action">Remove</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_callback">
            <xsl:with-param name="action">Add</xsl:with-param>
        </xsl:call-template>
        <xsl:call-template name="c_style_callback">
            <xsl:with-param name="action">Remove</xsl:with-param>
        </xsl:call-template>
    </xsl:if>
</xsl:template>

<xsl:template match="syntax_nopara/NoArguments">
    <p>（无）</p>
</xsl:template>

<xsl:template match="return">
    <h4>返回值</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="return/NoReturnValue">
    <p>此方法无返回值。</p>
</xsl:template>

<xsl:template match="remarks">
    <h4>备  注</h4>
    <xsl:apply-templates select="para|table|img"/>
</xsl:template>

<xsl:template match="requirements">
    <h4>相关信息</h4>
    <p> <table style="font-size:95%;vertical-align:top" cellpadding="5">
        <xsl:apply-templates select="system"/>
        <xsl:apply-templates select="dll"/>
        <xsl:apply-templates select="headerfile"/>
        <xsl:apply-templates select="library"/>
    </table></p>
</xsl:template>
<xsl:template match="requirements/system">
    <tr>
        <td>操作系统：</td>
        <td>
        <xsl:value-of select="system_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>
<xsl:template match="requirements/dll">
    <tr>
        <td>动态链接库：</td>
        <td>
        <xsl:value-of select="dll_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/headerfile">
    <tr>
        <td>头文件：</td>
        <td>
        <xsl:value-of select="file_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/library">
    <tr>
        <td>程序库：</td>
        <td>
            <xsl:value-of select="lib_name"/>
        </td>
        <td>
            <xsl:value-of select="lib_note"/>
        </td>
    </tr>
</xsl:template>

<xsl:template match="manpage/example">
    <h4>范  例</h4>
    <xsl:choose>
        <xsl:when test="sample_link[@url]">
            <p><xsl:apply-templates select="sample_link"/></p>
        </xsl:when>
        <xsl:otherwise>
            <p><script>showButton()</script></p>
        </xsl:otherwise>
    </xsl:choose>

    <xsl:apply-templates select="pre|para"/>
</xsl:template>

<xsl:template match="manpage/callback">
    <h4>相关callback函数介绍</h4>
    <xsl:apply-templates select="pre"/>
</xsl:template>

<xsl:template match="sample_link">
    <A class='smplink'><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute>范例程序及讲解</A>
</xsl:template>

<xsl:template match="pre"><pre class="codeview"><xsl:apply-templates select="link|text()"/></pre></xsl:template>

<xsl:template match="result">
    <h4>输  出</h4>
    <pre class="codeview"><xsl:value-of select="."/></pre>
</xsl:template>

<xsl:template match="manpage/references">
    <H4>参  见</H4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

<xsl:template match="sample[@url]">
    <div id="smppath"><xsl:value-of select="@url"/></div>
</xsl:template>

</xsl:stylesheet>