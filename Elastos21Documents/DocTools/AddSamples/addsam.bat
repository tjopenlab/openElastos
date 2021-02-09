::========================================================================
:: File:    $/Elastos/build/tools/addsam.bat
:: Purpose: Insert sample codes into .xml files
:: Usage:   addsam.bat [OPTION] [FILE ^| DIRECTORY]
:: Date:    2006-12-26
::
:: Depends: GNU sed 4.1.4 (GNUWin32)
::========================================================================
::
:: Assumption:
:: -----------
:: 1. Every page (.xml) is well formatted and may have a sample .cpp file.
:: 2. Every sample (.cpp) contains a "output" section of comment, which
::    holds the output of running
::
:: How it works ?
:: --------------
:: For every page, addsam.bat will:
:: 1. scan the page to find sample location by the <sample> tag
:: 2. split the source file into 'code' and 'output'
:: 3. re-scan the page to locate the <example> tag
:: 4. insert 'code' into <example></example> and insert 'output' after
::    </example> immediately.
::
:: TODO:
:: -----
:: 1. Clean up temporary filename
:: 2. Classify the types of errors for failed pages
:: 3. Choose .xml files more precisely
::    - eliminate orphans (the .xml files do not have entries in .idx file)
:: 4. Code the .bat as a .pl and use a XML parser
::
:: Future TODO:
:: ------------
:: 1. It's better to use some XML technology (for example: "Xinclude" or
::    XSLT's document() function to include the examples files (.cpp). But
::    that need some modifications to the existing .xsl file.
:: 2. xml2html is a VB program and don't bother anything when XSLT error.
::    Consider a new XSLT processor (i.e.: xsltproc)
:: 3. The current .xsl file is MSXML based. While the document process may
::    be emerged into Elastos IDE, which is Java based. So the existing
::    .xsl files may be refined to meet some XSLT's requirements.
::
::==========================================================================

@if "%_echo%"=="" echo off
setlocal

:: Global definitions here
set PROGPATH=%~dp0
set PROGPATH=%PROGPATH:~0,-1%

set SAMPLE_BASE_DIR=D:\Elastos21\Documents\Samples
set SAMPLE_BASE_DIR_SED=%SAMPLE_BASE_DIR:\=\\%
set SAMPLE_BASE_DIR_SED=%SAMPLE_BASE_DIR_SED:.=\.%

set TEMP_DIR=%~d0\%~n0.tmp

set TEMP_XML_LIST=%TEMP_DIR%\%~n0_xml_list.txt
set TEMP_PAIR0=%TEMP_DIR%\%~n0_success0.txt
set TEMP_PAIR=%TEMP_DIR%\%~n0_success.txt
set TEMP_LIST_FAILED=%TEMP_DIR%\%~n0_failed.txt
set TEMP_REPORT=%TEMP_DIR%\%~n0_report.htm
set TEMP_SAMPLE=%TEMP_DIR%\%~n0_sample.txt
set TEMP_RESULT=%TEMP_DIR%\%~n0_result.txt
set TEMP_XML=%TEMP_DIR%\%~n0_xml.txt

:: Process command options
for %%I in (%*) do (
    set ARG=%%I
    rem option started
    if "!ARG:~0,1!"=="-" (
        if "!ARG!"=="-h" (
            call :usage && goto :eof
        ) else if "!ARG:~0,2!"=="-f" (
            if "!ARG:~2!"=="" (
                echo %~nx0: no list file specified>&2
                goto :eof
            ) else (
                set XML_LIST=!ARG:~2!
            )
        ) else if "!ARG:~0,2!"=="-r" (
            set BE_RECURSIVE=true
        ) else (
            echo %~nx0: invalid option -- !ARG:~1!>&2
            goto :eof
        )
    ) else (
        set XML_FILE=!ARG!
    )
)
:options_parse_done

::echo Options:
::set BE_RECURSIVE
::set XML_LIST
::set XML_FILE

