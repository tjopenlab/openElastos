<!--==========================================================================-->
<!-- Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/interface"/></TITLE>
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
            <H3><xsl:value-of select="manpage/interface"/></H3>
            <p></p>
        </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/domains"/>
    <xsl:apply-templates select="manpage/attributes"/>
    <xsl:apply-templates select="manpage/constructs"/>
    <xsl:apply-templates select="manpage/methods"/>
    <xsl:apply-templates select="manpage/operators"/>
    <xsl:apply-templates select="manpage/macros"/>
    <xsl:apply-templates select="manpage/events"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:apply-templates select="manpage/example"/>
    <xsl:apply-templates select="manpage/result"/>
    <xsl:apply-templates select="manpage/references"/>
    <script>footer("e_KoreTide")</script>
<!--===========================  End of Chinese Edition  =================================-->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="/manpage//description">
    <xsl:apply-templates select="para|img"/>
</xsl:template>

<xsl:template match="/manpage/remarks">
    <h4>Remarks</h4>
    <xsl:apply-templates select="para|img|table"/>
</xsl:template>

<xsl:template match="para">
    <p><xsl:apply-templates select="i|b|link|text()"/></p>
</xsl:template>

<xsl:template match="text()"><xsl:value-of select="."/></xsl:template>

<xsl:template match="link"><a class="method"><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute><xsl:value-of select="."/></a></xsl:template>

<xsl:template match="img">
    <p><img><xsl:attribute name="src"><xsl:value-of select="@url"/></xsl:attribute></img></p>
</xsl:template>

<xsl:template match="b">
    <b><xsl:apply-templates select="i|link|text()"/></b>
</xsl:template>

<xsl:template match="i">
    <i><xsl:apply-templates select="b|link|text()"/></i>
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

<xsl:template match="domains">
    <xsl:if match="*"><h4>Domain</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">域</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="domain"/>
    </table>
    <xsl:apply-templates select="para"/>
</xsl:template>

<xsl:template match="domain">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="domain_url"/>.htm</xsl:attribute><xsl:value-of select="domain_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="domain_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="domain_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="attributes">
    <xsl:if match="*"><h4>Attributes</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Attribute</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="attr"/>
    </table>
    <xsl:apply-templates select="para"/>
</xsl:template>

<xsl:template match="attr">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="attr_url"/>.htm</xsl:attribute><xsl:value-of select="attr_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="attr_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="attr_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="methods">
    <xsl:if match="*"><h4>Methods</h4></xsl:if>
    <xsl:apply-templates select="parent"/>
    <xsl:apply-templates select="self"/>
</xsl:template>

<xsl:template match="parent">
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><A class="method"><xsl:attribute name="href"><xsl:value-of select="interface_url"/>.htm</xsl:attribute><xsl:value-of select="interface_name"/></A><xsl:if match="*">Method</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="method"/>
    </table>
    <br/>
</xsl:template>

<xsl:template match="self">
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Method</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="method"/>
    </table>
</xsl:template>

<xsl:template match="method">
    <TR>
        <TD class="cell"><A class="method"><xsl:attribute name="href"><xsl:value-of select="method_url"/>.htm</xsl:attribute><xsl:value-of select="method_name"/></A></TD>
        <TD class="cell"><xsl:apply-templates select="m_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="m_description">
	<xsl:apply-templates select="b|i|link|text()"/>
</xsl:template>

<xsl:template match="macros">
    <xsl:if match="*"><h4>Macros</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Macro</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="macro"/>
    </table>
    <xsl:apply-templates select="para"/>
</xsl:template>

<xsl:template match="macro">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="macro_url"/>.htm</xsl:attribute><xsl:value-of select="macro_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="macro_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="macro_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="constructs">
    <xsl:if match="*"><h4>Constructor</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Constructor</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="construct"/>
    </table>
    <xsl:apply-templates select="para"/>
</xsl:template>

<xsl:template match="construct">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="construct_url"/>.htm</xsl:attribute><xsl:value-of select="construct_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="construct_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="construct_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="operators">
    <xsl:if match="*"><h4>Operators</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Operator</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="operator"/>
    </table>
</xsl:template>

<xsl:template match="operator">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="operator_url"/>.htm</xsl:attribute><xsl:value-of select="operator_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="operator_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="operator_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="events">
    <xsl:if match="*"><h4>Events</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD  width="37%" class="cell"><xsl:value-of select="/manpage/interface"/><xsl:if match="*">Event</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="event"/>
    </table>
</xsl:template>

<xsl:template match="event">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="event_url"/>.htm</xsl:attribute><xsl:value-of select="event_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="event_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="event_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="requirements">
    <h4>Requirements</h4>
    <p> <table style="font-size:95%;vertical-align:top" cellpadding="5">
        <xsl:apply-templates select="system"/>
        <xsl:apply-templates select="dll"/>
        <xsl:apply-templates select="headerfile"/>
        <xsl:apply-templates select="library"/>
    </table></p>
</xsl:template>

<xsl:template match="requirements/system">
    <tr>
        <td>Operating System: </td>
        <td>
        <xsl:value-of select="system_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/dll">
    <tr>
        <td>DLL: </td>
        <td>
        <xsl:value-of select="dll_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/headerfile">
    <tr>
        <td>Header files: </td>
        <td>
        <xsl:value-of select="file_name"/>
        </td>
        <td></td>
    </tr>
</xsl:template>

<xsl:template match="requirements/library">
    <tr>
        <td>Library: </td>
        <td>
            <xsl:value-of select="lib_name"/>
        </td>
        <td>
            <xsl:value-of select="lib_note"/>
        </td>
    </tr>
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
    <A class='smplink'><xsl:attribute name="href"><xsl:value-of select="@url"/></xsl:attribute>Example's Code and Explain</A>
</xsl:template>

<xsl:template match="pre"><pre class="codeview"><xsl:apply-templates select="link|text()"/></pre></xsl:template>

<xsl:template match="result">
    <h4>Output</h4>
    <pre class="codeview">
    <xsl:value-of select="."/>
    </pre>
</xsl:template>

<xsl:template match="manpage/references">
    <h4>See Also</h4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

</xsl:stylesheet>