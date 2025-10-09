# Lab 4: Functions & Control Structures

Topics covered:

- [Function Recap](#function-recap)
- [Parameter Passing](#parameter-passing)
  - [Passing by Value](#passing-by-value)
  - [Passing by Reference](#passing-by-reference)
  - [Passing by Pointer](#passing-by-pointer)
- [Types of Functions](#types-of-functions)
  - [Return Types](#return-types)
  - [Parameter Types](#parameter-types)
  - [Function Signatures](#function-signatures)
- [Recursive Functions](#recursive-functions)
- [Control Structures](#control-structures)
  - [If Statements](#if-statements)
  - [For Loops](#for-loops)
  - [While Loops](#while-loops)

## Function Recap

A **function** is a reusable block of code that performs a specific task. Functions help organize code, avoid repetition, and make programs easier to understand and maintain.

**Basic function structure:**
```cpp
return_type function_name(parameter_list) {
    // function body
    return value; // if return_type is not void
}
```

**Simple example:**
```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);  // result = 8
    return 0;
}
```

## Parameter Passing

There are three main ways to pass parameters to functions in C++:

### Passing by Value

The function receives a **copy** of the argument. Changes inside the function don't affect the original variable.

```cpp
void changeValue(int x) {
    x = 100;  // Only changes the copy
}

int main() {
    int num = 5;
    changeValue(num);
    cout << num << endl;  // Output: 5 (unchanged)
    return 0;
}
```

**Characteristics:**
- Safe - original data cannot be modified
- Uses more memory (creates copies)
- Good for small data types

### Passing by Reference

The function receives a **reference** to the original variable. Changes inside the function affect the original variable.

```cpp
void changeValue(int& x) {  // Note the & symbol
    x = 100;  // Changes the original variable
}

int main() {
    int num = 5;
    changeValue(num);
    cout << num << endl;  // Output: 100 (changed)
    return 0;
}
```

**Characteristics:**
- Efficient - no copying
- Can modify original data
- Cleaner syntax than pointers

### Passing by Pointer

The function receives the **address** of the variable. Must dereference the pointer to access/modify the value.

```cpp
void changeValue(int* x) {  // Note the * symbol
    *x = 100;  // Dereference to change the original
}

int main() {
    int num = 5;
    changeValue(&num);  // Pass address with &
    cout << num << endl;  // Output: 100 (changed)
    return 0;
}
```

**Characteristics:**
- Can modify original data
- More explicit about memory addresses
- Can pass nullptr for optional parameters

**Comparison:**
```cpp
void byValue(int x)     { x = 10; }      // Copy - no change to original
void byReference(int& x) { x = 10; }     // Reference - changes original
void byPointer(int* x)   { *x = 10; }    // Pointer - changes original

int main() {
    int a = 1, b = 2, c = 3;
    
    byValue(a);      // a remains 1
    byReference(b);  // b becomes 10
    byPointer(&c);   // c becomes 10
    
    cout << a << " " << b << " " << c << endl;  // Output: 1 10 10
    return 0;
}
```

## Types of Functions

### Return Types

**Functions with return values:**
```cpp
int getSum(int a, int b) {
    return a + b;  // Must return an int
}

double getAverage(int a, int b) {
    return (a + b) / 2.0;  // Must return a double
}
```

**Functions without return values (void):**
```cpp
void printMessage() {
    cout << "Hello World!" << endl;
    // No return statement needed
}

void displayResult(int result) {
    cout << "Result: " << result << endl;
    return;  // Optional - can return early
}
```

### Parameter Types

**Functions with parameters:**
```cpp
int multiply(int x, int y) {
    return x * y;
}

void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}
```

**Functions without parameters:**
```cpp
int getCurrentYear() {
    return 2024;
}

void showMenu() {
    cout << "1. Add\n2. Subtract\n3. Exit" << endl;
}
```

### Function Signatures

**Difference between `()` and `(void)`:**

```cpp
// In C++, these are equivalent:
int getNumber();      // No parameters
int getNumber(void);  // Explicitly no parameters (C-style)

// In C, there's a difference:
int func();       // Can accept any number of arguments (unsafe)
int func(void);   // Explicitly no parameters (safe)
```

**For C++, prefer the simpler `()` syntax:**
```cpp
// Preferred C++ style:
void doSomething();
int calculate();

// C-style (works but unnecessary):
void doSomething(void);
int calculate(void);
```

**Function overloading (same name, different parameters):**
```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}
```

## Recursive Functions

**Recursion** is when a function calls itself. Every recursive function needs:
1. **Base case** - condition to stop recursion
2. **Recursive case** - function calls itself with modified parameters

**Simple example - Factorial:**
```cpp
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    
    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    cout << factorial(5) << endl;  // Output: 120 (5*4*3*2*1)
    return 0;
}
```

**How it works:**
```
factorial(5) = 5 * factorial(4)
             = 5 * 4 * factorial(3)
             = 5 * 4 * 3 * factorial(2)
             = 5 * 4 * 3 * 2 * factorial(1)
             = 5 * 4 * 3 * 2 * 1
             = 120
```

**Another example - Countdown:**
```cpp
void countdown(int n) {
    // Base case
    if (n <= 0) {
        cout << "Done!" << endl;
        return;
    }
    
    // Recursive case
    cout << n << " ";
    countdown(n - 1);
}

int main() {
    countdown(5);  // Output: 5 4 3 2 1 Done!
    return 0;
}
```

> [!WARNING]
> Always ensure your recursive function has a base case, or it will run forever and cause a stack overflow!

## Control Structures

### If Statements

**Basic if statement:**
```cpp
int age = 18;

if (age >= 18) {
    cout << "You can vote!" << endl;
}
```

**If-else:**
```cpp
int score = 85;

if (score >= 90) {
    cout << "Grade: A" << endl;
} else if (score >= 80) {
    cout << "Grade: B" << endl;
} else if (score >= 70) {
    cout << "Grade: C" << endl;
} else {
    cout << "Grade: F" << endl;
}
```

**Ternary operator (shorthand):**
```cpp
int a = 10, b = 20;
int max = (a > b) ? a : b;  // max = 20
```

### For Loops

**Basic for loop:**
```cpp
// Print numbers 1 to 5
for (int i = 1; i <= 5; i++) {
    cout << i << " ";
}
// Output: 1 2 3 4 5
```

**For loop structure:**
```cpp
for (initialization; condition; increment) {
    // loop body
}
```

**Common patterns:**
```cpp
// Count down
for (int i = 10; i >= 1; i--) {
    cout << i << " ";
}

// Step by 2
for (int i = 0; i < 10; i += 2) {
    cout << i << " ";  // Output: 0 2 4 6 8
}

// Array iteration
int arr[] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
```

### While Loops

**Basic while loop:**
```cpp
int count = 1;
while (count <= 5) {
    cout << count << " ";
    count++;
}
// Output: 1 2 3 4 5
```

**Do-while loop (executes at least once):**
```cpp
int num;
do {
    cout << "Enter a positive number: ";
    cin >> num;
} while (num <= 0);
```

**Infinite loop with break:**
```cpp
while (true) {
    cout << "Enter 'q' to quit: ";
    char input;
    cin >> input;
    
    if (input == 'q') {
        break;  // Exit the loop
    }
    
    cout << "You entered: " << input << endl;
}
```

**For vs While - When to use:**
- **For loop**: When you know the number of iterations
- **While loop**: When the number of iterations depends on a condition

```cpp
// Use for when count is known
for (int i = 0; i < 10; i++) {
    // Do something 10 times
}

// Use while when condition-based
while (userWantsToContinue) {
    // Keep going until user says stop
}
```
