# Lab 3: Pointers, Arrays & Strings
Topics covered:

- [Pointers Review](#pointers-review)
  - [Pointer Basics](#pointer-basics)
  - [Understanding `int*` vs `int[]` - A Common Source of Confusion](#understanding-int-vs-int---a-common-source-of-confusion)
  - [Pointer Arithmetic](#pointer-arithmetic)
  - [Common Pointer Mistakes](#common-pointer-mistakes)
  - [Dynamic Memory Allocation](#dynamic-memory-allocation)
- [Arrays and Memory Management](#arrays-and-memory-management)
  - [C-Style Arrays](#c-style-arrays)
  - [Dynamic Memory: C vs C++](#dynamic-memory-c-vs-c)
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

Understanding and avoiding these common mistakes is crucial for safe pointer usage.

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

A dangling pointer points to memory that has been deallocated or is no longer valid. This creates undefined behavior when accessed.

**Example 1 - Stack variable goes out of scope:**
```cpp
int* ptr;
{
    int x = 42;
    ptr = &x;               // ptr points to x
}  // x goes out of scope and is destroyed
cout << *ptr << endl;       // UNDEFINED: x no longer exists
```

**Example 2 - Pointer to deleted memory:**
```cpp
int* ptr1 = new int(42);
int* ptr2 = ptr1;           // Both point to same memory

delete ptr1;                // Memory is freed
ptr1 = nullptr;             // ptr1 is safe now

cout << *ptr2 << endl;      // UNDEFINED: ptr2 is now dangling!
```

**Example 3 - Returning pointer to local variable:**
```cpp
int* dangerous_function() {
    int local_var = 100;
    return &local_var;      // WRONG: local_var will be destroyed
}

int* ptr = dangerous_function();
cout << *ptr << endl;       // UNDEFINED: points to destroyed variable
```

**How to avoid dangling pointers:**
```cpp
// 1. Set pointers to nullptr after deletion
int* ptr = new int(42);
delete ptr;
ptr = nullptr;              // Now safe

// 2. Use dynamic allocation for data that outlives scope
int* safe_function() {
    int* ptr = new int(100); // Allocated on heap
    return ptr;              // Safe to return
}
// Remember to delete the returned pointer later!

// 3. Check validity before use
if (ptr != nullptr) {
    cout << *ptr << endl;
}
```

**3. Memory leaks:**

Memory leaks occur when dynamically allocated memory is not freed, causing the program to consume more and more memory over time.

**Example 1 - Forgot to delete:**
```cpp
void create_leak() {
    int* ptr = new int(42);
    // Forgot to delete ptr
}  // Memory leaked - 4 bytes lost forever

// If called 1000 times, 4000 bytes are leaked
for (int i = 0; i < 1000; i++) {
    create_leak();
}
```

**Example 2 - Early return without cleanup:**
```cpp
void risky_function(bool condition) {
    int* data = new int[1000];  // Allocate memory
    
    if (condition) {
        return;                 // LEAK: forgot to delete[] data
    }
    
    // Process data...
    delete[] data;              // Only reached if condition is false
}
```

**Example 3 - Exception thrown before cleanup:**
```cpp
void exception_leak() {
    int* ptr = new int(42);
    
    // Some operation that might throw
    if (some_error_condition) {
        throw std::exception(); // LEAK: ptr never deleted
    }
    
    delete ptr;  // Never reached if exception is thrown
}
```

**How to prevent memory leaks:**

**Method 1 - Always pair new/delete:**
```cpp
void no_leak() {
    int* ptr = new int(42);
    cout << *ptr << endl;
    delete ptr;     // Always delete what you new
    ptr = nullptr;  // Prevent dangling pointer
}
```

**Method 2 - Early cleanup with guard pattern:**
```cpp
void better_function(bool condition) {
    int* data = new int[1000];
    bool cleanup_needed = true;
    
    if (condition) {
        delete[] data;
        data = nullptr;     // Prevent dangling pointer
        cleanup_needed = false;
        return;
    }
    
    // Process data...
    
    if (cleanup_needed) {
        delete[] data;
        data = nullptr;     // Prevent dangling pointer
    }
}
```

**Detecting memory leaks:**
- **Valgrind** (Linux/Mac): `valgrind --leak-check=full ./your_program`
- **Visual Studio** (Windows): Built-in diagnostic tools
- **AddressSanitizer**: Compile with `-fsanitize=address`

> [!WARNING]
> Memory leaks in long-running programs (servers, GUI applications) can eventually cause the system to run out of memory, leading to crashes or system instability.

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

> [!NOTE]
> Modern C++ (C++11 and later) provides smart pointers like `std::unique_ptr` and `std::shared_ptr` for automatic memory management, but traditional `new`/`delete` remains important to understand.

## Arrays and Memory Management

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

### Dynamic Memory: C vs C++

The transition from C to C++ brought significant improvements in dynamic memory management while maintaining compatibility with C-style allocation.

#### C-Style Dynamic Memory Allocation

**Using malloc, calloc, realloc, and free:**

```c
#include <stdlib.h>

// malloc - allocates uninitialized memory
int* ptr1 = (int*)malloc(5 * sizeof(int));
if (ptr1 == NULL) {
    // Handle allocation failure
    exit(1);
}

// calloc - allocates zero-initialized memory
int* ptr2 = (int*)calloc(5, sizeof(int));  // 5 integers, all set to 0

// realloc - resize allocated memory
ptr1 = (int*)realloc(ptr1, 10 * sizeof(int));  // Resize to 10 integers

// Use the arrays
for (int i = 0; i < 5; i++) {
    ptr1[i] = i * 10;
    printf("%d ", ptr2[i]);  // All zeros initially
}

// Must manually free memory
free(ptr1);
free(ptr2);
ptr1 = NULL;  // Good practice to avoid dangling pointers
ptr2 = NULL;
```

#### C++ Dynamic Memory Allocation

**Using new and delete operators:**

```cpp
// new - allocates and can initialize
int* ptr1 = new int;           // Single integer (uninitialized)
int* ptr2 = new int(42);       // Single integer initialized to 42
int* ptr3 = new int();         // Single integer initialized to 0

// new[] - array allocation
int* arr1 = new int[5];        // Array of 5 integers (uninitialized)
int* arr2 = new int[5]();      // Array of 5 integers (zero-initialized)
int* arr3 = new int[5]{1, 2, 3, 4, 5};  // Array with initial values

// Use the arrays
for (int i = 0; i < 5; i++) {
    arr1[i] = i * 10;
    cout << arr2[i] << " ";    // All zeros initially
}

// delete and delete[] - free memory
delete ptr1;     // For single objects
delete ptr2;
delete ptr3;

delete[] arr1;   // For arrays - MUST use delete[]
delete[] arr2;
delete[] arr3;
```

#### Key Differences: C vs C++

| Aspect | C Style | C++ Style |
|--------|---------|-----------|
| **Allocation** | `malloc()`, `calloc()` | `new`, `new[]` |
| **Deallocation** | `free()` | `delete`, `delete[]` |
| **Type Safety** | Requires casting | Type-safe |
| **Initialization** | Manual or `calloc()` | Can initialize in allocation |
| **Constructor/Destructor** | Not called | Automatically called |
| **Error Handling** | Returns NULL | Throws exception (by default) |

#### Memory Management Best Practices

**1. Match allocation with deallocation:**
```cpp
// WRONG - Mismatched allocation/deallocation
int* ptr = (int*)malloc(sizeof(int));
delete ptr;  // Should use free()

int* arr = new int[10];
delete arr;  // Should use delete[]

// CORRECT - Matched pairs
int* ptr1 = (int*)malloc(sizeof(int));
free(ptr1);

int* ptr2 = new int;
delete ptr2;

int* arr = new int[10];
delete[] arr;
```

**2. Always check for allocation failure:**
```cpp
// C style
int* ptr = (int*)malloc(1000000 * sizeof(int));
if (ptr == NULL) {
    // Handle failure
    return -1;
}

// C++ style with exception handling
try {
    int* arr = new int[1000000];
    // Use array
    delete[] arr;
} catch (const std::bad_alloc& e) {
    cout << "Allocation failed: " << e.what() << endl;
}

// C++ style with nothrow
int* arr = new(std::nothrow) int[1000000];
if (arr == nullptr) {
    // Handle failure
    return -1;
}
delete[] arr;
```

**3. Avoid memory leaks and dangling pointers:**
```cpp
void safe_dynamic_allocation() {
    int* data = new int[100];
    
    try {
        // Use data...
        // If exception occurs, memory won't be leaked
        delete[] data;
        data = nullptr;
    } catch (...) {
        delete[] data;  // Clean up before re-throwing
        throw;
    }
}
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