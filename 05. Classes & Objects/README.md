# Lab 5: Classes & Objects

Topics covered:

- [Introduction to Classes](#introduction-to-classes)
  - [Class vs Object](#class-vs-object)
  - [Basic Class Syntax](#basic-class-syntax)
  - [Member Variables and Functions](#member-variables-and-functions)
- [Access Specifiers](#access-specifiers)
  - [Public](#public)
  - [Private](#private)
  - [Protected](#protected)
- [Creating and Using Objects](#creating-and-using-objects)
  - [Object Declaration](#object-declaration)
  - [Accessing Members](#accessing-members)
  - [Object Initialization](#object-initialization)
- [The `this` Pointer](#the-this-pointer)
- [Static Members](#static-members)
  - [Static Variables](#static-variables)
  - [Static Functions](#static-functions)

## Introduction to Classes

### Class vs Object

**Class**: A blueprint or template that defines the structure and behavior of objects.
**Object**: An instance of a class - a concrete entity created from the class blueprint.

Think of it like:
- **Class** = House blueprint (defines rooms, layout, features)
- **Object** = Actual house built from that blueprint

### Basic Class Syntax

```cpp
class ClassName {
private:
    // Private members (data and functions)
    
public:
    // Public members (data and functions)
    
protected:
    // Protected members (used with inheritance)
};
```

### Member Variables and Functions

```cpp
class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    void setName(string studentName) {
        name = studentName;
    }
    
    string getName() {
        return name;
    }
    
    void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
    }
};
```

## Access Specifiers

### Public
- Accessible from anywhere in the program
- Used for interface functions that external code should use

```cpp
class BankAccount {
public:
    void deposit(double amount) {  // Anyone can deposit
        balance += amount;
    }
    
    double getBalance() {  // Anyone can check balance
        return balance;
    }
    
private:
    double balance = 0.0;  // Only class methods can modify
};
```

### Private
- Only accessible within the same class
- Used to hide implementation details (encapsulation)
- Default access level for class members

```cpp
class Calculator {
private:
    double lastResult = 0.0;  // Hidden from outside access
    
    void logOperation(string op) {  // Internal helper function
        cout << "Operation: " << op << endl;
    }
    
public:
    double add(double a, double b) {
        lastResult = a + b;
        logOperation("addition");
        return lastResult;
    }
};
```

### Protected
- Accessible within the class and its derived classes
- Used in inheritance (covered in later labs)

## Creating and Using Objects

### Object Declaration

```cpp
// Stack allocation (automatic storage)
Student student1;
Student student2;

// Dynamic allocation (manual memory management)
Student* studentPtr = new Student();
```

### Accessing Members

```cpp
class Car {
public:
    string brand;
    int year;
    
    void startEngine() {
        cout << "Engine started!" << endl;
    }
};

int main() {
    // Stack object - use dot operator
    Car myCar;
    myCar.brand = "Toyota";
    myCar.year = 2023;
    myCar.startEngine();
    
    // Dynamic object - use arrow operator
    Car* carPtr = new Car();
    carPtr->brand = "Honda";
    carPtr->year = 2022;
    carPtr->startEngine();
    
    delete carPtr;  // Clean up memory
    return 0;
}
```

### Object Initialization

```cpp
class Rectangle {
private:
    double width, height;
    
public:
    // Setter functions for initialization
    void setDimensions(double w, double h) {
        width = w;
        height = h;
    }
    
    double getArea() {
        return width * height;
    }
};

int main() {
    Rectangle rect;
    rect.setDimensions(5.0, 3.0);
    cout << "Area: " << rect.getArea() << endl;
    return 0;
}
```

## The `this` Pointer

The `this` pointer refers to the current object instance. Useful when parameter names conflict with member variables:

```cpp
class Person {
private:
    string name;
    int age;
    
public:
    void setName(string name) {
        this->name = name;  // this->name refers to member variable
                           // name refers to parameter
    }
    
    void setAge(int age) {
        this->age = age;
    }
    
    // Method chaining using this
    Person& setInfo(string name, int age) {
        this->name = name;
        this->age = age;
        return *this;  // Return reference to current object
    }
};

int main() {
    Person person;
    person.setInfo("John", 25);  // Method chaining possible
    return 0;
}
```

## Static Members

### Static Variables

Static variables belong to the class, not to individual objects. All objects share the same static variable.

```cpp
class Counter {
private:
    static int objectCount;  // Shared by all Counter objects
    int instanceId;
    
public:
    Counter() {
        objectCount++;
        instanceId = objectCount;
    }
    
    static int getObjectCount() {
        return objectCount;
    }
    
    int getInstanceId() {
        return instanceId;
    }
};

// Static variable definition (required outside class)
int Counter::objectCount = 0;

int main() {
    Counter c1, c2, c3;
    
    cout << "Total objects created: " << Counter::getObjectCount() << endl;  // 3
    cout << "c2 instance ID: " << c2.getInstanceId() << endl;  // 2
    
    return 0;
}
```

### Static Functions

Static functions can be called without creating an object instance. They can only access static members.

```cpp
class MathUtils {
public:
    static double pi() {
        return 3.14159;
    }
    
    static double circleArea(double radius) {
        return pi() * radius * radius;
    }
    
    static int max(int a, int b) {
        return (a > b) ? a : b;
    }
};

int main() {
    // Call static functions without creating objects
    cout << "Pi: " << MathUtils::pi() << endl;
    cout << "Circle area: " << MathUtils::circleArea(5.0) << endl;
    cout << "Max: " << MathUtils::max(10, 20) << endl;
    
    return 0;
}
```

## Best Practices

1. **Encapsulation**: Keep data members private, provide public getter/setter functions
2. **Naming**: Use PascalCase for class names, mixedCamelCase for members
3. **Const Correctness**: Mark functions that don't modify state as `const`
4. **Memory Management**: Always `delete` dynamically allocated objects

```cpp
class BestPracticeExample {
private:
    string data;
    
public:
    void setData(const string& newData) {  // const reference parameter
        data = newData;
    }
    
    string getData() const {  // const function - doesn't modify object
        return data;
    }
};
```