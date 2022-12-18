# Created by HotariTobu

rm -R ./destination_data
rm -R ./intermediate_data_Filler
rm -R ./intermediate_data_Judge
rm -R ./intermediate_data_Reducer

echo source_directory_path = source_data > FillerOption.txt

# ./Filler___4_NEIGHBOR___MAX
# ./Filler___4_NEIGHBOR___MEAN
# ./Filler___4_NEIGHBOR___MEDIAN
# ./Filler___4_NEIGHBOR___MIN
# ./Filler___8_NEIGHBOR___MAX
# ./Filler___8_NEIGHBOR___MEAN
# ./Filler___8_NEIGHBOR___MEDIAN
./Filler___8_NEIGHBOR___MIN

# ./Judge___FLEXIBLE___4_NEIGHBOR
./Judge___FLEXIBLE___8_NEIGHBOR
# ./Judge___UNIFORM___4_NEIGHBOR
# ./Judge___UNIFORM___8_NEIGHBOR

# ./Reducer___4_NEIGHBOR
./Reducer___8_NEIGHBOR

./Converter