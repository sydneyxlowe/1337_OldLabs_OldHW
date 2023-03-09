//Sydney Lowe 2181244
//Fall 22 COSC 1137 Lab 5

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int COLS = 10;

// Function prototypes
int* maxPointer(int[], int);
void display2D(int array[][COLS], int size);

int main()
{
	const int ROWS = 10;
	int board[ROWS][COLS];
	int* iPtr = nullptr;
	int* maxrPtr = nullptr;
	int tempVal = 0;

	// Populate 2D array and display contents
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = rand() % ((500 - 10) + 1) + 10;
			cout << setw(4) << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Use of maxpointer function to swap max row elements with end elements
	for (int i = 0; i < ROWS; i++)
	{
		maxrPtr = maxPointer(board[i], COLS);
		tempVal = board[i][COLS - 1];
		board[i][COLS - 1] = *maxrPtr;
		*maxrPtr = tempVal;
	}

	iPtr = *board + 9; //address of last element of first row
	int* maxPtr = iPtr; //address of max element of array

	// Loop for iPtr to check each last element of each row and assign max value address to maxPtr
	for (int i = 0; i < ROWS; i++)
	{
		if (*(iPtr + i*COLS) > *maxPtr)
		{
			maxPtr = (iPtr + i*COLS);
		}
	}
	cout << "The maximum value of board is: " << * maxPtr << endl; //display maxPtr value

	// Loop for iPtr to find the row number of maxPtr
	int rowVal = 0;
	for (int i = 0; i < ROWS; i++)
	{
		if ((iPtr + i * COLS) == maxPtr)
		{
			rowVal = i;
		}
	}
	cout << "The maximum value is in row: " << rowVal + 1 << endl << endl; //display the row of max value

	int* tableX[3]; //declaration of tableX array of 3 pointers
	// Loop to set tableX elements to the addresses of the first 3 rows of board + display
	for (int i = 0; i < 3; i++)
	{
		tableX[i] = board[i];
		for (int j = 0; j < COLS; j++)
		{
			cout << setw(4) << *(tableX[i] + j) << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Set the first element of each row of tableX to -1
	for (int i = 0; i < 3; i++)
	{
		(*tableX[i]) = -1;
	}

	// Display tableX modified
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << setw(4) << *(tableX[i] + j) << " ";
		}
		cout << endl;
	}
	cout << endl;

	display2D(board, ROWS); //display board (was modified after tableX was modified

	return 0;
}

// Receive a 1D array and return a pointer pointing to the max value of the array
int* maxPointer(int array[], int size)
{
	int* maxPtr = &array[0];

	for (int i = 0; i < size; i++)
	{
		if (array[i] > *maxPtr)
		{
			maxPtr = &array[i];
		}
	}

	return maxPtr;
}

// Funciton to display a 2D array
void display2D(int array[][COLS], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << setw(4) << array[i][j] << " ";
		}
		cout << endl;
	}
}