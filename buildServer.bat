@echo off

REM This stores the path of the buildsuper.bat script
REM in CODE_HOME.  This way you can always include the
REM default files no matter where you store your code.
REM And no matter how you call buildsuper.bat.
SET CODE_HOME=%~dp0

SET SRC=%1
if "%SRC%" == "" SET SRC=..\code\ImServer.cpp

REM SET OPTS=/W4 /wd4310 /wd4100 /wd4201 /wd4505 /wd4996 /wd4127 /wd4510 /wd4512 /wd4610 /wd4457 /WX
SET OPTS=%OPTS% /GR- /nologo /FC

SET OPTS=%OPTS% /nologo /FC

SET DEBUG=/Zi

SET LNKOPTS=/link /INCREMENTAL:NO

mkdir build
pushd build
cl %OPTS% /I"%CODE_HOME% " %DEBUG% "%SRC%" %LNKOPTS% Ws2_32.lib
popd

REM file spammation preventation
REM del *.exp
REM del *.obj
REM del *.lib