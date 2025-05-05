## Overview
This project implement a dynamic linked list in C which can hold generic datatype
The library include some standard functions, including insertion, print, merge, sort, and etc.

## Features
- Generic linked list implemented "void pointer" to hold data where each node will allocate the memory on the heap using malloc().
- Since every node allocated on heap, function list_clean(**head) should always be called to free list after use.
-test file is for unit testing ensuring every functions work correctly, implemented by CUnit library.

## Installation & setup
- Clone this Repository and place header file in your project!!

''''bash
git clone https://github.com/Boonanan-paot/Generic_linked_list_lib_C.git
cd Generic_linked_list_lib_C