echo Making report directory...
mkdir "%TEMP_DIR%" 2>nul

echo Finding pages to be processed...
if not "%XML_FILE%"=="" (
    if not exist "%XML_FILE%" (
        echo %~nx0: %XML_FILE%: No such file or directory>&2
        goto :eof
    )
    set XML_LIST=%TEMP_XML_LIST%
    rem Detect if it is a directory
    dir /b /ad %XML_FILE% >nul 2>nul
    if "!errorlevel!"=="0" (
        if /I "%BE_RECURSIVE%"=="true" (
            1>"!XML_LIST!" call :mydir "%XML_FILE%\*.xml" 1
        ) else (
            1>"!XML_LIST!" call :mydir "%XML_FILE%\*.xml"
        )
    ) else (
        1>"!XML_LIST!" call :mydir "%XML_FILE%" 0
    )
) else if not "%XML_LIST%"=="" (
    if not exist "%XML_LIST%" (
        echo %~nx0: %XML_LIST%: No such file or directory>&2
        goto :eof
    )
    call :list_is_valid "%XML_LIST%"
    if ERRORLEVEL 1 goto :eof
) else (
    call :usage & goto :eof
)

:: TODO: refactoring the code
echo Finding their samples...
findstr /f:%XML_LIST% "<sample " | ^
sed "s/:[ \t]*<sample url=\"/,%SAMPLE_BASE_DIR_SED%\\/;s/\">[ \t]*/\\/;s/[ \t]*<\/sample>[ \t]*$/.cpp/" >"%TEMP_PAIR0%"

del "%TEMP_LIST_FAILED%" 2>nul
touch "%TEMP_LIST_FAILED%"
del "%TEMP_PAIR%" 2>nul
touch "%TEMP_PAIR%"
for /F "tokens=1* delims=," %%I in ('type "%TEMP_PAIR0%"') do (
    if exist %%J (
        >>"%TEMP_PAIR%" echo %%I,%%J
    ) else if exist %%~dpJsamples.cpp @(
        >>"%TEMP_PAIR%" echo %%I,%%~dpJsamples.cpp
    ) else (
        for /F "delims=" %%M in ('dir /ad /b "%%~dpJ" 2^>nul ^| wc -l') do (
            if "%%M"=="0" (
                >>"%TEMP_LIST_FAILED%" echo %%I,%%~dpJ,Bad sample url
            ) else (
                for /F "delims=" %%N in ('dir /b "%%~dpJ*.cpp" 2^>nul ^| wc -l') do (
                    if "%%N"=="1" (
                        for /F "delims=" %%P in ('dir /b "%%~dpJ*.cpp"') do (
                            >>"%TEMP_PAIR%" echo %%I,%%~dpJ%%P
                        )
                    ) else if "%%N"=="0" (
                        if /I "%%~dpJ"=="%SAMPLE_BASE_DIR%\" (
                            >>"%TEMP_LIST_FAILED%" echo %%I,%%~dpJ,No sample specified
                        ) else (
                            >>"%TEMP_LIST_FAILED%" echo %%I,%%~dpJ,No sample found
                        )
                    ) else (
                        >>"%TEMP_LIST_FAILED%" echo %%I,%%~dpJ,More than one sample
                    )
                )
            )
        )
    )
)
del "%TEMP_PAIR0%"

set CD_SED=%CD%
set CD_SED=%CD_SED:\=\\%
set CD_SED=%CD_SED:.=\.%

