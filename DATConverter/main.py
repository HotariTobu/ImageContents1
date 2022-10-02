from distutils import extension
from genericpath import isdir
import os

import converters.toobj as toobj
import converters.towrl as towrl

# toobj.to_bar.__name__
# toobj.to_bar()

# from importlib import import_module

# import_module('toobj').

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
    # dst_path = os.path.join(dst_dir, name + '.wrl')
    dst_path = os.path.join(dst_dir, name + '.obj')

    if os.path.isfile(dst_path):
        print('Skipped because already existed:', filename)
        continue

    print('Converting:', src_path, '>', dst_path)
    # towrl.to_point_set(src_path, dst_path)
    toobj.to_bar(src_path, dst_path)