# Lab 8: Inheritance

Topics covered:

- [Introduction to Inheritance](#introduction-to-inheritance)
  - [IS-A Relationship](#is-a-relationship)
  - [Base and Derived Classes](#base-and-derived-classes)
- [Inheritance Syntax](#inheritance-syntax)
  - [Public Inheritance](#public-inheritance)
  - [Protected Inheritance](#protected-inheritance)
  - [Private Inheritance](#private-inheritance)
- [Access Control in Inheritance](#access-control-in-inheritance)
- [Constructor and Destructor Chaining](#constructor-and-destructor-chaining)
- [Function Overriding](#function-overriding)
- [Multiple Inheritance](#multiple-inheritance)
- [Diamond Problem](#diamond-problem)

## Introduction to Inheritance

Inheritance allows a class to inherit properties and behaviors from another class, promoting code reuse and establishing hierarchical relationships.

### IS-A Relationship

Inheritance represents an "IS-A" relationship:
- A `Dog` IS-A `Animal`
- A `Car` IS-A `Vehicle`
- A `Student` IS-A `Person`

### Base and Derived Classes

- **Base Class (Parent/Super class)**: The class being inherited from
- **Derived Class (Child/Sub class)**: The class that inherits from the base class

```cpp
// Base class
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping" << endl;
    }
    
    virtual void makeSound() {
        cout << name << " makes a sound" << endl;
    }
};

// Derived class
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "Dog constructor: " << name << " (" << breed << ")" << endl;
    }
    
    void makeSound() override {  // Override base class method
        cout << name << " barks: Woof! Woof!" << endl;
    }
    
    void wagTail() {  // Dog-specific method
        cout << name << " is wagging tail" << endl;
    }
};
```

## Inheritance Syntax

### Public Inheritance

Most common form. Public and protected members of base class remain public and protected in derived class.

```cpp
class Vehicle {
protected:
    string brand;
    int year;
    
public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    
    void displayInfo() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
    
    virtual void start() {
        cout << "Vehicle starting..." << endl;
    }
};

class Car : public Vehicle {  // Public inheritance
private:
    int doors;
    
public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}
    
    void start() override {
        cout << "Car engine starting..." << endl;
    }
    
    void displayCarInfo() {
        displayInfo();  // Can access public method from base
        cout << "Doors: " << doors << endl;
    }
};

int main() {
    Car myCar("Toyota", 2023, 4);
    myCar.displayCarInfo();  // Accessing inherited method
    myCar.start();           // Calls overridden method
    return 0;
}
```

### Protected Inheritance

Public members of base class become protected in derived class.

```cpp
class Base {
public:
    void publicMethod() { cout << "Public method" << endl; }
protected:
    void protectedMethod() { cout << "Protected method" << endl; }
};

class Derived : protected Base {  // Protected inheritance
public:
    void accessMethods() {
        publicMethod();     // Now protected in Derived
        protectedMethod();  // Still protected
    }
};

int main() {
    Derived d;
    // d.publicMethod();  // ERROR: now protected
    d.accessMethods();    // OK
    return 0;
}
```

### Private Inheritance

All public and protected members of base class become private in derived class.

```cpp
class Engine {
public:
    void start() { cout << "Engine started" << endl; }
    void stop() { cout << "Engine stopped" << endl; }
};

class Car : private Engine {  // Private inheritance (composition-like)
public:
    void startCar() {
        start();  // Can access privately inherited method
    }
    
    void stopCar() {
        stop();   // Can access privately inherited method
    }
};

int main() {
    Car car;
    car.startCar();  // OK
    // car.start();  // ERROR: start() is private in Car
    return 0;
}
```

## Access Control in Inheritance

| Base Class Member | Public Inheritance | Protected Inheritance | Private Inheritance |
|-------------------|-------------------|---------------------|-------------------|
| Public | Public | Protected | Private |
| Protected | Protected | Protected | Private |
| Private | Not accessible | Not accessible | Not accessible |

```cpp
class AccessDemo {
public:
    int publicVar = 1;
    
protected:
    int protectedVar = 2;
    
private:
    int privateVar = 3;  // Never accessible in derived classes
    
public:
    void showAccess() {
        cout << "Public: " << publicVar << ", Protected: " << protectedVar 
             << ", Private: " << privateVar << endl;
    }
};

class PublicDerived : public AccessDemo {
public:
    void testAccess() {
        publicVar = 10;      // OK - public in derived
        protectedVar = 20;   // OK - protected in derived
        // privateVar = 30;  // ERROR - not accessible
    }
};

class ProtectedDerived : protected AccessDemo {
public:
    void testAccess() {
        publicVar = 10;      // OK - but now protected in this class
        protectedVar = 20;   // OK - still protected
        // privateVar = 30;  // ERROR - not accessible
    }
};
```

## Constructor and Destructor Chaining

Constructors are called from base to derived, destructors from derived to base.

```cpp
class Animal {
public:
    Animal(string name) {
        cout << "Animal constructor: " << name << endl;
    }
    
    virtual ~Animal() {  // Virtual destructor important for inheritance
        cout << "Animal destructor" << endl;
    }
};

class Mammal : public Animal {
public:
    Mammal(string name, string type) : Animal(name) {
        cout << "Mammal constructor: " << type << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destructor" << endl;
    }
};

class Dog : public Mammal {
public:
    Dog(string name, string breed) : Mammal(name, "Canine") {
        cout << "Dog constructor: " << breed << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor" << endl;
    }
};

int main() {
    cout << "Creating dog:" << endl;
    Dog myDog("Buddy", "Golden Retriever");
    
    cout << "\nDestroying dog:" << endl;
    return 0;
}
// Output:
// Creating dog:
// Animal constructor: Buddy
// Mammal constructor: Canine
// Dog constructor: Golden Retriever
//
// Destroying dog:
// Dog destructor
// Mammal destructor
// Animal destructor
```

## Function Overriding

Derived classes can override (redefine) virtual functions from base classes.

```cpp
class Shape {
protected:
    string color;
    
public:
    Shape(string c) : color(c) {}
    
    virtual double getArea() {  // Virtual function
        return 0.0;
    }
    
    virtual void draw() {       // Virtual function
        cout << "Drawing a " << color << " shape" << endl;
    }
    
    virtual ~Shape() {}  // Virtual destructor
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {}
    
    double getArea() override {  // Override virtual function
        return 3.14159 * radius * radius;
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
    
    void draw() override {
        cout << "Drawing a " << color << " rectangle " << width << "x" << height << endl;
    }
};

int main() {
    Shape* shapes[] = {
        new Circle("red", 5.0),
        new Rectangle("blue", 4.0, 6.0)
    };
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->draw();
        cout << "Area: " << shapes[i]->getArea() << endl;
        delete shapes[i];
    }
    
    return 0;
}
```

## Multiple Inheritance

A class can inherit from multiple base classes (use with caution).

```cpp
class Flyable {
public:
    virtual void fly() {
        cout << "Flying through the air" << endl;
    }
    
    virtual ~Flyable() {}
};

class Swimmable {
public:
    virtual void swim() {
        cout << "Swimming in water" << endl;
    }
    
    virtual ~Swimmable() {}
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(string name) : Animal(name, 2) {}
    
    void makeSound() override {
        cout << name << " quacks: Quack! Quack!" << endl;
    }
    
    void fly() override {
        cout << name << " is flying with wings" << endl;
    }
    
    void swim() override {
        cout << name << " is swimming with webbed feet" << endl;
    }
};

int main() {
    Duck duck("Donald");
    
    duck.eat();    // From Animal
    duck.fly();    // From Flyable
    duck.swim();   // From Swimmable
    duck.makeSound();  // Overridden
    
    return 0;
}
```

## Diamond Problem

Occurs when a class inherits from two classes that both inherit from the same base class.

```cpp
class Animal {
public:
    string name;
    Animal(string n) : name(n) {}
    virtual void eat() { cout << name << " is eating" << endl; }
};

class Mammal : public Animal {
public:
    Mammal(string n) : Animal(n) {}
    void giveBirth() { cout << name << " gives birth" << endl; }
};

class WingedAnimal : public Animal {
public:
    WingedAnimal(string n) : Animal(n) {}
    void flap() { cout << name << " flaps wings" << endl; }
};

// Problem: Bat inherits Animal twice (through Mammal and WingedAnimal)
class Bat : public Mammal, public WingedAnimal {
public:
    Bat(string n) : Mammal(n), WingedAnimal(n) {}
    // Which Animal::name? Which Animal::eat()?
};

// Solution: Virtual inheritance
class MammalVirtual : virtual public Animal {
public:
    MammalVirtual(string n) : Animal(n) {}
    void giveBirth() { cout << name << " gives birth" << endl; }
};

class WingedAnimalVirtual : virtual public Animal {
public:
    WingedAnimalVirtual(string n) : Animal(n) {}
    void flap() { cout << name << " flaps wings" << endl; }
};

class BatVirtual : public MammalVirtual, public WingedAnimalVirtual {
public:
    BatVirtual(string n) : Animal(n), MammalVirtual(n), WingedAnimalVirtual(n) {}
    // Now only one Animal base class
};

int main() {
    BatVirtual bat("Bruce");
    bat.eat();       // No ambiguity
    bat.giveBirth(); // From MammalVirtual
    bat.flap();      // From WingedAnimalVirtual
    
    return 0;
}
```

## Best Practices

1. **Use public inheritance** for IS-A relationships
2. **Make destructors virtual** in base classes
3. **Use `override` keyword** when overriding virtual functions
4. **Avoid deep inheritance hierarchies** (prefer composition)
5. **Be cautious with multiple inheritance** (consider interfaces/abstract classes)
6. **Use virtual inheritance** to solve diamond problem when necessary
7. **Follow Liskov Substitution Principle**: derived objects should be substitutable for base objects