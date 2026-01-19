# Common Mistakes in Object-Oriented Programming

This guide covers the most frequent mistakes students make when learning C++ and Object-Oriented Programming. Understanding these pitfalls will help you avoid them in exams and assignments.

## Table of Contents

- [Basic C++ Mistakes](#basic-c-mistakes)
- [Class and Object Mistakes](#class-and-object-mistakes)
- [Constructor and Destructor Mistakes](#constructor-and-destructor-mistakes)
- [Inheritance Mistakes](#inheritance-mistakes)
- [Polymorphism Mistakes](#polymorphism-mistakes)
- [Operator Overloading Mistakes](#operator-overloading-mistakes)
- [Memory Management Mistakes](#memory-management-mistakes)
- [Exception Handling Mistakes](#exception-handling-mistakes)
- [General Design Mistakes](#general-design-mistakes)

## Basic C++ Mistakes

### 1. Forgetting Semicolons After Class Definitions

```cpp
// WRONG
class Student {
    string name;
    int age;
} // Missing semicolon

// CORRECT
class Student {
    string name;
    int age;
}; // Semicolon required
```

### 2. Mixing C and C++ I/O

```cpp
// WRONG - Don't mix scanf/printf with cin/cout
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int age;
    string name;
    scanf("%d", &age);    // C-style input
    cout << "Age: " << age << endl;  // C++ style output
    return 0;
}

// CORRECT - Use consistent I/O style
int main() {
    int age;
    string name;
    cin >> age;           // C++ style input
    cout << "Age: " << age << endl;  // C++ style output
    return 0;
}
```

### 3. Not Using `using namespace std` or Forgetting `std::`

```cpp
// WRONG
#include <iostream>

int main() {
    cout << "Hello" << endl;  // Error: cout not declared
    return 0;
}

// CORRECT - Option 1
#include <iostream>
using namespace std;

int main() {
    cout << "Hello" << endl;
    return 0;
}

// CORRECT - Option 2
#include <iostream>

int main() {
    std::cout << "Hello" << std::endl;
    return 0;
}
```

### 4. Incorrect Array Declaration and Usage

```cpp
// WRONG
int main() {
    int n;
    cin >> n;
    int arr[n];  // Variable-length arrays not standard in C++
    return 0;
}

// CORRECT
int main() {
    const int SIZE = 10;
    int arr[SIZE];  // Fixed size
    
    // Or use dynamic allocation
    int n;
    cin >> n;
    int* arr2 = new int[n];
    delete[] arr2;
    return 0;
}
```

## Class and Object Mistakes

### 1. Making Everything Public

```cpp
// WRONG - No encapsulation
class BankAccount {
public:
    double balance;
    string accountNumber;
};

// CORRECT - Proper encapsulation
class BankAccount {
private:
    double balance;
    string accountNumber;
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalance() const {
        return balance;
    }
};
```

### 2. Forgetting `const` for Getter Methods

```cpp
// WRONG
class Student {
private:
    string name;
    
public:
    string getName() {  // Should be const
        return name;
    }
};

// CORRECT
class Student {
private:
    string name;
    
public:
    string getName() const {  // const method
        return name;
    }
};
```

### 3. Not Providing Proper Access Methods

```cpp
// WRONG - Direct access to private members impossible
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    // No way to get or set width/height after construction
};

// CORRECT
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    void setWidth(double w) { 
        if (w > 0) width = w; 
    }
    void setHeight(double h) { 
        if (h > 0) height = h; 
    }
};
```

## Constructor and Destructor Mistakes

### 1. Not Providing Default Constructor When Needed

```cpp
// WRONG
class Student {
private:
    string name;
    int age;
    
public:
    Student(string n, int a) : name(n), age(a) {}
    // No default constructor
};

int main() {
    Student students[5];  // Error: no default constructor
    return 0;
}

// CORRECT
class Student {
private:
    string name;
    int age;
    
public:
    Student() : name("Unknown"), age(0) {}  // Default constructor
    Student(string n, int a) : name(n), age(a) {}
};
```

### 2. Forgetting to Initialize All Members

```cpp
// WRONG
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w) : width(w) {
        // height not initialized!
    }
};

// CORRECT
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w) : width(w), height(0) {
        // All members initialized
    }
};
```

### 3. Memory Leaks in Destructors

```cpp
// WRONG
class DynamicArray {
private:
    int* data;
    int size;
    
public:
    DynamicArray(int s) : size(s) {
        data = new int[size];
    }
    
    // Missing destructor - memory leak!
};

// CORRECT
class DynamicArray {
private:
    int* data;
    int size;
    
public:
    DynamicArray(int s) : size(s) {
        data = new int[size];
    }
    
    ~DynamicArray() {
        delete[] data;  // Clean up memory
        data = nullptr; // set data to null pointer
    }
};
```

## Inheritance Mistakes

### 1. Forgetting Virtual Destructors

```cpp
// WRONG
class Base {
public:
    ~Base() { cout << "Base destructor" << endl; }
};

class Derived : public Base {
private:
    int* data;
    
public:
    Derived() { data = new int[100]; }
    ~Derived() { 
        delete[] data; 
        cout << "Derived destructor" << endl; 
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;  // Only Base destructor called - memory leak!
    return 0;
}

// CORRECT
class Base {
public:
    virtual ~Base() { cout << "Base destructor" << endl; }
};
```

### 2. Calling Virtual Functions in Constructors

```cpp
// WRONG
class Base {
public:
    Base() {
        init();  // Calls Base::init(), not derived version
    }
    
    virtual void init() {
        cout << "Base init" << endl;
    }
};

class Derived : public Base {
public:
    void init() override {
        cout << "Derived init" << endl;  // Never called from constructor
    }
};

// CORRECT - Avoid virtual calls in constructors
class Base {
public:
    Base() {
        // Don't call virtual functions here
    }
    
    virtual void init() {
        cout << "Base init" << endl;
    }
};
```

### 3. Incorrect Access Specifier Usage

```cpp
// WRONG
class Vehicle {
protected:
    string brand;
};

class Car : private Vehicle {  // Private inheritance
public:
    void setBrand(string b) {
        brand = b;  // OK inside class
    }
};

int main() {
    Car car;
    // Vehicle* ptr = &car;  // Error: private inheritance
    return 0;
}

// CORRECT - Use public inheritance for IS-A relationships
class Car : public Vehicle {
public:
    void setBrand(string b) {
        brand = b;
    }
};
```

## Polymorphism Mistakes

### 1. Forgetting `virtual` Keyword

```cpp
// WRONG
class Animal {
public:
    void makeSound() {  // Not virtual
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() {  // Hides base function, doesn't override
        cout << "Woof!" << endl;
    }
};

int main() {
    Animal* animal = new Dog();
    animal->makeSound();  // Prints "Animal sound" - not polymorphic
    delete animal;
    return 0;
}

// CORRECT
class Animal {
public:
    virtual void makeSound() {  // Virtual function
        cout << "Animal sound" << endl;
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() override {  // Override virtual function
        cout << "Woof!" << endl;
    }
};
```

### 2. Not Using `override` Keyword

```cpp
// WRONG - Typo in function name, no compiler error
class Base {
public:
    virtual void process() {}
};

class Derived : public Base {
public:
    void proces() {}  // Typo! Creates new function instead of overriding
};

// CORRECT - Use override to catch errors
class Derived : public Base {
public:
    void proces() override {}  // Compiler error: no matching virtual function
    void process() override {} // Correct override
};
```

### 3. Slicing Objects

```cpp
// WRONG
class Animal {
public:
    virtual void makeSound() { cout << "Animal" << endl; }
};

class Dog : public Animal {
private:
    string breed;
public:
    Dog(string b) : breed(b) {}
    void makeSound() override { cout << "Woof from " << breed << endl; }
};

void processAnimal(Animal animal) {  // Pass by value - slicing!
    animal.makeSound();  // Always calls Animal::makeSound()
}

// CORRECT
void processAnimal(Animal& animal) {  // Pass by reference
    animal.makeSound();  // Polymorphic call works correctly
}
```

## Operator Overloading Mistakes

### 1. Wrong Return Types

```cpp
// WRONG
class Complex {
public:
    void operator+(const Complex& other) {  // Should return Complex
        // ...
    }
    
    Complex operator=(const Complex& other) {  // Should return reference
        // ...
        return *this;
    }
};

// CORRECT
class Complex {
public:
    Complex operator+(const Complex& other) const {
        // ...
        return result;
    }
    
    Complex& operator=(const Complex& other) {
        // ...
        return *this;
    }
};
```

### 2. Not Checking Self-Assignment

```cpp
// WRONG
class MyClass {
public:
    MyClass& operator=(const MyClass& other) {
        delete[] data;  // Dangerous if this == &other
        data = new int[other.size];
        // Copy data...
        return *this;
    }
};

// CORRECT
class MyClass {
public:
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;
            data = new int[other.size];
            // Copy data...
        }
        return *this;
    }
};
```

## Memory Management Mistakes

### 1. Mixing `new`/`delete` with `malloc`/`free`

```cpp
// WRONG
int* ptr = new int[10];
free(ptr);  // Should use delete[]

int* ptr2 = (int*)malloc(10 * sizeof(int));
delete[] ptr2;  // Should use free()

// CORRECT
int* ptr = new int[10];
delete[] ptr;

int* ptr2 = (int*)malloc(10 * sizeof(int));
free(ptr2);
```

### 2. Using `delete` Instead of `delete[]`

```cpp
// WRONG
int* arr = new int[10];
delete arr;  // Should be delete[]

// CORRECT
int* arr = new int[10];
delete[] arr;
```

### 3. Double Deletion

```cpp
// WRONG
int* ptr = new int(42);
delete ptr;
delete ptr;  // Double deletion - undefined behavior

// CORRECT
int* ptr = new int(42);
delete ptr;
ptr = nullptr;  // Set to nullptr after deletion
```

## Exception Handling Mistakes

### 1. Catching by Value Instead of Reference

```cpp
// WRONG
try {
    throw runtime_error("Error message");
} catch (runtime_error e) {  // Copies exception object
    cout << e.what() << endl;
}

// CORRECT
try {
    throw runtime_error("Error message");
} catch (const runtime_error& e) {  // Catch by const reference
    cout << e.what() << endl;
}
```

### 2. Not Cleaning Up Resources in Exception Scenarios

```cpp
// WRONG
void processFile(const string& filename) {
    FILE* file = fopen(filename.c_str(), "r");
    
    if (someCondition) {
        throw runtime_error("Error");  // File not closed!
    }
    
    fclose(file);
}

// CORRECT
void processFile(const string& filename) {
    FILE* file = fopen(filename.c_str(), "r");
    
    try {
        if (someCondition) {
            throw runtime_error("Error");
        }
        fclose(file);
    } catch (...) {
        fclose(file);  // Clean up before rethrowing
        throw;
    }
}
```

## General Design Mistakes

### 1. Not Following Naming Conventions

```cpp
// WRONG
class bankaccount {  // Should be PascalCase
    string Account_Number;  // Inconsistent naming
    double m_balance;       // Hungarian notation not recommended
    
public:
    void Deposit(double Amount) {  // Inconsistent parameter naming
        m_balance += Amount;
    }
};

// CORRECT
class BankAccount {
    string accountNumber;   // mixedCamelCase for members
    double balance;
    
public:
    void deposit(double amount) {  // mixedCamelCase for functions
        balance += amount;
    }
};
```

### 2. Making Classes Too Large

```cpp
// WRONG - God class doing everything
class Student {
    string name, address, phone;
    double grades[100];
    
public:
    void calculateGPA() { /* ... */ }
    void printTranscript() { /* ... */ }
    void sendEmail() { /* ... */ }
    void processPayment() { /* ... */ }
    void scheduleClasses() { /* ... */ }
    // Too many responsibilities!
};

// CORRECT - Separate concerns
class Student {
    string name;
    string studentId;
    
public:
    string getName() const { return name; }
    string getId() const { return studentId; }
};

class GradeManager {
public:
    void calculateGPA(const Student& student) { /* ... */ }
    void printTranscript(const Student& student) { /* ... */ }
};
```

### 3. Not Using Appropriate Data Types

```cpp
// WRONG
class Person {
    string age;        // Age should be numeric
    int isMarried;     // Boolean should be bool
    float salary;      // Money should use double for precision
};

// CORRECT
class Person {
    int age;           // Numeric type for age
    bool isMarried;    // Boolean type
    double salary;     // Double for monetary values
};
```

## Exam Tips

### Before the Exam:
1. **Review basic syntax** - semicolons, brackets, naming conventions
2. **Practice memory management** - new/delete, constructors/destructors
3. **Understand inheritance hierarchy** - virtual functions, access specifiers
4. **Know when to use const** - const methods, const parameters
5. **Practice operator overloading** - return types, parameter types

### During the Exam:
1. **Read questions carefully** - understand what's being asked
2. **Check for missing semicolons** after class definitions
3. **Verify access specifiers** - public, private, protected
4. **Look for memory leaks** - every new should have corresponding delete
5. **Check virtual function usage** - base class pointers with derived objects
6. **Validate const correctness** - getter methods should be const
7. **Review exception handling** - catch by const reference

### Common Point Deductions:
- Missing semicolons after class definitions (-1 to -2 points)
- Incorrect access specifiers (-2 to -3 points)
- Memory leaks (-3 to -5 points)
- Missing virtual destructors (-2 to -3 points)
- Incorrect operator overloading syntax (-2 to -4 points)
- Poor naming conventions (-1 to -2 points)
- Missing const keywords (-1 to -2 points)

Remember: **Practice makes perfect!** The more you code and understand these concepts, the less likely you are to make these common mistakes.