# **Fund o C**

## Requirements
- Prints characters flowing down in a line (get terminal width / set terminal dimensions)
- Coloured output
- Interactive menu; encrypt save/ decrypt load / exit / different colour themes
- User data entered is filled up with random int’s
- Pepe default file and theme to print : extension is to print matrix background
- Compression of data / saved themes, etc…
- Debug menu? Unit tests?? -d option/argument (encrypt and decrypt simple message)

## Running the Application
The application is runnable per environment. Simply use the included makefile to clean, recompile all or recompile libraries.

### *Using make:*
* `make clean`, cleans all .o, .a and program generated files created during the compile process.
* `make all`, compiles all libraries and links them to the implementer (main.c).
* `make libraries`, compiles all libraries but doesn't link them, this is useful for debugging purposes. Otherwise, in typical use, simply call make all.
### *Chaing commands:*
* The usual double-ampersand (&&) used in bash allows chaining makefile commands;
	`make clean && make all`
