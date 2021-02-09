<!--==========================================================================-->
<!-- Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE><xsl:value-of select="manpage/class"/></TITLE>
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
           <H3><xsl:value-of select="manpage/class"/></H3>
           <p></p>
       </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/description"/>
    <xsl:apply-templates select="manpage/interfaces"/>
    <xsl:apply-templates select="manpage/event_aggregate"/>
    <xsl:apply-templates select="manpage/methods"/>
    <xsl:apply-templates select="manpage/operators"/>
    <xsl:apply-templates select="manpage/remarks"/>
    <xsl:apply-templates select="manpage/requirements"/>
    <xsl:if test="/manpage/routine_idx[.$ge$' ']"><p style="font-size:90%;font-weight:bold;margin-left:0"><A class="method"><xsl:attribute name="HREF"><xsl:value-of select="/manpage/routine_idx"/></xsl:attribute>【List of <xsl:value-of select="/manpage/class"/>Ref Class Members】</A></p></xsl:if>
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

<xsl:template match="interfaces">
<xsl:if match="*"><h4>Interface</h4></xsl:if>
<table class="methodtbl" cellspacing="0" cellpadding="0">
    <THEAD class="head">
    <TD width="37%" class="cell"><xsl:value-of select="/manpage/class"/>
    <xsl:if match="*">Interface</xsl:if>
    </TD>
    <TD class="cell">
    <xsl:if match="*">Description</xsl:if>
    </TD>
    </THEAD>
    <xsl:apply-templates select="interface"/>
</table>
</xsl:template>

<xsl:template match="interface">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="interface_url"/>.htm</xsl:attribute><xsl:value-of select="interface_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="interface_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="interface_description"><xsl:apply-templates select="link|text()"/></xsl:template>

<xsl:template match="event_aggregate">
    <xsl:if match="*"><h4>Event Aggregate</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/class"/><xsl:if match="*">Event Aggregate</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="event_aggr"/>
    </table>
</xsl:template>

<xsl:template match="event_aggr">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="eventaggr_url"/>.htm</xsl:attribute><xsl:value-of select="eventaggr_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="eventaggr_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="eventaggr_description"><xsl:apply-templates select="link|text()"/></xsl:template>

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

<xsl:template match="methods">
    <xsl:if match="*"><h4>Methods</h4></xsl:if>
    <table class="methodtbl" cellspacing="0" cellpadding="0">
        <THEAD class="head">
            <TD width="37%" class="cell"><xsl:value-of select="/manpage/class"/><xsl:if match="*">Method</xsl:if></TD>
            <TD class="cell"><xsl:if match="*">Description</xsl:if></TD>
        </THEAD>
        <xsl:apply-templates select="method"/>
    </table>
</xsl:template>

<xsl:template match="method">
    <TR>
        <TD class="cell"><B><A class="method"><xsl:attribute name="href"><xsl:value-of select="method_url"/>.htm</xsl:attribute><xsl:value-of select="method_name"/></A></B></TD>
        <TD class="cell"><xsl:apply-templates select="m_description"/></TD>
    </TR>
</xsl:template>

<xsl:template match="m_description"><xsl:apply-templates select="link|text()"/></xsl:template>

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

<xsl:template match="manpage/references">
    <H4>See Also</H4>
    <p><xsl:apply-templates select="reference"/></p>
</xsl:template>

<xsl:template match="reference">
    <A class="method"><xsl:attribute name="href"><xsl:value-of select="ref_url"/>.htm</xsl:attribute><xsl:value-of select="ref_name"/></A>
</xsl:template>

</xsl:stylesheet>