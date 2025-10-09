# Lab 1: Debugging & Errors
Topics covered:

- [Naming Conventions](#naming-conventions)
  - [Variables and Functions](#variables-and-functions)
  - [Constants](#constants)
  - [Static Variables](#static-variables)
  - [Classes (Preview)](#classes-preview)
  - [Examples of Good vs Bad Naming:](#examples-of-good-vs-bad-naming)
- [Main Function Signatures](#main-function-signatures)
- [Debugging](#debugging)
  - [Using the debugger](#using-the-debugger)
  - [Compilation Process](#compilation-process)
- [C vs C++ I/O Differences](#c-vs-c-io-differences)
  - [Reading from Keyboard](#reading-from-keyboard)
  - [Displaying on Console](#displaying-on-console)

## Naming Conventions

**Mixed Camel Case** is the standard naming convention we use in this course. It makes code more readable and follows common C++ practices.

### Variables and Functions
Use **mixedCamelCase** (first letter lowercase, capitalize first letter of each subsequent word):

```cpp
// Variables
int studentAge = 20;
string firstName = "John";
double averageScore = 85.5;
bool isGameOver = false;

// Functions
void calculateTotal() { }
int getUserInput() { }
string getFullName() { }
bool checkPassword() { }
```

### Constants
Use **ALL_CAPS** with underscores for constants:

```cpp
const int MAX_STUDENTS = 100;
const double PI = 3.14159;
const string DEFAULT_NAME = "Unknown";
```

### Static Variables
Use **s_** prefix with mixedCamelCase for static variables:

```cpp
// Static local variables (inside functions)
void updateCounter() {
    static int s_callCount = 0;  // Retains value between calls
    s_callCount++;
}

// Static global variables (file scope)
static int s_fileCounter = 0;
static string s_currentUser = "guest";
```

### Classes (Preview)
Use **PascalCase** (first letter uppercase) for class names:

```cpp
class StudentRecord { };
class GameEngine { };
class DatabaseConnection { };
```

### Examples of Good vs Bad Naming:

```cpp
// ✅ GOOD - Consistent naming conventions
int currentScore = 0;              // mixedCamelCase for local variables
int g_totalPlayers = 100;          // g_ prefix for globals
static int s_gameCount = 0;        // s_ prefix for statics
const int MAX_LIVES = 3;           // ALL_CAPS for constants
string playerName = "Alice";
void updatePlayerStats() { }

// ❌ BAD - Inconsistent naming
int current_score = 0;             // snake_case
int totalPlayers = 100;            // global without g_ prefix
static int gameCount = 0;          // static without s_ prefix
const int maxLives = 3;            // constant not in ALL_CAPS
string PlayerName = "Alice";       // PascalCase for variable
void UpdatePlayerStats() { }       // PascalCase for function
```

**Why Mixed Camel Case?**
- **Readable**: Easy to distinguish words without underscores
- **Standard**: Widely used in C++ and many other languages
- **Consistent**: Reduces confusion when reading code
- **Professional**: Industry standard practice

> [!TIP]
> Choose meaningful names that describe what the variable or function does. `studentAge` is better than `age`, and `calculateFinalGrade()` is better than `calc()`.

## Main Function Signatures
```cpp
int main()
// OR
int main(int argc, char** argv)  // argc -> no. of arguments
                                  // argv -> array of arguments (array of char*)
```

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

## C vs C++ I/O Differences

Understanding the differences between C and C++ input/output operations is crucial for debugging and choosing the right approach for your programs.

### Reading from Keyboard

**C Style (stdio.h):**
```c
#include <stdio.h>

int main() {
    int number;
    char name[50];
    
    printf("Enter a number: ");
    scanf_s("%d", &number);         // Secure version with bounds checking
    
    printf("Enter your name: ");
    scanf_s("%49s", name, 49);      // Secure version with buffer size limit
    
    printf("Number: %d, Name: %s\n", number, name);
    return 0;
}
```

**C++ Style (iostream):**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int number;
    string name;
    
    cout << "Enter a number: ";
    cin >> number;                  // No & needed, cin handles it
    
    cout << "Enter your name: ";
    cin >> name;                    // Works with string objects
    
    cout << "Number: " << number << ", Name: " << name << endl;
    return 0;
}
```

**Key Differences:**
- **C**: Requires format specifiers (`%d`, `%s`) and address-of operator (`&`) for variables
- **C++**: Type-safe, no format specifiers needed, automatic type detection
- **C**: Limited string handling with character arrays, requires buffer size management
- **C++**: Better string handling with `string` class
- **C**: Secure versions (`scanf_s`) require explicit buffer sizes to prevent overflow

**Reading Lines with Spaces:**
```c
// C - reading a line with spaces (secure approach)
char line[100];
fgets(line, sizeof(line), stdin);   // Always use fgets() instead of gets()
```

```cpp
// C++ - reading a line with spaces
string line;
getline(cin, line);                 // Much simpler and safer
```

**Input Methods Comparison: cin vs getline vs sscanf**

Different input methods have different strengths and use cases:

```cpp
// METHOD 1: Using std::cin (SIMPLEST for basic input)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int age;
    
    cout << "Enter name and age: ";
    cin >> name >> age;             // Simple and direct
    
    cout << "Name: " << name << ", Age: " << age << endl;
    return 0;
}
```

```cpp
// METHOD 2: Using getline + stringstream (BEST for complex parsing)
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string line;
    cout << "Enter name and age: ";
    getline(cin, line);             // Read entire line
    
    stringstream ss(line);
    string name;
    int age;
    ss >> name >> age;              // Parse from string buffer
    
    cout << "Name: " << name << ", Age: " << age << endl;
    return 0;
}
```

```c
// METHOD 3: Using C-style sscanf (LEGACY approach)
#include <stdio.h>

int main() {
    char input[100];
    char name[50];
    int age;
    
    printf("Enter name and age: ");
    fgets(input, sizeof(input), stdin);  // Read line first
    sscanf(input, "%49s %d", name, &age); // Parse from buffer
    
    printf("Name: %s, Age: %d\n", name, age);
    return 0;
}
```

**When to use std::cin (You're right - it's often the best choice!):**

✅ **Use `std::cin` when:**
- Reading simple, space-separated values
- Input format is predictable and controlled
- You want clean, readable code
- Performance matters (fastest option)
- Working with basic data types

```cpp
// Perfect use cases for std::cin:
int x, y;
cin >> x >> y;                    // Reading two numbers

string firstName, lastName;
cin >> firstName >> lastName;     // Reading two words

double price;
cin >> price;                     // Reading a single value
```

**When `std::cin` has limitations:**
- Names with spaces: "John Smith" → `cin` reads only "John"
- Mixed input formats on same line
- Need to validate entire line before parsing
- Input contains special characters or formatting

**Comparison Summary:**

| Method | Best For | Pros | Cons |
|--------|----------|------|------|
| `std::cin` | Simple, predictable input | Fast, clean, type-safe | Stops at whitespace |
| `getline` | Complex input with spaces | Handles full lines | Requires extra parsing |
| `sscanf` | Legacy C code | Flexible formatting | Buffer overflow risk |

```c
// DANGEROUS - Never do this:
char name[10];
sscanf(input, "%s", name);  // No size limit - buffer overflow risk!

// BETTER - But still limited:
sscanf(input, "%9s", name); // Limits to 9 chars + null terminator
```

**Error Handling Comparison:**

```cpp
// std::cin with error handling (RECOMMENDED for most cases)
string name;
int age;
cout << "Enter name and age: ";

if (cin >> name >> age) {
    cout << "Successfully read: " << name << ", " << age << endl;
} else {
    cout << "Failed to read input" << endl;
    cin.clear();                    // Clear error flags
    cin.ignore(1000, '\n');        // Skip bad input
}
```

```cpp
// getline with error handling (for complex input)
string line, name;
int age;
cout << "Enter name and age: ";

if (getline(cin, line)) {
    stringstream ss(line);
    if (ss >> name >> age) {
        cout << "Successfully parsed: " << name << ", " << age << endl;
    } else {
        cout << "Failed to parse input" << endl;
    }
} else {
    cout << "Failed to read input" << endl;
}
```

```c
// C sscanf with error handling
char input[100], name[50];
int age;
printf("Enter name and age: ");

if (fgets(input, sizeof(input), stdin)) {
    int parsed = sscanf(input, "%49s %d", name, &age);
    if (parsed == 2) {
        printf("Successfully parsed: %s, %d\n", name, age);
    } else {
        printf("Failed to parse input (got %d items)\n", parsed);
    }
} else {
    printf("Failed to read input\n");
}
```

> [!IMPORTANT]
> **Recommendation**: Use `std::cin` for most input scenarios - it's simple, fast, and safe. Only use `getline` when you specifically need to handle input with spaces or complex parsing requirements.

### Displaying on Console

**C Style Output:**
```c
#include <stdio.h>

int main() {
    int age = 25;
    double height = 5.9;
    char grade = 'A';
    
    printf("Age: %d\n", age);           // %d for integers
    printf("Height: %.1f\n", height);  // %.1f for one decimal place
    printf("Grade: %c\n", grade);      // %c for characters
    
    printf("Age: %d, Height: %.1f, Grade: %c\n", age, height, grade);
    return 0;
}
```

**C++ Style Output:**
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int age = 25;
    double height = 5.9;
    char grade = 'A';
    
    cout << "Age: " << age << endl;
    cout << "Height: " << fixed << setprecision(1) << height << endl;
    cout << "Grade: " << grade << endl;
    
    cout << "Age: " << age << ", Height: " << height << ", Grade: " << grade << endl;
    return 0;
}
```

**Formatting Differences:**
- **C**: Uses format specifiers (`%d`, `%f`, `%c`, etc.)
- **C++**: Uses stream manipulators (`fixed`, `setprecision`, etc.)
- **C**: All formatting done in the printf call
- **C++**: Formatting can be applied to the stream and affects subsequent output

**Error Handling:**
```c
// C - scanf_s returns number of successful conversions
int result = scanf_s("%d", &number);
if (result != 1) {
    printf("Invalid input!\n");
}
```

```cpp
// C++ - cin has state flags
cin >> number;
if (cin.fail()) {
    cout << "Invalid input!" << endl;
    cin.clear();        // Clear error flags
    cin.ignore(1000, '\n');  // Ignore bad input
}
```

**Security Considerations:**
- **Secure C Functions**: Use `scanf_s`, `strcpy_s`, `strcat_s` instead of their unsafe counterparts
- **Buffer Overflow Prevention**: Always specify buffer sizes in secure functions
- **Platform Support**: Secure functions are Microsoft-specific; use `fgets` and bounds checking for portability
- **Legacy Code**: Avoid `gets()`, `scanf()` without size limits, and unbounded string operations

```c
// Secure alternatives for common unsafe functions:
scanf_s("%49s", buffer, 49);        // Instead of scanf("%s", buffer)
strcpy_s(dest, sizeof(dest), src);  // Instead of strcpy(dest, src)
strcat_s(dest, sizeof(dest), src);  // Instead of strcat(dest, src)
fgets(buffer, sizeof(buffer), stdin); // Always preferred over gets()
```

**Performance Considerations:**
- **C I/O**: Generally faster, especially for large amounts of data
- **C++ I/O**: More convenient and type-safe, but can be slower
- **Mixed usage**: Avoid mixing C and C++ I/O in the same program (can cause synchronization issues)

> [!TIP]
> For competitive programming or performance-critical applications, consider using C-style I/O or add `ios_base::sync_with_stdio(false)` to speed up C++ I/O

> [!WARNING]
> Secure C functions (`scanf_s`, `strcpy_s`, etc.) are Microsoft Visual Studio extensions. For cross-platform code, use standard alternatives like `fgets()` with proper bounds checking