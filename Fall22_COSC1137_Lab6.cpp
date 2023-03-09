//Sydney Lowe 2181244
//Lab 6

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Function prototypes
void displayTeam(string*, int);
void youngestPerson(string*, int, string*, int);
string* merge(string*, int, string*, int);
void youngestPersonII(string*, int, string*, int);


int main()
{
	//variable declarations
	const int size = 36;
	string names[size];
	int count = 0, sizeA = 0, sizeB = 0, sizeC = 0;
	string* teamA = nullptr, *teamB = nullptr, *teamC = nullptr;
	ifstream infile("applicants.txt");

	//Assign names array to empty strings
	for (int i = 0; i < size; i++)
	{
		names[i] = " ";
	}

	//Assign names from file to the index of the person's age
	for (int i = 0; i < size; i++)
	{
		while (infile >> names[i] >> count)
		{
			names[count] = names[i];
			if (count != i)
			{
				names[i] = " ";
			}
		}
	}
	
	//Display contents of array
	for (int i = 0; i < size; i++)
	{
		if (names[i] == " ") //Mark space empty if no name associated with that "age"
		{
			cout << "--------" << endl;
		}

		else
		{
			cout << names[i] << " " << i << endl;
		}
	}
	cout << endl;
	
	//Determine size of each team
	for (int i = 0; i < size; i++)
	{
		if (names[i] != " " && i >= 10 && i <= 17)
			sizeA++;
		else if (names[i] != " " && i >= 18 && i <= 24)
			sizeB++;
		else if (names[i] != " " && i >= 25 && i <= 35)
			sizeC++;
	}

	//Dynamically allocate arrays for each team
	teamA = new string[sizeA];
	teamB = new string[sizeB];
	teamC = new string[sizeC];

	//Assign names to each new array based on age using original names array
	int j = 0, b = 0, c = 0;
	for (int i = 0; i < size; i++)
	{
		if (names[i] != " " && i >= 10 && i <= 17)
		{
			teamA[j] = names[i];
			j++;
		}

		else if (names[i] != " " && i >= 18 && i <= 24)
		{
			teamB[b] = names[i];
			b++;
		}

		else if (names[i] != " " && i >= 25 && i <= 35)
		{
			teamC[c] = names[i];
			c++;
		}
	}

	//Menu display + loop
	int choice;
	do
	{
		cout << "\t1.\tDisplay the names of the members of every team on separate lines.\n";
		cout << "\t2.\tDisplay the ages that are not represented in this research.\n";
		cout << "\t3.\tDisplay the names of the youngest and oldest participants regardless of teams.\n";
		cout << "\t4.\tDisplay the names and ages of the youngest volunteers on each team.\n";
		cout << "\t5.\tMerge two teams A and B and display the merged team's members.\n";
		cout << "\t6.\tExit.\n";
		cin >> choice;
		cout << endl;

		if (choice == 1)
		{
			cout << "Team A: ";
			displayTeam(teamA, sizeA);
			cout << "Team B: ";
			displayTeam(teamB, sizeB);
			cout << "Team C: ";
			displayTeam(teamC, sizeC);
			cout << endl;
		}

		else if (choice == 2)
		{
			cout << "The ages not represented are: ";
			for (int i = 10; i < size; i++) 
			{
				if (names[i] == " ") //If element is empty, display that index (age)
				{
					cout << i << " ";
				}
			}
			cout << endl << endl;
		}

		else if (choice == 3)
		{
			/*
			//loop to find oldest and youngest ages
			int youngest = 35;
			int oldest = 0;

			for (int i = 0; i < size; i++)
			{
				if (names[i] != " " && i < youngest)
					youngest = i;

				if (names[i] != " " && i > oldest)
					oldest = i;
			}
			*/

			//more effecient way of youngest and oldest names
			cout << "The youngest person was: " << teamA[0] << "\nThe oldest person was: " << teamC[sizeC-1] << endl << endl;
		}

		else if (choice == 4)
		{
			cout << "The youngest person on Team A";
			youngestPerson(names, size, teamA, sizeA);
			youngestPersonII(names, size, teamA, sizeA);
			cout << "The youngest person on Team B";
			youngestPerson(names, size, teamB, sizeB);
			youngestPersonII(names, size, teamB, sizeB);
			cout << "The youngest person on Team C";
			youngestPerson(names, size, teamC, sizeC);
			youngestPersonII(names, size, teamC, sizeC);
			cout << endl;
		}

		else if (choice == 5)
		{
			string* mergeArr = nullptr;
			mergeArr = merge(teamA, sizeA, teamB, sizeB);
			cout << "The new merged team includes: ";
			displayTeam(mergeArr, sizeA + sizeB);
			cout << endl;

			//release dynamic memory from merge function and nullify pointer
			delete[] mergeArr;
			mergeArr = nullptr;
		}

		else
		{
			choice = 6;
		}

	} while (choice != 6);

	//release dynamic memory and nullify pointers
	delete[] teamA;
	delete[] teamB;
	delete[] teamC;
	teamA = nullptr;
	teamB = nullptr;
	teamC = nullptr;

	return 0;
}

void displayTeam(string* array, int size) //Function displays a 1D array
{
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";

	cout << endl;
}

string* merge(string* arrayA, int sizeA, string* arrayB, int sizeB) //Function merges two arrays of strings + returns the pointer to it
{
	int newSize = sizeA + sizeB;
	string* newArray = nullptr;
	newArray = new string[newSize];

	for (int i = 0; i < sizeA; i++)
	{
		newArray[i] = arrayA[i];
	}

	for (int i = 0; i < sizeB; i++)
	{
		newArray[(i+ sizeA)] = arrayB[i];
	}

	return newArray;
}

void youngestPerson(string* array, int size, string* arrayB, int sizeB) //Function finds the youngest person in given team
{
	int youngest = 0;

	for (int i = 0; i < sizeB; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arrayB[i] == array[j] && youngest == 0)
			{
				youngest = j;
			}

			if (arrayB[i] == array[j] && j <= youngest)
			{
				youngest = j;
			}
		}
	}
	cout << " is: " << array[youngest] << " at age " << youngest << endl;
}

//More efficient loop for youngest person
void youngestPersonII(string* array, int size, string* arrayB, int sizeB)
{
	string youngest = arrayB[0];

	for (int i = 0; i < size; i++)
	{
		if (youngest == array[i])
		{
			cout << "The youngest person" << " is: " << array[i] << " at age " << i << endl;
		}
	}
}
