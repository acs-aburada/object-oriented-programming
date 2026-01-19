# Lab 9: Polymorphism

Topics covered:

- [Introduction to Polymorphism](#introduction-to-polymorphism)
  - [Types of Polymorphism](#types-of-polymorphism)
- [Compile-Time Polymorphism](#compile-time-polymorphism)
  - [Function Overloading](#function-overloading)
  - [Operator Overloading](#operator-overloading)
- [Runtime Polymorphism](#runtime-polymorphism)
  - [Virtual Functions](#virtual-functions)
  - [Pure Virtual Functions](#pure-virtual-functions)
  - [Abstract Classes](#abstract-classes)
- [Virtual Function Tables (vtable)](#virtual-function-tables-vtable)
- [Dynamic Binding](#dynamic-binding)
- [Polymorphic Containers](#polymorphic-containers)

## Introduction to Polymorphism

Polymorphism means "many forms" - the ability of objects of different types to be treated as objects of a common base type, while maintaining their specific behaviors.

### Types of Polymorphism

1. **Compile-time Polymorphism (Static)**: Resolved during compilation
   - Function overloading
   - Operator overloading
   - Template specialization

2. **Runtime Polymorphism (Dynamic)**: Resolved during execution
   - Virtual functions
   - Function overriding

## Compile-Time Polymorphism

### Function Overloading

Multiple functions with the same name but different parameter lists.

```cpp
class Calculator {
public:
    // Overloaded add functions
    int add(int a, int b) {
        cout << "Adding two integers" << endl;
        return a + b;
    }
    
    double add(double a, double b) {
        cout << "Adding two doubles" << endl;
        return a + b;
    }
    
    int add(int a, int b, int c) {
        cout << "Adding three integers" << endl;
        return a + b + c;
    }
    
    string add(string a, string b) {
        cout << "Concatenating strings" << endl;
        return a + b;
    }
};

int main() {
    Calculator calc;
    
    cout << calc.add(5, 3) << endl;           // Calls int version
    cout << calc.add(5.5, 3.2) << endl;      // Calls double version
    cout << calc.add(1, 2, 3) << endl;       // Calls three-parameter version
    cout << calc.add("Hello", " World") << endl; // Calls string version
    
    return 0;
}
```

### Operator Overloading

Giving new meanings to operators for user-defined types.

```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Overload + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // Overload == operator
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
    
    // Overload << operator for output
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
    
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3 = c1 + c2;  // Uses overloaded + operator
    
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
    
    if (c1 == c2) {  // Uses overloaded == operator
        cout << "c1 and c2 are equal" << endl;
    } else {
        cout << "c1 and c2 are different" << endl;
    }
    
    return 0;
}
```

## Runtime Polymorphism

### Virtual Functions

Functions that can be overridden in derived classes and are resolved at runtime.

```cpp
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {}
    
    // Virtual function - can be overridden
    virtual void makeSound() {
        cout << name << " makes a generic animal sound" << endl;
    }
    
    // Non-virtual function - cannot be overridden polymorphically
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    virtual ~Animal() {}  // Virtual destructor
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    
    void makeSound() override {  // Override virtual function
        cout << name << " barks: Woof! Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    
    void makeSound() override {
        cout << name << " meows: Meow! Meow!" << endl;
    }
};

void demonstratePolymorphism(Animal* animal) {
    animal->makeSound();  // Calls appropriate version based on actual object type
    animal->eat();        // Always calls Animal::eat()
}

int main() {
    Animal* animals[] = {
        new Dog("Buddy"),
        new Cat("Whiskers"),
        new Animal("Generic")
    };
    
    for (int i = 0; i < 3; i++) {
        demonstratePolymorphism(animals[i]);
        delete animals[i];
    }
    
    return 0;
}
```

### Pure Virtual Functions

Virtual functions with no implementation in the base class, making the class abstract.

```cpp
class Shape {  // Abstract class
protected:
    string color;
    
public:
    Shape(string c) : color(c) {}
    
    // Pure virtual functions
    virtual double getArea() = 0;
    virtual double getPerimeter() = 0;
    virtual void draw() = 0;
    
    // Regular virtual function
    virtual void displayInfo() {
        cout << "This is a " << color << " shape" << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Perimeter: " << getPerimeter() << endl;
    }
    
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {}
    
    double getArea() override {
        return 3.14159 * radius * radius;
    }
    
    double getPerimeter() override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() override {
        cout << "Drawing a " << color << " circle with radius " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(string c, double w, double h) : Shape(c), width(w), height(h) {}
    
    double getArea() override {
        return width * height;
    }
    
    double getPerimeter() override {
        return 2 * (width + height);
    }
    
    void draw() override {
        cout << "Drawing a " << color << " rectangle " << width << "x" << height << endl;
    }
};
```

### Abstract Classes

Classes with at least one pure virtual function. Cannot be instantiated directly.

```cpp
class Vehicle {  // Abstract class
protected:
    string brand;
    int year;
    
public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    
    // Pure virtual functions
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual double getFuelEfficiency() = 0;
    
    // Concrete function
    void displayBasicInfo() {
        cout << year << " " << brand << endl;
    }
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    int doors;
    
public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}
    
    void start() override {
        cout << "Car engine starting with key ignition" << endl;
    }
    
    void stop() override {
        cout << "Car engine stopping" << endl;
    }
    
    double getFuelEfficiency() override {
        return 25.5;  // MPG
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(string b, int y) : Vehicle(b, y) {}
    
    void start() override {
        cout << "Motorcycle starting with kick/button" << endl;
    }
    
    void stop() override {
        cout << "Motorcycle engine stopping" << endl;
    }
    
    double getFuelEfficiency() override {
        return 45.0;  // MPG
    }
};

int main() {
    // Vehicle v;  // ERROR: Cannot instantiate abstract class
    
    Vehicle* vehicles[] = {
        new Car("Toyota", 2023, 4),
        new Motorcycle("Harley", 2022)
    };
    
    for (int i = 0; i < 2; i++) {
        vehicles[i]->displayBasicInfo();
        vehicles[i]->start();
        cout << "Fuel efficiency: " << vehicles[i]->getFuelEfficiency() << " MPG" << endl;
        vehicles[i]->stop();
        cout << endl;
        delete vehicles[i];
    }
    
    return 0;
}
```

## Virtual Function Tables (vtable)

Understanding how virtual functions work internally.

```cpp
class Base {
public:
    virtual void func1() { cout << "Base::func1" << endl; }
    virtual void func2() { cout << "Base::func2" << endl; }
    void func3() { cout << "Base::func3" << endl; }  // Non-virtual
    
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void func1() override { cout << "Derived::func1" << endl; }
    // func2 not overridden - uses Base::func2
    void func3() { cout << "Derived::func3" << endl; }  // Hides Base::func3
};

void demonstrateVTable() {
    cout << "=== Virtual Function Table Demo ===" << endl;
    
    Base* basePtr = new Derived();
    
    basePtr->func1();  // Calls Derived::func1 (virtual, overridden)
    basePtr->func2();  // Calls Base::func2 (virtual, not overridden)
    basePtr->func3();  // Calls Base::func3 (non-virtual, static binding)
    
    delete basePtr;
    
    cout << "\n=== Direct Object Access ===" << endl;
    Derived derivedObj;
    derivedObj.func1();  // Calls Derived::func1
    derivedObj.func2();  // Calls Base::func2
    derivedObj.func3();  // Calls Derived::func3 (hides base version)
}
```

## Dynamic Binding

Runtime resolution of function calls based on object type.

```cpp
class Employee {
protected:
    string name;
    double baseSalary;
    
public:
    Employee(string n, double salary) : name(n), baseSalary(salary) {}
    
    virtual double calculatePay() {
        return baseSalary;
    }
    
    virtual void displayInfo() {
        cout << "Employee: " << name << ", Pay: $" << calculatePay() << endl;
    }
    
    virtual ~Employee() {}
};

class Manager : public Employee {
private:
    double bonus;
    
public:
    Manager(string n, double salary, double b) : Employee(n, salary), bonus(b) {}
    
    double calculatePay() override {
        return baseSalary + bonus;
    }
};

class SalesRep : public Employee {
private:
    double commission;
    double sales;
    
public:
    SalesRep(string n, double salary, double comm, double s) 
        : Employee(n, salary), commission(comm), sales(s) {}
    
    double calculatePay() override {
        return baseSalary + (commission * sales);
    }
};

void processPayroll(Employee** employees, int count) {
    double totalPayroll = 0;
    
    for (int i = 0; i < count; i++) {
        employees[i]->displayInfo();  // Dynamic binding
        totalPayroll += employees[i]->calculatePay();  // Dynamic binding
    }
    
    cout << "Total payroll: $" << totalPayroll << endl;
}

int main() {
    Employee* employees[] = {
        new Employee("John Doe", 50000),
        new Manager("Jane Smith", 80000, 15000),
        new SalesRep("Bob Johnson", 40000, 0.05, 200000)
    };
    
    processPayroll(employees, 3);
    
    for (int i = 0; i < 3; i++) {
        delete employees[i];
    }
    
    return 0;
}
```

## Polymorphic Containers

Using containers to store different types polymorphically.

```cpp
class Drawable {
public:
    virtual void draw() = 0;
    virtual void move(int x, int y) = 0;
    virtual ~Drawable() {}
};

class Circle : public Drawable {
private:
    int centerX, centerY, radius;
    
public:
    Circle(int x, int y, int r) : centerX(x), centerY(y), radius(r) {}
    
    void draw() override {
        cout << "Drawing circle at (" << centerX << "," << centerY 
             << ") with radius " << radius << endl;
    }
    
    void move(int x, int y) override {
        centerX += x;
        centerY += y;
        cout << "Circle moved to (" << centerX << "," << centerY << ")" << endl;
    }
};

class Square : public Drawable {
private:
    int x, y, size;
    
public:
    Square(int posX, int posY, int s) : x(posX), y(posY), size(s) {}
    
    void draw() override {
        cout << "Drawing square at (" << x << "," << y 
             << ") with size " << size << endl;
    }
    
    void move(int deltaX, int deltaY) override {
        x += deltaX;
        y += deltaY;
        cout << "Square moved to (" << x << "," << y << ")" << endl;
    }
};

int main() {
    const int MAX_SHAPES = 3;
    Drawable* shapes[MAX_SHAPES];
    
    shapes[0] = new Circle(10, 20, 5);
    shapes[1] = new Square(30, 40, 8);
    shapes[2] = new Circle(50, 60, 3);
    
    cout << "Drawing all shapes:" << endl;
    for (int i = 0; i < MAX_SHAPES; i++) {
        shapes[i]->draw();  // Polymorphic call
    }
    
    cout << "\nMoving all shapes:" << endl;
    for (int i = 0; i < MAX_SHAPES; i++) {
        shapes[i]->move(5, 5);  // Polymorphic call
    }
    
    cout << "\nDrawing after move:" << endl;
    for (int i = 0; i < MAX_SHAPES; i++) {
        shapes[i]->draw();  // Polymorphic call
    }
    
    // Clean up memory
    for (int i = 0; i < MAX_SHAPES; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

## Best Practices

1. **Use virtual destructors** in base classes with virtual functions
2. **Prefer `override` keyword** when overriding virtual functions
3. **Use pure virtual functions** to create interfaces/abstract classes
4. **Avoid virtual function calls** in constructors/destructors
5. **Consider performance implications** of virtual functions
6. **Use smart pointers** for polymorphic containers
7. **Follow the Liskov Substitution Principle**: derived classes should be substitutable for base classes
8. **Prefer composition over inheritance** when polymorphism isn't needed