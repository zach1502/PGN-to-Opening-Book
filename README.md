# pgnToOpeningBook

A simple tool to convert any number of .pgn chess game files into an easy to use opening book for a chess engine.
The format outputted is the same as a javascript object, a python dict and a C++ map. It will be in a text file.

You can copy and paste the book into your code and your engine will now have a simple opening book.

Time Complexity is O(n)

# How to Use
1. Compile `pgnToOpeningBook.cpp`.
For Example:
```g++ pgnToOpeningBook.cpp -o pgnBook```

2. Run the compiled program
```pgnBook <file1> <file2> ... <fileN>```

3. Wait

4. Opening Book will appear as `openingBook.txt` in the same directory as the executable.

# Credit

I used a *slightly* modified version of the THC Chess Library. https://github.com/billforsternz/thc-chess-library
Thank you.

