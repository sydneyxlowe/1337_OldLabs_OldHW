//Sydney Lowe 2181244
//Fall22 Lab 3 Solution

#include <iostream>
#include <fstream>
using namespace std;

const int COLS = 5;

//function prototypes
int highestScore(int[], int);
int averageScore(int[], int);
int maxAvgRowIndex(int[][COLS], int);
void names_ScoresPerAssign(int[][COLS], string[], int, int);
char letterGrade(int);
void studentInfo(int[][COLS], string[], int, string);

int main()
{
	const int ROWS = 10;
	const int SIZE = 10;
	string names[SIZE];
	int scores[ROWS][COLS];

	ifstream infile("gradeBook.txt");

	//Read content into one 1D array and one 2D array
	for (int i = 0; i < SIZE; i++)
	{
		infile >> names[i];
		for (int j = 0; j < COLS; j++)
			infile >> scores[i][j];
	}
	
	int choice;

	//do while loop to display menu of options until user exits
	do
	{
		cout << "\t1.\tWhat is the name of the student with the highest average score? \n";
		cout << "\t2.\tWhat is the highest score for a certain student?\n";
		cout << "\t3.\tList students' names and scores for certain assignment\n";
		cout << "\t4.\tList certain student's list of letter grades\n";
		cout << "\t5.\tExit\n";
		cout << "Please enter an option: ";
		cin >> choice;
		cout << endl;

		//if else statements
		if (choice == 1)
		{
			cout << "The student with the highest average score is " << names[maxAvgRowIndex(scores, ROWS)] << ". \n"<< "\n";
		}

		else if (choice == 2)
		{
			int index = -1;
			string name;
			cout << "Enter their first name: ";
			cin >> name;

			//for loop to check name and find name index
			for (int i = 0; i < ROWS; i++)
			{
				if (names[i] != name && i == ROWS - 1 && index == -1)
				{
					cout << name << " is not in the grade book." << "\n";
				}

				else
				{
					if (names[i] == name)
					{
						index = i;
						cout << "The highest score for " << name << " is " << highestScore(scores[index], COLS) << ". \n"<< endl;
					}
				}
			}
		}

		else if (choice == 3)
		{
			int assign;
			cout << "Enter the assignment number (1-5): ";
			cin >> assign;
			assign--;
			cout << endl;
			names_ScoresPerAssign(scores, names, ROWS, assign);
		}

		else if (choice == 4)
		{
			string sname;
			cout << "Enter their first name: ";
			cin >> sname;
			studentInfo(scores, names, ROWS, sname);
		}

		else
		{
			choice = 5;
		}
	} while (choice != 5);
	
	return 0;
}

//Receives a 1D array and its size, and returns the max value
int highestScore(int score[], int size)
{
	int highest = score[0];

	for (int i = 0; i < size; i++)
	{
		if (score[i] > highest)
		{
			highest = score[i];
		}
	}
	return highest;
}

//Receives a 1D array and its size and returns the average value
int averageScore(int score[], int size)
{
	int total = 0;
	int average;

	for (int i = 0; i < size; i++)
	{
		total += score[i];
	}
	
	average = total / size;

	return average;
}

//Receives a 2D array, its # of rows, and returns the index of the row that earns the max average score.
int maxAvgRowIndex(int scores[][COLS], int rows)
{
	int index = 0;
	int maxAvg = scores[0][0];

	for (int i = 0; i < rows; i++)
	{
		if (averageScore(scores[i], COLS) > maxAvg)
		{
			index = i - 1;
		}
		
	}
	
	return index;
}

//Receives 2D array info and outputs names of students along w scores for that assignment one student per line. 
void names_ScoresPerAssign(int score[][COLS], string name[], int rows, int number)
{
	for (int i = 0; i < rows; i++)
	{
		cout << name[i] << " " << score[i][number -1] << "\n";
	}
	cout << endl;
}

//Receives integer score and returns equivalent letter grade.
char letterGrade(int score)
{
	char scoreLetter;
	switch (score / 10)
	{
	case 10:
	case 9:
		scoreLetter = 'A';
		break;
	case 8:
		scoreLetter = 'B';
		break;
	case 7:
		scoreLetter = 'C';
		break;
	case 6:
		scoreLetter = 'D';
		break;
	}

	return scoreLetter;
}

//Receives 2D array, names array, array info, name of student to look for, displays name and grades for each score;
void studentInfo(int score[][COLS], string name[], int rows, string student)
{
	int index = -1;
	for (int i = 0; i < rows; i++)
	{
		
		if (name[i] != student && i == rows-1 && index == -1)
		{
			cout << student << " is not in the grade book." << "\n";
		}
		
		else
		{
			if (name[i] == student)
			{
				index = i;
				cout << student << " ";
				for (int j = 0; j < COLS; j++)
				{
					if (index >= 0)
					{
						int val = score[index][j];
						cout << letterGrade(val) << " ";
					}
				}
			}

		
		}
	}
	cout << endl << endl;
}

