"""Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os.path

img = Image.open(r"moonbench4x8.png")
OUTPUT_H = "output/moonbench4x8.h"
FONT_NAME = "MoonBench4x8MONO"
FONTSTR = """ !"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"""
CHAR_WIDTH = 4
CHAR_HEIGHT = 8
GLYPH_WIDTH = CHAR_WIDTH

#### Convert to C-header format
f = open(OUTPUT_H, 'w')
num_chars = len(FONTSTR)
f.write('static constexpr unsigned char ')
f.write(FONT_NAME)
f.write('[%d][%d] = {\n' % (num_chars+1, CHAR_WIDTH))

chars = []
for i in range(num_chars):
    ints = []
    for j in range(CHAR_WIDTH):
        x = i*GLYPH_WIDTH + j
        val = 0
        for y in range(CHAR_HEIGHT):
            rgb = img.getpixel((x,y))
            val = (val >> 1) | (0x80 if rgb[0] == 0 else 0)

        ints.append('0x%.2x' % (val))
    c = FONTSTR[i]
    if c == '\\': c = '"\\"' # bugfix
    f.write('\t{%s}, // %s\n' % (','.join(ints), c))


f.write('\t{%s}\n' % (','.join(['0x00']*CHAR_WIDTH)))
f.write('};')

f.close()
