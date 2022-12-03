# Created by HotariTobu

rm -R ./destination_data

./Converter

cd destination_data
for f in ./*.wrl; do
    open $f
done