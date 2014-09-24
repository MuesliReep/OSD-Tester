@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
cls
CD /D %~dp0

:: Compiler
set CC=mingw32-gcc

:: CFLAGS
set CFLAGS=-std=c99 -ID:/_libs/opencv/build/include

:: LIBS
set LIBS=-LD:/_libs/opencv/build/x86/mingw/lib -lm -lopencv_core231 -lopencv_imgproc231 -lopencv_highgui231

:: Dirs & Files
set SRCDIR=src
set BLDDIR=bld
set BIN=OSD-Tester
set OBJ=

set SRC_FILES=(main output ArrayHelper DataStream OSD Graphics Telemetry)

IF NOT EXIST %BLDDIR% mkdir %BLDDIR%

:: Execute

for %%i in %SRC_FILES% do echo CC   %SRCDIR%/%%i.c & %CC% %CFLAGS% -c %SRCDIR%/%%i.c -o %BLDDIR%/%%i.o

echo LINK %BIN%.exe
for %%i in %SRC_FILES% do set OBJ=!OBJ! %BLDDIR%/%%i.o
%CC% -o %BIN%.exe %OBJ% %LIBS%
