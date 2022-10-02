from distutils import extension
from genericpath import isdir
import os

import converter

src_dir = input('input directory path of .dat files: ')
dst_dir = input('output directory path of .wrl files: ')

filenames = os.listdir(src_dir)

if not os.path.isdir(dst_dir):
    os.makedirs(dst_dir)

for filename in filenames:
    (name, ext) = os.path.splitext(filename)

    if ext.lower() != '.dat':
        print('Skipped because not .dat:', filename)
        continue

    src_path = os.path.join(src_dir, filename)
    dst_path = os.path.join(dst_dir, name + '.wrl')

    if os.path.isfile(dst_path):
        print('Skipped because already existed:', filename)
        continue

    print('Converting:', src_path, '>', dst_path)
    converter.convert(src_path, dst_path)