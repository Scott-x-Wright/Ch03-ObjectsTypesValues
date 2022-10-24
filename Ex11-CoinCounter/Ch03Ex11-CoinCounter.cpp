// Ch03Ex11-CoinCounter.cpp
//
// Solution to Exercise 11 of Chapter 3 from Programming Principles and Practice Using C++ (2e)
// * counts coins and shows dollar (decimal) equivalent
//
// A comprehensive solution to this needs to deal with lots of interesting formatting nuances!
//
// 11/10/18	Scott Wright
//  1/13/21 Scott Wright: revised to compile with C++17 under gcc 10.2, clang 11.0.0, icc 21.1.9 and msvc 19.28.
//  3/25/21 Scott Wright: cleaned up and revised to conform to latest boilerplate code
// 10/21/22 Scott Wright: cleaned up penny output; revised to conform to latest boilerplate code

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

int exercise()
{
	cout << "Chapter 3, Exercise 11: coin counter.\n\n";

	int total_cents{ 0 };

	int pennies{ 0 };
	cout << "How many pennies do you have? ";
	cin >> pennies;
	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");
	if (pennies < 0)
		BAILOUT("You can't have a negative number of pennies!");
	total_cents += pennies;

	int nickels{ 0 };
	cout << "How many nickels do you have? ";
	cin >> nickels;
	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");
	if (nickels < 0)
		BAILOUT("You can't have a negative number of nickels!");
	total_cents += (5 * nickels);

	int dimes{ 0 };
	cout << "How many dimes do you have? ";
	cin >> dimes;
	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");
	if (dimes < 0)
		BAILOUT("You can't have a negative number of dimes!");
	total_cents += (10 * dimes);

	int quarters{ 0 };
	cout << "How many quarters do you have? ";
	cin >> quarters;
	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");
	if (quarters < 0)
		BAILOUT("You can't have a negative number of quarters!");
	total_cents += (25 * quarters);

	int half_dollars{ 0 };
	cout << "How many half dollars do you have? ";
	cin >> half_dollars;
	if (cin.fail())
		BAILOUT("Invalid input -- unable to continue");
	if (half_dollars < 0)
		BAILOUT("You can't have a negative number of half dollars!");
	total_cents += (50 * half_dollars);

	cout << "\nYou have " << pennies << " penn" << (pennies != 1 ? "ies" : "y") << ".\n";

	cout << "You have " << nickels << " nickel";
	if (nickels != 1)
		cout << 's';
	cout << ".\n";

	cout << "You have " << dimes << " dime";
	if (dimes != 1)
		cout << 's';
	cout << ".\n";

	cout << "You have " << quarters << " quarter";
	if (quarters != 1)
		cout << 's';
	cout << ".\n";

	cout << "You have " << half_dollars << " half dollar";
	if (half_dollars != 1)
		cout << 's';
	cout << ".\n";

	if (total_cents > 0)
	{
		// Show coin total in just cents...
		cout << "\nThe value of all your coins is " << total_cents << " cent";
		if (total_cents > 1)	// handle case of one cent
			cout << 's';
		cout << ", or $";
		// ...and in dollars...
		int dollars = total_cents / 100;
		if (dollars == 0)		// handle case of no dollars
			cout << '0';
		else
			cout << dollars;
		cout << '.';
		// ...and cents
		int cents = total_cents % 100;
		if (cents >= 10)
			cout << cents;
		else if (cents > 0)		// handle case of one to nine cents 
			cout << '0' << cents;
		else					// handle case of no cents
			cout << "00";
		cout << '.';
	}
	else if (total_cents == 0)
		cout << "\nYou're broke!";
	else
		BAILOUT("Unreachable code");

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
