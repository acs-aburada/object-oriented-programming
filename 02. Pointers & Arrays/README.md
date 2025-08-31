# Lab 2: Pointers & Arrays
Topics covered:

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

### Understanding `int*` vs `int[]` - A Common Source of Confusion

Many students get confused about the difference between `int*` and `int[]`. Let's clarify this once and for all:

#### The Key Difference

**`int[]` is an ARRAY TYPE** - it represents a fixed-size collection of integers stored in contiguous memory.

**`int*` is a POINTER TYPE** - it's a variable that holds the memory address of an integer (or the first integer in a sequence).

#### Declaration Context Matters

**1. In variable declarations:**
```cpp
int arr[5];        // arr is an ARRAY of 5 integers
int* ptr;          // ptr is a POINTER that can point to an integer
```

**2. In function parameters (this is where confusion happens):**
```cpp
void function1(int arr[]);     // arr is actually a POINTER parameter
void function2(int* ptr);      // ptr is a POINTER parameter

// These two function declarations are IDENTICAL!
// The compiler treats int[] as int* in function parameters
```

#### Memory Layout Comparison

```cpp
// Array declaration - creates actual storage
int numbers[4] = {10, 20, 30, 40};
// Memory: [10][20][30][40] - 4 consecutive integers

// Pointer declaration - creates storage for an address
int* ptr = numbers;  // ptr points to the first element
// Memory: ptr -> [address] -> points to -> [10][20][30][40]
```

#### What You Can and Cannot Do

**Arrays (`int[]`):**
```cpp
int arr[5] = {1, 2, 3, 4, 5};

// ✅ Can do:
cout << arr[0] << endl;        // Access elements
cout << sizeof(arr) << endl;   // Get total size in bytes (20 bytes)
int size = sizeof(arr) / sizeof(arr[0]);  // Calculate number of elements (5)

// ❌ Cannot do:
// arr = some_other_array;     // ERROR: Cannot reassign arrays
// arr++;                      // ERROR: Cannot modify array name
```

**Pointers (`int*`):**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// ✅ Can do:
cout << ptr[0] << endl;        // Access elements (same syntax as arrays!)
cout << *ptr << endl;          // Dereference to get value
ptr++;                         // Move to next element
ptr = some_other_array;        // Reassign to point elsewhere

// ⚠️ Be careful:
cout << sizeof(ptr) << endl;   // Only gives size of pointer (8 bytes on 64-bit)
                              // NOT the size of what it points to!
```

#### The Array-to-Pointer Decay Rule

This is the most important concept to understand:

```cpp
int arr[5] = {1, 2, 3, 4, 5};

// When you use the array name in most contexts,
// it automatically "decays" to a pointer to its first element
int* ptr1 = arr;        // arr decays to &arr[0]
int* ptr2 = &arr[0];    // Explicitly getting address of first element

// ptr1 and ptr2 are identical!
cout << (ptr1 == ptr2) << endl;  // true
```

#### Function Parameter Reality Check

```cpp
// These function signatures are IDENTICAL:
void print_array1(int arr[]);      // Looks like array parameter
void print_array2(int arr[10]);    // Size is ignored!
void print_array3(int* arr);       // Clearly a pointer parameter

// Inside any of these functions:
void print_array1(int arr[]) {
    // arr is actually a POINTER, not an array!
    cout << sizeof(arr) << endl;    // Prints 8 (pointer size), not array size
    
    // This is why you need to pass size separately:
    // print_array1(my_array, 5);   // Need to pass size as second parameter
}
```

#### Practical Example - Why This Matters

```cpp
#include <iostream>
using namespace std;

void wrong_way(int arr[]) {
    // This won't work as expected!
    int size = sizeof(arr) / sizeof(arr[0]);  // WRONG: gives 8/4 = 2, not actual size
    cout << "Wrong size calculation: " << size << endl;
}

void right_way(int arr[], int actual_size) {
    // This works correctly
    cout << "Correct size: " << actual_size << endl;
    for (int i = 0; i < actual_size; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    
    // In main, numbers is still an array
    int correct_size = sizeof(numbers) / sizeof(numbers[0]);  // 5
    cout << "Array size in main: " << correct_size << endl;
    
    wrong_way(numbers);                    // numbers decays to int*
    right_way(numbers, correct_size);      // Pass size explicitly
    
    return 0;
}
```

#### Summary for Students

1. **`int[]` creates an actual array** - fixed size, stored in contiguous memory
2. **`int*` is just a pointer** - holds an address, can be reassigned
3. **In function parameters, `int[]` becomes `int*`** - the array "decays" to a pointer
4. **Arrays know their size, pointers don't** - always pass array size to functions
5. **Both use the same `[]` syntax** for accessing elements, but they're fundamentally different

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
---
&rarr; **Data Type Size Impact**

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
```
---
&rarr; **Array Traversal with Pointer Arithmetic**

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
---
&rarr; **Common Safety Concerns**

**1. Bounds checking is YOUR responsibility:**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// DANGEROUS: No bounds checking
ptr += 10;                  // Points outside array bounds
// cout << *ptr << endl;    // UNDEFINED BEHAVIOR!

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
// void_ptr++;      // Compilation error!

// CORRECT: Cast to appropriate type first
int* int_ptr = static_cast<int*>(void_ptr);
int_ptr++;          // Now this works
```


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
    ptr = &x;               // ptr points to x
}  // x goes out of scope
cout << *ptr << endl;       // UNDEFINED: x no longer exists
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
    delete ptr;     // Free memory
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