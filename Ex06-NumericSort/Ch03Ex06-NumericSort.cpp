// Ch03Ex06-NumericSort.cpp
//
// Solution to Exercise 6 of Chapter 3 from Programming Principles and Practice Using C++ (2e)
// * sort three user-entered integer values from smallest to largest
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

inline void handleErrorTermination(const string& message, const int status) { cerr << "\n\n" << message << '\n'; keepwinopen(); exit(status); }

/* ------------------------------------------------------------------------------------------------------------ */

int exercise()
{
	cout << "Chapter 3, Exercise 6: Simple three-integer numeric sort.\n\n";

	cout << "Enter three whitespace-separated integer values to sort: ";
	//
	int val1, val2, val3;	// user-entered integer values to sort
	//
	cin >> val1 >> val2 >> val3;

	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");

	const string comma{ ", " };

	cout << "\nSorted: ";

	if (val1 <= val2 && val1 <= val3)		// val1 qualifies as smallest
	{
		cout << val1 << comma;

		if (val2 <= val3)
			cout << val2 << comma << val3;
		else
			cout << val3 << comma << val2;
	}
	else if (val2 <= val1 && val2 <= val3)	// val2 qualifies as smallest
	{
		cout << val2 << comma;

		if (val1 <= val3)
			cout << val1 << comma << val3;
		else
			cout << val3 << comma << val1;
	}
	else 									// val3 qualifies as smallest
	{
		cout << val3 << comma;

		if (val1 <= val2)
			cout << val1 << comma << val2;
		else
			cout << val2 << comma << val1;
	}

	cout << endl;

	return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------------------ */

#ifdef _MSC_VER
//
#define NOMINMAX	 // prevent Visual C++ redefinition of max()
#include "Windows.h" // includes debugapi.h which declares BOOL IsDebuggerPresent()
//
void keepwinopen()	 // terminate on user acknowledgement
{
	cin.clear();

	cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');

	if (IsDebuggerPresent())
		cout << "\nPress Enter to exit..." << flush, cin.get(); /* NOTE COMMA! */
}
//
#else // for Linux/gcc
//
void keepwinopen() {} // not needed for Linux/gcc
//
#endif

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
