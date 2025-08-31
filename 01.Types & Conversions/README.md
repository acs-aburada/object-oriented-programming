# Types, Cast & Arrays

## Types
In C++ there are multiple standard types that are used:
- `int` - integers &rarr; ex: 3, -10, 5
  - 4 bytes (32-bit) and 8 bytes (64-bit)
  - <mark>*signed type*</mark> = the most significant bit (first bit from the right) is the sign bit
  - [`-2.147.483.648`, `2.147.483.648`] or [`0x 1111 1111 1111 1111`, `0x 0111 1111 1111 1111`]
- `unsigned int` - integers &rarr; ex: 10, 43, 120
  - 4 bytes (32-bit) and 8 bytes (64-bit)
  - <mark>*unsigned type*
</mark>  - [`0`, `4.294.967.295`] or [`0x 0000 0000 0000 0000`, `0x 1111 1111 1111 1111`]

# Seminar 1: Object-Oriented Programming in C++  
### Type Conversions, Const Correctness, Static Members, and Arrays of Objects

---

## 📌 Topics Covered
1. Conversions between different types of objects
   - Cast operator
   - Assignment operator (`operator=`)
   - Copy constructor
2. `const` modifier
   - Constant objects
   - Constant references to objects
   - Pointers to constant objects
3. Static members
4. Arrays of objects and references to objects
5. Memory layout: *contiguous* vs *continuous*

---

## 1. Conversions Between Objects

### a) Cast Operator
The **cast operator** allows explicit conversion between types.  
Example:
```cpp
class A {
    int value;
public:
    A(int v) : value(v) {}
    int getValue() const { return value; }
    // Cast operator: convert A → int
    operator int() const {
        return value;
    }
};

int main() {
    A obj(42);
    int x = obj; // calls operator int()
}
```

✅ **Key idea:** You can define how objects of your class are converted to other types.

---

### b) Assignment Operator (`operator=`)
The **assignment operator** is used when an *already existing* object is assigned a new value.
```cpp
class B {
    int x;
public:
    B(int v=0) : x(v) {}
    B& operator=(const B& other) {
        if (this != &other) {
            x = other.x;
        }
        return *this;
    }
};
```

---

### c) Copy Constructor
The **copy constructor** creates a *new* object as a copy of another.
```cpp
class C {
    int x;
public:
    C(int v=0) : x(v) {}
    C(const C& other) : x(other.x) {} // copy constructor
};
```

📝 **Difference:**
- **Copy constructor**: invoked on initialization (new object created).  
- **Assignment operator**: invoked on assignment (object already exists).

---

## 2. `const` Modifier

### a) Constant Objects
A constant object **cannot be modified** after creation.
```cpp
class MyClass {
public:
    void show() const { /* allowed */ }
    void modify() { /* not allowed if object is const */ }
};

const MyClass obj;
// obj.modify(); ❌ error
obj.show();      ✅ ok
```

---

### b) Constant References
A **reference to const** prevents modification of the object via that reference.
```cpp
void print(const MyClass& obj) {
    obj.show();
    // obj.modify(); ❌
}
```

---

### c) Pointers to Constant Objects
```cpp
const MyClass* ptr = new MyClass();
// *ptr = MyClass(); ❌ error
ptr->show(); ✅ ok
```

📝 **Rule of thumb:**  
- `const Type* p` → the object is constant.  
- `Type* const p` → the pointer itself is constant.  
- `const Type* const p` → both are constant.

---

## 3. Static Members

- **Static data members** → shared by all objects of a class.
- **Static member functions** → do not depend on a specific object.

```cpp
class Counter {
    static int count;
public:
    Counter() { count++; }
    static int getCount() { return count; }
};

int Counter::count = 0;

int main() {
    Counter a, b, c;
    std::cout << Counter::getCount(); // 3
}
```

---

## 4. Arrays of Objects and References

### Arrays of Objects
When you declare an array of objects, all objects are constructed in **contiguous memory**:
```cpp
class A {
public:
    A() { std::cout << "Constructor\n"; }
};

int main() {
    A arr[3]; // Calls constructor 3 times
}
```

### Arrays of References? ❌  
C++ does **not** allow arrays of references directly, but you can use arrays of **pointers**:
```cpp
A a1, a2;
A* arr[2] = { &a1, &a2 };
```

---

## 5. Contiguous vs Continuous

🔹 **Contiguous**:  
- Means "next to each other in memory, without gaps".  
- Example: arrays of objects in C++ are stored in *contiguous* memory.  

```cpp
int arr[5]; 
// arr[0], arr[1], arr[2], arr[3], arr[4]
// all stored in adjacent memory cells
```

🔹 **Continuous**:  
- Means "without interruption in time or space" (general English meaning).  
- It is often mistakenly used when people mean *contiguous*.  

✅ **In programming, we care about *contiguous* memory, not continuous.**

---

## 📊 Diagrams

### Contiguous Memory (Array of Objects)
```
+---------+---------+---------+---------+
| obj[0]  | obj[1]  | obj[2]  | obj[3]  |
+---------+---------+---------+---------+
   ↑          ↑         ↑         ↑
 adjacent in memory → contiguous
```

### Pointers to Objects (Array of Pointers)
```
+---------+---------+---------+
| &obj1   | &obj2   | &obj3   |
+---------+---------+---------+
     ↓         ↓         ↓
   +-----+   +-----+   +-----+
   |obj1 |   |obj2 |   |obj3 |
   +-----+   +-----+   +-----+
```

---

## 🧠 Summary

- **Conversions**:  
  - Copy constructor (new object) vs assignment operator (existing object).  
  - Cast operator for explicit conversions.  

- **Const correctness**:  
  - `const` objects cannot call non-const member functions.  
  - Constant references and pointers ensure safe, read-only access.  

- **Static members**:  
  - Shared across all instances.  
  - Useful for counters, global data shared between objects.  

- **Arrays of objects**:  
  - Stored in **contiguous** memory.  
  - Arrays of references don’t exist, but arrays of pointers do.  

---

✍️ **Next step for students:**  
- Write a small class with all three (copy constructor, assignment operator, cast).  
- Experiment with `const` correctness.  
- Create a static member to count objects.  
- Allocate arrays of objects and pointers to objects, and examine memory layout with `sizeof` and addresses.  
