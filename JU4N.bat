@echo off
cd bin
del /q .\intermediate_data_Judge\
del /q .\destination_data\
Judge___UNIFORM___4_NEIGHBOR.exe
Converter.exe
cd destination_data
for /f %%i in ('dir /b /od') do set x="%%~fi"
start "" %x%