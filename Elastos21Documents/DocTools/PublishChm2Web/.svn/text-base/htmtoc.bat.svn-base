::==========================================================================
:: File:    $tools/doc/treehtm.bat
:: Purpose: HTML TOC page generator.
:: Usage:   treehtm.bat CONTENT_FILE HTML_PAGE
:: Date:    2006-09-11 (a disastrous day)
:: Depends: cat
:: Notes:   For lack of experience on using perl to concatenate files and
::          parse command line arguments. UGLY DESIGN. should be rewrite as
::          perl.
::==========================================================================

@if "%_echo%"=="" echo off
setlocal

if /I "%~1"=="-h" call :usage & goto :eof
if "%~1"=="" call :usage & goto :eof
if "%~2"=="" call :usage & goto :eof

set RES_DIR=%~dp0conf\htmtoc
set RES_FILES=doc.png folderclosed.png folderopen.png ^
              blank.png pnode.png mnode.png
set DIR_DEST=%~dp2

echo %~nx0: mkdir %DIR_DEST%
mkdir %DIR_DEST% 2>nul

echo %~nx0: generate %2 by htmtoc.pl
perl -w "%~dp0htmtoc.pl" %1 >"%~2"
:: concatenate head, generated skeleton and tail
cat "%RES_DIR%\htmhead" "%~2" "%RES_DIR%\htmtail" >%~n0_swap
copy /y %~n0_swap "%~2" >nul
del /q %~n0_swap

:: copy resource files (e.g. .png, .css)
echo %~nx0: copy several auxiliary files
for %%I in (%RES_FILES%) do (
    copy %RES_DIR%\%%I %DIR_DEST% >nul
)
goto :eof

:usage
echo Usage: %~nx0 CONTENT_FILE HTML_PAGE
echo HTML TOC page generator.
echo.
echo Content file (Tree hierarchy, 2 spaces-indent)
echo.
echo Operating System,
echo   Elastos,http://www.koretide.com
echo   Windows,http://www.microsoft.com
echo   Unix-like,
echo     UNIX,http://www.att.com
echo     FreeBSD,http://www.freebsd.org
echo Search Engine,
echo   Baidu,http://www.baidu.com
echo   Google,http://www.google.com
echo.
echo Example usage:
echo   %~nx0 content.txt toc.htm
goto :eof

endlocal
