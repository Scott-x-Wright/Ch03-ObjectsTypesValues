// Ch03Ex10-PrefixCalc.cpp
//
// Solution to Exercise 10 of Chapter 3 from Programming Principles and Practice Using C++ (2e)
// * simple arithermetic prefix calculator (i.e. + 2 3 ==> 5)
//
// 11/10/18	Scott Wright
//  1/13/21 Scott Wright: revised to compile with C++17 under gcc 10.2, clang 11.0.0, icc 21.1.9 and msvc 19.28.
//  3/25/21 Scott Wright: cleaned up and revised to conform to latest boilerplate code
// 10/21/22 Scott Wright: revised to conform to latest boilerplate code

#if __cplusplus < 201703L
#error "Souce code requires C++17 or later!"
#endif

#include <filesystem> // for std::filesystem::path::preferred_separator in BAILOUT
#include <iostream>
using std::cin, std::cout, std::cerr, std::flush, std::endl;
#include <stdexcept>
using std::exception, std::runtime_error;
#include <string>
using std::string, std::to_string;

// useful forms for uniformly throwing exceptions with more meaningful information
//
const string FILE_NAME_PATH{ __FILE__ }; //Ok, global namespace *is* cluttered by one (more) symbol...
#define FILENAME	(FILE_NAME_PATH.substr(FILE_NAME_PATH.rfind(std::filesystem::path::preferred_separator) + 1, FILE_NAME_PATH.size() - FILE_NAME_PATH.rfind(std::filesystem::path::preferred_separator)))
//
#define BAILOUT(message) throw runtime_error(string{message} + "\n[ in function " + __FUNCTION__ + "() at line " + to_string(__LINE__) + " of file " + FILENAME + " ]")

/* ------------------------------------------------------------------------------------------------------------ */

void keepwinopen();

void handleErrorTermination(const string& message, const int status) { cerr << "\n\n" << message << '\n'; keepwinopen(); exit(status); }

/* ------------------------------------------------------------------------------------------------------------ */

int exercise()	// use this as "main()" for problem/exercise
{
	cout << "Chapter 3, Exercise 10: simple arithmetic prefix calculator.\n\n";

	cout << "I can calculate simple prefix arithmetic operations using +, -, * and /.\n"
		 << "(You can also spell out the operations, i.e. \"plus\", \"minus\", \"mul\" and \"div\".)\n"
	     << "For example, \"* 2.5 1.5\" produces 2.5 * 1.5 = 3.75\n";

	cout << "\nEnter prefix operation to compute: ";
	//
	string operation;	// user-entered operand
	double val1, val2;	// user-entered double operands
	//
	cin >> operation >> val1 >> val2;

	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");

	cout << '\n';

	if (operation == "+" || operation == "plus")
	{
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 + val2;
	}
	else if (operation == "-" || operation == "minus")
	{
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 - val2;
	}
	else if (operation == "*" || operation == "mul")
	{
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 * val2;
	}
	else if (operation == "/" || operation == "div")
	{
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 / val2;
	}
	else
		BAILOUT("You entered an operator '" + operation + "' that I don't recognize.");

	if (cin.fail())
		BAILOUT("Invalid operation");

	cout << endl;

	return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------------------ */

#ifdef _MSC_VER
//
#define NOMINMAX	 // prevent Visual C++ redefinition of max()
#include "Windows.h" // includes debugapi.h which declares BOOL IsDebuggerPresent()
//
#endif

void keepwinopen()	 // terminate on user acknowledgement
{
#ifdef _MSC_VER
	if (IsDebuggerPresent())
	{
		cout << "\nPress Enter to exit..." << flush;

		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		cin.get();
	}
	else
#endif
		cout << endl;
}

/* ------------------------------------------------------------------------------------------------------------ */

int main()
{
	cout << "Programming Principles and Practice Using C++ (2e)\n";

	try
	{
		const int retVal = exercise();
		keepwinopen();
		return retVal;
	}
	catch (exception& e)
	{
		handleErrorTermination("Exception: " + string(e.what()), EXIT_FAILURE);
	}
	catch (...)
	{
		handleErrorTermination("UNKNOWN exception", EXIT_FAILURE);
	}
}
