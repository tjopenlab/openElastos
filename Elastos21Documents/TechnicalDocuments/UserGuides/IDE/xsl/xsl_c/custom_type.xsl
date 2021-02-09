<!--==========================================================================-->
<!-- Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/types"/></TITLE>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
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
    <div>
    <H3><xsl:choose>
        <xsl:when test="manpage/struct[.$ge$' ']">结构体：<xsl:value-of select="manpage/types"/></xsl:when>
        <xsl:when test="manpage/enum[.$ge$' ']">枚举类型：<xsl:value-of select="manpage/types"/></xsl:when>
    </xsl:choose></H3>
    <p></p>
    </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/enum"/>
    <xsl:apply-templates select="manpage/struct"/>
    <xsl:apply-templates select="manpage/struct/struct_member"/>
    <xsl:apply-templates select="manpage/struct/embeded_struct/embeded_struct_member"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/example"/>
    <xsl:apply-templates select="manpage/result"/>
    <script>footer("KoreTide")</script>
<!--===========================  End of Chinese Edition  =================================-->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="/manpage//description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="/manpage/remarks">
    <h4>备    注</h4>
    <xsl:apply-templates select="para|img|table"/>
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
    <TD class="cell"><xsl:value-of select="."/></TD>
</xsl:template>

<xsl:template match="enum">
    <xsl:if match="*"><h4>枚举成员</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:if match="*">枚举成员</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">枚举值</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">描  述</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="enum_member"/>
    </table>
</xsl:template>

<xsl:template match="enum_member">
    <TR>
        <TD class="cell"><B><xsl:value-of select="mem_name"/></B></TD>
        <TD class="cell"><xsl:value-of select="mem_value"/></TD>
        <TD class="cell"><xsl:value-of select="mem_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="struct">
    <div class="proto">
    <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
    <TR valign="top">
        <TD colspan="3" class="datatype">
            <code>typedef struct <xsl:choose><xsl:when test="struct_name"><xsl:value-of select="struct_name"/></xsl:when><xsl:otherwise><xsl:value-of select="/manpage/types"/></xsl:otherwise></xsl:choose> { </code>
        </TD>
    </TR>

    <xsl:for-each select="embeded_struct">
        <TR valign="top">
            <TD width="10%"></TD>
            <TD class="datatype"><xsl:value-of select="embeded_struct_type"/> {</TD>
                <xsl:for-each select="embeded_struct_member">
                    <TR>
                        <TD colspan="2"></TD>
                        <TD class="datatype"><xsl:value-of select="mem_type"/></TD>
                        <TD class="param"><xsl:value-of select="mem_name"/><span style="color:black; font-size:110%">;</span></TD>
                    </TR>
                </xsl:for-each>
        </TR>
        <TR valign="top">
            <TD width="10%"></TD>
            <TD class="datatype"><code>} <xsl:value-of select="embeded_struct_name"/>;</code></TD>
        </TR>
    </xsl:for-each>

    <xsl:for-each select="struct_member">
        <TR valign="top">
            <TD width="10%"></TD>
            <TD class="datatype"><xsl:value-of select="mem_type"/></TD>
            <TD class="param"><xsl:value-of select="mem_name"/><span style="color:black; font-size:110%">;</span></TD>
        </TR>
    </xsl:for-each>
    <TR><TD colspan="4" class="datatype"><code>}<xsl:value-of select="struct_alias"/>;</code></TD></TR>
    </TABLE>
    </div>
    <br/>
    <h4>结构体成员</h4>
</xsl:template>

<xsl:template match="struct/struct_member">
    <DL>
    <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="mem_name"/></DT>
    <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="mem_description"/></font></DD>
    </DL>
</xsl:template>

<xsl:template match="struct/embeded_struct/embeded_struct_member">
    <DL>
    <DT class="param" style="color:#222222;margin-left:42"><xsl:value-of select="mem_name"/></DT>
    <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black"><xsl:apply-templates select="mem_description"/></font></DD>
    </DL>
</xsl:template>

<xsl:template match="mem_description">
    <xsl:apply-templates select="link|text()|mem_table"/>
</xsl:template>

<xsl:template match="mem_table">
    <table class="agility_table" cellspacing="0" cellpadding="0">
        <xsl:apply-templates select="tr|th"/>
    </table><br/>
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

<xsl:template match="sample[@url]">
    <div id="smppath"><xsl:value-of select="@url"/></div>
</xsl:template>

</xsl:stylesheet>