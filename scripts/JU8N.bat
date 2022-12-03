@REM Created by guinpen98

@echo off
del /q .\intermediate_data_Judge\
del /q .\destination_data\
Judge___UNIFORM___8_NEIGHBOR.exe
echo source_directory_path = intermediate_data_Judge > ConverterOption.txt
Converter.exe
cd destination_data
for %%i in (*.wrl) do set x="%%i"
"..\view3dscene.exe.lnk" %x%