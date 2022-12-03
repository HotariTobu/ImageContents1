@REM Created by guinpen98

@echo off
del /q .\intermediate_data_Reducer\
del /q .\destination_data\
Reducer___8_NEIGHBOR.exe
Converter.exe
cd destination_data
for %%i in (*.wrl) do set x="%%i"
%x%