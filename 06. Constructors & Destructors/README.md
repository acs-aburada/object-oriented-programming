# Lab 6: Constructors & Destructors

Topics covered:

- [Constructors](#constructors)
  - [Default Constructor](#default-constructor)
  - [Parameterized Constructor](#parameterized-constructor)
  - [Copy Constructor](#copy-constructor)
  - [Constructor Overloading](#constructor-overloading)
- [Destructors](#destructors)
  - [When Destructors are Called](#when-destructors-are-called)
  - [Virtual Destructors](#virtual-destructors)
- [Object Lifecycle](#object-lifecycle)
- [Member Initialization Lists](#member-initialization-lists)
- [Rule of Three/Five](#rule-of-threefive)

## Constructors

Constructors are special member functions that initialize objects when they are created. They have the same name as the class and no return type.

### Default Constructor

A constructor with no parameters. If you don't define any constructor, C++ provides a default one.

```cpp
class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    // Default constructor
    Student() {
        name = "Unknown";
        age = 0;
        gpa = 0.0;
        cout << "Default constructor called" << endl;
    }
    
    void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
    }
};

int main() {
    Student student1;  // Calls default constructor
    student1.displayInfo();  // Output: Name: Unknown, Age: 0, GPA: 0
    return 0;
}
```

### Parameterized Constructor

A constructor that accepts parameters to initialize the object with specific values.

```cpp
class Rectangle {
private:
    double width, height;
    
public:
    // Parameterized constructor
    Rectangle(double w, double h) {
        width = w;
        height = h;
        cout << "Rectangle created with width: " << width << ", height: " << height << endl;
    }
    
    double getArea() {
        return width * height;
    }
};

int main() {
    Rectangle rect(5.0, 3.0);  // Calls parameterized constructor
    cout << "Area: " << rect.getArea() << endl;
    return 0;
}
```

### Copy Constructor

Creates a new object as a copy of an existing object. Takes a reference to an object of the same class.

```cpp
class Book {
private:
    string title;
    int pages;
    
public:
    // Parameterized constructor
    Book(string t, int p) : title(t), pages(p) {
        cout << "Book created: " << title << endl;
    }
    
    // Copy constructor
    Book(const Book& other) {
        title = other.title;
        pages = other.pages;
        cout << "Book copied: " << title << endl;
    }
    
    void displayInfo() {
        cout << "Title: " << title << ", Pages: " << pages << endl;
    }
};

int main() {
    Book book1("C++ Programming", 500);  // Parameterized constructor
    Book book2 = book1;                  // Copy constructor
    Book book3(book1);                   // Copy constructor (alternative syntax)
    
    book2.displayInfo();
    return 0;
}
```

### Constructor Overloading

You can have multiple constructors with different parameter lists.

```cpp
class BankAccount {
private:
    string accountNumber;
    double balance;
    string ownerName;
    
public:
    // Default constructor
    BankAccount() {
        accountNumber = "000000";
        balance = 0.0;
        ownerName = "Unknown";
    }
    
    // Constructor with account number only
    BankAccount(string accNum) {
        accountNumber = accNum;
        balance = 0.0;
        ownerName = "Unknown";
    }
    
    // Constructor with account number and initial balance
    BankAccount(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
        ownerName = "Unknown";
    }
    
    // Full constructor
    BankAccount(string accNum, double initialBalance, string owner) {
        accountNumber = accNum;
        balance = initialBalance;
        ownerName = owner;
    }
    
    void displayInfo() {
        cout << "Account: " << accountNumber << ", Balance: $" << balance 
             << ", Owner: " << ownerName << endl;
    }
};

int main() {
    BankAccount acc1;                                    // Default
    BankAccount acc2("123456");                          // Account number only
    BankAccount acc3("789012", 1000.0);                 // Account + balance
    BankAccount acc4("345678", 2500.0, "John Doe");     // Full info
    
    acc4.displayInfo();
    return 0;
}
```

## Destructors

Destructors are special member functions called when an object is destroyed. They clean up resources and perform final operations.

```cpp
class DynamicArray {
private:
    int* data;
    int size;
    
public:
    // Constructor
    DynamicArray(int s) {
        size = s;
        data = new int[size];
        cout << "Array of size " << size << " created" << endl;
    }
    
    // Destructor
    ~DynamicArray() {
        delete[] data;
        cout << "Array destroyed, memory freed" << endl;
    }
    
    void setValue(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }
    
    int getValue(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }
};

int main() {
    {
        DynamicArray arr(5);  // Constructor called
        arr.setValue(0, 100);
        cout << "Value at index 0: " << arr.getValue(0) << endl;
    }  // Destructor called automatically when arr goes out of scope
    
    cout << "Back in main" << endl;
    return 0;
}
```

### When Destructors are Called

1. **Automatic objects**: When they go out of scope
2. **Dynamic objects**: When `delete` is called
3. **Program termination**: For global/static objects

```cpp
class Logger {
private:
    string name;
    
public:
    Logger(string n) : name(n) {
        cout << name << " constructor called" << endl;
    }
    
    ~Logger() {
        cout << name << " destructor called" << endl;
    }
};

Logger globalLogger("Global");  // Global object

int main() {
    cout << "Entering main" << endl;
    
    Logger localLogger("Local");  // Local object
    
    Logger* dynamicLogger = new Logger("Dynamic");  // Dynamic object
    
    cout << "About to delete dynamic object" << endl;
    delete dynamicLogger;  // Explicit destructor call
    
    cout << "Exiting main" << endl;
    return 0;
}  // localLogger destructor called here
   // globalLogger destructor called after main ends
```

## Object Lifecycle

Understanding when constructors and destructors are called:

```cpp
class LifecycleDemo {
private:
    string name;
    
public:
    LifecycleDemo(string n) : name(n) {
        cout << name << " - Constructor" << endl;
    }
    
    LifecycleDemo(const LifecycleDemo& other) : name(other.name + "_copy") {
        cout << name << " - Copy Constructor" << endl;
    }
    
    ~LifecycleDemo() {
        cout << name << " - Destructor" << endl;
    }
    
    void doSomething() {
        cout << name << " - Doing something" << endl;
    }
};

void functionWithLocalObject() {
    LifecycleDemo local("Local");
    local.doSomething();
}  // local destructor called here

int main() {
    cout << "=== Creating objects ===" << endl;
    LifecycleDemo obj1("Object1");
    LifecycleDemo obj2 = obj1;  // Copy constructor
    
    cout << "=== Function call ===" << endl;
    functionWithLocalObject();
    
    cout << "=== Dynamic allocation ===" << endl;
    LifecycleDemo* dynObj = new LifecycleDemo("Dynamic");
    dynObj->doSomething();
    delete dynObj;
    
    cout << "=== End of main ===" << endl;
    return 0;
}  // obj1 and obj2 destructors called here
```

## Member Initialization Lists

More efficient way to initialize member variables, especially for const members and references.

```cpp
class Person {
private:
    const int id;           // const member - must be initialized
    string& nameRef;        // reference member - must be initialized
    string name;
    int age;
    
public:
    // Using initialization list (preferred)
    Person(int personId, string& nameReference, string personName, int personAge) 
        : id(personId), nameRef(nameReference), name(personName), age(personAge) {
        cout << "Person created with ID: " << id << endl;
    }
    
    // This would NOT work for const and reference members:
    // Person(int personId, string& nameReference, string personName, int personAge) {
    //     id = personId;        // ERROR: cannot assign to const
    //     nameRef = nameReference;  // ERROR: cannot assign to reference
    //     name = personName;    // OK but less efficient
    //     age = personAge;      // OK but less efficient
    // }
    
    void displayInfo() {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    string originalName = "John";
    Person person(1001, originalName, "John Doe", 25);
    person.displayInfo();
    return 0;
}
```

## Rule of Three/Five

If a class needs a custom destructor, copy constructor, or copy assignment operator, it probably needs all three (Rule of Three) or all five (Rule of Five, including move operations).

```cpp
class ResourceManager {
private:
    int* data;
    int size;
    
public:
    // Constructor
    ResourceManager(int s) : size(s) {
        data = new int[size];
        cout << "Resource allocated" << endl;
    }
    
    // Destructor
    ~ResourceManager() {
        delete[] data;
        cout << "Resource deallocated" << endl;
    }
    
    // Copy constructor
    ResourceManager(const ResourceManager& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Resource copied" << endl;
    }
    
    // Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;     // Clean up existing resource
            
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            cout << "Resource assigned" << endl;
        }
        return *this;
    }
    
    void setValue(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }
    
    int getValue(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }
};

int main() {
    ResourceManager rm1(3);
    rm1.setValue(0, 100);
    
    ResourceManager rm2 = rm1;    // Copy constructor
    ResourceManager rm3(5);
    rm3 = rm1;                    // Copy assignment operator
    
    cout << "rm2 value: " << rm2.getValue(0) << endl;
    return 0;
}
```

## Best Practices

1. **Always initialize all members** in constructors
2. **Use initialization lists** when possible
3. **Provide copy constructor and assignment operator** if managing resources
4. **Make destructors virtual** in base classes (covered in inheritance)
5. **Follow Rule of Three/Five** for resource management
6. **Use const references** for copy constructor parameters