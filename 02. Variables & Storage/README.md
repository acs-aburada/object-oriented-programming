# Lab 2: Variables & Storage

Topics covered:

- [Types](#types)
  - [Integer Types](#integer-types)
  - [Floating-Point Types](#floating-point-types)
  - [Other Types](#other-types)
  - [Signed vs Unsigned](#signed-vs-unsigned)
- [Variables \& Storage](#variables--storage)
  - [Global Variables](#global-variables)
  - [Static Variables](#static-variables)
  - [Const Variables](#const-variables)

## Types

C++ provides several primitive (built-in) data types for storing different kinds of values.

### Integer Types
| Type | Size (bytes) | Range | Description |
|------|--------------|--------|-------------|
| `char` | 1 | -128 to 127 | Single character or small integer |
| `short` | 2 | -32,768 to 32,767 | Short integer |
| `int` | 4 | -2,147,483,648 to 2,147,483,647 | Standard integer |
| `long` | 4/8 | Platform dependent | Long integer |
| `long long` | 8 | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 | Very long integer |

### Floating-Point Types
| Type | Size (bytes) | Precision | Description |
|------|--------------|-----------|-------------|
| `float` | 4 | ~7 decimal digits | Single-precision floating-point |
| `double` | 8 | ~15 decimal digits | Double-precision floating-point |
| `long double` | 8/12/16 | Platform dependent | Extended precision floating-point |

### Other Types
| Type | Size (bytes) | Values | Description |
|------|--------------|--------|-------------|
| `bool` | 1 | `true` or `false` | Boolean value |
| `void` | - | No value | Represents absence of type |

### Signed vs Unsigned

**Signed types** can store both positive and negative values:
- Use one bit for the sign (positive/negative)
- Example: `int` ranges from -2,147,483,648 to 2,147,483,647

**Unsigned types** can only store non-negative values:
- Use all bits for the magnitude
- Double the positive range compared to signed
- Example: `unsigned int` ranges from 0 to 4,294,967,295

```cpp
int signed_num = -100;        // Can be negative
unsigned int unsigned_num = 100; // Cannot be negative (0 or positive only)
```

> [!TIP]
> Use `unsigned` when you know the value will never be negative (like array indices, counts, etc.)

## Variables & Storage

### Global Variables

**Global variables** are declared outside any function and can be accessed from anywhere in the program.

```cpp
int global_counter = 0;  // Global variable

int main() {
    global_counter = 10;  // Can access from main
    return 0;
}

void some_function() {
    global_counter++;     // Can access from any function
}
```

**Characteristics:**
- Accessible from any function in the program
- Stored in static memory (not on the stack)
- Initialized to zero by default if not explicitly initialized
- Exist for the entire program duration

> [!WARNING]
> Avoid excessive use of global variables as they can make code harder to debug and maintain

### Static Variables

**Static variables** have different behavior depending on where they're declared:

**1. Local Static Variables (inside functions):**
```cpp
void counter_function() {
    static int count = 0;  // Local static - initialized only once
    count++;
    cout << "Called " << count << " times" << endl;
}

int main() {
    counter_function();  // Output: Called 1 times
    counter_function();  // Output: Called 2 times
    counter_function();  // Output: Called 3 times
    return 0;
}
```

**2. Global Static Variables (outside functions):**
```cpp
static int file_counter = 0;  // Global static - only accessible in this file

void increment_counter() {
    file_counter++;  // Can access from any function in this file
}

int main() {
    increment_counter();
    cout << file_counter << endl;  // Output: 1
    return 0;
}
```

**Key differences:**
- **Local static**: Retains value between calls, but only accessible within that function
- **Global static**: Accessible throughout the file, but hidden from other source files

### Const Variables

**Const variables** are immutable - their value cannot be changed after initialization.

```cpp
const int MAX_SIZE = 100;        // Must be initialized
const double PI = 3.14159;

int main() {
    // MAX_SIZE = 200;  // ERROR: Cannot modify const variable
    
    const int user_input = 50;   // Runtime initialization allowed
    return 0;
}
```

**Benefits of const:**
- Prevents accidental modification
- Makes code more readable and self-documenting
- Compiler optimizations
- Can catch errors at compile-time

```cpp
void process_data(const int& data) {  // Parameter cannot be modified
    // data = 100;  // ERROR: Cannot modify const parameter
}
```
