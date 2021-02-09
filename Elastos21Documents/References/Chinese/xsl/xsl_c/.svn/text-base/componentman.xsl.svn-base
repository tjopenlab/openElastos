<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" standalone="yes" omit-xml-declaration="no"
    encoding="gb2312" media-type="text/html" indent="yes"/>
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/component"/></TITLE>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <SCRIPT LANGUAGE="VBSCRIPT" src="/xsl/samplemenu.vbs"></SCRIPT>
</HEAD>

<BODY>
    <div id="nsbanner">
        <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
            <TR class="titlebar">
                <TD><xsl:value-of select="manpage/volume"/></TD>
            </TR>
        </TABLE>
    </div>

    <DIV id="nstext" valign="bottom">
        <div>
            <H3><xsl:value-of select="manpage/component"/></H3>
            <p></p>
        </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/classes"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:apply-templates select="manpage/references"/>
    <script>footer("KoreTide")</script>
<!--===========================  End of Chinese Edition  =================================-->
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
    <TD class="cell"><xsl:value-of select="."/></TD>
</xsl:template>

<xsl:template match="/manpage//description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="classes">
    <h4>构件包含的类</h4>
    <p><table WIDTH="85%" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell" align="center"><xsl:value-of select="/manpage/component"/>构件中包含的类</TD>
            <TD width="67%" class="cell" align="center">描叙</TD>
        </THEAD>
        <xsl:apply-templates select="class"/>
    </table></p>
</xsl:template>

<xsl:template match="class">
    <TR>
        <TD class="cell" align="center"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="class_url"/>.htm</xsl:attribute><xsl:value-of select="class_name"/></A></B></TD>
        <TD class="cell" align="center"><xsl:value-of select="class_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="/manpage/remarks">
    <h4>备    注</h4>
    <xsl:apply-templates select="para|img|table"/>
</xsl:template>

<xsl:template match="requirements">
    <h4>相关信息</h4>
    <p><table style="font-size:95%;vertical-align:top" cellpadding="5">
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

<xsl:template match="manpage/references">
    <H4>参  见</H4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

</xsl:stylesheet>