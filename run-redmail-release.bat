:: bat command script to run redmail in Windows
:: the following DLL's needed to run

:: All of them can be found here:
:: C:\QtSDK\Desktop\Qt\4.7.4\mingw\bin\
:: 4.7.4 - is the version of Qt you use (can be differ)

:: ======= DLL LIST =======
:: libgcc_s_dw2-1.dll
:: mingwm10.dll

:: phonond4.dll
:: QtCored4.dll
:: QtGuid4.dll
:: QtNetworkd4.dll
:: QtWebKitd4.dll

:: phonon4.dll
:: QtCore4.dll
:: QtGui4.dll
:: QtNetwork4.dll
:: QtWebKit4.dll

:: it take about 38,5 MB for debug version and 29,8 MB for release
:: just copy them to the same directory with redmail.exe and run
:: or copy to dlls directory and run using this script

@echo off

set QT_VER=4.7.4
set QT_LIB_PATH=C:\QtSDK\Desktop\Qt\%QT_VER%\mingw\bin

:: check dlls directory
if not exist dlls\* (
    :: there are no dlls directory
    echo no dlls directory
    if exist dlls (
        :: dlls is a file
        echo dlls is a file, deleting
        del dlls
    )
    md dlls
    echo dlls dir created
)

:: check dlls
for %%D in (
"libgcc_s_dw2-1.dll"
"mingwm10.dll"
"phonon4.dll"
"QtCore4.dll"
"QtGui4.dll"
"QtNetwork4.dll"
"QtWebKit4.dll"
) do (
    if not exist dlls\%%~D (
        echo %%~D is missing
        copy %QT_LIB_PATH%\%%~D dlls\ >nul
    )
)

:: run using dlls
PATH=%PATH%;dlls\
redmail-build\release\redmail.exe

