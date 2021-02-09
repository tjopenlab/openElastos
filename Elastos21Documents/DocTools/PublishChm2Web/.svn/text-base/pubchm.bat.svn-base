::==========================================================================
:: File:    pubchm.bat
:: Purpose: Make "Elastos Reference" browsable in browser
:: Usage:   pubchm IDX_FILE
:: Depends: htmtoc, GNU sed
:: TODO:    use munge to subst strings in .xml (no temp file need)
::==========================================================================

@if "%_echo%"=="" echo off
setlocal

set DOC_FILE=*.htm *.css *.bmp *.jpg *.js *.vbs
set MIRROR_DIR=d:\mirror
set DOCSRC_DIR=%CD%

if "%~1" == "" call :usage & goto :eof

if not exist %1 (
    echo %~nx0: %~1: No such file>&2
    exit /b 1
)
:: if exist %MIRROR_DIR% (
::     echo %~nx0: Make sure %MIRROR_DIR% is not present before running>&2
::     exit /b 1
:: )

echo Creating a TOC page ...
:: create a foldable TOC page
set FILTER1="0,/\[FILES\]/d;1,/#####/d;/^[ \t]*#/d;/^[ \t]*$/d"
set FILTER2="s/,[^,]\+,[ \t]*/,/"
cat "%~1" | sed -e %FILTER1% -e %FILTER2% >content.txt
call htmtoc.bat content.txt %MIRROR_DIR%\toc.htm

echo Adding a index page ...
copy "%~dp0conf\pubchm\index.htm" %MIRROR_DIR% >nul

echo Creating a mirror dir: %MIRROR_DIR% ...
:: foreach page:
::   get it's relative path
::   md its mirror dir
::   copy the file
for /F %%I in ('@dir /s /b %DOC_FILE%') do (
    set FP=%%~dpI
    mkdir %MIRROR_DIR%\!FP:%CD%\=! 2>nul
    copy /y %%I %MIRROR_DIR%\!FP:%CD%\=! >nul
)

echo Forward to %MIRROR_DIR% ...
cd /D %MIRROR_DIR%

echo Modifing .htm files ...
:: runs it in mirror dir
::
:: for (all .htm files) {
::   F = file's path
::   RP = relative path from current dir
::   RP = relative path from current dir to xsl
::   make RP usable for sed (. -> \.  / -> \/)
::   show
::   using sed:
::     remove links to samplemunu.vbs
::     make linking to common.css relative
::     make linking to docdemo.css relative
::     if find a link to runningbar.js, change it to a link to common.css
::     if find a link to docstyles.js, change it to a link to docdemo.css
:: }
::
:: For example:
::   %%I     D:\mirror\resource_debug_kits\tools\cat.htm
::   !F!     D:\mirror\resource_debug_kits\tools\
::   !RP!    resource_debug_kits\tools\
::   !RP!    ../../
::   !RP!    \.\.\/\.\.\/
::
for /F %%I in ('dir /s /b *.htm') do (
    set F=%%~dpI
    set RP=!F:%CD%\=!
rem a trick to put stream into env var
    for /F %%P in ('echo !RP! ^| sed "s/[^^\\]//g;s/\\/\.\.\//g"') do set RP=%%P
    if not "!RP!"=="" (
        set RP=!RP:.=\.!
        set RP=!RP:/=\/!
    )
    title %%I "!RP!"
    sed ^
    -e "/samplemenu.vbs/d" ^
    -e "/common\.css/s/\(\/\)\(xsl\)/!RP!\2/" ^
    -e "/docdemo\.css/s/\(\/\)\(xsl\)/!RP!\2/" ^
    -e "/runningbar\.js/c <link rel='stylesheet' href='!RP!xsl/common.css' type='text\/css'>" ^
    -e "/docstyles\.js/c <link rel='stylesheet' href='!RP!xsl/docdemo.css' type='text\/css'>" ^
    %%I > %%I.new
    copy /y %%I.new %%I > nul
    del /q %%I.new
)
goto :eof

:usage
echo.Usage: %~nx0 IDX_FILE
echo.Make "Elastos Reference" browsable in browser
echo.
echo.Examples:
echo.  %~nx0 Elastos20Chs.idx      generate from Chinese docs
goto :eof

endlocal
