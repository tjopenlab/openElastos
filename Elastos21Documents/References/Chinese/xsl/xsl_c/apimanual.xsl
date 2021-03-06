<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" standalone="yes" omit-xml-declaration="no"
    encoding="gb2312" media-type="text/html" indent="yes"/>
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
                <xsl:when test="manpage/volume[.!='']">
                    <TD><xsl:value-of select="manpage/volume"/></TD>
                </xsl:when>
                <xsl:otherwise>
                    <TD> “Elastos”应用编程接口 </TD>
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
    <xsl:apply-templates select="manpage/syntax_nopara"/>
    <H4>参  数</H4>
    <xsl:apply-templates select="manpage/syntax_nopara/NoArguments"/>
    <xsl:apply-templates select="manpage/syntax/NoArguments"/>
    <xsl:apply-templates select="manpage/syntax/parameters"/>
    <xsl:apply-templates select="manpage/return"/>
    <xsl:apply-templates select="manpage/return/NoReturnValue"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:apply-templates select="manpage/example"/>
    <xsl:apply-templates select="manpage/result"/>
    <xsl:if test="/manpage/routine_idx[.!='']"><p style="font-size:90%;font-weight:bold;margin-left:0"><A class="method"><xsl:attribute name="HREF"><xsl:value-of select="/manpage/routine_idx"/></xsl:attribute>【同类API列表】</A></p></xsl:if>
    <xsl:apply-templates select="manpage/references"/>
    <script>footer("KoreTide")</script>
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
    <xsl:attribute name="title">See the <xsl:choose><xsl:when test="c_style">C Style</xsl:when><xsl:when test="cpp_style">C++ style</xsl:when></xsl:choose> usages of <xsl:value-of select="/manpage/title"/>.</xsl:attribute><xsl:choose>
    <xsl:when test="c_style">
    C Style Page
    </xsl:when>
    <xsl:when test="cpp_style">
    C++ Style
    </xsl:when>
    </xsl:choose>
</xsl:template>

<xsl:template match="description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="link|text()"/></p>
</xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="style1"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
</xsl:template>

<xsl:template match="syntax">
    <div class="proto">
    <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
    <TR valign="top">
    <TD colspan="4" class="datatype"><xsl:value-of select="return_val"/>
    <xsl:choose>
        <xsl:when test="api_name[.!='']">
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
        <TD class="param"><xsl:value-of select="param_name"/><xsl:if test="position()!=last()"><span style="color:black; font-size:110%">,</span></xsl:if></TD>
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

<xsl:template match="syntax_nopara">
    <div class="proto">
    <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
    <TR valign="top">
    <TD colspan="4" class="datatype"><xsl:value-of select="return_val"/>
    <xsl:choose>
        <xsl:when test="api_name[.!='']">
            <xsl:value-of select="api_name"/>();
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="/manpage/title"/>();
        </xsl:otherwise>
    </xsl:choose>
    </TD>
    </TR>
    </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template match="manpage/syntax_nopara/NoArguments">
    <p>（无）</p>
</xsl:template>

<xsl:template match="manpage/syntax/NoArguments">
    <p>（无）</p>
</xsl:template>


<xsl:template match="syntax/parameters">
    <DL><xsl:for-each select="api_param">
    <xsl:if test="param_note[.!='']">
        <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="param_name"/></DT>
        <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="param_inout"/><xsl:apply-templates select="param_note/para|param_note/para_table"/></font></DD>
    </xsl:if>
    <xsl:if test="optional_arguments/need_note">
            <DT class="param" style="color:#222222;margin-left:42">argument</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">可选参数</font></DD>
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
    <h4>相关信息</h4>
    <p><table style="font-size:95%;vertical-align:top" cellpadding="5">
    <xsl:apply-templates select="system"/>
    <xsl:apply-templates select="headerfile"/>
    <xsl:apply-templates select="library"/>
    </table></p>
</xsl:template>
<xsl:template match="requirements/system">
    <tr>
        <td>操作系统：</td>
        <td><xsl:value-of select="system_name"/></td>
        <td></td>
    </tr>
</xsl:template>
<xsl:template match="requirements/headerfile">
    <tr>
        <td>头文件：</td>
        <td><xsl:value-of select="file_name"/></td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/library">
    <tr>
        <td>程序库：</td>
        <td><xsl:value-of select="lib_name"/></td>
        <td><xsl:value-of select="lib_note"/></td>
    </tr>
</xsl:template>

<xsl:template match="manpage/remarks">
    <h4>备  注</h4>
    <xsl:apply-templates select="para|table|remarkview"/>
</xsl:template>

<xsl:template match="remarkview">
    <pre class="codeview"><xsl:value-of select="."/></pre>
</xsl:template>

<xsl:template match="manpage/return">
    <h4>返回值</h4>
    <xsl:apply-templates select="para|table"/>
</xsl:template>

<xsl:template match="return/NoReturnValue">
    <p>此函数无返回值。</p>
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

    <xsl:apply-templates select="pre"/>
</xsl:template>

<xsl:template match="sample_link">
    <A class='smplink'><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute>范例程序及讲解</A>
</xsl:template>

<xsl:template match="pre"><pre class="codeview"><xsl:apply-templates select="link|text()"/></pre></xsl:template>

<xsl:template match="manpage/result">
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