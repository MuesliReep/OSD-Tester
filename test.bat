@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
cls

set var=a
set var=%var% b
set var=%var% c
set var=%var% d

echo %var%

set var=
set list=(a b c d)
for %%i in %list% do set var=!var! %%i

echo %var%
