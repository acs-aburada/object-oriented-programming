# Lab 7: Operator Overloading

Topics covered:

- [Introduction to Operator Overloading](#introduction-to-operator-overloading)
  - [What is Operator Overloading](#what-is-operator-overloading)
  - [Overloadable vs Non-overloadable Operators](#overloadable-vs-non-overloadable-operators)
- [Member Function Overloading](#member-function-overloading)
- [Non-Member Function Overloading](#non-member-function-overloading)
- [Friend Functions](#friend-functions)
- [Common Operators](#common-operators)
  - [Arithmetic Operators](#arithmetic-operators)
  - [Comparison Operators](#comparison-operators)
  - [Assignment Operators](#assignment-operators)
  - [Stream Operators](#stream-operators)
  - [Subscript Operator](#subscript-operator)
  - [Function Call Operator](#function-call-operator)
- [Best Practices](#best-practices)

## Introduction to Operator Overloading

### What is Operator Overloading

Operator overloading allows you to define custom behavior for operators when used with user-defined types (classes). It makes your classes more intuitive to use by allowing natural syntax.

```cpp
// Without operator overloading
Complex c1(3, 4);
Complex c2(1, 2);
Complex c3 = c1.add(c2);  // Verbose

// With operator overloading
Complex c1(3, 4);
Complex c2(1, 2);
Complex c3 = c1 + c2;     // Natural and intuitive
```

### Overloadable vs Non-overloadable Operators

**Overloadable operators:**
```
+  -  *  /  %  ^  &  |  ~  !  =  <  >  +=  -=  *=  /=  %=  ^=  &=
|=  <<  >>  >>=  <<=  ==  !=  <=  >=  &&  ||  ++  --  ,  ->*  ->
()  []  new  delete  new[]  delete[]
```

**Non-overloadable operators:**
```
::  .  .*  ?:  sizeof  typeid
```

## Member Function Overloading

Operators defined as member functions of the class.

```cpp
class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Member function operator overloading
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    // Compound assignment operators
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
    
    // Unary operators
    Vector2D operator-() const {  // Negation
        return Vector2D(-x, -y);
    }
    
    Vector2D& operator++() {  // Pre-increment
        ++x;
        ++y;
        return *this;
    }
    
    Vector2D operator++(int) {  // Post-increment
        Vector2D temp(*this);
        ++(*this);
        return temp;
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
};

int main() {
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    Vector2D v3 = v1 + v2;    // Uses operator+
    Vector2D v4 = v1 - v2;    // Uses operator-
    Vector2D v5 = v1 * 2.0;   // Uses operator*
    
    v1 += v2;                 // Uses operator+=
    
    cout << "v3: "; v3.display();
    cout << "v4: "; v4.display();
    cout << "v5: "; v5.display();
    cout << "v1 after +=: "; v1.display();
    
    if (v1 == v2) {
        cout << "v1 and v2 are equal" << endl;
    }
    
    return 0;
}
```

## Non-Member Function Overloading

Operators defined as free functions (not member functions).

```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

// Non-member operator functions
Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.getReal() + c2.getReal(), c1.getImag() + c2.getImag());
}

Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1.getReal() - c2.getReal(), c1.getImag() - c2.getImag());
}

Complex operator*(const Complex& c, double scalar) {
    return Complex(c.getReal() * scalar, c.getImag() * scalar);
}

// Commutative multiplication (scalar * complex)
Complex operator*(double scalar, const Complex& c) {
    return c * scalar;  // Reuse the above operator
}

bool operator==(const Complex& c1, const Complex& c2) {
    return (c1.getReal() == c2.getReal()) && (c1.getImag() == c2.getImag());
}

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    Complex c3 = c1 + c2;     // Non-member operator+
    Complex c4 = c1 * 2.0;    // Non-member operator*
    Complex c5 = 3.0 * c1;    // Commutative multiplication
    
    cout << "c3: "; c3.display();
    cout << "c4: "; c4.display();
    cout << "c5: "; c5.display();
    
    return 0;
}
```

## Friend Functions

Friend functions can access private members of a class, useful for operator overloading.

```cpp
class Matrix {
private:
    int rows, cols;
    int** data;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
    
    void setValue(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }
    
    int getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        return 0;
    }
    
    // Friend function for matrix addition
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    
    // Friend function for stream output
    friend ostream& operator<<(ostream& os, const Matrix& m);
    
    // Friend function for stream input
    friend istream& operator>>(istream& is, Matrix& m);
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

// Friend function implementations
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        throw invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix result(m1.rows, m1.cols);
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

ostream& operator<<(ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.data[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m) {
    cout << "Enter matrix elements (" << m.rows << "x" << m.cols << "):" << endl;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            is >> m.data[i][j];
        }
    }
    return is;
}

int main() {
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    
    m1.setValue(0, 0, 1); m1.setValue(0, 1, 2);
    m1.setValue(1, 0, 3); m1.setValue(1, 1, 4);
    
    m2.setValue(0, 0, 5); m2.setValue(0, 1, 6);
    m2.setValue(1, 0, 7); m2.setValue(1, 1, 8);
    
    cout << "Matrix 1:" << endl << m1;
    cout << "Matrix 2:" << endl << m2;
    
    Matrix m3 = m1 + m2;
    cout << "Sum:" << endl << m3;
    
    return 0;
}
```

## Common Operators

### Arithmetic Operators

```cpp
class Fraction {
private:
    int numerator, denominator;
    
    void simplify() {
        int gcd = findGCD(abs(numerator), abs(denominator));
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    
    int findGCD(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }
    
    // Arithmetic operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                       denominator * other.denominator);
    }
    
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                       denominator * other.denominator);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }
    
    Fraction operator/(const Fraction& other) const {
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
    
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if (f.denominator == 1) {
            os << f.numerator;
        } else {
            os << f.numerator << "/" << f.denominator;
        }
        return os;
    }
};

int main() {
    Fraction f1(1, 2);  // 1/2
    Fraction f2(1, 3);  // 1/3
    
    cout << f1 << " + " << f2 << " = " << (f1 + f2) << endl;  // 5/6
    cout << f1 << " - " << f2 << " = " << (f1 - f2) << endl;  // 1/6
    cout << f1 << " * " << f2 << " = " << (f1 * f2) << endl;  // 1/6
    cout << f1 << " / " << f2 << " = " << (f1 / f2) << endl;  // 3/2
    
    return 0;
}
```

### Comparison Operators

```cpp
class Student {
private:
    string name;
    double gpa;
    
public:
    Student(string n, double g) : name(n), gpa(g) {}
    
    // Comparison operators
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }
    
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
    
    bool operator<=(const Student& other) const {
        return gpa <= other.gpa;
    }
    
    bool operator>=(const Student& other) const {
        return gpa >= other.gpa;
    }
    
    bool operator==(const Student& other) const {
        return gpa == other.gpa;
    }
    
    bool operator!=(const Student& other) const {
        return gpa != other.gpa;
    }
    
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.name << " (GPA: " << s.gpa << ")";
        return os;
    }
};

int main() {
    Student s1("Alice", 3.8);
    Student s2("Bob", 3.5);
    
    cout << s1 << " vs " << s2 << endl;
    
    if (s1 > s2) {
        cout << s1 << " has higher GPA" << endl;
    } else if (s1 < s2) {
        cout << s2 << " has higher GPA" << endl;
    } else {
        cout << "Same GPA" << endl;
    }
    
    return 0;
}
```

### Assignment Operators

```cpp
class DynamicArray {
private:
    int* data;
    int size;
    
public:
    DynamicArray(int s = 0) : size(s) {
        data = (size > 0) ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = (size > 0) ? new int[size] : nullptr;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;     // Clean up existing data
            
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Destructor
    ~DynamicArray() {
        delete[] data;
    }
    
    // Compound assignment operators
    DynamicArray& operator+=(const DynamicArray& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                data[i] += other.data[i];
            }
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
        return 0;
    }
    
    int getSize() const { return size; }
};

int main() {
    DynamicArray arr1(3);
    arr1.setValue(0, 10);
    arr1.setValue(1, 20);
    arr1.setValue(2, 30);
    
    DynamicArray arr2(3);
    arr2.setValue(0, 1);
    arr2.setValue(1, 2);
    arr2.setValue(2, 3);
    
    DynamicArray arr3 = arr1;  // Copy constructor
    DynamicArray arr4(5);
    arr4 = arr1;               // Assignment operator
    
    arr1 += arr2;              // Compound assignment
    
    cout << "arr1 after +=: ";
    for (int i = 0; i < arr1.getSize(); i++) {
        cout << arr1.getValue(i) << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Stream Operators

```cpp
class Time {
private:
    int hours, minutes, seconds;
    
public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }
    
    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        hours %= 24;  // 24-hour format
    }
    
    // Output stream operator
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setfill('0') << setw(2) << t.hours << ":"
           << setw(2) << t.minutes << ":"
           << setw(2) << t.seconds;
        return os;
    }
    
    // Input stream operator
    friend istream& operator>>(istream& is, Time& t) {
        char colon1, colon2;
        is >> t.hours >> colon1 >> t.minutes >> colon2 >> t.seconds;
        t.normalize();
        return is;
    }
};

int main() {
    Time t1(14, 30, 45);
    cout << "Time 1: " << t1 << endl;
    
    Time t2;
    cout << "Enter time (HH:MM:SS): ";
    cin >> t2;
    cout << "Time 2: " << t2 << endl;
    
    return 0;
}
```

### Subscript Operator

```cpp
class SafeArray {
private:
    int* data;
    int size;
    
public:
    SafeArray(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    ~SafeArray() {
        delete[] data;
    }
    
    // Subscript operator for non-const objects
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Subscript operator for const objects
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
};

int main() {
    SafeArray arr(5);
    
    // Using subscript operator to set values
    for (int i = 0; i < arr.getSize(); i++) {
        arr[i] = i * 10;
    }
    
    // Using subscript operator to get values
    for (int i = 0; i < arr.getSize(); i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    
    try {
        arr[10] = 100;  // This will throw an exception
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}
```

### Function Call Operator

```cpp
class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    // Function call operator
    int operator()(int value) const {
        return value * factor;
    }
    
    // Overloaded function call operator
    int operator()(int a, int b) const {
        return (a + b) * factor;
    }
};

class Accumulator {
private:
    int sum;
    
public:
    Accumulator() : sum(0) {}
    
    // Function call operator that modifies state
    int operator()(int value) {
        sum += value;
        return sum;
    }
    
    int getSum() const { return sum; }
};

int main() {
    Multiplier times3(3);
    
    cout << "5 * 3 = " << times3(5) << endl;        // Uses operator()(int)
    cout << "(2+4) * 3 = " << times3(2, 4) << endl; // Uses operator()(int, int)
    
    Accumulator acc;
    cout << "Accumulating: ";
    for (int i = 1; i <= 5; i++) {
        cout << acc(i) << " ";  // Uses operator()(int)
    }
    cout << endl;
    
    return 0;
}
```

## Best Practices

1. **Follow conventional meanings**: `+` should add, `==` should compare equality
2. **Return appropriate types**: 
   - Arithmetic operators return new objects
   - Compound assignment operators return references to `*this`
   - Comparison operators return `bool`
3. **Implement related operators consistently**: If you overload `==`, also overload `!=`
4. **Use member functions** for operators that modify the object (`+=`, `++`, etc.)
5. **Use non-member functions** for symmetric operators (`+`, `*`, etc.)
6. **Use friend functions** when you need access to private members
7. **Always check for self-assignment** in assignment operators
8. **Make comparison operators `const`**
9. **Consider performance**: Avoid unnecessary object creation
10. **Provide both const and non-const versions** of subscript operator when needed