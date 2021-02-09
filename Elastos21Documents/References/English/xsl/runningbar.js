//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
var ie4 = false;
var advanced = false;
var elaexist = true;
var elapath = "";

if (navigator.appName == "Microsoft Internet Explorer") {
    var ver = navigator.appVersion;
    var v = new Number(ver.substring(0,ver.indexOf(".", 0)));
    if (v >= 4) {
        advanced = true;
        ie4 = true;

        // Look for 5.x buried somewhere in the version string.
        var toks = ver.split(/[^0-9.]/);
        if (toks) {
            for (var i = 0; i < toks.length; i++) {
                var tok = toks[i];
                if (tok.indexOf(".", 0) > 0) {
                    if (tok >= 5.5)
                        ie4 = false;
                }
            }
        }
    }
}

if (advanced) {
    document.write("<link rel='stylesheet' href='/xsl/common.css'/>");
    window.onload = bodyOnLoad;
}

function bodyOnLoad()
{
    if (advanced & !ie4) {
        resizeBan();
        window.onresize = closeIE4;
    }
}

function closeIE4(){
    resizeBan();  //also resize the non-scrolling banner
    return;
}

function resizeBan(){
//resizes nonscrolling banner
var obanner= document.all.item("nsbanner");
var oText= document.all.item("nstext");
    if (oText ==null) return;
    if (obanner != null){
        document.body.scroll = "no"
        document.all.nstext.style.overflow= "auto";
        document.all.nsbanner.style.width= document.body.offsetWidth-2;
        document.all.nstext.style.width= document.body.offsetWidth-4;
        document.all.nstext.style.top= document.all.nsbanner.offsetHeight-40;
        if (document.body.offsetHeight > document.all.nsbanner.offsetHeight)
                document.all.nstext.style.height= document.body.offsetHeight - (document.all.nsbanner.offsetHeight+4)
        else document.all.nstext.style.height=0
    }
}

function footer(lang){
document.write("<br/><br/><hr width='90%' size='1' align='center'>");
if (lang == "chinese"){
    document.write("<div align='center'><a class='method' href='/copyright.htm' style='font-size:75%;font-style:italic'>��̩���ͿƼ����޹�˾ ��Ȩ���� 2000��--2004��</a><p></p></div>");
}
else if (lang == "KoreTide"){
    document.write("<div style='font-size:75%;font-style:italic;color:555555;text-align:center'><a class='method' href='http://www.koretide.com.cn'>��̩���ͿƼ����޹�˾</a>����������: <a href='mailto:support@koretide.com.cn' class='method'>support@koretide.com.cn</a>��</div><p></p>");
}
else if (lang == "e_KoreTide"){
    document.write("<div style='font-size:75%;font-style:italic;color:555555;text-align:center'><a class='method' href='http://www.koretide.com.cn'>KoreTide Corp. </a> (Technical support: <a href='mailto:support@koretide.com.cn' class='method'>support@koretide.com.cn</a>)</div><p></p>");
}
else {
    document.write("<div align='center'><a class='method' href='/copyright.htm' style='font-size:75%;font-style:italic'>Copyright &copy; 2000-2004,  KoreTide Corp.  All Rights Reserved.</a><p></p></div>");
}
}

function runSample(ops){
    if ((advanced & elaexist) || b_ReadPath()) {
        if ((elapath != "") || b_ReadPath()){
            var line, path;
            path = document.all.smppath.innerText;
            switch (ops){
                case 1: line = "explorer " + elapath + "src\\samples\\" + path;
                        b_RunSample(line);
                        break;
                case 2: line = "\"" + elapath + "build\\misc\\Elastos.SDK.NTOS DBG\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 3: line = "\"" + elapath + "build\\misc\\Elastos.SDK.NTOS RLS\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 4: line = "\"" + elapath + "build\\misc\\Elastos.SDK.IX86 DBG\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 5: line = "\"" + elapath + "build\\misc\\Elastos.SDK.IX86 RLS\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 6: line = "\"" + elapath + "build\\misc\\Elastos.SDK.ARM DBG\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 7: line = "\"" + elapath + "build\\misc\\Elastos.SDK.ARM RLS\"";
                        line = line + " & cd samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                default:
            }
        }
    }
}

function showButton() {
    var osmppath = document.all.item("smppath");
    if (osmppath == null) return;
    document.write("<OBJECT id='smpmenu'  type='application/x-oleobject'  classid='clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11'>");
    document.write("<PARAM name='Command' value='Related Topics, menu'>");
    document.write("<PARAM name='Button' value='Text:�����������з���' style='font-size:20;font-style:italic;bgcolor:000066;text-align:center' WIDTH=400 HEIGHT=500>");
    document.write("<PARAM name='Item1' value='�������;javascript:runSample(1); ' >");
    document.write("<PARAM name='Item2' value='��Elastos.SDK.NTOS DBG�����±���;javascript:runSample(2); ' >");
    document.write("<PARAM name='Item3' value='��Elastos.SDK.NTOS RLS�����±���;javascript:runSample(3); ' >");
    document.write("<PARAM name='Item4' value='��Elastos.SDK.IX86 DBG�����±���;javascript:runSample(4); ' >");
    document.write("<PARAM name='Item5' value='��Elastos.SDK.IX86 RLS�����±���;javascript:runSample(5); ' >");
    document.write("<PARAM name='Item6' value='��Elastos.SDK.ARM DBG �����±���;javascript:runSample(6); ' >");
    document.write("<PARAM name='Item7' value='��Elastos.SDK.ARM RLS �����±���;javascript:runSample(7); ' >");
    document.write("</OBJECT>");
}

function showButton_e() {
    var osmppath = document.all.item("smppath");
    if (osmppath == null) return;
    document.write("<OBJECT id='smpmenu'  type='application/x-oleobject'  classid='clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11'>");
    document.write("<PARAM name='Command' value='Related Topics, menu'>");
    document.write("<PARAM name='Button' value='Text:Browse or compile example' style='font-size:20;font-style:italic;bgcolor:000066;text-align:center' WIDTH=400 HEIGHT=500>");
    document.write("<PARAM name='Item1' value='Browse example;javascript:runSample(1); ' >");
    document.write("<PARAM name='Item2' value='Compile example in Elastos.SDK.NTOS DBG environment;javascript:runSample(2); ' >");
    document.write("<PARAM name='Item3' value='Compile example in Elastos.SDK.NTOS RLS environment;javascript:runSample(3); ' >");
    document.write("<PARAM name='Item4' value='Compile example in Elastos.SDK.IX86 DBG environment;javascript:runSample(4); ' >");
    document.write("<PARAM name='Item5' value='Compile example in Elastos.SDK.IX86 RLS environment;javascript:runSample(5); ' >");
    document.write("<PARAM name='Item6' value='Compile example in Elastos.SDK.ARM DBG environment;javascript:runSample(6); ' >");
    document.write("<PARAM name='Item7' value='Compile example in Elastos.SDK.ARM RLS environment;javascript:runSample(7); ' >");
    document.write("</OBJECT>");
}

function showSample() {
    var osmppath = document.all.item("smppath");
    if (osmppath == null) return;
    document.write("<A href='javascript:runSample(1)' class='smplink' title='Browse the sample in Windows Explorer'>�򿪷�������Ŀ¼</A>");
}

