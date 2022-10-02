def to_bar(src_path, dst_path):
    with open(src_path, mode='r') as src_file, open(dst_path, mode='w') as dst_file:
        for (i, line) in enumerate(src_file):
            tokens = line.split()
            if len(tokens) < 3:
                continue

            [x, y, z] = [float(token) for token in tokens]
            if z < -9999:
                continue

            v0 = 1 + i * 8

            for dx in range(2):
                for dy in range(2):
                    dst_file.write(f"v {x + dx} {y + dy} {z}\n")
                    dst_file.write(f"v {x + dx} {y + dy} 0\n")

                    v1 = v0 + dx * 2 + dy * 4
                    v2 = v1 + (((dx + dy) % 2 + 1) * 2) * ((-1) ** dy)
                    dst_file.write(f"f {v1} {v1 + 1} {v2 + 1} {v2}\n")
            
            dst_file.write(f"f {v0} {v0 + 2} {v0 + 6} {v0 + 4}\n")