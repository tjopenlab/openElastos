<!--==========================================================================-->
<!-- Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.-->
<!--==========================================================================-->

<?xml version="1.0" encoding="GB2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<HTML>
<HEAD>
    <TITLE>
        <xsl:choose>
            <xsl:when test="manpage/AddEventHandler[.$ge$' ']"><xsl:value-of select="manpage/AddEventHandler/class"/>Ref::Add<xsl:value-of select="manpage/AddEventHandler/event"/>Handler</xsl:when>
            <xsl:when test="manpage/RemoveEventHandler[.$ge$' ']"><xsl:value-of select="manpage/RemoveEventHandler/class"/>Ref::Remove<xsl:value-of select="manpage/RemoveEventHandler/event"/>Handler</xsl:when>
            <xsl:when test="manpage/ClassEventHandler[.$ge$' ']"><xsl:value-of select="manpage/ClassEventHandler/class"/><xsl:value-of select="manpage/ClassEventHandler/event"/>Handler</xsl:when>
            <xsl:when test="manpage/Instantiate[.$ge$' ']"><xsl:value-of select="manpage/Instantiate/class"/>Ref::Instantiate</xsl:when>
            <xsl:when test="manpage/IsValid[.$ge$' ']"><xsl:value-of select="manpage/IsValid/class"/>Ref::IsValid</xsl:when>
            <xsl:when test="manpage/operator[.$ge$' ']"><xsl:value-of select="manpage/operator/class"/>Ref::operator ==</xsl:when>
        </xsl:choose>
    </TITLE>
    <META HTTP-EQUIV="Content-Type" Content="text/html; charset=gb2312"/>
    <SCRIPT SRC="/xsl/runningbar.js"></SCRIPT>
    <SCRIPT LANGUAGE="VBSCRIPT" src="/xsl/samplemenu.vbs"></SCRIPT>
</HEAD>

<BODY>
    <div id="nsbanner">
    <TABLE width="100%" border="1" cellspacing="0" rules="none" cellpadding="0" frame="below">
    <TR class="titlebar">
        <TD><xsl:choose>
            <xsl:when test="manpage/AddEventHandler[.$ge$' ']"><xsl:value-of select="manpage/AddEventHandler/volume"/></xsl:when>
            <xsl:when test="manpage/RemoveEventHandler[.$ge$' ']"><xsl:value-of select="manpage/RemoveEventHandler/volume"/></xsl:when>
            <xsl:when test="manpage/ClassEventHandler[.$ge$' ']"><xsl:value-of select="manpage/ClassEventHandler/volume"/></xsl:when>
            <xsl:when test="manpage/Instantiate[.$ge$' ']"><xsl:value-of select="manpage/Instantiate/volume"/></xsl:when>
            <xsl:when test="manpage/IsValid[.$ge$' ']"><xsl:value-of select="manpage/IsValid/volume"/></xsl:when>
            <xsl:when test="manpage/operator[.$ge$' ']"><xsl:value-of select="manpage/operator/volume"/></xsl:when>
        </xsl:choose></TD>
    </TR>
    </TABLE>
    </div>

    <DIV id="nstext" valign="bottom">
    <div>
        <xsl:choose>
            <xsl:when test="manpage/AddEventHandler[.$ge$' ']"><h3><A class="method"><xsl:attribute name="href">../<xsl:value-of select="manpage/AddEventHandler/class"/>Ref.htm</xsl:attribute><xsl:value-of select="manpage/AddEventHandler/class"/>Ref</A>::Add<xsl:value-of select="manpage/AddEventHandler/event"/>Handler</h3></xsl:when>
            <xsl:when test="manpage/RemoveEventHandler[.$ge$' ']"><h3><A class="method"><xsl:attribute name="href">../<xsl:value-of select="manpage/RemoveEventHandler/class"/>Ref.htm</xsl:attribute><xsl:value-of select="manpage/RemoveEventHandler/class"/>Ref</A>::Remove<xsl:value-of select="manpage/RemoveEventHandler/event"/>Handler</h3></xsl:when>
            <xsl:when test="manpage/ClassEventHandler[.$ge$' ']"><h3><xsl:value-of select="manpage/ClassEventHandler/class"/><xsl:value-of select="manpage/ClassEventHandler/event"/>Handler</h3></xsl:when>
            <xsl:when test="manpage/Instantiate[.$ge$' ']"><h3><A class="method"><xsl:attribute name="href">../<xsl:value-of select="manpage/Instantiate/class"/>Ref.htm</xsl:attribute><xsl:value-of select="manpage/Instantiate/class"/>Ref</A>::Instantiate</h3></xsl:when>
            <xsl:when test="manpage/IsValid[.$ge$' ']"><h3><A class="method"><xsl:attribute name="href">../<xsl:value-of select="manpage/IsValid/class"/>Ref.htm</xsl:attribute><xsl:value-of select="manpage/IsValid/class"/>Ref</A>::IsValid</h3></xsl:when>
            <xsl:when test="manpage/operator[.$ge$' ']"><h3><A class="method"><xsl:attribute name="href">../<xsl:value-of select="manpage/operator/class"/>Ref.htm</xsl:attribute><xsl:value-of select="manpage/operator/class"/>Ref</A>::operator ==</h3></xsl:when>
        </xsl:choose>
        <p></p>
    </div>
