<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" standalone="yes" omit-xml-declaration="no"
    encoding="gb2312" media-type="text/html" indent="yes"/>
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/bar"/>：<xsl:value-of select="manpage/title"/></TITLE>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <style type="text/css">.paramtbl {font-size:90%}</style>
</HEAD>
<BODY>
    <div id="nsbanner">
        <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
            <TR class="titlebar">
            <xsl:choose>
                <xsl:when test="manpage/volume[.!='']">
                    <TD><xsl:value-of select="manpage/volume"/></TD>
                </xsl:when>
                <xsl:otherwise>
                    <TD align="left" width="33%">命令&amp;工具介绍</TD>
                </xsl:otherwise>
            </xsl:choose>
            </TR>
        </TABLE>
    </div>
    <DIV id="nstext" valign="bottom">
    <p></p>
    <xsl:apply-templates select="manpage/title"/>
<!--===========================  Chinese Edition Below  ================================= -->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/syntax"/>
    <xsl:apply-templates select="manpage/NoArguments"/>
    <xsl:apply-templates select="manpage/parameters"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/examples"/>
    <xsl:apply-templates select="manpage/references"/>
    <p></p>
    <script>footer("KoreTide")</script>
<!--===========================  End of Chinese Edition ================================= -->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="link|text()|br"/></p>
</xsl:template>

<xsl:template match="pre"><pre class="codeview"><xsl:value-of select="."/></pre></xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="style1"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
</xsl:template>

<xsl:template match="text()">
    <xsl:value-of select="."/>
</xsl:template>


<xsl:template match="br"><br/></xsl:template>

<xsl:template match="title">
    <H3><xsl:if test="/manpage/category[.!='']"><xsl:value-of select="/manpage/category"/>:</xsl:if><xsl:value-of select="."/></H3>
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

<xsl:template match="description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="syntax">
    <H4>命令格式</H4>
    <DD><TABLE WIDTH="90%">
        <TR valign="top">
            <TD width="10%"><xsl:apply-templates select="cmd_name/text()|cmd_name/br"/></TD>
            <TD><B><xsl:apply-templates select="cmd_param/text()|cmd_param/br"/></B></TD>
        </TR>
    </TABLE></DD>
</xsl:template>

<xsl:template match="manpage/NoArguments">
    <H4>参数说明</H4>
    <p>（无）</p>
</xsl:template>

<xsl:template match="manpage/parameters">
    <H4>参数说明</H4>
    <TABLE class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="30%" class="cell">参  数</TD>
            <TD class="cell">描  述</TD>
        </THEAD>
        <xsl:apply-templates select="param"/>
    </TABLE>
</xsl:template>

<xsl:template match="param">
    <TR valign="top">
        <TD class="cell"><xsl:apply-templates select="param_name/text()|param_name/br|param_name/link"/></TD>
        <TD class="cell"><xsl:apply-templates select="param_note/text()|param_note/br|param_note/link"/></TD>
    </TR>
</xsl:template>

<xsl:template match="manpage/examples">
    <H4>用法示例</H4>
    <DD><TABLE WIDTH="80%" border="0" cellpadding="5" cellspacing="2" style="font-size:95%">
        <xsl:apply-templates select="example"/>
    </TABLE></DD>
</xsl:template>

<xsl:template match="example">
    <xsl:if test="eg_line">
        <pre class="codeview"><I><B><xsl:apply-templates select="eg_line/text()|eg_line/br|eg_line/link"/></B></I></pre>
    </xsl:if>
    <xsl:if test="eg_note">
        <p><xsl:apply-templates select="eg_note/text()|eg_note/br|eg_note/link"/></p>
    </xsl:if>
    <xsl:if test="eg_result">
        <pre class="codeview"><xsl:value-of select="eg_result"/></pre>
    </xsl:if>
</xsl:template>

<xsl:template match="manpage/remarks">
    <h4>备  注</h4>
    <xsl:apply-templates select="para|img|pre|table"/>
</xsl:template>

<xsl:template match="manpage/references">
    <H4>参  见</H4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

</xsl:stylesheet>