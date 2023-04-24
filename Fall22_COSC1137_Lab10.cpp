//Sydney Lowe 2181244
//COSC 1137 Lab 10
//Main code

#include <iostream>
#include <iomanip>
#include "NumArray.h"
using namespace std;

int main()
{
	//Variable declarations
	int size;
	float num;
	
	//User input for size of the array
	cout << "How many numbers do you want to store? ";
	cin >> size;

	//Object instantiation
	NumArray list(size);

	//User input of values, stored using class function
	cout << "Enter the " << size << " numbers:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Number " << i + 1 << ": ";
		cin >> num;
		list.setNum(num, i);
	}

	//Output of entered values using class function
	cout << endl << "Here are the numbers you entered: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Number " << i + 1 << ": " << list.getNum(i) << endl;
	}
	cout << endl;

	//Output of max, min, and average using class function
	cout << "The highest of those numbers is: " << list.getMax(size) << endl;
	cout << "The lowest of those numbers is: " << list.getMin(size) << endl;
	cout << fixed << showpoint << setprecision(2);
	cout << "The average of those numbers is: " << list.getAvg(size) << endl;

	return 0;
}