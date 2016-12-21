Generic HashTable library in pure C
===================================

With this C library you can create create a hash table with user defined key type and value type and user defined hash function, hence the term "generic".



##Source Files
============
1. `dll.h` - Doubly linked list header
2. `dll.c` - Doubly linked list implementation
3. `hash.h` - Hash table header
4. `hash.c` - Hash table implementation using separate chaining
5. `test_ll.c` - A sample program used to test the functionality of doubly linked list library.
6. `test_hash.c` - A sample program used to test the functionality of hash table library.

##Build library from source

To build the library and run the tests, do
```
$ make
```

##Use library in your programs

To compile and run your program that uses this library, do
```
$ gcc -Wall -I<repo_root> -L<repo root>/lib -ldlnklst -lgenhash -o <executable_name> <your_program>.c
$ LD_LIBRARY_PATH=<repo_root>/lib <path/to/executable_name>
```