<!--===========================  Chinese Edition Below  =================================-->
    <xsl:apply-templates select="manpage/AddEventHandler"/>
    <xsl:apply-templates select="manpage/RemoveEventHandler"/>
    <xsl:apply-templates select="manpage/ClassEventHandler"/>
    <xsl:apply-templates select="manpage/Instantiate"/>
    <xsl:apply-templates select="manpage/IsValid"/>
    <xsl:apply-templates select="manpage/operator"/>
    <script>footer("e_KoreTide")</script>
<!--===========================  End of Chinese Edition =================================-->
    </DIV>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="AddEventHandler">
    <p>Register <A class="method"><xsl:attribute name="href">../<xsl:value-of select="class"/>.htm</xsl:attribute><xsl:value-of select="class"/></A> object <A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A> event handler.</p>

    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">ECODEAdd<xsl:value-of select="event"/>Handler(</TD>
        </TR>
        <TR valign="top">
            <TD width="8%"></TD>
            <TD><font class="datatype">const <xsl:value-of select="class"/><xsl:value-of select="event"/>Handler&amp;</font></TD>
            <TD class="param">ehRef</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div>

    <H4>Parameters</H4>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">ehRef</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">The reference of <A class="method"><xsl:attribute name="href"><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler</A>. <xsl:value-of select="class"/><xsl:value-of select="event"/>Handler is the handle of <xsl:value-of select="class"/> class <xsl:value-of select="event"/> event handler.</font></DD>
        </DL>
    <h4>Return Value</h4>
        <p>This method return S_OK if successful.</p>
        <p>For additional information about ECODE, see <a class="method" href="../../../../elatypes/hresult.htm">ECODE</a> in the Introduction.</p>

    <h4>Remarks</h4>
        <p>If user invoke Add<xsl:value-of select="event"/>Handler to register <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event handler, it is required to invoke <A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Remove<xsl:value-of select="event"/>Handler</A> to cancel the event handler afterwards.
</p>

    <xsl:apply-templates select="requirements"/>

    <h4>See Also</h4>
        <p style="text-align:left"><A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Remove<xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href"><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A></p>
</xsl:template>


<xsl:template match="RemoveEventHandler">
    <p>Cancel <A class="method"><xsl:attribute name="href">../<xsl:value-of select="class"/>.htm</xsl:attribute><xsl:value-of select="class"/></A> object <A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A> event handler.</p>

    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">ECODERemove<xsl:value-of select="event"/>Handler(</TD>
        </TR>
        <TR valign="top">
            <TD width="8%"></TD>
            <TD><font class="datatype">const <xsl:value-of select="class"/><xsl:value-of select="event"/>Handler&amp;</font></TD>
            <TD class="param">ehRef</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div>

    <H4>Parameters</H4>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">ehRef</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">The reference of <A class="method"><xsl:attribute name="href"><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler</A>. <xsl:value-of select="class"/><xsl:value-of select="event"/>Handler is the handle of <xsl:value-of select="class"/> class <xsl:value-of select="event"/> event handler.</font></DD>
        </DL>

    <h4>Return Value</h4>
        <p>This method return S_OK if successful.</p>
        <p>For additional information about ECODE, see <a class="method" href="../../../../elatypes/hresult.htm">ECODE</a> in the Introduction.</p>

    <h4>Remarks</h4>
        <p>If user invoke <A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Add<xsl:value-of select="event"/>Handler</A> to register <xsl:value-of select="class"/> object <xsl:value-of select="event"/>event handler, it is required to invoke Remove<xsl:value-of select="event"/>Handler to cancel the event handler afterwards.</p>

    <xsl:apply-templates select="requirements"/>

    <h4>See Also</h4>
        <p style="text-align:left"><A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Add<xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href"><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A></p>
