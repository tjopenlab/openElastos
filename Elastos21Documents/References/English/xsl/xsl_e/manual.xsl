<!--==========================================================================-->
<!-- Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">

<HTML>
<HEAD>
    <title> <xsl:value-of select= "/manpage/title"/> </title>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <SCRIPT LANGUAGE="VBSCRIPT" src="/xsl/samplemenu.vbs"></SCRIPT>
</HEAD>

<BODY>
    <xsl:apply-templates select="manpage/sample[@url]"/>
    <div id="nsbanner">
        <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
            <TR class="titlebar">
                <TD align="left"><xsl:value-of select="manpage/volume"/></TD>
            </TR>
        </TABLE>
    </div>

    <DIV id="nstext" valign="bottom">
        <div>
            <H3><xsl:value-of select="manpage/title"/></H3>
        </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/syntax"/>
    <H4>Parameters</H4>
    <xsl:apply-templates select="manpage/syntax/NoArguments"/>
    <xsl:apply-templates select="manpage/syntax/parameters"/>
    <xsl:apply-templates select="manpage/return"/>
    <xsl:apply-templates select="manpage/return/NoReturnValue"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:apply-templates select="manpage/example"/>
    <xsl:apply-templates select="manpage/result"/>
    <xsl:if test="/manpage/routine_idx[.$ge$' ']"><p style="font-size:90%;font-weight:bold;margin-left:0"><A class="method"><xsl:attribute name="HREF"><xsl:value-of select="/manpage/routine_idx"/></xsl:attribute>【Functions of Same Category】</A></p></xsl:if>
    <xsl:apply-templates select="manpage/references"/>
    <script>footer("e_KoreTide")</script>
<!--===========================  End of Chinese Edition =================================-->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="link|text()"/></p>
</xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="method"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
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
    <TD class="cell"><xsl:apply-templates select="link|text()"/></TD>
</xsl:template>

<xsl:template match="/manpage//description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="syntax">
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <TR valign="top">
                <TD colspan="5" class="datatype"><xsl:value-of select="return_val"/>
                    <xsl:choose>
                        <xsl:when test="func_name[.$ge$' ']"><xsl:value-of select="func_name"/></xsl:when>
                    </xsl:choose>
                    (
                 </TD>
            </TR>
            <xsl:for-each select="parameters/func_param">
            <xsl:choose>
                <xsl:when test="optional_arguments">
                    <TR valign="top">
                        <TD width="8%"></TD>
                            <xsl:choose>
                                <xsl:when test="param_type">
                                <TD class="datatype"><xsl:value-of select="param_type"/></TD>
                                </xsl:when>
                            </xsl:choose>
                        <TD class="param"><xsl:value-of select="param_name"/><span style="font-weight:Regular; color:black; font-family:Veranda">  [ ,</span></TD>
                        <TD class="param">argument<span style="font-weight:Regular; color:black; font-family:Veranda">  ]...</span></TD>
                    </TR>
                </xsl:when>
                <xsl:otherwise>
                    <TR valign="top">
                        <TD width="8%"></TD>
                            <xsl:choose>
                                <xsl:when test="param_type">
                                <TD class="datatype"><xsl:value-of select="param_type"/></TD>
                                </xsl:when>
                            </xsl:choose>
                        <TD class="param"><xsl:value-of select="param_name"/><xsl:if test="context()[not(end())]"><span style="color:black; font-size:110%">,</span></xsl:if></TD>
                    </TR>
                </xsl:otherwise>
            </xsl:choose>
            </xsl:for-each>
            <TR>
                <TD colspan="5" class="datatype">);</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template match="syntax/parameters">
    <DL><xsl:for-each select="func_param">
        <xsl:if test="param_note[.$ge$' ']">
            <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="param_name"/></DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="param_note/para|param_note/para_table"/></font></DD>
        </xsl:if>
        <xsl:if test="optional_arguments/need_note">
            <DT class="param" style="color:#222222;margin-left:42">argument</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">Optional parameter.</font></DD>
        </xsl:if>
    </xsl:for-each></DL>
</xsl:template>

<xsl:template match="param_note/para">
    <xsl:apply-templates select="link|text()"/><BR/><BR/>
</xsl:template>

<xsl:template match="para_table">
    <table class="agility_table" cellspacing="0" cellpadding="0">
        <xsl:apply-templates select="tr|th"/>
    </table><br/>
</xsl:template>

<xsl:template match="syntax/NoArguments">
    <p>(NULL)</p>
</xsl:template>

<xsl:template match="return">
    <h4>Return Value</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="return/NoReturnValue">
    <p>This function does not return a value.</p>
</xsl:template>

<xsl:template match="remarks">
    <h4>Remarks</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="requirements">
    <h4>Requirements</h4>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="20%" class="cell">
                <xsl:if match="*">Routine</xsl:if>
            </TD>
            <TD width="20%" class="cell">
                <xsl:if match="*">Required header</xsl:if>
            </TD>
            <xsl:if test="routine/optional_headers[.$ge$' ']">
            <TD width="20%" class="cell">
                <xsl:if match="*">Optional headers</xsl:if>
            </TD>
            </xsl:if>
            <TD class="cell">
                <xsl:if match="*">Compatibility</xsl:if>
            </TD>
        </THEAD>
        <xsl:apply-templates select="routine"/>
    </table>
    <p></p>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="30%" class="cell">
                Library
            </TD>
            <TD class="cell">
                Description
            </TD>
        </THEAD>
        <TR>
            <TD class="cell">
                libc.lib
            </TD>
            <TD class="cell">
                Single thread static library
            </TD>
        </TR>
        <TR>
            <TD class="cell">
                elacrt.lib
            </TD>
            <TD class="cell">
                Import library for elacrt.dll
            </TD>
        </TR>
    </table>
</xsl:template>

<xsl:template match="routine">
    <TR>
        <TD class="cell"><B><xsl:value-of select="routine_name"/></B></TD>
        <TD class="cell"><xsl:value-of select="headerfile"/></TD>
        <xsl:if test="optional_headers[.$ge$' ']">
            <TD class="cell"><xsl:value-of select="optional_headers"/></TD>
        </xsl:if>
        <TD class="cell"><xsl:value-of select="compatibility"/></TD>
    </TR>
</xsl:template>

<xsl:template match="manpage/example">
    <h4>Example</h4>
    <xsl:choose>
        <xsl:when test="sample_link[@url]">
            <p><xsl:apply-templates select="sample_link"/></p>
        </xsl:when>
        <xsl:otherwise>
            <p><script>showButton_e()</script></p>
        </xsl:otherwise>
    </xsl:choose>

    <xsl:apply-templates select="pre"/>
</xsl:template>

<xsl:template match="sample_link">
    <A class='smplink'><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute>Example Code and Replain</A>
</xsl:template>

<xsl:template match="pre">
    <pre class="codeview"><xsl:apply-templates select="link|text()"/></pre>
</xsl:template>

<xsl:template match="result">
    <h4>Output</h4>
    <pre class="codeview"><xsl:value-of select="."/></pre>
</xsl:template>

<xsl:template match="manpage/references">
    <H4>See Also</H4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

<xsl:template match="sample[@url]">
    <div id="smppath"><xsl:value-of select="@url"/></div>
</xsl:template>

</xsl:stylesheet>