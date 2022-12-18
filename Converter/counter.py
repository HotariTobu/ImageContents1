filename = input('filename: ')

points_count = 0
faces_count = 0

with open(filename, 'r') as f:
    is_counting_points = False
    is_counting_faces = False

    for line in f:
        if 'point' in line:
            is_counting_points = True
        
        if 'coordIndex' in line:
            is_counting_faces = True

        if is_counting_points:
            if '[' in line:
                points_count = 0
            else:
                points_count += 1
        
        if is_counting_faces:
            if '[' in line:
                faces_count = 0
            else:
                faces_count += 1

        if ']' in line:
            is_counting_points = False
            is_counting_faces = False

print('points count:', points_count)
print('faces count:', faces_count)