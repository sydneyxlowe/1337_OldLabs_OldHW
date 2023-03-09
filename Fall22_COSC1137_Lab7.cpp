//Sydney Lowe 2181244
//COSC 1137 Lab 7

#include <iostream>
#include <fstream>
using namespace std;

//Function prototypes
void displaySorted(string**, int);
string* findName(string*, string, int);
int whatRank(string**, string*, int);
void selectATeam(string**);

int main()
{
	//variable declarations
	string fileName, name;
	int rows, place, choice;
	string* names = nullptr;
	string** rankPtr;

	//User input of file name + number of rows in file
	cout << "Please enter the name of your file: ";
	cin >> fileName;
	cout << "Please enter the number of students in the file: ";
	cin >> rows;
	cout << endl;

	//Dynamic allocation of 1D array of strings and 2D array of pointers to strings
	names = new string[rows];
	rankPtr = new string * [rows+1];

	//Reading of file into arrays
	ifstream infile(fileName);
	for (int i = 0; i < rows; i++)
	{
		infile >> names[i] >> place;
		rankPtr[place] = &names[i];
	}
	
	//Menu loop
	do
	{
		//Option outputs
		cout << "1. Display the list of students sorted by their rankings." << endl;
		cout << "2. Inquiry about a student." << endl;
		cout << "3. Select a team." << endl;
		cout << "4. Exit" << endl;
		cout << "Please enter your choice: ";
		cin >> choice;
		cout << endl;

		//Choice 1
		if (choice == 1)
		{
			displaySorted(rankPtr, rows);
		}

		//Choice 2
		else if (choice == 2)
		{
			string* foundName = nullptr; //new pointer to string
			cout << "Please enter the name of the student: ";
			cin >> name;
			foundName = findName(names, name, rows); //pointer assigned to returned pointer from function

			//Check if name existed in list
			if (foundName == nullptr)
			{
				cout << name << " was not on list of applicants." << endl << endl;
			}

			//Conditional outputs if name was found
			else
			{
				cout << name << "'s ranking is: " << whatRank(rankPtr, foundName, rows) << endl;
				if (foundName == &names[rows-1]) //If the name entered was the last name on the list
				{
					cout << "There is no one ahead of " << name << " on the list." << endl;
					cout << "The person behind " << name << " on the list is " << *(foundName - 1) << endl;
				}
			
				else if (foundName == &names[0]) //If the name entered was the first name on the list
				{
					cout << "The person ahead of " << name << " on the list is " << *(foundName + 1) << endl;
					cout << "There is no one behind " << name << " on the list." << endl;
				}

				else //If name entered was in the middle of the list
				{
					cout << "The person ahead of " << name << " on the list is " << *(foundName + 1) << endl;
					cout << "The person behind " << name << " on the list is " << *(foundName - 1) << endl;
				}

				cout << endl;
			}
		}

		//Choice 3
		else if (choice == 3)
		{
			selectATeam(rankPtr);
		}
		
		//Exception choice
		else
		{
			choice = 4;
		}

	} while (choice != 4);

	//Deletion and nullifying of dynamic memory
	delete[] rankPtr;
	delete[] names;
	names = nullptr;
	rankPtr = nullptr;

	return 0;
}

//Function to display the sorted dynamic 2D array of pointers
void displaySorted(string** ptr, int size)
{
	for (int i = 1; i < size + 1; i++)
		cout << i << ": " << * ptr[i] << endl;
	cout << endl;
}

//Finds + returns the address of the name that was input using array of names
string* findName(string* ptr, string name, int size)
{
	string* nameSpot = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (name == ptr[i])
		{
			nameSpot = &ptr[i];
		}
	}

	return nameSpot;
}

//Receives address of name and returns the rank that address has in 2D array of pointers
int whatRank(string** arrayptr, string* namesptr, int size)
{
	int rank = 0;

	for (int i = 1; i < size + 1; i++)
	{
		if (arrayptr[i] == namesptr)
		{
			rank = i;
		}
	}

	return rank;
}

//Create a team function
void selectATeam(string** names)
{
	int students, rank, highest = 10, lowest = 1;
	
	//User input amount of students wanted
	cout << "Enter the amount of students needed for your team: ";
	cin >> students;
	string* newTeam = new string[students];
	
	//Loop to allocate new array + determine highest and lowest ranks
	for (int i = 0; i < students; i++)
	{
		cout << "Enter a ranking: ";
		cin >> rank;
		newTeam[i] = *names[rank];

		if (rank < highest)
		{
			highest = rank;
		}

		if (rank > lowest)
		{
			lowest = rank;
		}
	}
	cout << endl;

	//Output of info
	cout << "The members of your team are: " << endl;
	for (int i = 0; i < students; i++)
		cout << newTeam[i] << " ";
	cout << endl;
	cout << "The highest ranking member of your team is " << *names[highest] << " with a rank of: " << highest << endl;
	cout << "The lowest ranking member of your team is " << *names[lowest] << " with a rank of: " << lowest << endl << endl;

	//Delete and nullify dynamic memory
	delete[] newTeam;
	newTeam = nullptr;
}

