# Lab 10: Exception Handling

Topics covered:

- [Introduction to Exception Handling](#introduction-to-exception-handling)
  - [What are Exceptions](#what-are-exceptions)
  - [Why Use Exception Handling](#why-use-exception-handling)
- [Basic Exception Handling](#basic-exception-handling)
  - [try-catch Blocks](#try-catch-blocks)
  - [Throwing Exceptions](#throwing-exceptions)
  - [Multiple catch Blocks](#multiple-catch-blocks)
- [Standard Exception Classes](#standard-exception-classes)
- [Custom Exception Classes](#custom-exception-classes)
- [Best Practices](#best-practices)

## Introduction to Exception Handling

### What are Exceptions

Exceptions are runtime errors that disrupt the normal flow of program execution. They provide a way to handle errors gracefully instead of crashing the program.

### Why Use Exception Handling

```cpp
// Traditional error handling (problematic)
int divide(int a, int b, bool& success) {
    if (b == 0) {
        success = false;
        return 0;  // Meaningless return value
    }
    success = true;
    return a / b;
}

// Exception-based error handling (better)
int divide(int a, int b) {
    if (b == 0) {
        throw invalid_argument("Division by zero");
    }
    return a / b;
}
```

**Benefits of exception handling:**
- Separates error handling from normal code flow
- Cannot be ignored (unlike return codes)
- Provides detailed error information
- Allows error handling at appropriate level
- Automatic cleanup through destructors

## Basic Exception Handling

### try-catch Blocks

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        int a = 10;
        int b = 0;
        
        if (b == 0) {
            throw runtime_error("Cannot divide by zero!");
        }
        
        int result = a / b;
        cout << "Result: " << result << endl;
    }
    catch (const runtime_error& e) {
        cout << "Runtime error caught: " << e.what() << endl;
    }
    
    cout << "Program continues..." << endl;
    return 0;
}
```

### Throwing Exceptions

```cpp
class BankAccount {
private:
    double balance;
    string accountNumber;
    
public:
    BankAccount(string accNum, double initialBalance) 
        : accountNumber(accNum), balance(initialBalance) {
        if (initialBalance < 0) {
            throw invalid_argument("Initial balance cannot be negative");
        }
    }
    
    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Withdrawal amount cannot be negative");
        }
        if (amount > balance) {
            throw runtime_error("Insufficient funds");
        }
        balance -= amount;
    }
    
    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Deposit amount cannot be negative");
        }
        balance += amount;
    }
    
    double getBalance() const {
        return balance;
    }
};

int main() {
    try {
        BankAccount account("12345", 1000.0);
        
        account.withdraw(500.0);
        cout << "Balance after withdrawal: $" << account.getBalance() << endl;
        
        account.withdraw(600.0);  // This will throw an exception
    }
    catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    }
    
    return 0;
}
```

### Multiple catch Blocks

```cpp
void demonstrateMultipleCatch() {
    try {
        int choice;
        cout << "Enter choice (1-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                throw 42;  // int exception
                break;
            case 2:
                throw 3.14;  // double exception
                break;
            case 3:
                throw string("String exception");  // string exception
                break;
            default:
                throw runtime_error("Invalid choice");
        }
    }
    catch (int e) {
        cout << "Caught integer exception: " << e << endl;
    }
    catch (double e) {
        cout << "Caught double exception: " << e << endl;
    }
    catch (const string& e) {
        cout << "Caught string exception: " << e << endl;
    }
    catch (const runtime_error& e) {
        cout << "Caught runtime_error: " << e.what() << endl;
    }
    catch (...) {  // Catch-all handler
        cout << "Caught unknown exception" << endl;
    }
}
```

## Standard Exception Classes

C++ provides a hierarchy of standard exception classes:

```cpp
#include <stdexcept>
#include <iostream>

void demonstrateStandardExceptions() {
    try {
        // logic_error examples
        string str = "not a number";
        int num = stoi(str);  // Throws invalid_argument
    }
    catch (const invalid_argument& e) {
        cout << "invalid_argument: " << e.what() << endl;
    }
    
    try {
        // runtime_error examples
        int* ptr = new int[1000000000];  // May throw bad_alloc
        delete[] ptr;
    }
    catch (const bad_alloc& e) {
        cout << "bad_alloc: " << e.what() << endl;
    }
}

// Exception hierarchy demonstration
void catchByBaseClass() {
    try {
        throw out_of_range("Index out of bounds");
    }
    catch (const logic_error& e) {  // Catches out_of_range (derived class)
        cout << "Caught logic_error: " << e.what() << endl;
    }
    catch (const exception& e) {    // Would catch any standard exception
        cout << "Caught exception: " << e.what() << endl;
    }
}
```

**Standard Exception Hierarchy:**
```
exception
├── logic_error
│   ├── invalid_argument
│   ├── domain_error
│   ├── length_error
│   └── out_of_range
├── runtime_error
│   ├── range_error
│   ├── overflow_error
│   └── underflow_error
├── bad_alloc
├── bad_cast
└── bad_typeid
```

## Custom Exception Classes

```cpp
// Custom exception class inheriting from standard exception
class InsufficientFundsException : public runtime_error {
private:
    double requestedAmount;
    double availableBalance;
    
public:
    InsufficientFundsException(double requested, double available)
        : runtime_error("Insufficient funds for transaction"),
          requestedAmount(requested), availableBalance(available) {}
    
    double getRequestedAmount() const { return requestedAmount; }
    double getAvailableBalance() const { return availableBalance; }
    
    const char* what() const noexcept override {
        static string message = "Insufficient funds: requested $" + 
                               to_string(requestedAmount) + 
                               ", available $" + 
                               to_string(availableBalance);
        return message.c_str();
    }
};

// Another custom exception
class InvalidAccountException : public logic_error {
private:
    string accountNumber;
    
public:
    InvalidAccountException(const string& accNum)
        : logic_error("Invalid account number"), accountNumber(accNum) {}
    
    const string& getAccountNumber() const { return accountNumber; }
    
    const char* what() const noexcept override {
        static string message = "Invalid account number: " + accountNumber;
        return message.c_str();
    }
};

// Enhanced BankAccount class with custom exceptions
class EnhancedBankAccount {
private:
    string accountNumber;
    double balance;
    
    bool isValidAccountNumber(const string& accNum) {
        return accNum.length() >= 5 && accNum.find_first_not_of("0123456789") == string::npos;
    }
    
public:
    EnhancedBankAccount(const string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {
        
        if (!isValidAccountNumber(accNum)) {
            throw InvalidAccountException(accNum);
        }
        
        if (initialBalance < 0) {
            throw invalid_argument("Initial balance cannot be negative");
        }
    }
    
    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Withdrawal amount cannot be negative");
        }
        
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        
        balance -= amount;
    }
    
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

int main() {
    try {
        EnhancedBankAccount account("12345", 1000.0);
        account.withdraw(1500.0);  // Will throw InsufficientFundsException
    }
    catch (const InsufficientFundsException& e) {
        cout << e.what() << endl;
        cout << "Requested: $" << e.getRequestedAmount() << endl;
        cout << "Available: $" << e.getAvailableBalance() << endl;
    }
    catch (const InvalidAccountException& e) {
        cout << e.what() << endl;
        cout << "Account: " << e.getAccountNumber() << endl;
    }
    catch (const exception& e) {
        cout << "Standard exception: " << e.what() << endl;
    }
    
    return 0;
}
```


## Best Practices

```cpp
class BestPracticesDemo {
public:
    // 1. Catch exceptions by const reference
    void goodCatchPractice() {
        try {
            throw runtime_error("Test error");
        }
        catch (const runtime_error& e) {  // Good: const reference
            cout << e.what() << endl;
        }
    }
    
    // 2. Use specific exception types
    void validateInput(int value) {
        if (value < 0) {
            throw invalid_argument("Value must be non-negative");
        }
    }
    
    // 3. Don't throw in destructors
    class GoodClass {
    public:
        ~GoodClass() {
            try {
                // risky operation
            } catch (...) {
                // Log error but don't rethrow
            }
        }
    };
    
    // 4. Handle resources properly
    void processFile(const string& filename) {
        FILE* file = fopen(filename.c_str(), "r");
        
        if (!file) {
            throw runtime_error("Cannot open file");
        }
        
        try {
            // Process file
        } catch (...) {
            fclose(file);  // Clean up before rethrowing
            throw;
        }
        
        fclose(file);  // Normal cleanup
    }
};

double safeSqrt(double value) {
    if (value < 0) {
        throw invalid_argument("Cannot calculate square root of negative number");
    }
    
    return sqrt(value);
}
```

**Key Guidelines:**

1. **Catch by const reference** to avoid unnecessary copying
2. **Use specific exception types** rather than generic ones
3. **Don't throw in destructors**
4. **Clean up resources** properly in exception scenarios
5. **Document exception behavior** in function comments
6. **Prefer standard exceptions** when they fit the error
7. **Handle exceptions at the appropriate level** in your program
8. **Don't use exceptions for normal control flow** - they're for errors only