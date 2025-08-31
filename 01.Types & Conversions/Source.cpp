// Conversions between different types of objects (cast operator, operator = and copy
//constructor), const modifier, static members(static), constant objects, constant
//references to objects and pointers to constant objects.
//Arrays of objects and of references to objects.

#include <iostream>

using namespace std;

void main(void*)
{
	float a = 23.42F;
	cout << "type of a: " << typeid(a).name() 
		 << "\ta = " << a << endl;
	// - cast operator
	//   special operator that forces one data type to be converted into another.
	// -> unary operator
	
	// general cast op
	int b;
	b = (int)a;
	cout << "type of b: " << typeid(b).name() 
		 << "\t\tb = " << b << endl;

	// 
}