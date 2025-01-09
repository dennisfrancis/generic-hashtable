# Generic HashTable library in C
This is a hash table library in C where key type, value type and hash function are user defined.

# Source Files
1. `dll.h` - Doubly linked list header
2. `dll.c` - Doubly linked list implementation
3. `hash.h` - Hash table header
4. `hash.c` - Hash table implementation using separate chaining
5. `test_ll.c` - A sample program used to test the functionality of doubly linked list library.
6. `test_hash.c` - A sample program used to test the functionality of hash table library.

## How to build?

The project uses a standard cmake build system. To build:
```
$ cd build
$ cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release  # Use Debug for debug build or RelWithDebInfo for symbols enabled build.
$ make -j3                                     # This will build and run the test-suite.
```
The libraries and test binaries will be available in build once the above steps are done.

