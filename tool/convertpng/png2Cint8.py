"""Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

from PIL import Image
import os

os.makedirs("output", exist_ok=True)

for path in os.listdir():
    if path.endswith(".png"):
        image = Image.open(path)
        print("\n"
              "static constexpr int {name}_width  {w}\n"
              "static constexpr int {name}_height {h}\n"
              "\n"
              "static constexpr uint8_t {name}_data[] = {{\n"
              .format(name=path.replace(".png", ""), w=image.width, h=image.height), end='')
        for y in range(0, image.height):
          for x in range(0, (image.width + 7)//8 * 8):
            if x == 0:
              print("  ", end='')
            if x % 8 == 0:
              print("0b", end='')  
            bit = '0'
            if x < image.width and image.getpixel((x,y)) != 0:
              bit = '1'
            print(bit, end='')   
            if x % 8 == 7:
              print(",", end='')
          print()
        print("};")