</xsl:template>


<xsl:template match="ClassEventHandler">
    <p><xsl:value-of select="class"/><xsl:value-of select="event"/>Handler class is the handler of <A class="method"><xsl:attribute name="href">../<xsl:value-of select="class"/>.htm</xsl:attribute><xsl:value-of select="class"/></A> class <A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A> event handler. The following are two constructors of this class. When event handler is a member function of one of the classes, use the first constructor. When event handler is a normal function, use the second constructor.
</p>

    <xsl:apply-templates select="syntax"/>
    <H4>Parameters</H4>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">pThis</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">Pointer to template class T.</font></DD>
        </DL>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">pFunc1 </DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">Pointer to one of template class T members which is <xsl:value-of select="event"/> event handler defined by user.</font></DD>
        </DL>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">pFunc2 </DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">Point to the function which is <xsl:value-of select="event"/> event handler defined by user.</font></DD>
        </DL>

    <h4>Remarks</h4>
        <p>The event handler which pFunc1 and pFunc2 pointer to, its return value's type mast be ECODE, and the event handler mast accord with STDMETHODCALLTYPE(__stdcall) calling convention. The first parameter is the reference of <A class="method"><xsl:attribute name="href">../<xsl:value-of select="class"/>Ref.htm</xsl:attribute><xsl:value-of select="class"/>Ref</A>, other parameters accord with parameters of <xsl:value-of select="event"/>.</p>
    <xsl:apply-templates select="requirements"/>

    <h4>Example</h4>
<pre class="codeview">
/*
 * For example：CMyClass::My<xsl:value-of select="event"/> is the <xsl:value-of select="event"/> event handler defined by user,
 * and My<xsl:value-of select="event"/> is CMyClass class's member, use the first constructor.
 */

ECODE __stdcall CMyClass::My<xsl:value-of select="event"/>(<xsl:for-each select="syntax/parameters/api_param/param_func/func_param">
            /* [in] */ <xsl:value-of select="fp_type"/><xsl:value-of select="fp_name"/><xsl:if test="context()[not(end())]"><span style="color:black; font-size:110%">,</span></xsl:if>
        </xsl:for-each>)
{
    ……
    // Add the code of My<xsl:value-of select="event"/> event handler here
    ……
}

ECODE <xsl:value-of select="event"/>Demo::AtEntry(EzArray&lt;EzStr&gt; argcv)
{
    ……
    CMyClass pMyClass = new CMyClass;
    <xsl:choose><xsl:when match=".[class='CForm']">
    /* <a class="method" href="../../../../car/car_file/inline_func/MyMainForm.htm">MyMainForm</a> return the class smartpointer
     * pointed to CForm object. Invoke <A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler</A> to registor
     * CForm object <xsl:value-of select="event"/> event handler My<xsl:value-of select="event"/>
     */
    MyMainForm().Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:when><xsl:when match=".[class='CGraphics']">
    /* <a class="method" href="../../../../car/car_file/inline_func/MyMainGraphics.htm">MyMainGraphics</a> return the smartpointer
     * pointed to CGraphics object. Invoke <A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler</A> to registor
     * <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event handler My<xsl:value-of select="event"/>
     */
    MyMainGraphics().Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:when><xsl:otherwise>
    /* m_<xsl:value-of select="class"/> is the member of <xsl:value-of select="event"/>Demo class，and it is the class smartpointer
     * pointed to <xsl:value-of select="class"/> object. Invoke <A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler</A> to registor
     * <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event handler My<xsl:value-of select="event"/>.
     */
    m_<xsl:value-of select="class"/>.Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:otherwise></xsl:choose>
    ……
}

