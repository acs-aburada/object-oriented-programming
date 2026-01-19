# Lab 12: Binary File Handling

Topics covered:

- [Introduction to Binary Files](#introduction-to-binary-files)
  - [Text vs Binary Files](#text-vs-binary-files)
  - [When to Use Binary Files](#when-to-use-binary-files)
- [Basic Binary File Operations](#basic-binary-file-operations)
  - [Opening Binary Files](#opening-binary-files)
  - [Writing Binary Data](#writing-binary-data)
  - [Reading Binary Data](#reading-binary-data)
- [Working with Primitive Data Types](#working-with-primitive-data-types)
  - [Array Operations](#array-operations)
  - [String Handling in Binary Files](#string-handling-in-binary-files)
- [Working with Structures and Classes](#working-with-structures-and-classes)
  - [Simple Structure Example](#simple-structure-example)
  - [Class with Binary I/O Methods](#class-with-binary-io-methods)
- [File Position and Seeking](#file-position-and-seeking)
  - [Random Access in Binary Files](#random-access-in-binary-files)
- [Practical Examples](#practical-examples)
  - [Simple Database System](#simple-database-system)
  - [Game Save System](#game-save-system)
- [Best Practices](#best-practices)
  - [1. Always Use Binary Mode](#1-always-use-binary-mode)
  - [2. Handle Endianness for Portability](#2-handle-endianness-for-portability)
  - [3. Use Fixed-Size Data Structures](#3-use-fixed-size-data-structures)
  - [4. Version Your File Formats](#4-version-your-file-formats)
  - [5. Error Checking and Validation](#5-error-checking-and-validation)
- [Summary](#summary)

## Introduction to Binary Files

### Text vs Binary Files

**Text Files:**
- Store data as human-readable characters
- Use encoding (ASCII, UTF-8)
- Larger file size
- Platform-dependent line endings
- Easy to debug and inspect

**Binary Files:**
- Store data in binary format (0s and 1s)
- Exact memory representation
- Smaller file size
- Platform-independent
- Faster read/write operations
- Not human-readable

```cpp
// Text file example: storing number 1234
// File contains: '1', '2', '3', '4' (4 bytes)

// Binary file example: storing number 1234
// File contains: binary representation of int (4 bytes)
```

### When to Use Binary Files

Use binary files for:
- Storing large amounts of numeric data
- Saving program state or objects
- Creating data files for applications
- Performance-critical applications
- Exact data preservation (no conversion losses)
- Multimedia files (images, audio, video)

## Basic Binary File Operations

### Opening Binary Files

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Open for writing binary data
    ofstream outputFile("data.bin", ios::binary);
    
    // Open for reading binary data
    ifstream inputFile("data.bin", ios::binary);
    
    // Open for both reading and writing
    fstream file("data.bin", ios::binary | ios::in | ios::out);
    
    // Always check if file opened successfully
    if (!outputFile.is_open()) {
        cout << "Error opening file for writing" << endl;
        return 1;
    }
    
    outputFile.close();
    return 0;
}
```

### Writing Binary Data

```cpp
void writeBinaryBasics() {
    ofstream file("numbers.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Write different data types
    int number = 42;
    double decimal = 3.14159;
    char character = 'A';
    bool flag = true;
    
    // Use write() method for binary data with C-style casting
    file.write((char*)&number, sizeof(number));
    file.write((char*)&decimal, sizeof(decimal));
    file.write((char*)&character, sizeof(character));
    file.write((char*)&flag, sizeof(flag));
    
    file.close();
    cout << "Binary data written successfully" << endl;
}

// Alternative method using put() for single bytes
void writeBinaryBytes() {
    ofstream file("bytes.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Write individual bytes
    file.put(65);   // ASCII 'A'
    file.put(66);   // ASCII 'B'
    file.put(67);   // ASCII 'C'
    
    file.close();
}
```

### Reading Binary Data

```cpp
void readBinaryBasics() {
    ifstream file("numbers.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Read the same data types in same order
    int number;
    double decimal;
    char character;
    bool flag;
    
    // Use read() method for binary data with C-style casting
    file.read((char*)&number, sizeof(number));
    file.read((char*)&decimal, sizeof(decimal));
    file.read((char*)&character, sizeof(character));
    file.read((char*)&flag, sizeof(flag));
    
    // Display read data
    cout << "Number: " << number << endl;
    cout << "Decimal: " << decimal << endl;
    cout << "Character: " << character << endl;
    cout << "Flag: " << (flag ? "true" : "false") << endl;
    
    file.close();
}

// Reading with error checking
void safeReadBinary() {
    ifstream file("numbers.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    int number;
    if (file.read((char*)&number, sizeof(number))) {
        cout << "Successfully read number: " << number << endl;
    } else {
        cout << "Failed to read number" << endl;
    }
    
    // Check how many bytes were actually read
    streamsize bytesRead = file.gcount();
    cout << "Bytes read: " << bytesRead << endl;
    
    file.close();
}
```

## Working with Primitive Data Types

### Array Operations

```cpp
void writeIntArray() {
    ofstream file("array.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    int numbers[] = {10, 20, 30, 40, 50};
    int arraySize = 5;
    
    // Write array size first
    file.write((char*)&arraySize, sizeof(arraySize));
    
    // Write array data
    file.write((char*)numbers, sizeof(numbers));
    
    file.close();
    cout << "Array written to binary file" << endl;
}

void readIntArray() {
    ifstream file("array.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    int arraySize;
    
    // Read array size first
    file.read((char*)&arraySize, sizeof(arraySize));
    
    cout << "Array size: " << arraySize << endl;
    
    // Dynamically allocate array
    int* numbers = new int[arraySize];
    
    // Read array data
    file.read((char*)numbers, arraySize * sizeof(int));
    
    // Display array
    cout << "Array contents: ";
    for (int i = 0; i < arraySize; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    delete[] numbers;
    file.close();
}
```

### String Handling in Binary Files

```cpp
void writeBinaryString() {
    ofstream file("strings.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    string text = "Hello, Binary World!";
    
    // Method 1: Write length first, then string data
    size_t length = text.length();
    file.write((char*)&length, sizeof(length));
    file.write(text.c_str(), length);
    
    file.close();
    cout << "String written to binary file" << endl;
}

void readBinaryString() {
    ifstream file("strings.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Read string length first
    size_t length;
    file.read((char*)&length, sizeof(length));
    
    // Allocate buffer and read string data
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';  // Null terminate
    
    string text(buffer);
    cout << "Read string: " << text << endl;
    
    delete[] buffer;
    file.close();
}

// Fixed-length string approach
void writeFixedString() {
    ofstream file("fixed_strings.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    const int STRING_SIZE = 50;
    char name[STRING_SIZE] = "John Doe";
    
    // Write fixed-size string
    file.write(name, STRING_SIZE);
    
    file.close();
}
```

## Working with Structures and Classes

### Simple Structure Example

```cpp
struct Student {
    int id;
    char name[50];
    double gpa;
    int age;
};

void writeStudentBinary() {
    ofstream file("students.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    Student student1 = {1001, "Alice Johnson", 3.85, 20};
    Student student2 = {1002, "Bob Smith", 3.92, 21};
    Student student3 = {1003, "Carol Brown", 3.78, 19};
    
    // Write structures directly using C-style casting
    file.write((char*)&student1, sizeof(Student));
    file.write((char*)&student2, sizeof(Student));
    file.write((char*)&student3, sizeof(Student));
    
    file.close();
    cout << "Students written to binary file" << endl;
}

void readStudentBinary() {
    ifstream file("students.bin", ios::binary);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    Student student;
    int count = 1;
    
    cout << "Students from binary file:" << endl;
    cout << "ID\tName\t\tGPA\tAge" << endl;
    cout << "--------------------------------" << endl;
    
    // Read structures until end of file
    while (file.read((char*)&student, sizeof(Student))) {
        cout << student.id << "\t" << student.name << "\t\t" 
             << student.gpa << "\t" << student.age << endl;
        count++;
    }
    
    file.close();
}
```

### Class with Binary I/O Methods

```cpp
class Employee {
private:
    int employeeId;
    char name[100];
    double salary;
    int department;
    
public:
    Employee() : employeeId(0), salary(0.0), department(0) {
        strcpy(name, "");
    }
    
    Employee(int id, const string& empName, double sal, int dept) 
        : employeeId(id), salary(sal), department(dept) {
        strncpy(name, empName.c_str(), 99);
        name[99] = '\0';
    }
    
    // Write object to binary file
    void writeToBinary(ofstream& file) const {
        file.write((char*)this, sizeof(Employee));
    }
    
    // Read object from binary file
    void readFromBinary(ifstream& file) {
        file.read((char*)this, sizeof(Employee));
    }
    
    // Display employee information
    void display() const {
        cout << "ID: " << employeeId << ", Name: " << name 
             << ", Salary: $" << salary << ", Dept: " << department << endl;
    }
    
    // Getters
    int getId() const { return employeeId; }
    string getName() const { return string(name); }
    double getSalary() const { return salary; }
    int getDepartment() const { return department; }
};

void employeeFileDemo() {
    // Write employees to binary file
    {
        ofstream file("employees.bin", ios::binary);
        if (!file.is_open()) {
            cout << "Error creating file" << endl;
            return;
        }
        
        Employee emp1(101, "John Smith", 50000.0, 1);
        Employee emp2(102, "Jane Doe", 55000.0, 2);
        Employee emp3(103, "Mike Johnson", 48000.0, 1);
        
        emp1.writeToBinary(file);
        emp2.writeToBinary(file);
        emp3.writeToBinary(file);
        
        file.close();
        cout << "Employees written to binary file" << endl;
    }
    
    // Read employees from binary file
    {
        ifstream file("employees.bin", ios::binary);
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        
        Employee emp;
        cout << "\nEmployees from binary file:" << endl;
        
        while (file.read((char*)&emp, sizeof(Employee))) {
            emp.display();
        }
        
        file.close();
    }
}
```

## File Position and Seeking

### Random Access in Binary Files

```cpp
void demonstrateRandomAccess() {
    // Create a file with multiple integers
    {
        ofstream file("random_access.bin", ios::binary);
        if (!file.is_open()) return;
        
        for (int i = 0; i < 10; i++) {
            int value = i * 10;  // 0, 10, 20, 30, ...
            file.write((char*)&value, sizeof(value));
        }
        file.close();
    }
    
    // Random access reading
    {
        fstream file("random_access.bin", ios::binary | ios::in | ios::out);
        if (!file.is_open()) return;
        
        // Read value at position 3 (4th integer)
        file.seekg(3 * sizeof(int), ios::beg);
        int value;
        file.read((char*)&value, sizeof(value));
        cout << "Value at position 3: " << value << endl;
        
        // Modify value at position 5
        file.seekp(5 * sizeof(int), ios::beg);
        int newValue = 999;
        file.write((char*)&newValue, sizeof(newValue));
        
        // Read all values to verify
        file.seekg(0, ios::beg);
        cout << "All values: ";
        for (int i = 0; i < 10; i++) {
            file.read((char*)&value, sizeof(value));
            cout << value << " ";
        }
        cout << endl;
        
        file.close();
    }
}

void filePositionOperations() {
    fstream file("position_demo.bin", ios::binary | ios::in | ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Write some data
    for (int i = 1; i <= 5; i++) {
        file.write((char*)&i, sizeof(i));
    }
    
    // Get file size
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;
    
    // Move to beginning
    file.seekg(0, ios::beg);
    
    // Read and display current position
    int value;
    while (file.tellg() < fileSize) {
        streampos currentPos = file.tellg();
        file.read((char*)&value, sizeof(value));
        cout << "Position " << currentPos << ": " << value << endl;
    }
    
    file.close();
}
```

## Practical Examples

### Simple Database System

```cpp
class PersonDatabase {
private:
    struct Person {
        int id;
        char firstName[50];
        char lastName[50];
        int age;
        char email[100];
        
        Person() : id(0), age(0) {
            strcpy(firstName, "");
            strcpy(lastName, "");
            strcpy(email, "");
        }
    };
    
    string filename;
    
public:
    PersonDatabase(const string& file) : filename(file) {}
    
    void addPerson(int id, const string& first, const string& last, 
                   int age, const string& email) {
        ofstream file(filename, ios::binary | ios::app);
        
        if (!file.is_open()) {
            cout << "Error opening database file" << endl;
            return;
        }
        
        Person person;
        person.id = id;
        person.age = age;
        strncpy(person.firstName, first.c_str(), 49);
        strncpy(person.lastName, last.c_str(), 49);
        strncpy(person.email, email.c_str(), 99);
        
        file.write((char*)&person, sizeof(Person));
        file.close();
        
        cout << "Person added to database" << endl;
    }
    
    void displayAllPersons() {
        ifstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            cout << "Database file not found" << endl;
            return;
        }
        
        Person person;
        cout << "\n=== PERSON DATABASE ===" << endl;
        cout << "ID\tFirst Name\tLast Name\tAge\tEmail" << endl;
        cout << "--------------------------------------------------------" << endl;
        
        while (file.read((char*)&person, sizeof(Person))) {
            cout << person.id << "\t" << person.firstName << "\t\t" 
                 << person.lastName << "\t\t" << person.age << "\t" 
                 << person.email << endl;
        }
        
        file.close();
    }
    
    bool findPersonById(int searchId) {
        ifstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            cout << "Database file not found" << endl;
            return false;
        }
        
        Person person;
        while (file.read((char*)&person, sizeof(Person))) {
            if (person.id == searchId) {
                cout << "Person found:" << endl;
                cout << "ID: " << person.id << endl;
                cout << "Name: " << person.firstName << " " << person.lastName << endl;
                cout << "Age: " << person.age << endl;
                cout << "Email: " << person.email << endl;
                file.close();
                return true;
            }
        }
        
        file.close();
        cout << "Person with ID " << searchId << " not found" << endl;
        return false;
    }
    
    int getRecordCount() {
        ifstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            return 0;
        }
        
        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.close();
        
        return fileSize / sizeof(Person);
    }
};

void databaseDemo() {
    PersonDatabase db("people.bin");
    
    // Add some people
    db.addPerson(1, "John", "Doe", 30, "john.doe@email.com");
    db.addPerson(2, "Jane", "Smith", 25, "jane.smith@email.com");
    db.addPerson(3, "Bob", "Johnson", 35, "bob.johnson@email.com");
    
    // Display all records
    db.displayAllPersons();
    
    // Search for specific person
    db.findPersonById(2);
    
    // Show record count
    cout << "Total records: " << db.getRecordCount() << endl;
}
```

### Game Save System

```cpp
class GameSave {
private:
    struct SaveData {
        char playerName[50];
        int level;
        int score;
        int lives;
        float health;
        bool hasKey;
        int inventory[10];  // Item IDs
        
        SaveData() : level(1), score(0), lives(3), health(100.0f), hasKey(false) {
            strcpy(playerName, "Player");
            for (int i = 0; i < 10; i++) {
                inventory[i] = 0;
            }
        }
    };
    
public:
    void saveGame(const string& filename, const string& playerName, 
                  int level, int score, int lives, float health, 
                  bool hasKey, int inventory[]) {
        ofstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            cout << "Error creating save file" << endl;
            return;
        }
        
        SaveData saveData;
        strncpy(saveData.playerName, playerName.c_str(), 49);
        saveData.level = level;
        saveData.score = score;
        saveData.lives = lives;
        saveData.health = health;
        saveData.hasKey = hasKey;
        
        for (int i = 0; i < 10; i++) {
            saveData.inventory[i] = inventory[i];
        }
        
        file.write((char*)&saveData, sizeof(SaveData));
        file.close();
        
        cout << "Game saved successfully!" << endl;
    }
    
    bool loadGame(const string& filename) {
        ifstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            cout << "Save file not found" << endl;
            return false;
        }
        
        SaveData saveData;
        if (file.read((char*)&saveData, sizeof(SaveData))) {
            cout << "=== GAME LOADED ===" << endl;
            cout << "Player: " << saveData.playerName << endl;
            cout << "Level: " << saveData.level << endl;
            cout << "Score: " << saveData.score << endl;
            cout << "Lives: " << saveData.lives << endl;
            cout << "Health: " << saveData.health << "%" << endl;
            cout << "Has Key: " << (saveData.hasKey ? "Yes" : "No") << endl;
            
            cout << "Inventory: ";
            for (int i = 0; i < 10; i++) {
                if (saveData.inventory[i] != 0) {
                    cout << saveData.inventory[i] << " ";
                }
            }
            cout << endl;
            
            file.close();
            return true;
        }
        
        file.close();
        cout << "Error loading save file" << endl;
        return false;
    }
};

void gameSaveDemo() {
    GameSave gameSave;
    
    // Create sample game state
    int inventory[10] = {101, 102, 0, 205, 0, 0, 0, 0, 0, 0};
    
    // Save game
    gameSave.saveGame("savegame.dat", "Hero123", 5, 15000, 2, 75.5f, true, inventory);
    
    // Load game
    gameSave.loadGame("savegame.dat");
}
```

## Best Practices

### 1. Always Use Binary Mode

```cpp
// CORRECT
ofstream file("data.bin", ios::binary);

// WRONG - May cause data corruption
ofstream file("data.bin");
```

### 2. Handle Endianness for Portability

```cpp
// For cross-platform compatibility, consider byte order
void writePortableInt(ofstream& file, int value) {
    // Convert to little-endian for consistency
    char bytes[4];
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
    
    file.write(bytes, 4);
}
```

### 3. Use Fixed-Size Data Structures

```cpp
// GOOD - Fixed size, predictable layout
struct FixedRecord {
    int id;
    char name[50];  // Fixed size
    double value;
};

// PROBLEMATIC - Variable size
struct VariableRecord {
    int id;
    string name;    // Variable size - don't write directly
    double value;
};
```

### 4. Version Your File Formats

```cpp
struct FileHeader {
    char signature[4];  // "MYFT"
    int version;        // File format version
    int recordCount;    // Number of records
};

void writeVersionedFile() {
    ofstream file("versioned.bin", ios::binary);
    
    FileHeader header;
    strcpy(header.signature, "MYFT");
    header.version = 1;
    header.recordCount = 0;
    
    file.write((char*)&header, sizeof(header));
    // ... write data ...
    file.close();
}
```

### 5. Error Checking and Validation

```cpp
bool safeBinaryRead(const string& filename) {
    ifstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    
    // Check file size
    file.seekg(0, ios::end);
    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    if (fileSize == 0) {
        cout << "File is empty" << endl;
        file.close();
        return false;
    }
    
    file.close();
    return true;
}
```

## Summary

**Key Points for Binary File Handling:**

1. **Always use `ios::binary` flag** when opening binary files
2. **Use `write()` and `read()`** methods with C-style casting `(char*)`
3. **Be careful with data structure layout** - use fixed-size members
4. **Handle endianness** for cross-platform compatibility
5. **Version your file formats** for future compatibility
6. **Always validate file operations** and data integrity
7. **Use appropriate data types** - avoid variable-length structures
8. **Consider file headers** for metadata and validation
9. **Test with different file sizes** and edge cases
10. **Document your binary file format** for maintenance

Binary files are powerful for performance-critical applications and exact data storage, but require careful handling to ensure data integrity and portability.