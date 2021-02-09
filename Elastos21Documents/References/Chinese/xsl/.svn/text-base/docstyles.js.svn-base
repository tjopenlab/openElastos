//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
var advanced = true;
var elaexist = true;
var elapath = "";

document.write("<link rel='stylesheet' href='/xsl/docdemo.css' type='text/css'>");
document.write("<SCRIPT LANGUAGE='VBSCRIPT' src='/xsl/samplemenu.vbs'></SCRIPT>");
function footer(lang){
document.write("<br/><br/><hr width='90%' size='1' align='center'>");
if (lang == "chinese"){
    document.write("<div align='center'><a class='style1' href='/copyright.htm' style='font-size:80%;font-style:italic'>上海科泰世纪科技有限公司 2000年--2008年 版权所有&copy;</a><p></p></div>");
}
else if (lang == "english"){
    document.write("<div align='center'><a class='style1' href='/copyright.htm' style='font-size:80%;font-style:italic'>Copyright &copy; 2000--2008 Koretide Corp. All Rights Reserved.</a><p></p></div>");
}
else if (lang == "KoreTide"){
    document.write("<div style='font-size:75%;font-family:times new roman;font-style:italic;color:555555;text-align:center'><a class='style1' href='http://www.kortide.com.cn'>上海科泰世纪科技有限公司</a>（技术服务: <a href='mailto:support@kortide.com.cn' class='style1'>support@kortide.com.cn</a>）</div><p></p>");
}
else if (lang == "english,KoreTide") {
    document.write("<div style='font-size:75%;font-family:times new roman;font-style:italic;color:555555;text-align:center'><a class='style1' href='http://www.kortide.com.cn'>Kortide Corp.</a> (Technical Support: <a href='mailto:support@kortide.com.cn' class='style1'>support@kortide.com.cn</a>) </div><p></p>");
}
else if (lang == "e_KoreTide") {
    document.write("<div style='font-size:75%;font-family:times new roman;font-style:italic;color:555555;text-align:center'><a class='style1' href='http://www.kortide.com.cn'>Kortide Corp.</a> (Technical Support: <a href='mailto:support@kortide.com.cn' class='style1'>support@kortide.com.cn</a>) </div><p></p>");
}
else {
    document.write("<div align='center'><a class='style1' href='/copyright.htm' style='font-size:80%;font-style:italic'>Copyright &copy; 2000-2008,  Kortide Corp.  All Rights Reserved.</a><p></p></div>");
}
}

function runSample(ops){
    if ((advanced & elaexist) || b_ReadPath()) {
        if ((elapath != "") || b_ReadPath()){
            var line, path;
            path = document.all.smppath.innerText;
            switch (ops){
                case 1: line = "explorer " + elapath + "src\\Elastos20.Hlp\\samples\\" + path;
                        b_RunSample(line);
                        break;
                case 2: line = "\"" + elapath + "build\\misc\\ElastosSDK NT.DBG.lnk\"";
                        line = line + " & cd Elastos20.Hlp\\samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 3: line = "\"" + elapath + "build\\misc\\ElastosSDK NT.RLS.lnk\"";
                        line = line + " & cd Elastos20.Hlp\\samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 4: line = "\"" + elapath + "build\\misc\\ElastosSDK X86.DBG.lnk\"";
                        line = line + " & cd Elastos20.Hlp\\samples\\" + path + " & cls ";
                        b_RunSample(line);
                        break;
                case 5: line = "\"" + elapath + "build\\misc\\ElastosSDK X86.RLS.lnk\"";
                        line = line + " & cd Elastos20.Hlp\\samples\\" + path + " & cls ";
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
//    document.write("<PARAM name='Button' value='Text:浏览或编译运行范例' style='font-size:20;font-style:italic;bgcolor:000066;text-align:center' WIDTH=400 HEIGHT=500>");
    document.write("<PARAM name='Item1' value='浏览范例;javascript:runSample(1); ' >");
    document.write("<PARAM name='Item2' value='在ElastosSDK NT.DBG环境下编译;javascript:runSample(2); ' >");
    document.write("<PARAM name='Item3' value='在ElastosSDK NT.RLS环境下编译;javascript:runSample(3); ' >");
    document.write("<PARAM name='Item4' value='在ElastosSDK X86.DBG环境下编译;javascript:runSample(4); ' >");
    document.write("<PARAM name='Item5' value='在ElastosSDK X86.RLS环境下编译;javascript:runSample(5); ' >");
    document.write("</OBJECT>");
}

function showButton_e() {
    var osmppath = document.all.item("smppath");
    if (osmppath == null) return;
    document.write("<OBJECT id='smpmenu'  type='application/x-oleobject'  classid='clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11'>");
    document.write("<PARAM name='Command' value='Related Topics, menu'>");
    document.write("<PARAM name='Button' value='Text:Browse or compile example' style='font-size:20;font-style:italic;bgcolor:000066;text-align:center' WIDTH=400 HEIGHT=500>");
    document.write("<PARAM name='Item1' value='Browse example;javascript:runSample(1); ' >");
    document.write("<PARAM name='Item2' value='Compile example in ElastosSDK NT.DBG environment;javascript:runSample(2); ' >");
    document.write("<PARAM name='Item3' value='Compile example in ElastosSDK NT.RLS environment;javascript:runSample(3); ' >");
    document.write("<PARAM name='Item4' value='Compile example in ElastosSDK X86.DBG environment;javascript:runSample(4); ' >");
    document.write("<PARAM name='Item5' value='Compile example in ElastosSDK X86.RLS environment;javascript:runSample(5); ' >");
    document.write("</OBJECT>");
}

function showSample() {
    var osmppath = document.all.item("smppath");
    if (osmppath == null) return;
    document.write("<A href='javascript:runSample(1)' class='smplink' title='Browse the sample in Windows Explorer'>Sample</A>");
}
