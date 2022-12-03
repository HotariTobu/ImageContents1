# Created by HotariTobu

rm -R ./intermediate_data_Reducer
rm -R ./destination_data

Reducer___4_NEIGHBOR

echo source_directory_path = intermediate_data_Reducer > ConverterOption.txt
./Converter

cd destination_data
for f in ./*.wrl; do
    open $f
done