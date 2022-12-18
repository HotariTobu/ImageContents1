@REM Created by guinpen98

@echo off
del /q .\destination_data\
del /q .\intermediate_data_Filler\
del /q .\intermediate_data_Judge\
del /q .\intermediate_data_Reducer\
echo source_directory_path = source_data > FillerOption.txt
@REM Filler___4_NEIGHBOR___MAX.exe
@REM Filler___4_NEIGHBOR___MEAN.exe
@REM Filler___4_NEIGHBOR___MEDIAN.exe
@REM Filler___4_NEIGHBOR___MIN.exe
@REM Filler___8_NEIGHBOR___MAX.exe
@REM Filler___8_NEIGHBOR___MEAN.exe
@REM Filler___8_NEIGHBOR___MEDIAN.exe
Filler___8_NEIGHBOR___MIN.exe
@REM Judge___FLEXIBLE___4_NEIGHBOR.exe
Judge___FLEXIBLE___8_NEIGHBOR.exe
@REM Judge___UNIFORM___4_NEIGHBOR.exe
@REM Judge___UNIFORM___8_NEIGHBOR.exe
@REM Reducer___4_NEIGHBOR.exe
Reducer___8_NEIGHBOR.exe
Converter.exe