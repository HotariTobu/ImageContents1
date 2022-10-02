TEMPLATE1 = """#VRML V2.0 utf8

Shape {
    appearance Appearance {
        material Material {
            diffuseColor 1.0 0.0 0.0
            emissiveColor 1.0 0.0 0.0
        }
    }
    geometry PointSet {
        coord Coordinate {
            point [
"""

TEMPLATE2 = """
            ]
        }
    }
}
"""

def to_point_set(src_path, dst_path):
    with open(src_path, mode='r') as src_file, open(dst_path, mode='w') as dst_file:
        dst_file.write(TEMPLATE1)

        for line in src_file:
            tokens = line.split()
            if len(tokens) < 3:
                continue

            [x_str, y_str, z_str] = tokens
            if float(z_str) >= 0:
                dst_file.write(line.strip() + ',\n')

        dst_file.write(TEMPLATE2)