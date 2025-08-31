# Lab 1: C++ Fundamentals & Debugging
<div style="text-align:justify">
Topics covered:

- [Debugging](#debugging)
  - [Using the debugger](#using-the-debugger)
  - [Compilation Process](#compilation-process)
- [Pointers Review](#pointers-review)
  - [Pointer Basics](#pointer-basics)
  - [Pointer Arithmetic](#pointer-arithmetic)
  - [Common Pointer Mistakes](#common-pointer-mistakes)
  - [Dynamic Memory Allocation](#dynamic-memory-allocation)
- [Arrays and Vectors](#arrays-and-vectors)
  - [C-Style Arrays](#c-style-arrays)
  - [Modern Vectors](#modern-vectors)
  - [Array vs Vector Comparison](#array-vs-vector-comparison)
  - [Multi-dimensional Arrays](#multi-dimensional-arrays)
- [String Handling](#string-handling)
  - [C-Style Strings](#c-style-strings)
  - [C++ String Class](#c-string-class)
  - [String Operations](#string-operations)
- [Practice Exercises](#practice-exercises)
  - [Exercise 1: Debugging Challenge](#exercise-1-debugging-challenge)
  - [Exercise 2: Pointer Manipulation](#exercise-2-pointer-manipulation)
  - [Exercise 3: Array Processing](#exercise-3-array-processing)



## Debugging

`Debugging` is the systematic process of finding, analyzing, and fixing errors, known as "bugs," in software or hardware to ensure it functions correctly.

It is important to know how to debug a program to be able to diagnose unwanted behaviour and fix issues easily and quickly.

During tests and especially during exams, debugging will be the best method to solve problems that occur despite initially not understanding where the issue originates from.

**Types of errors:**
1. **Compile-time errors**: Syntax errors, type mismatches
2. **Link-time errors**: Missing function definitions, library issues
3. **Runtime errors**: Crashes, incorrect behavior during execution

**Basic debugging workflow:**
1. **Reproduce the bug**: Make it happen consistently
2. **Isolate the problem**: Narrow down where it occurs
3. **Use debugging tools**: Breakpoints, variable inspection
4. **Fix and verify**: Test that the fix works

> [!NOTE]
> `debugger` = a software tool that developers use to observe, control, and fix errors in other programs. \
> \
> It allows them to pause program execution at specific points (breakpoints), examine the values of variables and memory, step through code line by line, and view the call stack to understand the program's flow

### Using the debugger
The debugger incorporates multiple tools with different uses, the most common are:
- `step over`: executes the current line of code and pauses on the next line, without entering any function calls
- `step into`: enters the code of the current line if it is/contains a function and pauses at the first line of the function
- `step out`: continues the program’s execution until it exits the current function
- `continue`: resumes normal execution


**Common syntax errors:**
- Missing semicolons
- Mismatched parentheses or braces
- Misspelled keywords
- Incorrect variable declarations

### Compilation Process
&rarr; [Understanding compilation](https://www.toptal.com/c-plus-plus/c-plus-plus-understanding-compilation](https://www.geeksforgeeks.org/cpp/how-to-compile-a-cpp-program-using-gcc/))

> [!NOTE]
> The instructions assume the usage of `gcc` (GNU Compiler Collection) as the compiler, but there are many others available (g++, clang, ***Microsoft Visual C++ aka MSVC***, etc.)

Steps to compile and execute a `.cpp` file:
1. Source Code (.cpp, .h files)
2. Preprocessing
3. Compilation
4. Assembly
5. Linking
6. Execution

```bash
# ~ preprocessing ~

#   - Replaces #include <....> with actual code from the included files.
#   - Expands macros
#   n- Handles conditional compilation (#ifdef, etc.)

g++ -E main.cpp -o main.i
```

```bash
# ~ compilation ~

#   - Does Syntax checking
#   - Converts C++ to Assembly code (.s file)

g++ -S main.i -o main.s
```

```bash
# ~ assembly ~
g++ -c main.cpp -o main.o
```

```bash
# ~ linking ~

#   - Connects the main() function in main.o to add() in math_utils.o
#   - Resolves symbols from the standard library

g++ main.o math_utils.o -o main
```

```bash
# ~ execution ~
./main.exe
```

> [!NOTE]
> The usual steps required to obtain an executable is: \
> `assembly` > `linking` > `execution`

**C++11 specific compilation:**
```bash
g++ -std=c++11 -o program source.cpp
```

## Pointers Review

### Pointer Basics

A pointer is a variable that stores the memory address of another variable:

```cpp
int x = 42;
int* ptr = &x;  // ptr holds the address of x

cout << "Value of x: " << x << endl;            // 42
cout << "Address of x: " << &x << endl;         // Memory address
cout << "Value of ptr: " << ptr << endl;        // Same as &x
cout << "Value pointed to: " << *ptr << endl;   // 42
```

**Key concepts:**
- `&` (address-of operator): Gets the address of a variable
- `*` (dereference operator): Gets the value at an address
- Pointer declaration: `type* pointer_name`

### Pointer Arithmetic

Pointer arithmetic allows you to perform mathematical operations on pointers to navigate through memory efficiently. This is particularly useful when working with arrays and dynamic memory.

#### Basic Operations

**1. Increment and Decrement:**
```cpp
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;  // Points to first element (index 0)

cout << *ptr << endl;        // 10 (arr[0])
ptr++;                       // Move to next element
cout << *ptr << endl;        // 20 (arr[1])
ptr--;                       // Move back one element
cout << *ptr << endl;        // 10 (arr[0])
```

**2. Addition and Subtraction:**
```cpp
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;

cout << *(ptr + 0) << endl;  // 10 (arr[0])
cout << *(ptr + 1) << endl;  // 20 (arr[1])
cout << *(ptr + 3) << endl;  // 40 (arr[3])

ptr += 2;                    // Move 2 elements forward
cout << *ptr << endl;        // 30 (arr[2])

ptr -= 1;                    // Move 1 element back
cout << *ptr << endl;        // 20 (arr[1])
```

#### Data Type Size Impact

The key concept: **pointer arithmetic is scaled by the size of the data type**

```cpp
// Integer array (each int is typically 4 bytes)
int int_arr[] = {1, 2, 3, 4, 5};
int* int_ptr = int_arr;

cout << "int_ptr address: " << int_ptr << endl;        // e.g., 0x1000
cout << "int_ptr + 1: " << (int_ptr + 1) << endl;     // e.g., 0x1004 (4 bytes later)
cout << "int_ptr + 2: " << (int_ptr + 2) << endl;     // e.g., 0x1008 (8 bytes later)

// Character array (each char is 1 byte)
char char_arr[] = {'a', 'b', 'c', 'd', 'e'};
char* char_ptr = char_arr;

cout << "char_ptr address: " << (void*)char_ptr << endl;        // e.g., 0x2000
cout << "char_ptr + 1: " << (void*)(char_ptr + 1) << endl;     // e.g., 0x2001 (1 byte later)
cout << "char_ptr + 2: " << (void*)(char_ptr + 2) << endl;     // e.g., 0x2002 (2 bytes later)

// Double array (each double is typically 8 bytes)
double double_arr[] = {1.1, 2.2, 3.3};
double* double_ptr = double_arr;

cout << "double_ptr address: " << double_ptr << endl;          // e.g., 0x3000
cout << "double_ptr + 1: " << (double_ptr + 1) << endl;       // e.g., 0x3008 (8 bytes later)
```

#### Pointer Subtraction

You can subtract pointers to find the distance between them:

```cpp
int arr[] = {10, 20, 30, 40, 50};
int* start = arr;
int* end = arr + 4;  // Points to last element

// Distance between pointers (in number of elements)
ptrdiff_t distance = end - start;
cout << "Distance: " << distance << " elements" << endl;  // 4

// This is equivalent to:
cout << "Array size: " << (end - start + 1) << " elements" << endl;  // 5
```

#### Array Traversal with Pointer Arithmetic

**Method 1: Using pointer increment**
```cpp
int arr[] = {10, 20, 30, 40, 50};
int size = sizeof(arr) / sizeof(arr[0]);  // Calculate array size

cout << "Forward traversal:" << endl;
for (int* ptr = arr; ptr < arr + size; ptr++) {
    cout << *ptr << " ";
}
cout << endl;

cout << "Backward traversal:" << endl;
for (int* ptr = arr + size - 1; ptr >= arr; ptr--) {
    cout << *ptr << " ";
}
cout << endl;
```

**Method 2: Using index-like notation**
```cpp
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;
int size = 5;

cout << "Using pointer arithmetic like array indexing:" << endl;
for (int i = 0; i < size; i++) {
    cout << "ptr[" << i << "] = " << ptr[i] << " = " << *(ptr + i) << endl;
}
```

#### Pointer Arithmetic with Different Data Types

```cpp
struct Point {
    int x, y;
};

Point points[] = {{1, 2}, {3, 4}, {5, 6}};
Point* ptr = points;

cout << "Point 0: (" << ptr->x << ", " << ptr->y << ")" << endl;
ptr++;  // Moves by sizeof(Point) bytes
cout << "Point 1: (" << ptr->x << ", " << ptr->y << ")" << endl;
ptr++;
cout << "Point 2: (" << ptr->x << ", " << ptr->y << ")" << endl;

// Alternative notation
ptr = points;
for (int i = 0; i < 3; i++) {
    cout << "Point " << i << ": (" << (ptr + i)->x << ", " << (ptr + i)->y << ")" << endl;
}
```

#### Comparison Operations

Pointers can be compared when they point to elements of the same array:

```cpp
int arr[] = {10, 20, 30, 40, 50};
int* start = arr;
int* middle = arr + 2;
int* end = arr + 4;

cout << "start < middle: " << (start < middle) << endl;    // true (1)
cout << "middle > start: " << (middle > start) << endl;    // true (1)
cout << "end >= middle: " << (end >= middle) << endl;      // true (1)
cout << "start == arr: " << (start == arr) << endl;       // true (1)
```

#### Practical Example: Finding Elements

```cpp
int find_element(int* arr, int size, int target) {
    for (int* ptr = arr; ptr < arr + size; ptr++) {
        if (*ptr == target) {
            return ptr - arr;  // Return index
        }
    }
    return -1;  // Not found
}

int main() {
    int numbers[] = {15, 23, 8, 42, 16};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int index = find_element(numbers, size, 42);
    if (index != -1) {
        cout << "Found 42 at index: " << index << endl;
    }
    
    return 0;
}
```

#### Dynamic Memory and Pointer Arithmetic

```cpp
int main() {
    int size = 5;
    int* dynamic_arr = new int[size];
    
    // Initialize using pointer arithmetic
    for (int* ptr = dynamic_arr; ptr < dynamic_arr + size; ptr++) {
        *ptr = (ptr - dynamic_arr) * 10;  // 0, 10, 20, 30, 40
    }
    
    // Print using pointer arithmetic
    cout << "Dynamic array contents: ";
    for (int* ptr = dynamic_arr; ptr < dynamic_arr + size; ptr++) {
        cout << *ptr << " ";
    }
    cout << endl;
    
    delete[] dynamic_arr;
    return 0;
}
```

#### Common Pitfalls and Safety

**1. Bounds checking is YOUR responsibility:**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// DANGEROUS: No bounds checking
ptr += 10;  // Points outside array bounds
// cout << *ptr << endl;  // UNDEFINED BEHAVIOR!

// SAFE: Always check bounds
if (ptr >= arr && ptr < arr + 5) {
    cout << *ptr << endl;
}
```

**2. Pointer arithmetic only works within the same memory block:**
```cpp
int arr1[3] = {1, 2, 3};
int arr2[3] = {4, 5, 6};
int* ptr1 = arr1;
int* ptr2 = arr2;

// WRONG: Comparing pointers from different arrays
// if (ptr1 < ptr2) { ... }  // Undefined behavior!

// WRONG: Arithmetic between different arrays
// ptrdiff_t diff = ptr2 - ptr1;  // Undefined behavior!
```

**3. Be careful with void pointers:**
```cpp
int arr[] = {1, 2, 3, 4, 5};
void* void_ptr = arr;

// WRONG: Can't do arithmetic on void*
// void_ptr++;  // Compilation error!

// CORRECT: Cast to appropriate type first
int* int_ptr = static_cast<int*>(void_ptr);
int_ptr++;  // Now this works
```

#### Performance Considerations

Pointer arithmetic is often faster than array indexing in loops:

```cpp
// Slower: Array indexing
for (int i = 0; i < size; i++) {
    process(arr[i]);
}

// Faster: Pointer arithmetic (compiler may optimize both the same way)
for (int* ptr = arr; ptr < arr + size; ptr++) {
    process(*ptr);
}

// Modern C++: Range-based for loop (recommended)
for (const auto& element : arr) {
    process(element);
}
```

**Important notes:**
- Pointer arithmetic depends on the data type size
- `ptr++` moves by `sizeof(type)` bytes
- Only works meaningfully with arrays or allocated memory
- Always ensure you stay within valid memory bounds
- Pointer arithmetic is undefined for pointers from different memory blocks

### Common Pointer Mistakes

**1. Dereferencing null pointers:**
```cpp
int* ptr = nullptr;
cout << *ptr << endl;  // CRASH: Segmentation fault
```

**Fix:**
```cpp
int* ptr = nullptr;
if (ptr != nullptr) {
    cout << *ptr << endl;
}
```

**2. Dangling pointers:**
```cpp
int* ptr;
{
    int x = 42;
    ptr = &x;  // ptr points to x
}  // x goes out of scope
cout << *ptr << endl;  // UNDEFINED: x no longer exists
```

**3. Memory leaks:**
```cpp
void create_leak() {
    int* ptr = new int(42);
    // Forgot to delete ptr
}  // Memory leaked
```

**Fix:**
```cpp
void no_leak() {
    int* ptr = new int(42);
    cout << *ptr << endl;
    delete ptr;  // Free memory
    ptr = nullptr;  // Avoid dangling pointer
}
```

### Dynamic Memory Allocation

Allocate memory at runtime using `new` and `delete`:

```cpp
// Single variable
int* ptr = new int(42);
cout << *ptr << endl;
delete ptr;

// Array allocation
int size = 5;
int* arr = new int[size];
for (int i = 0; i < size; i++) {
    arr[i] = i * 10;
}

// Use the array
for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
}

delete[] arr;  // Note: delete[] for arrays
```

**C++11 smart pointers (recommended):**
```cpp
#include <memory>

// Automatic memory management
std::unique_ptr<int> ptr = std::make_unique<int>(42);
// No need to call delete - automatic cleanup
```

## Arrays and Vectors

### C-Style Arrays

Traditional arrays with fixed size:

```cpp
// Declaration and initialization
int numbers[5] = {1, 2, 3, 4, 5};
char name[] = "Hello";  // Size automatically determined

// Accessing elements
for (int i = 0; i < 5; i++) {
    cout << numbers[i] << " ";
}

// Array as function parameter
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
```

**Limitations:**
- Fixed size at compile time
- No bounds checking
- Size information lost when passed to functions
- Manual memory management for dynamic arrays

### Modern Vectors

C++11 vectors provide dynamic, safe arrays:

```cpp
#include <vector>

// Declaration and initialization
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::vector<int> empty_vector;
std::vector<int> sized_vector(10, 0);  // 10 elements, all 0

// Adding elements
numbers.push_back(6);
numbers.insert(numbers.begin(), 0);  // Insert at beginning

// Accessing elements safely
cout << numbers.at(0) << endl;  // Bounds-checked access
cout << numbers[0] << endl;     // Direct access (faster)

// Size and capacity
cout << "Size: " << numbers.size() << endl;
cout << "Capacity: " << numbers.capacity() << endl;

// Iteration
for (size_t i = 0; i < numbers.size(); i++) {
    cout << numbers[i] << " ";
}

// Range-based for loop (C++11)
for (const auto& num : numbers) {
    cout << num << " ";
}
```

### Array vs Vector Comparison

| Feature | C-Style Array | Vector |
|---------|---------------|--------|
| Size | Fixed at compile time | Dynamic |
| Memory | Stack or manual heap | Automatic management |
| Bounds checking | None | Optional with `.at()` |
| Size information | Lost in functions | Always available |
| Performance | Minimal overhead | Small overhead |
| Safety | Manual | Automatic |

### Multi-dimensional Arrays

**C-style 2D arrays:**
```cpp
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Access elements
cout << matrix[1][2] << endl;  // 7
```

**Vector of vectors:**
```cpp
std::vector<std::vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Access elements
cout << matrix[1][2] << endl;  // 7

// Dynamic sizing
matrix.push_back({13, 14, 15, 16});
```

## String Handling

### C-Style Strings

Character arrays terminated by null character (`\0`):

```cpp
#include <cstring>

char str1[] = "Hello";
char str2[20];

// String operations
strcpy(str2, str1);           // Copy string
strcat(str2, " World");       // Concatenate
int len = strlen(str2);       // Get length
int result = strcmp(str1, str2); // Compare strings

cout << str2 << endl;         // "Hello World"
cout << "Length: " << len << endl;
```

**Problems with C-strings:**
- Fixed size buffers
- Manual memory management
- Easy to cause buffer overflows
- Complex string operations

### C++ String Class

Modern string handling with the `std::string` class:

```cpp
#include <string>

std::string str1 = "Hello";
std::string str2 = "World";

// String operations
std::string combined = str1 + " " + str2;
str1 += " there";             // Append
int len = str1.length();      // Get length

// Comparison
if (str1 == str2) {
    cout << "Strings are equal" << endl;
}

// Access characters
cout << str1[0] << endl;      // 'H'
cout << str1.at(1) << endl;   // 'e' (bounds-checked)
```

### String Operations

Common string manipulation operations:

```cpp
std::string text = "Hello, World!";

// Substring
std::string sub = text.substr(7, 5);  // "World"

// Find
size_t pos = text.find("World");      // Position of "World"
if (pos != std::string::npos) {
    cout << "Found at position: " << pos << endl;
}

// Replace
text.replace(7, 5, "C++");           // "Hello, C++!"

// Case conversion (manual)
for (char& c : text) {
    c = std::tolower(c);
}

// Conversion to C-string
const char* c_str = text.c_str();
```

## Practice Exercises

### Exercise 1: Debugging Challenge

Debug the following code that has multiple errors:

```cpp
#include <iostream>

int main() {
    int* ptr;
    cout << *ptr << endl;  // Bug 1
    
    int arr[3] = {1, 2, 3};
    for (int i = 0; i <= 3; i++) {  // Bug 2
        cout << arr[i] << endl;
    }
    
    int* dynamic = new int[5];
    // Use dynamic array
    // Bug 3: Missing cleanup
    
    return 0;
}
```

### Exercise 2: Pointer Manipulation

Write a function that:
- Takes an array and its size as parameters
- Uses pointers to find the minimum and maximum values
- Returns both values through pointer parameters

```cpp
void find_min_max(int* arr, int size, int* min, int* max) {
    // TODO: Implement using pointer arithmetic
}
```

### Exercise 3: Array Processing

Create a program that:
- Reads integers from user input into a vector
- Processes the data using both C-style arrays and vectors
- Compares performance and safety aspects
- Demonstrates proper memory management

```cpp
#include <vector>
#include <chrono>

int main() {
    // TODO: Implement array processing comparison
    return 0;
}
```
</div>