// Ch03-Drill.cpp: Drill for P3Cpp Chapter 3
//
// 11/ 9/18	Scott Wright
//  1/12/21 Scott Wright: revised to compile with C++17 under gcc 10.2, clang 11.0.1, icc 2021.1.2 and msvc 19.28.
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
	cout << "Chapter 3, Drill\n\n";

	cout << "Enter the name of the person you want to write to: ";
	string first_name;
	cin >> first_name;

	cout << "Enter " << first_name << "'s age (in years): ";
	int age{ 0 };
	cin >> age;
	if (age <= 0 || age >= 110)
		BAILOUT("Invalid age '" + to_string(age) + "' given");

	cout << "Enter the name of a mutual friend: ";
	string friend_name;
	cin >> friend_name;

	cout << "Enter sex of mutual friend (one character: 'm' for male or 'f' for female): ";
	char friend_sex;
	cin >> friend_sex;
	if (friend_sex != 'f' && friend_sex != 'm')
		BAILOUT("Invalid sex '" + string{ friend_sex } + "' given");

	cout << "\nDear " << first_name << ",\n\n";
	cout << "\tHow are you? I am fine, but I miss you.\n";
	cout << "I have been quite busy recently. ";
	//cout << "\n\tHave you seen " << friend_name << " lately?";
	if (friend_sex == 'f')
		cout << "If you see " << friend_name << ", please ask her to call me.\n";
	if (friend_sex == 'm')
		cout << "If you see " << friend_name << ", please ask him to call me.\n";
	cout << "\n\tI hear you just had a birthday and are " << age << " years old. ";
	if (age < 12)
		cout << "Next year you will be " << age + 1 << '.';
	if (age == 17)
		cout << "Next year you will be able to vote.";
	if (age > 70)
		cout << "I hope you are enjoying retirement.";
	cout << '\n';
	cout << "\nYours sincerely,\n\n\nScott";
	
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
	catch (runtime_error& e)
	{
		handleErrorTermination("Runtime error: " + string(e.what()), EXIT_FAILURE);
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
