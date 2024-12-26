import os


images = []

for file in os.listdir('res'):
    if file.endswith('png'):
        images.append(file.split('.')[0])

header_file = []
for image in images:
    header_file.append(f'#include <res/{image}.h>\n')
header_file.append(f'#define NUM_IMAGES {len(images)}\n')
header_file.append('const uint8_t* const images[NUM_IMAGES] = {\n')
for image in images:
    header_file.append(f'    {image}_tiles,\n')
header_file.append('};\n')
header_file.append('const palette_color_t* const palettes[NUM_IMAGES] = {\n')
for image in images:
    header_file.append(f'    {image}_palettes,\n')
header_file.append('};\n')

with open('src/images.h', 'w') as f:
    f.writelines(header_file)
