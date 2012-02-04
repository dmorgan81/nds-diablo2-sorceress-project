set path=c:\devkitPro\msys\bin;%path%
make clean
del *.ncb > nul
del *.user > nul
del /Q Debug\*.*
rd Debug
