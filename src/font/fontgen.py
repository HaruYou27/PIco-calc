#Copyright 2025 - HaruYou27
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os
import numpy

FONTSTR = """!"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"""

IN_PATH = "input/"
for path in os.listdir():
    if path.endswith(".png"):
        print(path)
        img = Image.open(IN_PATH + path).convert('1')
        image = numpy.array(img, dtype=numpy.uint8)
        file = open(path.replace(".png", ".h"), 'w')

        num_chars = len(FONTSTR)
        font_width = img.width
        name = path.replace(".png", "")

        c_array = 'static constexpr unsigned char ' + name + "_width = " + str(font_width) + ";\n" + 'static constexpr unsigned char ' + name + '[][{width}] ='.format(width=font_width) + "\n{"
        for y in range(0, img.height, 8):
            c_array += "\n    {"
            for x in range(font_width):
                value = 0
                for i in range(8):
                    pixel = image[y + i, x]
                    value = (value >> 1) | (0x80 if pixel == 0 else 0)
                if not value:
                    break
                c_array += '0x%.2x,' % (value)
            c_array = c_array.strip(',') + "},"
        file.write(c_array.strip(',') + '\n};')
        file.close()
