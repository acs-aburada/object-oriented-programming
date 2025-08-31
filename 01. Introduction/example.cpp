#include <iostream>

using namespace std;

// example function for debugging purposes
int getSum(int a, int b) {
    return a + b;
}

int main() {
    // --- ERRORS ---
    // 
    // there are two types of errors that we will focus on
    // 
    // COMPILE-TIME errors = get detected by the compiler before execution
    //                     eg.: Missing Parenthesis; Printing the value of 
    //                          variable without declaring it; Missing semicolon (terminator)
    // 
    // RUNTIME errors = cause the program to crash or terminate abnormally (unexpected behaviour)
    //                     eg.: dividing by zero, an index out of bounds error when trying to access 
    //                          a non-existent list element, or data type errors where the program receives 
    //                          input it can't process, like a string when a number was expected
    
    // compile-time error
    // int a = 4   // missing semicolon -> compiler will point to this line
    int b = 5;
    cout << b << endl;

    // runtime errors

    // accessing out of bounds memory
    int v[5] = {1, 2, 3, 4, 5};
    cout << v[5] << endl;   // accessing out of bounds -> runtime error
                            // some compilers might point out this issue

    int i = 5;
    cout << v[i] << endl;

    for (i = 0; i < 5; i++) {
        i += 10;
        cout << v[i] << endl;
    }

    int x = 3;
    x -= 3;
    //cout << 3 / x << endl;  // this will crash the program
                              // the debugger is able to point out the runtime error

    // --- DEBUGGING ---
    // 
    // step over: executes the current line of code and pauses on the next line, 
    //            without entering any function calls
    // step into: enters the code of the current line if it is / contains a function 
    //            and pauses at the first line of the function
    // step out: continues the program’s execution until it exits the current function
    // continue: resumes normal execution

    // try out step over, step into, step out functions

    int n = 0;
    for (i = 1; i <= 3; i++) {
        n += getSum(0, i);
        if (i == 3)
            cout << "end of \"for\"" << endl;
    }
    cout << n << endl;

    return 0;
}

//int main(int argc, char** argv) {
//    cout << argc << endl;
//
//    for (int i = 0; i < argc; i++) {
//        cout << argv[i] << " ";
//    }
//
//    return 0;
//}