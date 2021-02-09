#==========================================================================
# Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
#==========================================================================
#
# File:     $/Elastos.Dev/build/misc/html2chm.pl
# Purpose:  This program is used to generate three files
#           (1) $outFile.hhp -- project file
#           (2) $outFile.hhc -- content file
#           (3) $outFile.hhk -- inFile file
#           These three files are essential to generate $outFile.chm.  The $inFile
#           is an input file that defines indices and topics for the $outFile.chm
# Usage:    perl htm2chm.pl [-i | -o] inFile outFile
# Author:
# Date:     2001-12-2
#
#==========================================================================


if( scalar(@ARGV) < 3 ) {
    print "Usage:perl htm2chm.pl [-i | -o] inFile outFile\n";
    exit(-1);
}

exit(1) if (checkIdx($ARGV[1]) > 0);

if ($ARGV[0] eq "-i") {
    printIndex($ARGV[1], $ARGV[2]);
} else {
    printHh($ARGV[1], $ARGV[2]);
    generatChm("$ARGV[2].hhp");
}

exit(0);

# 生成 chm 帮助文件
sub generatChm
{
    my $hhpFile = shift;
    my $hhcRet;

    $hhcRet = system("hhc", $hhpFile);
}

sub printIndex
{
    my $inFile = shift;
    my $outFile = shift;
    open(FDIN, "<$inFile")|| die "Could not open file: $inFile\n";
    open(FDOUT, ">>$outFile")|| die "Could not open file: $outFile\n";

    while ($line = <FDIN>) {
        $line =~ s/^/  /;
        print FDOUT $line;
    }
    close(FDIN);
    close(FDOUT);
}

