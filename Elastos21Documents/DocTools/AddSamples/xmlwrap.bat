::==========================================================================
:: File:    %MYTOOLS%\xmlwrap.bat
:: Purpose: Convert FILE(s) into a simple xml file.
:: Usage:   xmlwrap.bat TAG [FILE]
:: Date:    2006-12-22
::
:: Depends: cat, sed
::==========================================================================

@setlocal

:: Process command options
@if /I "%1"=="-h" @call :usage && goto :eof
@if "%1"=="" @(
    call :usage && goto :eof
) else (
    set TAG=%1
)
@set FLATFILE=%2

:: Main routine here
@echo ^<%TAG%^>
@cat %FLATFILE% | sed -f "%~dp0xmlesc.sed"
@echo ^</%TAG%^>
@goto :eof

:: Sub routines here
:usage
@echo Usage: %~nx0 TAG [FILE]
@echo Convert FILE(s) into a simple xml file. The output is standard out.
@echo.
@echo   -h          Display this help and exit
@echo.
@echo With no FILE, read standard in.
@echo.
@echo Examples:
@echo   %~nx0 code hello.cpp    Make hello.cpp to a xml with ^<code^>^</code^>
@goto :eof

@endlocal
