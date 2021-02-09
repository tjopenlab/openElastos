<!--==========================================================================-->
<!-- Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/title"/></TITLE>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <SCRIPT LANGUAGE="VBSCRIPT" src="/xsl/samplemenu.vbs"></SCRIPT>
</HEAD>
<BODY>
    <xsl:apply-templates select="manpage/sample[@url]"/>
    <div id="nsbanner">
    <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
        <TR class="titlebar">
            <xsl:choose>
                <xsl:when test="manpage/volume[.$ge$' ']">
                    <TD><xsl:value-of select="manpage/volume"/></TD>
                </xsl:when>
                <xsl:otherwise>
                    <TD> Elastos API Manual </TD>
                </xsl:otherwise>
            </xsl:choose>
        </TR>
    </TABLE>
    </div>
    <DIV id="nstext" valign="bottom">
    <xsl:apply-templates select="manpage/c_or_cpp"/>
    <H3><xsl:value-of select="manpage/title"/></H3>

<!--===========================  Chinese Edition Below  ================================= -->
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
<!--===========================  End of Chinese Edition ================================= -->
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
    <xsl:attribute name="title">See the <xsl:choose><xsl:when match="c_style">C Style</xsl:when><xsl:when match="cpp_style">C++ style</xsl:when></xsl:choose> usages of <xsl:value-of select="/manpage/title"/>.</xsl:attribute><xsl:choose>
    <xsl:when match="c_style">
    C Style Page
    </xsl:when>
    <xsl:when match="cpp_style">
    C++ Style
    </xsl:when>
    </xsl:choose>
</xsl:template>

<xsl:template match="description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="i|b|link|text()"/></p>
</xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="style1"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
</xsl:template>

<xsl:template match="b">
    <b><xsl:apply-templates select="i|link|text()"/></b>
</xsl:template>

<xsl:template match="i">
    <i><xsl:apply-templates select="b|link|text()"/></i>
</xsl:template>

<xsl:template match="syntax">
    <div class="proto">
    <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
    <TR valign="top">
    <TD colspan="4" class="datatype"><xsl:value-of select="return_val"/>
    <xsl:choose>
        <xsl:when test="api_name[.$ge$' ']">
            <xsl:value-of select="api_name"/>(
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="/manpage/title"/>(
        </xsl:otherwise>
    </xsl:choose>
    </TD>
    </TR>
    <xsl:for-each select="parameters/api_param">
     <xsl:choose>
     <xsl:when test="optional_arguments">
        <TR valign="top">
            <TD width="8%"></TD>
        <xsl:choose>
            <xsl:when test="param_type">
            <TD class="datatype"><xsl:value-of select="param_type"/></TD>
            </xsl:when>
        </xsl:choose>
            <TD class="param"><xsl:value-of select="param_name"/><span style="font-weight:Regular; color:black;font-family:Veranda">  [ ,</span></TD>
            <TD class="param">argument<span style="font-weight:Regular; color:black;ont-family:Veranda"> ]...</span></TD>
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

<xsl:template match="manpage/syntax/NoArguments">
    <p>(NULL)</p>
</xsl:template>

<xsl:template match="syntax/parameters">
    <DL><xsl:for-each select="api_param">
    <xsl:if test="param_note[.$ge$' ']">
        <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="param_name"/></DT>
        <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="param_inout"/><xsl:apply-templates select="param_note/para|param_note/para_table"/></font></DD>
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

<xsl:template match="param_inout">
    <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="requirements">
    <h4>Requirements</h4>
    <p><table style="font-size:95%;vertical-align:top" cellpadding="5">
    <xsl:apply-templates select="system"/>
    <xsl:apply-templates select="headerfile"/>
    <xsl:apply-templates select="library"/>
    </table></p>
</xsl:template>

<xsl:template match="requirements/system">
    <tr>
        <td>Operating System: </td>
        <td><xsl:value-of select="system_name"/></td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/headerfile">
    <tr>
        <td>Header Files: </td>
        <td><xsl:value-of select="file_name"/></td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/library">
    <tr>
        <td>Library: </td>
        <td><xsl:value-of select="lib_name"/></td>
        <td><xsl:value-of select="lib_note"/></td>
    </tr>
</xsl:template>

<xsl:template match="manpage/remarks">
    <h4>Remarks</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="manpage/return">
    <h4>Return Value</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="return/NoReturnValue">
    <p>This function does not return a value.</p>
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
    <A class='smplink'><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute>范例程序及讲解</A>
</xsl:template>

<xsl:template match="pre"><pre class="codeview"><xsl:apply-templates select="link|text()"/></pre></xsl:template>

<xsl:template match="manpage/result">
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