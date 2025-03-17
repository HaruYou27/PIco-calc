"""Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation paths (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."""

import os
import textwrap
import unicodedata

file_output = open("book.h", "w")
file_output.write("static constexpr char *BOOK_DATA[] =\n{\n")

titles = []
os.chdir("input")
for path in os.listdir():
    if path.endswith(".txt"):
        print(path)
        file = open(path)
        text = file.read()
        file.close()

        titles.append(textwrap.shorten(path.replace(".txt", ""), 32, placeholder=""))

        text = unicodedata.normalize("NFKD", text)
        # Filter out diacritics and keep only ASCII characters
        text_ascii = "".join(char for char in text if not unicodedata.combining(char))
        text = text_ascii
        text = textwrap.fill(text, 32, replace_whitespace=False)
        text = text.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')

        file_output.write('    "' + text + '",\n')
file_output.write("\n};")

file_output.write("static constexpr char *BOOK_TITLE[] =\n{\n")
for title in titles:
    file_output.write('"' + title + '",\n')
file_output.write("NULL\n};")

file_output.close()

