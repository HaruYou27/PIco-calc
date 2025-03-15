"""Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os

os.makedirs("output", exist_ok=True)
FONTSTR = """ !"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"""
CHAR_WIDTH = 4
CHAR_HEIGHT = 8

for path in os.listdir():
    if path.endswith(".png"):
        img = Image.open(path)

        FONT_NAME = path.replace(".png", '')

        path = path.replace(".png", ".h")
        OUTPUT_H = os.path.join("output/", path)

        #### Convert to C-header format
        file = open(OUTPUT_H, 'w')
        num_chars = len(FONTSTR)
        file.write('static constexpr int ')
        file.write(FONT_NAME)
        file.write("_WIDTH = ")
        file.write(str(CHAR_WIDTH))
        file.write(";\n")
        file.write('static constexpr unsigned char ')
        file.write(FONT_NAME)
        file.write('[%d][%d] = \n{\n' % (num_chars+1, CHAR_WIDTH))

        chars = []
        for i in range(num_chars):
            ints = []
            for j in range(CHAR_WIDTH):
                x = i*CHAR_WIDTH + j
                val = 0
                for y in range(CHAR_HEIGHT):
                    rgb = img.getpixel((x,y))
                    val = (val >> 1) | (0x80 if rgb[0] == 0 else 0)

                ints.append('0x%.2x' % (val))
            c = FONTSTR[i]
            if c == '\\': c = '"\\"' # bugfix
            file.write('\t{%s}, // %s\n' % (','.join(ints), c))


        file.write('\t{%s}\n' % (','.join(['0x00']*CHAR_WIDTH)))
        file.write('};')

        file.close()