echo Adding samples to pages...
for /F "tokens=1* delims=," %%I in (%TEMP_PAIR%) do (
    rem (echo Adding %%J&echo     to %%I)|sed "s/%CD_SED%/./I"
    sed -f "%~dp0getcode.sed" %%J | sed -f "%~dp0rmtbl.sed" | call "%~dp0xmlwrap.bat" pre >%TEMP_SAMPLE%
    sed -n -f "%~dp0getres.sed" %%J | call "%~dp0xmlwrap.bat" result >%TEMP_RESULT%
    rem BUG: case-sensitive pattern. Do not rely on it.
    rem "/<example>/Ir file" always make sed crash on some files
    sed -f "%~dp0rmsam.sed" %%I | sed -e "/<example>/r %TEMP_SAMPLE%" -e "/<\/example>/r %TEMP_RESULT%" >%TEMP_XML%
    copy /y %TEMP_XML% %%I >nul
    del %TEMP_XML%
    rem echo.
)

del "%TEMP_XML_LIST%" "%TEMP_PAIR0%" "%TEMP_SAMPLE%" 2>nul
del "%TEMP_RESULT%" "%TEMP_XML%" 2>nul

::echo See %TEMP_PAIR%
if exist %TEMP_LIST_FAILED% (
    echo Dumping list of failed files...
    echo   %TEMP_LIST_FAILED%
)

call :make_report
echo Making reports...
echo   %TEMP_REPORT%
start %TEMP_REPORT%

goto :eof


::========================================================================
:: Procedure:  mydir
:: Purpose:    dir wrapper
:: Parameters: %1 - file/directory name (wildcards are supported)
::             %2 - 1 for recursive, 0 for non-recursive
:: Return:     ERRORLEVEL is 0, if files/directories found
::             ERRORLEVEL is 1, if no files/directories found
::========================================================================
:mydir
setlocal
if "%~1"=="" goto :eof
set BASE_PATH=%~dp1
if "%~2"=="1" (
    dir /b /s "%~1" 2>nul
) else (
    for /F "delims=" %%I in ('dir /b "%~1" 2^>nul') do (
        echo %BASE_PATH%%%I
    )
)
endlocal
goto :eof


::========================================================================
:: Procedure:  list_is_valid
:: Purpose:    test if all the files listed in %1 are exist
:: Parameters: %1 - list file
:: Return:     ERRORLEVEL is 0, if all files are exist
::             ERRORLEVEL is 1, if any file is not exist
::========================================================================
:list_is_valid
for /F "delims=" %%I in ('type "%~1"') do (
    if not exist "%%I" (
        echo %~nx0: %%I: No such file or directory>&2
        goto :eof
    )
)
goto :eof


::========================================================================
:: Procedure:  make_report
:: Purpose:    Generate a neat report
::========================================================================
:: TODO:
:: 1. clean up interface
:: 2. classify errors
::========================================================================
:make_report
setlocal
set REPORT_TITLE=Reports of %~nx0
set REPORT=%TEMP_REPORT%

:: Head
>"%REPORT%"  echo "<html>"
>>"%REPORT%" echo "<head>"
>>"%REPORT%" echo "  <title>%REPORT_TITLE%</title>"
>>"%REPORT%" echo "<head>"
>>"%REPORT%" echo "<body>"
>>"%REPORT%" echo "<h1>%REPORT_TITLE%</h1>"
>>"%REPORT%" echo "<hr>"

