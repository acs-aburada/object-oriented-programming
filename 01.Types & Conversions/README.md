# Lab 1 — Types, Conversions, Const, Static, Arrays (C++23)

**Welcome to Object-Oriented Programming!** This is your first lab where you'll learn fundamental concepts that form the backbone of C++ programming.

- [Fundamental Types](#fundamental-types)
  - [Integer Types (Whole Numbers)](#integer-types-whole-numbers)
  - [Floating-Point Types (Decimal Numbers)](#floating-point-types-decimal-numbers)
  - [Boolean Type](#boolean-type)
  - [Character Types](#character-types)
  - [Pointer Types](#pointer-types)
  - [Custom Types - Creating Your Own Data Types](#custom-types---creating-your-own-data-types)
- [Structs - Simple Data Containers](#structs---simple-data-containers)
  - [Structs can have functions too!](#structs-can-have-functions-too)
  - [Constructors - Smart Initialization](#constructors---smart-initialization)
  - [More Struct Examples](#more-struct-examples)
- [Introducing Visibility - Controlling Access](#introducing-visibility---controlling-access)
  - [Adding Private Members to Structs](#adding-private-members-to-structs)
- [Classes - Objects with Controlled Behavior](#classes---objects-with-controlled-behavior)
  - [Simple Class Examples](#simple-class-examples)
  - [More Complex Class Example](#more-complex-class-example)
- [Struct vs Class - When to Use Which?](#struct-vs-class---when-to-use-which)
  - [The Technical Difference](#the-technical-difference)
  - [Use Struct When:](#use-struct-when)
  - [Use Class When:](#use-class-when)
  - [Decision Guide:](#decision-guide)
  - [Real Examples:](#real-examples)
- [Conversions Between Types](#conversions-between-types)
  - [1. Implicit conversions (automatic)](#1-implicit-conversions-automatic)
  - [2. Explicit conversions (you ask for them)](#2-explicit-conversions-you-ask-for-them)
- [Creating Your Own Conversions](#creating-your-own-conversions)
  - [Conversion constructors (converting TO your class)](#conversion-constructors-converting-to-your-class)
  - [Conversion operators (converting FROM your class)](#conversion-operators-converting-from-your-class)
- [Copy Constructor vs Assignment Operator](#copy-constructor-vs-assignment-operator)
  - [When is a new object created?](#when-is-a-new-object-created)
  - [Copy Constructor](#copy-constructor)
  - [Assignment Operator](#assignment-operator)
  - [Why do we need both?](#why-do-we-need-both)
- [The `const` Keyword - Making Things Unchangeable](#the-const-keyword---making-things-unchangeable)
  - [const variables](#const-variables)
  - [const with pointers (this is tricky!)](#const-with-pointers-this-is-tricky)
  - [const member functions](#const-member-functions)
  - [const references (very common in function parameters)](#const-references-very-common-in-function-parameters)
- [Static Members - Sharing Data Between All Objects](#static-members---sharing-data-between-all-objects)
  - [static data members](#static-data-members)
  - [inline static (C++17 and later)](#inline-static-c17-and-later)
  - [static member functions](#static-member-functions)
  - [static local variables](#static-local-variables)
- [Arrays of Objects](#arrays-of-objects)
  - [Basic arrays of objects](#basic-arrays-of-objects)
  - [Modern arrays with vector](#modern-arrays-with-vector)
  - [Arrays of pointers vs arrays of objects](#arrays-of-pointers-vs-arrays-of-objects)
  - [Can you have arrays of references?](#can-you-have-arrays-of-references)
- [Common Mistakes and How to Avoid Them](#common-mistakes-and-how-to-avoid-them)
  - [1. Shallow vs Deep Copy](#1-shallow-vs-deep-copy)
  - [2. Forgetting const correctness](#2-forgetting-const-correctness)
  - [3. Using C-style casts](#3-using-c-style-casts)
- [Practice Exercises](#practice-exercises)
  - [Exercise 1: Temperature Converter](#exercise-1-temperature-converter)
  - [Exercise 2: Student Registry](#exercise-2-student-registry)
  - [Exercise 3: Dynamic Array](#exercise-3-dynamic-array)
- [Quick Reference](#quick-reference)
  - [When to use each cast:](#when-to-use-each-cast)
  - [Copy constructor vs Assignment:](#copy-constructor-vs-assignment)
  - [const guidelines:](#const-guidelines)
  - [static guidelines:](#static-guidelines)


## Fundamental Types

In programming, a **type** tells the computer what kind of data you're working with, how much memory it needs, what operations you can perform on it, and what values it can hold.

### Integer Types (Whole Numbers)

| Type | 32-bit Size | 64-bit Size | Signed Range (for given size) | Unsigned Range (for given size) |
|------|-------------|-------------|-------------------------------|----------------------------------|
| `char` | 1 byte | 1 byte | -128 to 127 (8-bit) | 0 to 255 (8-bit) |
| `short` | 2 bytes | 2 bytes | -32,768 to 32,767 (16-bit) | 0 to 65,535 (16-bit) |
| `int` | 4 bytes | 4 bytes | -2,147,483,648 to 2,147,483,647 (32-bit) | 0 to 4,294,967,295 (32-bit) |
| `long` | 4 bytes | 8 bytes | -2,147,483,648 to 2,147,483,647 (32-bit size)<br>-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 (64-bit size) | 0 to 4,294,967,295 (32-bit size)<br>0 to 18,446,744,073,709,551,615 (64-bit size) |
| `long long` | 8 bytes | 8 bytes | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 (64-bit) | 0 to 18,446,744,073,709,551,615 (64-bit) |

> [!TIP]
> <font color="lightgreen"> It is not important to know these ranges from memory, the only relevant values are those of type `char` (both `signed` and `unsigned`).</font>

```cpp
// Signed integers (can be negative)
int temperature = -15;        // 4 bytes, can be negative
short small_number = 1000;    // 2 bytes, smaller range
long big_number = 2000000000; // 4 or 8 bytes depending on architecture
long long huge = 9223372036854775807LL; // Always 8 bytes

// Unsigned integers (only positive)
unsigned int count = 4000000000U;     // Can hold larger positive values
unsigned char byte_value = 255;       // 0-255 range
unsigned short port = 65535;          // Network ports often use this

// Character type (special integer)
char letter = 'A';           // Stores ASCII value 65
char digit = '7';            // Stores ASCII value 55 equal to '7', NOT number 7
```

**Key Properties:**
- **Overflow behavior**: When you exceed the maximum value, it wraps around
```cpp
unsigned char x = 255;
x++;  // x is now 0 (wrapped around)

int y = 2147483647;  // Maximum signed int value
y++;  // Undefined behavior! Could be -2147483648 or crash
```
> [!NOTE]
> <font color="#2e7eff"><code style="color:#5797ff">Overflow</code> = when a computer program or system tries to store more data in a fixed-size location than it can handle, resulting in data loss or corruption</font>

### Floating-Point Types (Decimal Numbers)

| Type | Size | Precision | Range (approximate) |
|------|------|-----------|---------------------|
| `float` | 4 bytes | ~7 decimal digits | ±3.4 × 10³⁸ |
| `double` | 8 bytes | ~15-17 decimal digits | ±1.7 × 10³⁰⁸ |
| `long double` | 8-16 bytes | Varies by compiler | Extended precision |

```cpp
float pi_f = 3.14159f;           // 'f' suffix for float literals
double pi_d = 3.141592653589793; // Default for decimal literals
long double pi_ld = 3.141592653589793238L; // 'L' suffix

// Precision demonstration
float imprecise = 0.1f + 0.2f;   // Might not equal exactly 0.3!
double more_precise = 0.1 + 0.2; // Better, but still not perfect

// Special floating-point values
double positive_infinity = 1.0 / 0.0;  // inf
double negative_infinity = -1.0 / 0.0; // -inf
double not_a_number = 0.0 / 0.0;       // nan
```

**Key Properties:**
- **IEEE 754 standard**: How computers store floating-point numbers
- **Precision loss**: Not all decimal numbers can be represented exactly
- **Comparison issues**: Never use `==` with floating-point numbers
```cpp
// WRONG
if (0.1 + 0.2 == 0.3) { /* might never execute */ }

// CORRECT
double epsilon = 1e-9;
if (abs((0.1 + 0.2) - 0.3) < epsilon) { /* safe comparison */ }
```

### Boolean Type

| Type | Size | Values |
|------|------|--------|
| `bool` | 1 byte | `true` (1) or `false` (0) |

```cpp
// Any non-zero value converts to true
bool from_int = 42;             // true
bool from_zero = 0;             // false
bool from_pointer = nullptr;    // false
```

### Character Types

| Type | Size | Purpose | Range |
|------|------|---------|-------|
| `char` | 1 byte | ASCII characters | -128 to 127 or 0 to 255 |
| `signed char` | 1 byte | Explicitly signed | -128 to 127 |
| `unsigned char` | 1 byte | Explicitly unsigned | 0 to 255 |
| `wchar_t` | 2-4 bytes | Wide characters (Unicode) | Platform dependent |
| `char16_t` | 2 bytes | UTF-16 characters | 0 to 65,535 |
| `char32_t` | 4 bytes | UTF-32 characters | 0 to 4,294,967,295 |

```cpp
char ascii_char = 'A';           // ASCII character
char ascii_value = 65;           // Same as 'A'

// Wide characters for international text
wchar_t wide_char = L'ñ';        // Spanish ñ
char16_t utf16_char = u'€';      // Euro symbol
char32_t utf32_char = U'🚀';     // Rocket emoji

// String literals
const char* ascii_string = "Hello";
const wchar_t* wide_string = L"Hëllö";
const char16_t* utf16_string = u"Héllo";
const char32_t* utf32_string = U"H€llo 🌍";
```

### Pointer Types

| Architecture | Pointer Size |
|--------------|-------------|
| 32-bit | 4 bytes |
| 64-bit | 8 bytes |

```cpp
int x = 42;
int* ptr = &x;              // Pointer to int
int** ptr_to_ptr = &ptr;    // Pointer to pointer to int

// Null pointer
int* null_ptr = nullptr;    // Modern C++ way
int* old_null = NULL;       // C-style (avoid)
int* zero_ptr = 0;          // Also null (avoid)

// Void pointer (can point to anything)
void* generic_ptr = &x;     // Points to x, but type info lost
```

### Custom Types - Creating Your Own Data Types

Now that you understand the building blocks, let's create our own types to group related data together.

## Structs - Simple Data Containers

A `struct` is the simplest way to group related data together:

```cpp
struct Student {
    string name;
    int age;
    double gpa;
};
```

Now you can create and use Student objects:

```cpp
Student alice;
alice.name = "Alice";
alice.age = 20;
alice.gpa = 3.8;

Student bob = {"Bob", 19, 3.2};  // Initialize all at once

cout << alice.name << " is " << alice.age << " years old" << endl;
```

### Structs can have functions too!

```cpp
struct Point {
    double x, y;
    
    double distance_from_origin() {
        return sqrt(x*x + y*y);
    }
    
    void move(double dx, double dy) {
        x += dx;
        y += dy;
    }
};

Point p = {3.0, 4.0};
cout << "Distance: " << p.distance_from_origin() << endl;  // 5.0
p.move(1.0, 1.0);  // Now p is at (4.0, 5.0)
```

### Constructors - Smart Initialization

Instead of setting values manually, you can add a **constructor**:

```cpp
struct Rectangle {
    double width, height;
    
    Rectangle(double w, double h) {
        width = w;
        height = h;
    }
    
    double area() {
        return width * height;
    }
};

Rectangle room(10.0, 12.0);  // Create 10x12 rectangle
cout << "Room area: " << room.area() << endl;
```

### More Struct Examples

```cpp
// Configuration data
struct GameSettings {
    int screen_width;
    int screen_height;
    bool fullscreen;
    double volume;
};

// Mathematical objects
struct Color {
    int red, green, blue;
    
    Color(int r, int g, int b) : red(r), green(g), blue(b) {}
};

// Return multiple values from functions
struct MinMax {
    int minimum;
    int maximum;
};

MinMax find_min_max(vector<int> numbers) {
    MinMax result;
    result.minimum = *min_element(numbers.begin(), numbers.end());
    result.maximum = *max_element(numbers.begin(), numbers.end());
    return result;
}
```

**Key point about structs**: Everything is **public** by default - anyone can access and modify all the data directly.

## Introducing Visibility - Controlling Access

Sometimes you don't want everyone to access all parts of your data. C++ provides three levels of access:

- **public**: Anyone can access
- **private**: Only the class/struct itself can access
- **protected**: Only the class and its children can access (we'll learn about inheritance later)

### Adding Private Members to Structs

```cpp
struct BankAccount {
public:  // Anyone can use these
    string owner_name;
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double get_balance() {
        return balance;
    }

private:  // Only BankAccount can use these
    double balance = 0.0;
    string account_number = "SECRET123";
};

BankAccount account;
account.owner_name = "Alice";  // OK - public
account.deposit(100.0);        // OK - public
cout << account.get_balance(); // OK - public

// account.balance = -1000;    // ERROR! balance is private
// account.account_number = "HACKED"; // ERROR! private
```

**Why private members?** 
- Prevent invalid data (negative balance)
- Hide implementation details
- Control how data is accessed and modified

## Classes - Objects with Controlled Behavior

A `class` is almost identical to a `struct`, with one difference: **everything is private by default**.

```cpp
class SimpleCounter {
    int count = 0;  // PRIVATE by default
    
public:  // Must explicitly make things public
    void increment() {
        count++;
    }
    
    void reset() {
        count = 0;
    }
    
    int get_value() {
        return count;
    }
};

SimpleCounter counter;
counter.increment();
counter.increment();
cout << counter.get_value() << endl;  // 2

// counter.count = 1000;  // ERROR! count is private
```

### Simple Class Examples

```cpp
class Temperature {
    double celsius;
    
public:
    Temperature(double temp) : celsius(temp) {}
    
    double to_fahrenheit() {
        return celsius * 9.0/5.0 + 32.0;
    }
    
    void set_celsius(double temp) {
        celsius = temp;
    }
    
    double get_celsius() {
        return celsius;
    }
};

Temperature today(25.0);
cout << "Today: " << today.to_fahrenheit() << "°F" << endl;
```

```cpp
class Timer {
    int seconds;
    
public:
    Timer() : seconds(0) {}
    
    void tick() {
        seconds++;
    }
    
    void reset() {
        seconds = 0;
    }
    
    int get_minutes() {
        return seconds / 60;
    }
    
    int get_seconds() {
        return seconds % 60;
    }
};

Timer stopwatch;
stopwatch.tick();
stopwatch.tick();
cout << stopwatch.get_minutes() << ":" << stopwatch.get_seconds() << endl;
```

### More Complex Class Example

```cpp
class SafeArray {
    vector<int> data;
    
public:
    SafeArray(int size) : data(size, 0) {}
    
    bool set(int index, int value) {
        if (index >= 0 && index < data.size()) {
            data[index] = value;
            return true;
        }
        return false;  // Invalid index
    }
    
    int get(int index) {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        return -1;  // Error value
    }
    
    int size() {
        return data.size();
    }
};

SafeArray arr(10);
arr.set(5, 42);
cout << arr.get(5) << endl;  // 42
cout << arr.get(15) << endl; // -1 (error - index too big)
```

## Struct vs Class - When to Use Which?

### The Technical Difference
```cpp
struct MyStruct {
    int public_by_default;  // PUBLIC by default
private:
    int must_specify_private;
};

class MyClass {
    int private_by_default; // PRIVATE by default
public:
    int must_specify_public;
};
```

**That's the ONLY difference!** But the usage patterns are very different:

### Use Struct When:
- **Simple data containers** - mainly storing related values
- **All data can be public** - no need to hide anything
- **Mathematical objects** - points, colors, vectors
- **Configuration data** - settings, options
- **Returning multiple values** from functions

```cpp
struct Point2D {
    double x, y;
    Point2D(double x_val, double y_val) : x(x_val), y(y_val) {}
};

struct StudentGrade {
    string subject;
    double grade;
    string letter_grade;
};

struct DatabaseConfig {
    string host;
    int port;
    string username;
    bool use_ssl;
};
```

### Use Class When:
- **Need data protection** - prevent invalid states
- **Complex behavior** - the object "does things"
- **Resource management** - files, memory, network connections
- **Business logic** - accounts, users, game objects

```cpp
class Calculator {
    double result = 0;
    
public:
    void add(double x) { result += x; }
    void multiply(double x) { result *= x; }
    void clear() { result = 0; }
    double get_result() { return result; }
};

class FileWriter {
    string filename;
    bool is_open = false;
    
public:
    FileWriter(string name) : filename(name) {}
    bool open();
    bool write(string data);
    void close();
};
```

### Decision Guide:

| **Question** | **Struct** | **Class** |
|--------------|------------|-----------|
| Can all data be public? | ✅ Yes | ❌ No |
| Mainly storing data? | ✅ Yes | ❌ No |
| Simple operations only? | ✅ Yes | ❌ No |
| Need to prevent invalid data? | ❌ No | ✅ Yes |
| Complex behavior? | ❌ No | ✅ Yes |
| Managing resources? | ❌ No | ✅ Yes |

### Real Examples:

**Good struct usage:**
```cpp
struct RGB {
    int red, green, blue;
    RGB(int r, int g, int b) : red(r), green(g), blue(b) {}
};

struct PlayerScore {
    string player_name;
    int score;
    int level;
};
```

**Good class usage:**
```cpp
class BankAccount {
    double balance;
    string account_id;
    
public:
    BankAccount(string id) : account_id(id), balance(0) {}
    bool deposit(double amount);
    bool withdraw(double amount);
    double get_balance() const;
};

class GameCharacter {
    int health;
    int max_health;
    
public:
    GameCharacter() : health(100), max_health(100) {}
    void take_damage(int damage);
    void heal(int amount);
    bool is_alive() const;
};
```

---

## Conversions Between Types

Sometimes you need to convert from one type to another. There are several ways to do this.

### 1. Implicit conversions (automatic)
Some conversions happen automatically:

```cpp
int x = 5;
double y = x;  // int automatically converts to double
cout << y;     // prints 5.0
```

### 2. Explicit conversions (you ask for them)

#### C-style cast (old way - avoid this!)
```cpp
double pi = 3.14159;
int approx = (int)pi;  // becomes 3 (truncates decimal part)
```

#### static_cast (modern way - preferred!)
```cpp
double pi = 3.14159;
int approx = static_cast<int>(pi);  // same result, but safer
```

**Why is static_cast better?**
- The compiler checks if the conversion makes sense
- It's more visible in your code
- It prevents dangerous conversions

#### const_cast (for removing/adding const)
```cpp
void print_number(const int* num) {
    // num points to a const int, we can't change it
    cout << *num << endl;
}

void modify_number(int* num) {
    *num = 42;  // this function needs to modify the number
}

int main() {
    const int value = 10;
    print_number(&value);  // works fine
    
    // modify_number(&value);  // ERROR! Can't pass const int* to int*
    modify_number(const_cast<int*>(&value));  // removes const (dangerous!)
}
```

#### reinterpret_cast (low-level, very dangerous)
```cpp
int number = 65;
char* as_char = reinterpret_cast<char*>(&number);
// Treats the memory of 'number' as if it contains a char
// Very dangerous - only use when you know exactly what you're doing!
```

#### dynamic_cast (for inheritance - you'll learn this later)
```cpp
// We'll cover this when we learn about inheritance
```

---

## Creating Your Own Conversions

### Conversion constructors (converting TO your class)

```cpp
struct Temperature {
    double celsius;
    
    // This constructor allows: Temperature t = 25.0;
    Temperature(double c) : celsius(c) {
        cout << "Converting " << c << " to Temperature" << endl;
    }
};

int main() {
    Temperature room = 22.5;  // calls Temperature(22.5)
    Temperature hot(100.0);   // also calls Temperature(100.0)
}
```

But sometimes automatic conversion is dangerous:

```cpp
struct BankAccount {
    double balance;
    
    // BAD: BankAccount account = 1000000; might be a mistake!
    BankAccount(double initial_balance) : balance(initial_balance) {}
};
```

Use `explicit` to prevent accidental conversions:

```cpp
struct BankAccount {
    double balance;
    
    // GOOD: Must explicitly write BankAccount(1000000)
    explicit BankAccount(double initial_balance) : balance(initial_balance) {}
};

int main() {
    // BankAccount account = 1000000;  // ERROR! 
    BankAccount account(1000000);      // OK - explicit
}
```

### Conversion operators (converting FROM your class)

```cpp
struct Temperature {
    double celsius;
    
    Temperature(double c) : celsius(c) {}
    
    // Convert Temperature to double
    operator double() const {
        return celsius;
    }
    
    // Convert Temperature to Fahrenheit (as int)
    explicit operator int() const {
        return static_cast<int>(celsius * 9.0 / 5.0 + 32.0);
    }
};

int main() {
    Temperature room(25.0);
    
    double temp_as_double = room;  // calls operator double()
    cout << "Celsius: " << temp_as_double << endl;
    
    int fahrenheit = static_cast<int>(room);  // calls explicit operator int()
    cout << "Fahrenheit: " << fahrenheit << endl;
}
```

---

## Copy Constructor vs Assignment Operator

This is **super important** and confuses many beginners!

### When is a new object created?

```cpp
Student alice("Alice", 20, 'A');
Student bob = alice;    // NEW object created - calls COPY CONSTRUCTOR
Student charlie;        // NEW empty object
charlie = alice;        // EXISTING object modified - calls ASSIGNMENT OPERATOR
```

### Copy Constructor
Called when creating a **new** object from an existing one:

```cpp
struct Student {
    string name;
    int age;
    char grade;
    
    // Copy constructor
    Student(const Student& other) {
        cout << "Copy constructor called!" << endl;
        name = other.name;
        age = other.age;
        grade = other.grade;
    }
};
```

**When is it called?**
```cpp
Student alice("Alice", 20, 'A');
Student bob = alice;           // Copy constructor
Student charlie(alice);        // Copy constructor
pass_student_by_value(alice);  // Copy constructor (making copy for function)
```

### Assignment Operator
Called when assigning to an **existing** object:

```cpp
struct Student {
    string name;
    int age;
    char grade;
    
    // Assignment operator
    Student& operator=(const Student& other) {
        cout << "Assignment operator called!" << endl;
        if (this == &other) return *this;  // Don't copy to yourself!
        
        name = other.name;
        age = other.age;
        grade = other.grade;
        return *this;
    }
};
```

**When is it called?**
```cpp
Student alice("Alice", 20, 'A');
Student bob("Bob", 19, 'B');
bob = alice;  // Assignment operator - bob already exists
```

### Why do we need both?

For simple types like `int` and `string`, the default copying works fine. But when your class manages resources (like memory), you need to be careful:

```cpp
struct SimpleArray {
    int* data;
    int size;
    
    SimpleArray(int s) : size(s), data(new int[s]) {
        cout << "Created array of size " << size << endl;
    }
    
    // Without proper copy constructor:
    // SimpleArray arr1(5);
    // SimpleArray arr2 = arr1;  // DANGER! Both point to same memory!
    // When arr1 and arr2 are destroyed, same memory deleted twice = CRASH!
    
    // Proper copy constructor (deep copy)
    SimpleArray(const SimpleArray& other) : size(other.size), data(new int[size]) {
        cout << "Copy constructor: creating new array" << endl;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];  // Copy each element
        }
    }
    
    // Proper assignment operator
    SimpleArray& operator=(const SimpleArray& other) {
        cout << "Assignment operator called" << endl;
        if (this == &other) return *this;  // Self-assignment check
        
        delete[] data;  // Clean up old memory
        size = other.size;
        data = new int[size];  // Allocate new memory
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];  // Copy each element
        }
        return *this;
    }
    
    ~SimpleArray() {
        cout << "Destructor: deleting array" << endl;
        delete[] data;
    }
};
```

---

## The `const` Keyword - Making Things Unchangeable

`const` means "constant" - something that cannot be changed.

### const variables

```cpp
const int MAX_STUDENTS = 30;
// MAX_STUDENTS = 40;  // ERROR! Cannot change const variable
```

### const with pointers (this is tricky!)

```cpp
int x = 10;
int y = 20;

// Pointer to const int - can't change the VALUE through pointer
const int* ptr1 = &x;
// *ptr1 = 15;  // ERROR! Can't change value
ptr1 = &y;      // OK - can change what it points to

// Const pointer - can't change WHERE it points
int* const ptr2 = &x;
*ptr2 = 15;     // OK - can change the value
// ptr2 = &y;   // ERROR! Can't change what it points to

// Const pointer to const int - can't change ANYTHING
const int* const ptr3 = &x;
// *ptr3 = 15;  // ERROR! Can't change value
// ptr3 = &y;   // ERROR! Can't change what it points to
```

### const member functions

```cpp
struct Student {
    string name;
    int age;
    
    // const member function - promises not to change the object
    void print_info() const {
        cout << "Name: " << name << ", Age: " << age << endl;
        // age++;  // ERROR! const function can't modify members
    }
    
    // non-const member function - can modify the object
    void have_birthday() {
        age++;  // OK - non-const function can modify
        cout << "Happy birthday! Now " << age << " years old." << endl;
    }
};

int main() {
    Student alice{"Alice", 20};
    alice.print_info();    // OK
    alice.have_birthday(); // OK
    
    const Student bob{"Bob", 19};  // const object
    bob.print_info();     // OK - const function on const object
    // bob.have_birthday(); // ERROR! non-const function on const object
}
```

### const references (very common in function parameters)

```cpp
void print_student(const Student& s) {  // Pass by const reference
    cout << s.name << endl;  // OK - just reading
    // s.age++;              // ERROR! Can't modify through const reference
}

int main() {
    Student alice{"Alice", 20};
    print_student(alice);  // Efficient - no copying, safe - can't modify
}
```

**Why use const references?**
- **Efficient**: No copying (unlike pass-by-value)
- **Safe**: Function can't accidentally modify your object
- **Clear intent**: Shows the function only reads, doesn't modify

---

## Static Members - Sharing Data Between All Objects

Sometimes you want data that belongs to the **class itself**, not to individual objects.

### static data members

```cpp
struct Student {
    string name;
    int age;
    static int total_students;  // Shared by ALL Student objects
    
    Student(string n, int a) : name(n), age(a) {
        total_students++;  // Increment when new student created
    }
    
    ~Student() {
        total_students--;  // Decrement when student destroyed
    }
};

// Must define static members outside the class
int Student::total_students = 0;

int main() {
    cout << "Students: " << Student::total_students << endl;  // 0
    
    Student alice("Alice", 20);
    cout << "Students: " << Student::total_students << endl;  // 1
    
    Student bob("Bob", 19);
    cout << "Students: " << Student::total_students << endl;  // 2
    
    // Can access through objects too
    cout << "Students: " << alice.total_students << endl;     // 2
}
```

### inline static (C++17 and later)

```cpp
struct Student {
    string name;
    int age;
    inline static int total_students = 0;  // Can initialize here!
    
    Student(string n, int a) : name(n), age(a) {
        total_students++;
    }
};

// No need for separate definition!
```

### static member functions

```cpp
struct Student {
    string name;
    int age;
    inline static int total_students = 0;
    
    Student(string n, int a) : name(n), age(a) {
        total_students++;
    }
    
    // static function - belongs to class, not individual objects
    static int get_total_students() {
        return total_students;
        // return age;  // ERROR! No 'this' pointer in static functions
    }
    
    static void print_class_info() {
        cout << "This is the Student class." << endl;
        cout << "Current students: " << total_students << endl;
    }
};

int main() {
    Student::print_class_info();  // Call without any object!
    
    Student alice("Alice", 20);
    Student bob("Bob", 19);
    
    cout << Student::get_total_students() << endl;  // 2
    cout << alice.get_total_students() << endl;     // 2 (also works)
}
```

### static local variables

```cpp
int get_next_id() {
    static int id = 0;  // Initialized only once, keeps value between calls
    return ++id;
}

int main() {
    cout << get_next_id() << endl;  // 1
    cout << get_next_id() << endl;  // 2
    cout << get_next_id() << endl;  // 3
}
```

---

## Arrays of Objects

### Basic arrays of objects

```cpp
struct Point {
    int x, y;
    
    Point() : x(0), y(0) {  // Default constructor
        cout << "Point created at (0,0)" << endl;
    }
    
    Point(int x_val, int y_val) : x(x_val), y(y_val) {
        cout << "Point created at (" << x << "," << y << ")" << endl;
    }
};

int main() {
    // Array of 3 Points - calls default constructor 3 times
    Point points[3];
    
    // Initialize with specific values
    Point triangle[3] = {
        Point(0, 0),
        Point(3, 0),
        Point(1, 2)
    };
    
    // Access elements
    for (int i = 0; i < 3; i++) {
        cout << "Point " << i << ": (" << triangle[i].x << "," << triangle[i].y << ")" << endl;
    }
}
```

### Modern arrays with vector

```cpp
#include <vector>

int main() {
    vector<Point> points;  // Empty vector
    
    // Add points
    points.push_back(Point(1, 2));
    points.push_back(Point(3, 4));
    
    // Or initialize directly
    vector<Point> triangle = {
        Point(0, 0),
        Point(3, 0),
        Point(1, 2)
    };
    
    // Access elements safely
    for (size_t i = 0; i < triangle.size(); i++) {
        cout << "Point " << i << ": (" << triangle[i].x << "," << triangle[i].y << ")" << endl;
    }
    
    // Or use range-based for loop (easier!)
    for (const Point& p : triangle) {
        cout << "Point: (" << p.x << "," << p.y << ")" << endl;
    }
}
```

### Arrays of pointers vs arrays of objects

```cpp
int main() {
    // Array of objects - objects stored directly in array
    Point objects[3] = {Point(1,1), Point(2,2), Point(3,3)};
    
    // Array of pointers - pointers stored in array, objects elsewhere
    Point* pointers[3] = {
        new Point(1, 1),
        new Point(2, 2),
        new Point(3, 3)
    };
    
    // Access objects
    cout << objects[0].x << endl;    // Direct access
    cout << pointers[0]->x << endl;  // Access through pointer
    
    // Clean up pointers
    for (int i = 0; i < 3; i++) {
        delete pointers[i];
    }
}
```

### Can you have arrays of references?

**No!** References must be initialized when created, and arrays can't do that:

```cpp
int a = 1, b = 2, c = 3;
// int& refs[3] = {a, b, c};  // ERROR! Can't have array of references
```

But you can use `reference_wrapper`:

```cpp
#include <functional>
#include <vector>

int main() {
    int a = 1, b = 2, c = 3;
    
    vector<reference_wrapper<int>> refs = {a, b, c};
    
    refs[0].get() = 10;  // Changes 'a' to 10
    cout << a << endl;   // Prints 10
}
```

---

## Common Mistakes and How to Avoid Them

### 1. Shallow vs Deep Copy

```cpp
struct BadArray {
    int* data;
    int size;
    
    BadArray(int s) : size(s), data(new int[s]) {}
    
    // Using default copy constructor - DANGEROUS!
    // BadArray arr1(5);
    // BadArray arr2 = arr1;  // Both point to same memory!
    // When destructors run, same memory deleted twice = CRASH!
};

struct GoodArray {
    int* data;
    int size;
    
    GoodArray(int s) : size(s), data(new int[s]) {}
    
    // Proper copy constructor
    GoodArray(const GoodArray& other) : size(other.size), data(new int[size]) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];  // Copy each element
        }
    }
    
    // Proper assignment operator
    GoodArray& operator=(const GoodArray& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
    
    ~GoodArray() {
        delete[] data;
    }
};
```

### 2. Forgetting const correctness

```cpp
struct Student {
    string name;
    int age;
    
    // BAD: Should be const since it doesn't modify the object
    string get_name() { return name; }
    
    // GOOD: const member function
    string get_name() const { return name; }
};

// BAD: Unnecessary copying
void print_student(Student s) {
    cout << s.get_name() << endl;
}

// GOOD: Pass by const reference
void print_student(const Student& s) {
    cout << s.get_name() << endl;
}
```

### 3. Using C-style casts

```cpp
double x = 3.14;

int bad = (int)x;              // BAD: C-style cast
int good = static_cast<int>(x); // GOOD: C++ style cast
```

---

## Practice Exercises

### Exercise 1: Temperature Converter
Create a `Temperature` class that:
- Stores temperature in Celsius
- Has a constructor that takes Celsius value
- Has conversion operators to Fahrenheit and Kelvin
- Has const member functions to get values

```cpp
struct Temperature {
    double celsius;
    
    // TODO: Implement constructor
    // TODO: Implement conversion operators
    // TODO: Implement const member functions
};
```

### Exercise 2: Student Registry
Create a `Student` class that:
- Has name, age, and ID
- Uses static member to track total number of students
- Has proper copy constructor and assignment operator
- Has static function to get total student count

```cpp
struct Student {
    string name;
    int age;
    int id;
    inline static int total_students = 0;
    
    // TODO: Implement constructors
    // TODO: Implement copy constructor and assignment operator
    // TODO: Implement static functions
};
```

### Exercise 3: Dynamic Array
Create a `DynamicArray` class that:
- Manages its own memory
- Has proper copy constructor and assignment operator (deep copy)
- Has destructor to clean up memory
- Can add elements and access by index

```cpp
struct DynamicArray {
    int* data;
    int size;
    int capacity;
    
    // TODO: Implement all necessary functions
};
```

---

## Quick Reference

### When to use each cast:
- **static_cast**: Safe conversions (int ↔ double, Base* → Derived*)
- **const_cast**: Add/remove const (rarely needed)
- **reinterpret_cast**: Dangerous bit reinterpretation (avoid!)
- **dynamic_cast**: Safe downcasting with inheritance (later topic)
- **C-style cast**: Never use in modern C++!

### Copy constructor vs Assignment:
- **Copy constructor**: Creating new object from existing one
- **Assignment operator**: Modifying existing object

### const guidelines:
- Make member functions `const` if they don't modify the object
- Pass large objects by `const&` to avoid copying
- Use `const` variables for values that shouldn't change

### static guidelines:
- Use `static` data members for class-wide information
- Use `static` member functions for operations that don't need object instance
- Use `inline static` for C++17 and later

---

**Next steps**: Practice these concepts! Try the exercises and experiment with different combinations. Understanding these fundamentals is crucial for everything else in OOP.