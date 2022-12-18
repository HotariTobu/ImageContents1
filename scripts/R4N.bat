@REM Created by guinpen98

@echo off
rmdir /s /q .\intermediate_data_Reducer\
rmdir /s /q .\destination_data\
Reducer___4_NEIGHBOR.exe
echo source_directory_path = intermediate_data_Reducer > ConverterOption.txt
Converter.exe
cd destination_data
for %%i in (*.wrl) do set x="%%i"
if exist ..\view3dscene.exe.lnk (
    ..\view3dscene.exe.lnk %x%
) else (
    %x%
)