ECODE <xsl:value-of select="event"/>Demo::AtExit()
{
    ……
    CMyClass pMyClass = new CMyClass;
    <xsl:choose><xsl:when match=".[class='CForm']">
    /* Invoke <A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler</A> to cancel CForm object <xsl:value-of select="event"/> event
     * handler My<xsl:value-of select="event"/>.
     */
    MyMainForm().Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:when><xsl:when match=".[class='CGraphics']">
    /* Invoke <A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler</A> to cancel <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event
     * handler My<xsl:value-of select="event"/>.
     */
    MyMainGraphics().Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:when><xsl:otherwise>
    /* Invoke <A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute><xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler</A> to cancel <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event
     * handler My<xsl:value-of select="event"/>.
     */
    m_<xsl:value-of select="class"/>.Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(pMyClass, &amp;CMyClass::My<xsl:value-of select="event"/>));</xsl:otherwise></xsl:choose>
    ……
}
</pre>

<pre class="codeview">
/*
 * For example：My<xsl:value-of select="event"/> is the <xsl:value-of select="event"/> event handler difined by user, and My<xsl:value-of select="event"/> is
 * normal function, use the second constructor.
 */

ECODE __stdcall My<xsl:value-of select="event"/>(<xsl:for-each select="syntax/parameters/api_param/param_func/func_param">
            /* [in] */ <xsl:value-of select="fp_type"/><xsl:value-of select="fp_name"/><xsl:if test="context()[not(end())]"><span style="color:black; font-size:110%">,</span></xsl:if>
        </xsl:for-each>)
{
    ……
    // Add the code of My<xsl:value-of select="event"/> event handler here
    ……
}

ECODE <xsl:value-of select="event"/>Demo::AtEntry(EzArray&lt;EzStr&gt; argcv)
{
    ……<xsl:choose><xsl:when match=".[class='CForm']">
    /* MyMainForm returns the class smartpointer pointed to CForm object. Invoke
     * <xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler to registor CForm object <xsl:value-of select="event"/> event handler
     * My<xsl:value-of select="event"/>.
     */
    MyMainForm().Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:when><xsl:when match=".[class='CGraphics']">
    //MyMainGraphics returns the class smartpointer pointed to CGraphics object.
    //Invoke <xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler to registor <xsl:value-of select="class"/> object <xsl:value-of select="event"/> event handler My<xsl:value-of select="event"/>
    MyMainGraphics().Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:when><xsl:otherwise>
    /* m_<xsl:value-of select="class"/> is the member of <xsl:value-of select="event"/>Demo class, and it is the smartpointer pointed
     * to <xsl:value-of select="class"/> object. Invoke <xsl:value-of select="class"/>Ref::Add<xsl:value-of select="event"/>Handler to registor <xsl:value-of select="class"/>
     * object <xsl:value-of select="event"/> event handler  My<xsl:value-of select="event"/>.
     */
    m_<xsl:value-of select="class"/>.Add<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:otherwise></xsl:choose>
    ……
}

ECODE <xsl:value-of select="event"/>Demo::AtExit()
{
    ……<xsl:choose><xsl:when match=".[class='CForm']">
    /* Invoke <xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler to cancel the main form object <xsl:value-of select="event"/>
     * event handler My<xsl:value-of select="event"/>.
     */
    MyMainForm().Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:when><xsl:when match=".[class='CGraphics']">
    /* Invoke <xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler to cancel <xsl:value-of select="class"/> object <xsl:value-of select="event"/>
     * event handler My<xsl:value-of select="event"/>.
     */
    MyMainGraphics().Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:when><xsl:otherwise>
    /* Invoke <xsl:value-of select="class"/>Ref::Remove<xsl:value-of select="event"/>Handler to cancel <xsl:value-of select="class"/> object <xsl:value-of select="event"/>
     * event handler My<xsl:value-of select="event"/>.
     */
    m_<xsl:value-of select="class"/>.Remove<xsl:value-of select="event"/>Handler(<xsl:value-of select="class"/><xsl:value-of select="event"/>Handler(&amp;My<xsl:value-of select="event"/>));</xsl:otherwise></xsl:choose>
    ……
}
</pre>

    <h4> See Also </h4>
        <p style="text-align:left"><A class="method"><xsl:attribute name="href">Add<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Add<xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href">Remove<xsl:value-of select="event"/>Handler.htm</xsl:attribute>Remove<xsl:value-of select="event"/>Handler</A><A class="method"><xsl:attribute name="href"><xsl:value-of select="eventpath"/>.htm</xsl:attribute><xsl:value-of select="event"/></A></p>
</xsl:template>