:: Summary
>>"%REPORT%" echo "<h2>Summary</h2>"
>>"%REPORT%" echo "<pre style='background:#D9D9D9'>"
::>>"%REPORT%" echo "Running Dir:   %CD%"
::>>"%REPORT%" echo "Command Line:  %0 %*"
>>"%REPORT%" (for /F "delims=" %%I in ('now') do echo "Date and Time: %%I")
>>"%REPORT%" (for /F %%I in ('wc -l "%TEMP_PAIR%"') do echo "<a href='#_success'>Success Files</a>: %%I")
>>"%REPORT%" (for /F %%I in ('wc -l "%TEMP_LIST_FAILED%"') do echo "<a href='#_fail'>Failed  Files</a>: %%I")
>>"%REPORT%" echo "</pre>"
:: Failed pages
>>"%REPORT%" echo "<h2><a name='_fail'></a>Failed files</h2>"
>>"%REPORT%" echo "<table border=1 cellspacing=0 cellpadding=4 width='100%%'>"
>>"%REPORT%" echo "<tr>"
>>"%REPORT%" echo "  <td width='85%%' style='color:#FF0000;background:#D9D9D9'>"
>>"%REPORT%" echo "    <b>Help Page</b>"
>>"%REPORT%" echo "    <hr align=left width='16'>"
>>"%REPORT%" echo "    <b>Samples Path</b>"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "  <td width='15%%' style='color:#FF0000;background:#D9D9D9'>"
>>"%REPORT%" echo "    <b>Error Category</b>"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "</tr>"
for /F "tokens=1-3 delims=," %%I in ('type "%TEMP_LIST_FAILED%"') do (
>>"%REPORT%" echo "<tr>"
>>"%REPORT%" echo "  <td>"
>>"%REPORT%" echo "    <a href="%%I">%%I</a>"
>>"%REPORT%" echo "    <hr align=left width='16'>"
>>"%REPORT%" echo "    <a href="%%J">%%J</a>"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "  <td>"
>>"%REPORT%" echo "    %%K"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "</tr>"
)
>>"%REPORT%" echo "</table>"
:: Successful pages
>>"%REPORT%" echo "<h2><a name='_success'></a>Successful files</h2>"
>>"%REPORT%" echo "<table border=1 cellspacing=0 cellpadding=4 width='100%%'>"
>>"%REPORT%" echo "<tr>"
>>"%REPORT%" echo "  <td style='color:#008000;background:#D9D9D9'>"
>>"%REPORT%" echo "    <b>Help Page</b>"
>>"%REPORT%" echo "    <hr align=left width='16'>"
>>"%REPORT%" echo "    <b>Sample Added</b>"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "</tr>"
for /F "tokens=1,2 delims=," %%I in ('type "%TEMP_PAIR%"') do (
>>"%REPORT%" echo "<tr>"
>>"%REPORT%" echo "  <td>"
>>"%REPORT%" echo "    <a href="%%I">%%I</a>"
>>"%REPORT%" echo "    <hr align=left width='16'>"
>>"%REPORT%" echo "    <a href="%%J">%%J</a>"
>>"%REPORT%" echo "  </td>"
>>"%REPORT%" echo "</tr>"
)
>>"%REPORT%" echo "</table>"
:: Tail
>>"%REPORT%" echo "<br><hr>"
>>"%REPORT%" echo "<i>Generated by %~nx0</i>"
>>"%REPORT%" echo "</body>"
>>"%REPORT%" echo "</html>"
:: Remove surrounding
sed "s/^ *\"//;s/\" *$//" "%REPORT%">"%REPORT%.tmp"
copy /y "%REPORT%.tmp" "%REPORT%" 1>nul
del "%REPORT%.tmp"
endlocal
goto :eof


:usage
echo Copyright (C) Koretide, Inc. 2007. All rights reserved
echo.
echo Usage: %~nx0 [OPTION] [FILE ^| DIRECTORY]
echo Insert sample codes into .xml files.
echo.
echo   -flist     Reads .xml file list from the file specified.
echo   -r         Search .xml in the directory recursively.
echo   -h         Display this help and exit.
echo.
echo If both -flist and FILE ^| DIRECTORY are present, the list will be ignored.
echo Samples are searched in %SAMPLE_BASE_DIR% by default.
echo.
echo The sample source code is indicated by the tag ^<sample^> in .xml files.
echo The script use some simple regexp to match it and may try to make a guess
echo on sample files properly. So manual review are highly recommended before
echo releasing the final .chm.
echo.
echo Examples:
echo   %~nx0 -r Elastos21.Hlp\Chinese      Process all .xml recursively
echo   %~nx0 -faddsam_failed.txt           Process all unsolved .xml files
echo   %~nx0 crt_library\stdio             Process all .xml in a directory
echo   %~nx0 crt_library\stdio\fscanf.xml  Process exactly one .xml file
goto :eof

endlocal
