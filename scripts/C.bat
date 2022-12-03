@REM Created by guinpen98

@echo off
del /q .\destination_data\
Converter.exe
cd destination_data
for %%i in (*.wrl) do set x="%%i"
%x%