<xsl:template match="Instantiate">

    <xsl:choose>
    <xsl:when match=".[volume='Elastos Filesystem Class Library']">
    <p>Create <xsl:value-of select="class"/> object, and make the correlative class smartpointer pointed to the object.</p>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">ECODEInstantiate(</TD>
        </TR>
        <TR valign="top">
            <TD width="8%"></TD>
            <TD><font class="datatype">DWORD</font></TD>
            <TD class="param">dwClsContext</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div>
    </xsl:when>
    <xsl:otherwise>
    <p>Create <xsl:value-of select="class"/> object, and make the correlative class smartpointer pointed to the object. This method has two syntax, as follows:</p>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">ECODEInstantiate(</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div><br/>

    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">ECODEInstantiate(</TD>
        </TR>
        <TR valign="top">
            <TD width="8%"></TD>
            <TD><font class="datatype">DWORD</font></TD>
            <TD class="param">dwClsContext</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div>
    </xsl:otherwise>
    </xsl:choose>

    <H4>Parameters</H4>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">dwClsContext</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">Specify the relative place of object and client, the list of parameters as follow:</font></DD><BR/><BR/>
            <TABLE class="agility_table" cellspacing="0" cellpadding="0">
                <THEAD class="head">
                    <TD class="cell">Parameter Value</TD>
                    <TD class="cell">Description</TD>
                </THEAD>
                <xsl:choose>
                <xsl:when match=".[volume='Elastos Filesystem Class Library']">
                <TR>
                    <TD class="cell">CTX_KERN_DOMAIN</TD>
                    <TD class="cell">The object and the client in different domain, and the object in kernel</TD>
                </TR>
                </xsl:when>
                <xsl:otherwise>
                <TR>
                    <TD class="cell">CTX_SAME_DOMAIN</TD>
                    <TD class="cell">The object and the client in same domain</TD>
                </TR>
                <TR>
                    <TD class="cell">CTX_DIFF_DOMAIN</TD>
                    <TD class="cell">The object and the client in diff domain, but in same process</TD>
                </TR>
                <TR>
                    <TD class="cell">CTX_DIFF_PROCESS</TD>
                    <TD class="cell">The object and the client in diff domain, but in same machine</TD>
                </TR>
                <TR>
                    <TD class="cell">CTX_DIFF_MACHINE</TD>
                    <TD class="cell">The object and the client in different machine</TD>
                </TR>
                </xsl:otherwise>
                </xsl:choose>
            </TABLE><BR/><BR/>
            <xsl:choose>
                <xsl:when match=".[volume='Elastos Graphics Class Library']">
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">For additional information, see <a class="method" href="../../../../car/code_running_env.htm">context</a>. </font></DD>
                </xsl:when>
                <xsl:otherwise>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">For additional information, see <a class="method" href="../../../car/code_running_env.htm">context</a>. </font></DD>
                </xsl:otherwise>
            </xsl:choose>
        </DL>

    <h4>Return Value</h4>
        <p>The list of return value as follow:</p>
        <p><TABLE class="agility_table" cellspacing="0" cellpadding="0">
            <THEAD class="head">
                <TD class="cell">Return Value</TD>
                <TD class="cell">Description</TD>
            </THEAD>
            <TR>
                <TD class="cell">S_OK</TD>
                <TD class="cell">The method succeeded. </TD>
            </TR>
            <TR>
                <TD class="cell">CO_S_NOTALLINTERFACES</TD>
                <TD class="cell">At least one, but not all, of the interfaces requested in the class were successfully retrieved. </TD>
            </TR>
            <TR>
                <TD class="cell">E_NOINTERFACE</TD>
                <TD class="cell">All of the interfaces requested in the class were not successfully retrieved.</TD>
            </TR>
        </TABLE></p>
        <xsl:choose>
            <xsl:when match=".[volume='Elastos Graphics Class Library']">
                <p>For additional information about ECODE, see <a class="method" href="../../../../elatypes/hresult.htm">ECODE</a> in the Introduction.</p>
            </xsl:when>
            <xsl:otherwise>
                <p>For additional information about ECODE, see <a class="method" href="../../../elatypes/hresult.htm">ECODE</a> in the Introduction.</p>
            </xsl:otherwise>
        </xsl:choose>

    <h4>Remarks</h4>
        <xsl:choose>
        <xsl:when match=".[volume='Elastos Filesystem Class Library']">
        <p>When user create object of file system, user mast specify that parameter dwClsContext's value is CTX_KERN_DOMAIN.</p>
        </xsl:when>
        <xsl:otherwise>
        <p>When user disinterest the relative place of the object and the client, choose the first syntex which needn't parameter. The system's default value is one of CTX_SAME_DOMAIN, CTX_DIFF_DOMAIN and CTX_DIFF_PROCESS, the relative place of the object and the client are confirm by PRI.</p>
        <p>When user interest the relative place of the object and the client, choose the second syntex which need parameter. </p>
        </xsl:otherwise>
        </xsl:choose>

    <xsl:apply-templates select="requirements"/>

    <h4>See Also</h4>
        <p style="text-align:left"><A class="method"><xsl:attribute name="href">../<xsl:value-of select="class"/>.htm</xsl:attribute><xsl:value-of select="class"/></A></p>
