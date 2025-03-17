"""Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os
import numpy
import math

files = []

for path in os.listdir("input"):
    if path.endswith(".png"):
        
        image = Image.open(path)
        img_array = numpy.array(image, dtype=numpy.uint8)


        path = path.replace(".png", ".h")
        file = open(os.path.join("output", path), "w")
        width = image.width
        height = image.height
        page = math.ceil(height / 8)
        file.write("static constexpr unsigned char {name}_WIDTH = {w};\nstatic constexpr unsigned char {name}_PAGE = {h};\nstatic constexpr unsigned char {name}_data[] = ".format(name=path.replace(".h", ""), w=width, h=page))

        c_array_str = "{"
        # Iterate over the image in 8-pixel vertical chunks
        for y in range(0, height, 8):
            for x in range(width):
                # Extract 8 vertical pixels
                byte = 0
                for i in range(8):
                    if y + i < height:
                        pixel = img_array[y + i, x]
                        byte |= (pixel & 0x01) << (7 - i)
                c_array_str += f"0x{byte:02X}, "
        c_array_str = c_array_str + "};"
        file.write(c_array_str)
        file.close()