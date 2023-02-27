# CMap
Map implementation in C

## How to use it
The map is an opaque data type, that means that
the header file only contains the struct and function declarations (map.h), the implementation of the structs and functions is located in another file (map.c). 

If you want to use the map in your own project, because of the map being opaque, you can only work with map-pointers and not with maps themselves (similarly to file pointers in C). An example as to how to use it is provided in the main.c file.

In order to run the file, you'll need to compile the main.c (or the file in your project containing the main function) file together with the map.c file.

### Compile with GCC
If you use gcc as a compiler, run the following command to compile the code in the source-folder:
```
gcc main.c map.c -o main.exe
```
Now you can run the code with:
```
.\main
```

### Compile with Clang
With clang, you'll need to:

Compile the files into object files with
```
clang -c main.c
clang -c map.c
```
Then link the object files to a binary file:
```
clang main.o map.o
```
Last but not least, run the binary file:
```
.\a.out
```

## Mentioning
You're free to use my map as you like, extend it, improve its functionality etc.. If however, you use it in your own project and it goes public, please do mention me somewhere :)