</xsl:template>

<xsl:template match="IsValid">
    <p>Judge whether <xsl:value-of select="class"/>'s smartpointer is valid.</p>

    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <TR valign="top">
                <TD colspan="5" class="datatype">BOOLIsValid(</TD>
            </TR>
            <TR>
                <TD colspan="5" class="datatype">);</TD>
            </TR>
        </TABLE>
    </div>

    <H4>Parameters</H4>
        <P>(NULL)</P>

    <h4>Return Value</h4>
        <p>This method return TRUE if <xsl:value-of select="class"/>'s smartpointer is valid, else return FALSE.</p>

    <h4>Remarks</h4>
        <p>Before using class smartpointer, you mast make sure that it is valid. Only valid class smartpointer can be used to invoke all methods of correlative class. If the class smartpointer isn't instantiated by Instantiate method, then need invoke IsValid to judge whether
the class smartpointer is valid. </p>
        <p>The first case: When class smartpointer is transfered to function as parameter, need invoke IsValid to judge its validity. For example: </p>
        <pre class="codeview">
void Foo(<xsl:value-of select="class"/>Ref&amp; senderRef)
{
    if (!senderRef.IsValid()) { //Invoke IsValid to judge the class smartpointer senderRef's validity.
        assert(0 &amp;&amp; "senderRef is invalid.");
        return;
    }
    ……
}
</pre>
        <p>The second case: When class smartpointer is switch by invoke i2i function, need invoke IsValid to judge its validity. For example: </p>
        <pre class="codeview">
<xsl:value-of select="class"/>Ref c<xsl:value-of select="class"/>Ref;

//There is interface smartpointer IXXXRef pointed to <xsl:value-of select="class"/> object, then you may get correlative class smartpointer though the interface smartpointer.
<xsl:value-of select="class"/>Ref c<xsl:value-of select="class"/>Ref = i2i(IXXXRef);