sub printHh
{
    my $inFile = shift;
    my $outFile = shift;

    open(FDFORMAT,"<$inFile")|| die "Could not open file: $inFile\n";
    open(FDHHP,">$outFile.hhp") || die "Could not open file: $outFile.hhp\n";
    open(FDHHC,">$outFile.hhc") || die "Could not open file: $outFile.hhc\n";
    open(FDHHK,">$outFile.hhk") || die "Could not open file: $outFile.hhk\n";

    my $linehhk;
    my $linehhc;
    my $linefrm;

    $linehhk = "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">
    <HTML>
    <HEAD>
    <meta name=\"GENERATOR\" content=\"Microsoft&reg; HTML Help Workshop 4.1\">
    <!-- Sitemap 1.0 -->
    </HEAD><BODY>
    <UL>";

    $linehhc = "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">
    <HTML>
    <HEAD>
    <meta name=\"GENERATOR\" content=\"Microsoft&reg; HTML Help Workshop 4.1\">
    <!-- Sitemap 1.0 -->
    </HEAD><BODY>
    <OBJECT type=\"text/site properties\">
        <param name=\"Window Styles\" value=\"0x800025\">
    </OBJECT>
    <UL>
    ";

    print FDHHK $linehhk;
    print FDHHC $linehhc;

    # $str[0] : title
    # $str[1] : index
    # $str[2] : filename
    my $degreethis = 0;
    my $degreelast = 0;
    my $filename;
    my $pathname;
    my $location = "Zyco帮助";
    my @str;
    my $isindex = 0;
    while ($linefrm = <FDFORMAT>) {
        next if ($linefrm =~m"^#");   # if not two ',' in this line go to next line
        next if ($linefrm =~m"^(\s+)$");
        if ($linefrm =~ m"^\[") {
            if ($linefrm =~ m"\[FILES\]") {
                $isindex = 1;
            }
            else {
                if ($linefrm =~ m"\[OPTIONS\]" || $linefrm =~ m"\[WINDOWS\]") {
                    $isindex = 0;
                }
            }
        }
        if ($isindex == 0) {
            print FDHHP $linefrm;
            next;
        }

        @commanum=($linefrm =~m","g);
        if (scalar(@commanum) == 0) { # 模板文件
            print FDHHP $linefrm;
            next;
        }
        $linefrm =~ s/\n$//g;

        @str = split(',',$linefrm);
        if ($str[0] =~m"^(\s+)(\S)(.*)"){
            $degreethis = length($1) / 2;
            $str[0] = $2.$3;
        }
        else {
            $degreethis = 0;
        }

        $str[2] = $2 if ($str[2] =~m"(\s+)(\S+)");
        $filename = $str[2];

		#以前是在这里写hhp的，现在移到pei modify后面
        # wirte to file:$outFile.hhp
        #print FDHHP $filename;
        #print FDHHP "\n";
        
        # wirte to file:$outFile.hhk
        $str[1] = $2.$3 if ($str[1] =~m"(\s+)(\S)(.*)");
        
        #pei modify it
        #只要字符串中有&就算
        if ($filename =~ m/&/) {
        	
        	my $line_inc = "";
        	my $str2 = "<param name=\"Local\" value=\"";
        	
        	#filename需要去掉前面的“&”和尾空格
        	#chomp($filename);
        	$filename = substr($filename,1);
        	$pathname = substr($filename, 0, rindex($filename, "\\")+1);
        	my $str3 = "$str2"."$pathname";
        	
        	open(INC_HHK, "<$filename".".hhk") || die "& included file error: $filename";
        	open(INC_HHP, "<$filename".".hhp") || die "& included file error: $filename";
        	open(INC_HHC, "<$filename".".hhc") || die "& included file error: $filename";
        	
        	print "\nMeet an included package: $str[0]";
        	print "\n";
        	
        	#added 2008.1.22
        	$span = $degreethis - $degreelast;
        	if ($span < 0) {
            	for ($i = 0; $i > $span; $i--) {
                	print FDHHC "\n</UL>";
            	}
        	}
        	if ($span > 0) {
            	print FDHHC "\n<UL>";
        	}
        	$degreelast = $degreethis;

        	#$filename = $filename.".html";
        	#print FDHHC "</UL>";
        	print FDHHC "\n       <LI> <OBJECT type=\"text/sitemap\">
            <param name=\"Name\" value=\"".$str[0]."\">
            <param name=\"local\" value=\"".$pathname."index.html\">
            </OBJECT>
            ";
        	
        	#process the hhk file
        	#skip line to <UL> until </BODY>
        	#---------------------------------------------
        	while( $line_inc = <INC_HHK> ) {
        		if ($line_inc =~ m"<UL>") {
        			last;
        		}
        	}
        	print FDHHK "<UL>";
        	while( $line_inc = <INC_HHK> ) {
        		if ($line_inc =~ m"<BODY>") {
        			last;
        		}
        		print FDHHK $line_inc;
        	}
        	close(INC_HHK);
        	
        	#the same to hhc file
        	#skip line to <UL> until </BODY>
        	#---------------------------------------------
        	while( $line_inc = <INC_HHC> ) {
        		if ($line_inc =~ m"<UL>") {
        			last;
        		}
        	}
        	print FDHHC "<UL>";
        	while( $line_inc = <INC_HHC> ) {
        		if ($line_inc =~ m"</BODY>") {
        			last;
        		}
        		
        		$line_inc =~ s/$str2/$str3/;
        		print FDHHC $line_inc;
        	}
        	close(INC_HHC);
        	 
        	#hhp file
        	#--------------------------------------------
        	while( $line_inc = <INC_HHP> ) {
        		if ($line_inc =~ m"\[FILES\]") {
        			last;
        		}
        	}
        	while( $line_inc = <INC_HHP> ) {
        		if ($line_inc =~ m"^\[") {
        			last;
        		}
        		#同样的路径，不同的文件名
        		print FDHHP "$pathname"."$line_inc";
        	}
        	close(INC_HHP);
                    	
        	next;
        }
        #END of pei modify it
        
        # wirte to file:$outFile.hhp
        print FDHHP $filename;
        print FDHHP "\n";


        if ($filename eq "") {
            print FDHHK "\n       <LI> <OBJECT type=\"text/sitemap\">
            <param name=\"Name\" value=\"".$str[1]."\">
            </OBJECT>";
        }
        else {
            if ($str[1] =~m";") {
                @strindex = split(';',$str[1]);
                for ($i = 0; $i < @strindex; $i++) {
                   print FDHHK "\n       <LI> <OBJECT type=\"text/sitemap\">
                <param name=\"Name\" value=\"".$strindex[$i]."\">
                <param name=\"Name\" value=\"".$location."\">
                <param name=\"local\" value=\"".$filename."\">
                </OBJECT>";
                }
            }
            else {
                print FDHHK "\n       <LI> <OBJECT type=\"text/sitemap\">
                <param name=\"Name\" value=\"".$str[1]."\">
                <param name=\"Name\" value=\"".$location."\">
                <param name=\"local\" value=\"".$filename."\">
                </OBJECT>";
            }
        }

        # wirte to file:$outFile.hhc
        $span = $degreethis - $degreelast;
        if ($span < 0) {
            for ($i = 0; $i > $span; $i--) {
                print FDHHC "\n</UL>";
            }
        }
        if ($span > 0) {
            print FDHHC "\n<UL>";
        }
        print FDHHC "\n       <LI> <OBJECT type=\"text/sitemap\">
            <param name=\"Name\" value=\"".$str[0]."\">
            <param name=\"local\" value=\"".$filename."\">
            </OBJECT>
            ";

        $degreelast = $degreethis;
    }

    print FDHHP "\n\n[INFOTYPES]";

    print FDHHK "\n</UL>\n";
    print FDHHK "</BODY>\n</HTML>";

    if ($degreethis > 0) {
        for ($i = 1; $i <= $degreethis; $i++) {
            print FDHHC "\n       </UL>";
        }
    }
    print FDHHC "\n</UL>\n";
    print FDHHC "</BODY>\n</HTML>";


    close(FDFORMAT);
    close(FDHHP);
    close(FDHHK);
    close(FDHHC);
}

