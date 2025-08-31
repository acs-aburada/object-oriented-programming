# Lab 1: C++ Fundamentals & Debugging
Topics covered:

- [Debugging](#debugging)
  - [Using the debugger](#using-the-debugger)
  - [Compilation Process](#compilation-process)

## Main Function Signatures
```cpp
int main()
// OR
int main(int argc, char* argv[])  // argc -> no. of arguments
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