if (!c<xsl:value-of select="class"/>Ref.IsValid()) { //Invoke IsValid to judge class smartpointer c<xsl:value-of select="class"/>Ref's validity.
    assert(0 &amp;&amp; "c<xsl:value-of select="class"/>Ref" is invalid.");
    return 1;
}
</pre>

    <xsl:apply-templates select="requirements"/>
</xsl:template>

<xsl:template match="operator">
    <p>Judge whether <xsl:value-of select="class"/>'s class smartpoint and the appointed class smartpoint point to the same object. </p>

    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
        <TR valign="top">
            <TD colspan="5" class="datatype">BOOLoperator ==(</TD>
        </TR>
        <TR valign="top">
            <TD width="8%"></TD>
            <TD><font class="datatype">const <xsl:value-of select="class"/>Ref&amp;</font></TD>
            <TD class="param">cRef</TD>
        </TR>
        <TR>
            <TD colspan="5" class="datatype">);</TD>
        </TR>
        </TABLE>
    </div>

    <H4>Parameters</H4>
        <DL>
            <DT class="param" style="color:#222222;margin-left:42">cRef</DT>
            <DD style="margin-left:80"><font style="font-weight:normal;font-style:normal;color:black">appointed class smartpointer</font></DD>
        </DL>

    <h4>Return Value</h4>
        <p>If both class smartpointers point to the same object, return TRUE; else, return FALSE.</p>

    <xsl:apply-templates select="requirements"/>

    <h4>Example</h4>
        <pre class="codeview">
//g_<xsl:value-of select="class"/> is the class smartpointer pointed to <xsl:value-of select="class"/> object.
<xsl:value-of select="class"/>Ref g_<xsl:value-of select="class"/>;

void Foo(<xsl:value-of select="class"/>Ref&amp; senderRef)
{
    if (!senderRef.IsValid()) { //Invoke IsValid to judge whether class smartpointer senderRef is valid.
        assert(0 &amp;&amp; "senderRef is invalid.");
        return;
    }

    if (senderRef == g_<xsl:value-of select="class"/>) { //Judge whether class smartpointer senderRef and g_<xsl:value-of select="class"/> point to the same object.
        ……
        return;
    }
    ……
}
</pre>
</xsl:template>

<xsl:template match="requirements">
    <h4>Requirments</h4>
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

<xsl:template match="syntax">
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <TR valign="top">
                    <TD colspan="5" class="datatype">
                    <xsl:if test="return_val[.$ge$' ']">
                        <xsl:value-of select="return_val"/>
                    </xsl:if>
                    <xsl:choose>
                    <xsl:when test="method_name[.$ge$' ']">
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
                    <TD><xsl:if test="param_inout[.$ge$' ']">/* <xsl:value-of select="param_inout"/> */</xsl:if><font class="datatype"><xsl:value-of select="param_type"/></font></TD>
                    </xsl:when>
                    </xsl:choose>
                    <xsl:choose>
                        <xsl:when test="param_func">
                            <TD><xsl:apply-templates select="param_func"/></TD>
                        </xsl:when>
                        <xsl:otherwise>
                            <TD class="param"><xsl:value-of select="param_name"/><xsl:if test="context()[not(end())]"><span style="color:black; font-size:110%">,</span></xsl:if></TD>
                        </xsl:otherwise>
                    </xsl:choose>
                </TR>
            </xsl:for-each>
            <TR>
                <TD colspan="5" class="datatype">);</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
    <div class="proto">
        <TABLE cellspacing="3" cellpadding="2" style="font-size:90%">
            <TR valign="top">
                    <TD colspan="5" class="datatype">
                    <xsl:choose>
                    <xsl:when test="method_name[.$ge$' ']">
                    <xsl:value-of select="method_name"/>
                    </xsl:when>
                    <xsl:otherwise>
                    <xsl:value-of select="/manpage/method | /manpage/macro"/>
                    </xsl:otherwise>
                    </xsl:choose>
                (</TD>
            </TR>
            <xsl:for-each select="parameters/api_param">
                <xsl:if test="param_func[.$ge$' ']">
                <TR valign="top">
                    <TD width="8%"></TD>
                    <xsl:choose>
                    <xsl:when test="param_type">
                    <TD><xsl:if test="param_inout[.$ge$' ']">/* <xsl:value-of select="param_inout"/> */</xsl:if><font class="datatype"><xsl:value-of select="param_type"/></font></TD>
                    </xsl:when>
                    </xsl:choose>
                    <xsl:choose>
                        <xsl:when test="param_func">
                            <TD><xsl:apply-templates select="param_func"/></TD>
                        </xsl:when>
                    </xsl:choose>
                </TR>
                </xsl:if>
            </xsl:for-each>
            <TR>
                <TD colspan="5" class="datatype">);</TD>
            </TR>
        </TABLE>
    </div>
    <br/>
</xsl:template>

<xsl:template match="param_func">
    <TABLE style="font-size:90%">
        <TR>
        <TD>(
        <xsl:choose>
            <xsl:when test="func_return">
                <xsl:value-of select="func_return"/>
            </xsl:when>
        </xsl:choose>
        </TD>

        <TD>
        <xsl:choose>
            <xsl:when test="func_name">
                <font class="param"><xsl:value-of select="func_name"/></font>
            </xsl:when>
        </xsl:choose>) (
        </TD>
        </TR>

    <xsl:for-each select="func_param">
    <TR valign="top">
    <xsl:choose>
    <xsl:when test="fp_type">
        <TD>/*<xsl:value-of select="fp_inout"/>*/<xsl:value-of select="fp_type"/></TD>
    </xsl:when>
    </xsl:choose>
    <xsl:choose>
        <xsl:when test="fp_name">
            <TD><xsl:value-of select="fp_name"/><xsl:if test="context()[not(end())]"><span style="color:black; font-size:110%">,</span></xsl:if></TD>
        </xsl:when>
    </xsl:choose>
    </TR>
    </xsl:for-each>
    <TR>
    <TD>)</TD>
    </TR>
    </TABLE>
</xsl:template>

</xsl:stylesheet>