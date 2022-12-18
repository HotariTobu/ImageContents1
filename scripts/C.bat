@REM Created by guinpen98

@echo off
rmdir /s /q .\destination_data\
Converter.exe
cd destination_data
for %%i in (*.wrl) do set x="%%i"
if exist ..\view3dscene.exe.lnk (
    ..\view3dscene.exe.lnk %x%
) else (
    %x%
)