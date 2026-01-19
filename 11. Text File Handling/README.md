# Lab 11: Text File Handling

Topics covered:

- [Introduction to File Handling](#introduction-to-file-handling)
  - [Why Use Files](#why-use-files)
  - [File Streams in C++](#file-streams-in-c)
- [Reading from Text Files](#reading-from-text-files)
  - [Opening Files for Reading](#opening-files-for-reading)
  - [Reading Different Data Types](#reading-different-data-types)
  - [Reading Line by Line](#reading-line-by-line)
  - [Reading Entire File](#reading-entire-file)
- [Writing to Text Files](#writing-to-text-files)
  - [Opening Files for Writing](#opening-files-for-writing)
- [File Opening Modes](#file-opening-modes)
  - [Basic Opening Modes](#basic-opening-modes)
  - [Detailed Mode Explanations](#detailed-mode-explanations)
  - [Combining Multiple Modes](#combining-multiple-modes)
  - [Practical Mode Selection Guide](#practical-mode-selection-guide)
  - [Mode Selection Decision Tree](#mode-selection-decision-tree)
  - [Appending to Files](#appending-to-files)
- [File Operations](#file-operations)
  - [Checking File Status](#checking-file-status)
  - [File Position Management](#file-position-management)
  - [Error Handling](#error-handling)
- [Practical Examples](#practical-examples)
  - [Student Grade Manager](#student-grade-manager)
  - [Configuration File Handler](#configuration-file-handler)
  - [Log File System](#log-file-system)
- [Best Practices](#best-practices)
  - [1. Always Check File Operations](#1-always-check-file-operations)
  - [2. Use Appropriate File Modes](#2-use-appropriate-file-modes)
  - [3. Always Close Files](#3-always-close-files)
  - [4. Handle Different File Formats](#4-handle-different-file-formats)
  - [5. Use Meaningful File Names and Paths](#5-use-meaningful-file-names-and-paths)
- [Summary](#summary)

## Introduction to File Handling

### Why Use Files

Files allow programs to:
- Store data permanently (persistence)
- Share data between different program runs
- Process large amounts of data
- Create logs and reports
- Save user preferences and settings

### File Streams in C++

C++ provides three main file stream classes:
- `ifstream` - Input file stream (reading)
- `ofstream` - Output file stream (writing)
- `fstream` - File stream (reading and writing)

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
```

## Reading from Text Files

### Opening Files for Reading

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inputFile;
    
    // Method 1: Open file using open()
    inputFile.open("data.txt");
    
    // Method 2: Open file in constructor
    // ifstream inputFile("data.txt");
    
    // Check if file opened successfully
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file data.txt" << endl;
        return 1;
    }
    
    cout << "File opened successfully!" << endl;
    
    // Always close the file
    inputFile.close();
    return 0;
}
```

### Reading Different Data Types

```cpp
void readBasicData() {
    ifstream inputFile("numbers.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    int number;
    double decimal;
    string word;
    
    // Reading different data types
    inputFile >> number;   // Read integer
    inputFile >> decimal;  // Read double
    inputFile >> word;     // Read string (until whitespace)
    
    cout << "Number: " << number << endl;
    cout << "Decimal: " << decimal << endl;
    cout << "Word: " << word << endl;
    
    inputFile.close();
}

// Example file content (numbers.txt):
// 42
// 3.14159
// Hello
```

### Reading Line by Line

```cpp
void readLineByLine() {
    ifstream inputFile("text.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    string line;
    int lineNumber = 1;
    
    // Read file line by line
    while (getline(inputFile, line)) {
        cout << "Line " << lineNumber << ": " << line << endl;
        lineNumber++;
    }
    
    inputFile.close();
}

// Alternative method using eof()
void readUsingEOF() {
    ifstream inputFile("data.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    string line;
    while (!inputFile.eof()) {
        getline(inputFile, line);
        if (!line.empty()) {  // Skip empty lines at end
            cout << line << endl;
        }
    }
    
    inputFile.close();
}
```

### Reading Entire File

```cpp
void readEntireFile() {
    ifstream inputFile("document.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    string content;
    string line;
    
    // Read entire file into a string
    while (getline(inputFile, line)) {
        content += line + "\n";
    }
    
    cout << "File contents:" << endl;
    cout << content << endl;
    
    inputFile.close();
}

// Reading character by character
void readCharByChar() {
    ifstream inputFile("sample.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    char ch;
    cout << "File contents (char by char): ";
    
    while (inputFile.get(ch)) {  // Read character including whitespace
        cout << ch;
    }
    
    inputFile.close();
}
```

## Writing to Text Files

### Opening Files for Writing

```cpp
void basicWriting() {
    ofstream outputFile;
    
    // Method 1: Open using open()
    outputFile.open("output.txt");
    
    // Method 2: Open in constructor
    // ofstream outputFile("output.txt");
    
    if (!outputFile.is_open()) {
        cout << "Error: Could not create/open file" << endl;
        return;
    }
    
    // Write to file
    outputFile << "Hello, World!" << endl;
    outputFile << "This is line 2" << endl;
    
    cout << "Data written to file successfully!" << endl;
    
    outputFile.close();
}
```

## File Opening Modes

C++ provides several file opening modes that control how files are opened and accessed:

### Basic Opening Modes

```cpp
#include <iostream>
#include <fstream>
using namespace std;

void demonstrateOpeningModes() {
    // ios::in - Open for input (reading)
    ifstream inputFile("data.txt", ios::in);
    // Default for ifstream, can be omitted
    
    // ios::out - Open for output (writing)
    ofstream outputFile("output.txt", ios::out);
    // Default for ofstream, can be omitted
    
    // ios::app - Open for appending (writing at end)
    ofstream appendFile("log.txt", ios::app);
    
    // ios::ate - Open and seek to end of file
    fstream ateFile("data.txt", ios::ate);
    
    // ios::trunc - Truncate file to zero length if it exists
    ofstream truncFile("temp.txt", ios::trunc);
    
    // ios::binary - Open in binary mode
    ofstream binaryFile("data.bin", ios::binary);
}
```

### Detailed Mode Explanations

#### `ios::in` - Input Mode
- **Purpose**: Opens file for reading
- **Behavior**: File must exist, or opening fails
- **File pointer**: Positioned at beginning of file
- **Default for**: `ifstream`

```cpp
void inputModeExample() {
    ifstream file("existing_file.txt", ios::in);
    
    if (!file.is_open()) {
        cout << "File doesn't exist or cannot be opened" << endl;
        return;
    }
    
    string content;
    while (getline(file, content)) {
        cout << content << endl;
    }
    file.close();
}
```

#### `ios::out` - Output Mode
- **Purpose**: Opens file for writing
- **Behavior**: Creates file if it doesn't exist, truncates if it does
- **File pointer**: Positioned at beginning of file
- **Default for**: `ofstream`

```cpp
void outputModeExample() {
    ofstream file("new_file.txt", ios::out);
    
    // This will overwrite existing content
    file << "This replaces all previous content" << endl;
    file << "Previous data is lost" << endl;
    
    file.close();
}
```

#### `ios::app` - Append Mode
- **Purpose**: Opens file for writing at the end
- **Behavior**: Creates file if it doesn't exist, preserves existing content
- **File pointer**: Always positioned at end of file for writing
- **Use case**: Logging, adding records without losing existing data

```cpp
void appendModeExample() {
    // First, create initial content
    ofstream initialFile("log.txt", ios::out);
    initialFile << "Initial log entry" << endl;
    initialFile.close();
    
    // Now append to existing content
    ofstream appendFile("log.txt", ios::app);
    appendFile << "New log entry" << endl;
    appendFile << "Another entry" << endl;
    appendFile.close();
    
    // File now contains all three lines
}
```

#### `ios::ate` - At End Mode
- **Purpose**: Opens file and moves to end immediately
- **Behavior**: File pointer starts at end, but can be moved
- **Difference from app**: You can seek to other positions
- **Use case**: When you need to know file size or append selectively

```cpp
void ateModeExample() {
    fstream file("data.txt", ios::in | ios::out | ios::ate);
    
    if (!file.is_open()) {
        cout << "Cannot open file" << endl;
        return;
    }
    
    // Get file size (we're at the end)
    streampos fileSize = file.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;
    
    // Can move to beginning if needed
    file.seekg(0, ios::beg);
    
    string line;
    getline(file, line);
    cout << "First line: " << line << endl;
    
    file.close();
}
```

#### `ios::trunc` - Truncate Mode
- **Purpose**: Truncates file to zero length if it exists
- **Behavior**: Existing content is deleted
- **Use case**: When you want to completely replace file content

```cpp
void truncateModeExample() {
    // Create file with some content
    ofstream createFile("temp.txt");
    createFile << "This content will be deleted" << endl;
    createFile << "This too" << endl;
    createFile.close();
    
    // Truncate the file (delete all content)
    ofstream truncFile("temp.txt", ios::trunc);
    truncFile << "Only this line remains" << endl;
    truncFile.close();
}
```

### Combining Multiple Modes

You can combine modes using the bitwise OR operator (`|`):

```cpp
void combinedModesExamples() {
    // Read and write mode
    fstream file1("data.txt", ios::in | ios::out);
    
    // Append and read mode
    fstream file2("log.txt", ios::in | ios::app);
    
    // Create new file for read/write, truncate if exists
    fstream file3("new_data.txt", ios::in | ios::out | ios::trunc);
    
    // Binary append mode
    ofstream file4("binary_log.bin", ios::app | ios::binary);
}
```

### Practical Mode Selection Guide

```cpp
class FileModeGuide {
public:
    void demonstratePracticalUsage() {
        // Reading existing configuration
        ifstream config("config.txt", ios::in);
        
        // Creating new report (overwrite existing)
        ofstream report("report.txt", ios::out);
        
        // Adding to log file (preserve existing entries)
        ofstream log("application.log", ios::app);
        
        // Database file (read/write, create if needed)
        fstream database("data.db", ios::in | ios::out | ios::app);
        
        // Temporary file (start fresh each time)
        ofstream temp("temp.txt", ios::out | ios::trunc);
    }
    
    void showModeEffects() {
        cout << "=== File Mode Effects ===" << endl;
        
        // Create initial file
        ofstream initial("test_modes.txt");
        initial << "Line 1" << endl << "Line 2" << endl;
        initial.close();
        
        cout << "Initial file created with 2 lines" << endl;
        
        // Test ios::out (truncates)
        ofstream outMode("test_modes.txt", ios::out);
        outMode << "New content" << endl;
        outMode.close();
        cout << "After ios::out - file has only new content" << endl;
        
        // Test ios::app (preserves and appends)
        ofstream appMode("test_modes.txt", ios::app);
        appMode << "Appended line" << endl;
        appMode.close();
        cout << "After ios::app - file has both old and new content" << endl;
        
        // Show final content
        ifstream final("test_modes.txt");
        string line;
        cout << "Final file content:" << endl;
        while (getline(final, line)) {
            cout << "  " << line << endl;
        }
        final.close();
    }
};
```

### Mode Selection Decision Tree

```cpp
void chooseFileMode() {
    cout << "File Mode Selection Guide:" << endl;
    cout << "=========================" << endl;
    
    cout << "\nUse ios::in when:" << endl;
    cout << "- Reading existing files" << endl;
    cout << "- File must already exist" << endl;
    cout << "- No modifications needed" << endl;
    
    cout << "\nUse ios::out when:" << endl;
    cout << "- Creating new files" << endl;
    cout << "- Completely replacing file content" << endl;
    cout << "- Don't care about existing content" << endl;
    
    cout << "\nUse ios::app when:" << endl;
    cout << "- Adding to existing files" << endl;
    cout << "- Logging applications" << endl;
    cout << "- Preserving existing data" << endl;
    
    cout << "\nUse ios::ate when:" << endl;
    cout << "- Need to know file size first" << endl;
    cout << "- Want to append but may seek elsewhere" << endl;
    cout << "- Reading file size for validation" << endl;
    
    cout << "\nUse ios::trunc when:" << endl;
    cout << "- Explicitly want to delete existing content" << endl;
    cout << "- Starting fresh with existing filename" << endl;
    cout << "- Combined with other modes for clarity" << endl;
    
    cout << "\nUse combined modes when:" << endl;
    cout << "- ios::in | ios::out: Read and modify existing file" << endl;
    cout << "- ios::out | ios::trunc: Explicitly overwrite (same as ios::out)" << endl;
    cout << "- ios::in | ios::app: Read existing and append new data" << endl;
}

### Writing Different Data Types

```cpp
void writeVariousData() {
    ofstream outputFile("mixed_data.txt");
    
    if (!outputFile.is_open()) {
        cout << "Error creating file" << endl;
        return;
    }
    
    // Writing different data types
    int age = 25;
    double salary = 50000.75;
    string name = "John Doe";
    bool isEmployed = true;
    
    outputFile << "Name: " << name << endl;
    outputFile << "Age: " << age << endl;
    outputFile << "Salary: " << salary << endl;
    outputFile << "Employed: " << (isEmployed ? "Yes" : "No") << endl;
    
    // Writing formatted data
    outputFile << "Formatted salary: $" << fixed << setprecision(2) << salary << endl;
    
    outputFile.close();
    cout << "Mixed data written to file!" << endl;
}
```

### Appending to Files

```cpp
void appendToFile() {
    // Open file in append mode
    ofstream outputFile("log.txt", ios::app);
    
    if (!outputFile.is_open()) {
        cout << "Error opening file for append" << endl;
        return;
    }
    
    // Get current time for log entry
    time_t now = time(0);
    char* timeStr = ctime(&now);
    
    outputFile << "Log entry at: " << timeStr;
    outputFile << "Application started successfully" << endl;
    outputFile << "---" << endl;
    
    outputFile.close();
    cout << "Log entry added!" << endl;
}
```

## File Operations

### Checking File Status

```cpp
void checkFileStatus() {
    ifstream inputFile("test.txt");
    
    // Check various file states
    if (inputFile.is_open()) {
        cout << "File is open" << endl;
    }
    
    if (inputFile.good()) {
        cout << "File stream is in good state" << endl;
    }
    
    if (inputFile.eof()) {
        cout << "End of file reached" << endl;
    }
    
    if (inputFile.fail()) {
        cout << "File operation failed" << endl;
    }
    
    if (inputFile.bad()) {
        cout << "File stream is corrupted" << endl;
    }
    
    inputFile.close();
}

void safeFileReading() {
    ifstream inputFile("numbers.txt");
    
    if (!inputFile.is_open()) {
        cout << "Cannot open file" << endl;
        return;
    }
    
    int number;
    while (inputFile >> number) {  // Read until failure or EOF
        cout << "Read number: " << number << endl;
    }
    
    // Check why reading stopped
    if (inputFile.eof()) {
        cout << "Reached end of file" << endl;
    } else if (inputFile.fail()) {
        cout << "Failed to read (possibly wrong format)" << endl;
    }
    
    inputFile.close();
}
```

### File Position Management

```cpp
void filePositionDemo() {
    fstream file("position_test.txt", ios::in | ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // Write some data
    file << "Hello World" << endl;
    file << "Second line" << endl;
    file << "Third line" << endl;
    
    // Get current position
    streampos writePos = file.tellp();
    cout << "Current write position: " << writePos << endl;
    
    // Move to beginning for reading
    file.seekg(0, ios::beg);
    
    string line;
    getline(file, line);
    cout << "First line: " << line << endl;
    
    // Get current read position
    streampos readPos = file.tellg();
    cout << "Current read position: " << readPos << endl;
    
    // Move to specific position
    file.seekg(6, ios::beg);  // Move to position 6
    getline(file, line);
    cout << "From position 6: " << line << endl;
    
    file.close();
}
```

### Error Handling

```cpp
void robustFileHandling(const string& filename) {
    ifstream inputFile;
    
    try {
        inputFile.open(filename);
        
        if (!inputFile.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }
        
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
            
            // Check for read errors
            if (inputFile.bad()) {
                throw runtime_error("Error reading from file");
            }
        }
        
        inputFile.close();
        
    } catch (const exception& e) {
        cout << "File error: " << e.what() << endl;
        
        if (inputFile.is_open()) {
            inputFile.close();
        }
    }
}
```

## Practical Examples

### Student Grade Manager

```cpp
class GradeManager {
private:
    struct Student {
        string name;
        int id;
        double grade;
    };
    
public:
    void saveStudents(const string& filename) {
        ofstream outputFile(filename);
        
        if (!outputFile.is_open()) {
            cout << "Error creating file" << endl;
            return;
        }
        
        int numStudents;
        cout << "How many students? ";
        cin >> numStudents;
        
        for (int i = 0; i < numStudents; i++) {
            Student student;
            cout << "Enter name: ";
            cin >> student.name;
            cout << "Enter ID: ";
            cin >> student.id;
            cout << "Enter grade: ";
            cin >> student.grade;
            
            // Save to file
            outputFile << student.name << " " << student.id << " " << student.grade << endl;
        }
        
        outputFile.close();
        cout << "Students saved to " << filename << endl;
    }
    
    void loadStudents(const string& filename) {
        ifstream inputFile(filename);
        
        if (!inputFile.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        
        Student student;
        cout << "Students from file:" << endl;
        cout << "Name\t\tID\tGrade" << endl;
        cout << "------------------------" << endl;
        
        while (inputFile >> student.name >> student.id >> student.grade) {
            cout << student.name << "\t\t" << student.id << "\t" << student.grade << endl;
        }
        
        inputFile.close();
    }
    
    void calculateAverageFromFile(const string& filename) {
        ifstream inputFile(filename);
        
        if (!inputFile.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        
        double sum = 0;
        int count = 0;
        Student student;
        
        while (inputFile >> student.name >> student.id >> student.grade) {
            sum += student.grade;
            count++;
        }
        
        if (count > 0) {
            cout << "Average grade: " << (sum / count) << endl;
        } else {
            cout << "No students found in file" << endl;
        }
        
        inputFile.close();
    }
};
```

### Configuration File Handler

```cpp
class ConfigManager {
private:
    string configFile;
    
public:
    ConfigManager(const string& filename) : configFile(filename) {}
    
    void createDefaultConfig() {
        ofstream config(configFile);
        
        if (!config.is_open()) {
            cout << "Error creating config file" << endl;
            return;
        }
        
        config << "# Application Configuration" << endl;
        config << "window_width=800" << endl;
        config << "window_height=600" << endl;
        config << "fullscreen=false" << endl;
        config << "sound_enabled=true" << endl;
        config << "difficulty=medium" << endl;
        
        config.close();
        cout << "Default configuration created" << endl;
    }
    
    string readSetting(const string& key) {
        ifstream config(configFile);
        
        if (!config.is_open()) {
            cout << "Config file not found" << endl;
            return "";
        }
        
        string line;
        while (getline(config, line)) {
            // Skip comments and empty lines
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            // Find the key
            size_t pos = line.find('=');
            if (pos != string::npos) {
                string fileKey = line.substr(0, pos);
                if (fileKey == key) {
                    config.close();
                    return line.substr(pos + 1);
                }
            }
        }
        
        config.close();
        return "";  // Key not found
    }
    
    void updateSetting(const string& key, const string& value) {
        // Read all lines
        ifstream inputFile(configFile);
        string content = "";
        string line;
        bool keyFound = false;
        
        while (getline(inputFile, line)) {
            if (line.empty() || line[0] == '#') {
                content += line + "\n";
                continue;
            }
            
            size_t pos = line.find('=');
            if (pos != string::npos) {
                string fileKey = line.substr(0, pos);
                if (fileKey == key) {
                    content += key + "=" + value + "\n";
                    keyFound = true;
                } else {
                    content += line + "\n";
                }
            } else {
                content += line + "\n";
            }
        }
        inputFile.close();
        
        // If key not found, add it
        if (!keyFound) {
            content += key + "=" + value + "\n";
        }
        
        // Write back to file
        ofstream outputFile(configFile);
        outputFile << content;
        outputFile.close();
    }
};
```

### Log File System

```cpp
class Logger {
private:
    string logFile;
    
    string getCurrentTime() {
        time_t now = time(0);
        char buffer[80];
        struct tm* timeinfo = localtime(&now);
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }
    
public:
    Logger(const string& filename) : logFile(filename) {}
    
    void logInfo(const string& message) {
        ofstream log(logFile, ios::app);
        if (log.is_open()) {
            log << "[INFO] " << getCurrentTime() << " - " << message << endl;
            log.close();
        }
    }
    
    void logError(const string& message) {
        ofstream log(logFile, ios::app);
        if (log.is_open()) {
            log << "[ERROR] " << getCurrentTime() << " - " << message << endl;
            log.close();
        }
    }
    
    void logWarning(const string& message) {
        ofstream log(logFile, ios::app);
        if (log.is_open()) {
            log << "[WARNING] " << getCurrentTime() << " - " << message << endl;
            log.close();
        }
    }
    
    void displayLog() {
        ifstream log(logFile);
        if (!log.is_open()) {
            cout << "No log file found" << endl;
            return;
        }
        
        string line;
        cout << "=== LOG FILE CONTENTS ===" << endl;
        while (getline(log, line)) {
            cout << line << endl;
        }
        log.close();
    }
    
    void clearLog() {
        ofstream log(logFile, ios::trunc);  // Truncate file
        log.close();
        cout << "Log file cleared" << endl;
    }
};
```

## Best Practices

### 1. Always Check File Operations

```cpp
// GOOD
ifstream file("data.txt");
if (!file.is_open()) {
    cout << "Error: Cannot open file" << endl;
    return;
}

// BAD - No error checking
ifstream file("data.txt");
string data;
file >> data;  // Might fail silently
```

### 2. Use Appropriate File Modes

```cpp
// Reading only
ifstream inputFile("data.txt");

// Writing (overwrites existing file)
ofstream outputFile("output.txt");

// Appending (adds to end of existing file)
ofstream logFile("log.txt", ios::app);

// Reading and writing
fstream file("data.txt", ios::in | ios::out);
```

### 3. Always Close Files

```cpp
// Manual closing
ifstream file("data.txt");
// ... use file ...
file.close();

// Automatic closing (recommended)
{
    ifstream file("data.txt");
    // ... use file ...
}  // File automatically closed when going out of scope
```

### 4. Handle Different File Formats

```cpp
void readCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    
    string line;
    while (getline(file, line)) {
        // Process CSV line
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos) {
            string field = line.substr(0, pos);
            cout << "Field: " << field << endl;
            line.erase(0, pos + 1);
        }
        cout << "Last field: " << line << endl;
    }
    file.close();
}
```

### 5. Use Meaningful File Names and Paths

```cpp
// GOOD - Descriptive names
void saveUserPreferences() {
    ofstream file("user_preferences.txt");
    // ...
}

void exportStudentGrades() {
    ofstream file("student_grades_2024.csv");
    // ...
}

// BAD - Unclear names
void saveData() {
    ofstream file("data.txt");  // What kind of data?
    // ...
}
```

## Summary

**Key Points to Remember:**

1. **Always check** if files open successfully
2. **Use appropriate stream types**: `ifstream` for reading, `ofstream` for writing
3. **Handle errors gracefully** with proper exception handling
4. **Close files** when done (automatic with scope-based management)
5. **Use meaningful file names** and organize files logically
6. **Consider file formats** (CSV, plain text, etc.) for data exchange
7. **Test file operations** with different scenarios (missing files, permissions, etc.)

Text file handling is essential for data persistence, configuration management, logging, and data exchange between applications.