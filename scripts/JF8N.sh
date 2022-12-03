# Created by HotariTobu

rm -R ./intermediate_data_Judge
rm -R ./destination_data

./Judge___FLEXIBLE___8_NEIGHBOR

echo source_directory_path = intermediate_data_Judge > ConverterOption.txt
./Converter

cd destination_data
for f in ./*.wrl; do
    open $f
done