# To check whether the blanks of the start of the line is even(2x);
sub checkIdx
{
    $inFile = shift;
    my $errorflag = 0;
    my $line;
    my $linenum = 0;
    my $isindex = 0;

    open(FDFORMAT,"<$inFile")|| die "Could not open file: $inFile\n";
    print "Checking Index file : $inFile......\n";

    while ($line = <FDFORMAT>) {
        $linenum = $linenum + 1;
        next if($line =~m"^#");
        if ($line =~ m"^\[") {
            if ($line =~ m"\[FILES\]") {
                $isindex = 1;
            }
            else {
                if ($line =~ m"\[OPTIONS\]" || $line =~ m"\[WINDOWS\]") {
                    $isindex = 0;
                }
                else {
                    $errorflag = 1;
                }
            }
        }
        next if ($isindex == 0);

        if ($line =~m"^(\s+)\S") {
            my $len = length($1);
            if ($line =~m"\t") {
                print "Line ".$linenum." :Tab is not allowed in input file!!!\n";
                print $line;
                $errorflag = 1;
            }
            if (($len % 2) != 0) {
                print "Line ".$linenum." :There are $len blanks at the start of this line!!!\n";
                print $line;
                $errorflag = 1;
            }
        }
        @commanum=($line =~m","g);
        next if (scalar(@commanum) == 0); # 模板文件，没有','
        if (scalar(@commanum) != 2) {
            print "Line ".$linenum." :There must be exactly two ','s per line!!!\n";
            print $line;
            $errorflag = 1;
        }

    } # while ($line = <FDFORMAT>)
    close(FDFORMAT);

    if ($errorflag == 1) {  #if check error exit;
        print "Found errors in file $inFile!!!\n";
    }

    return($errorflag);
}
