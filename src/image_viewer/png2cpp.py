#Copyright 2025 - HaruYou27
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os
import numpy
import math
import textwrap

file = open("gallery.h", "w")
file.write("static constexpr char *GALLERY_TITLE[] =\n{\n")

paths = []
os.chdir("input")
for path in os.listdir():
    if path.endswith(".png"):
        paths.append(path)
        file.write('    "' + textwrap.shorten(path.replace(".png", ""), 32, placeholder="") + '",\n')
file.write("    nullptr\n};\n")

file.write("static constexpr unsigned char GALLERY_SIZE[][2] =\n{")
for path in paths:
    image = Image.open(path)
    file.write("\n    {" + str(image.width) + ", ")
    file.write(str(math.ceil(image.height / 8)) + "},")
file.write("\n};\n")

file.write("static constexpr unsigned char *GALLERY_DATA[] =\n{\n")
for path in paths:
    print(path)
    image = Image.open(path).convert('1')
    img_array = numpy.array(image, dtype=numpy.uint8)
    
    width = image.width
    height = image.height
    page = math.ceil(height / 8)
    c_array_str = "    {"
    for y in range(0, height, 8):
        for x in range(width):
            value = 0
            for i in range(8):
                if y + i < height:
                    pixel = img_array[y + i, x]
                    # I have no idea how this works.
                    value = (value >> 1) | (0x80 if pixel == 0 else 0) 
            c_array_str += '0x%.2x,' % (value)
    file.write(c_array_str + "},\n")
file.write("};")
file.close()
