// Ch03-TryThis.cpp: "Try This" examples for P3Cpp Chapter 3
//
// 11/8/18	Scott Wright

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Sec. 3.9.2
	double d = 0;
	while (cin >> d)
	{
#pragma warning(suppress: 4244)
		int i = d;
#pragma warning(suppress: 4244)
		char c = i;
		int i2 = c;
		cout << "d == " << d << ", i == " << i << ", i2 == " << i2 << ", char(" << c << ")\n";
	}

	// Sec. 3.5.1
	/*
	string previous = " ";
	string current;
	while (cin >> current)
	{
		if (previous == current)
			cout << "repeated word: " << current << '\n';

		previous = current;
	}
	*/

	// Sec. 3.4
	/*
	cout << "Enter a floating-point value: ";
	int n;
	cin >> n;
	cout << "n == " << n
		<< "\nn + 1 == " << n + 1
		<< "\nthree times n == " << 3 * n
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n * n
		<< "\nhalf of n == " << n / 2
		<< "\nsquare root of n == " << sqrt(static_cast<double>(n))
		<< '\n';
	*/

	// Sec. 3.3
	/*
	cout << "Please enter your first name and age: ";
	string first_name = "???";
	double age = -1;

	cin >> first_name >> age;

	int months = static_cast<int>(12 * age);	// more advanced than text, but obviates warning

	cout << "Hello, " << first_name << " (age " << months << " months)\n";
	*/

	// keepwinopen on user acknowledgement
#pragma warning(suppress: 6031)
	fflush(stdout); cout << "\nPress Enter to exit..."; fflush(stdin); getc(stdin);

	return EXIT_SUCCESS;
}
