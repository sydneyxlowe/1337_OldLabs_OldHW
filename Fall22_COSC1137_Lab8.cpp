//Sydney Lowe 2181244
//COSC 1137 Lab 8

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

//Structure declaration
struct applicant
{
	string name;
	string major;
	double GPA;
	string projectID;
};

int main()
{
	//variables
	applicant appList[50];
	ifstream infile("Fall22_1137_Lab8.txt");
	int numOfApplicants = 0, choice;
	string givID, givMajor;
	double minGPA;
	vector <applicant> membersVec;
	vector <applicant> finalCutVec;

	//Populate the application array using the file + keep count of applicants
	for (int i = 0; i < 50; i++)
	{
		if (infile >> appList[i].name)
		{
			infile >> appList[i].major >> appList[i].GPA;
			numOfApplicants++;
		}
	}

	//Display user input menu
	cout << "Please enter your Project ID: ";
	cin >> givID;
	cout << "Please enter the major criteria: ";
	cin >> givMajor;
	cout << "Please enter the minimum GPA criteria: ";
	cin >> minGPA;

	//Populate member array based on criteria given
	for (int i = 0; i < numOfApplicants; i++)
	{
		if (appList[i].major == givMajor && appList[i].GPA >= minGPA)
		{
			membersVec.push_back(appList[i]);
		}
	}

	//Display members who meet criteria
	cout << endl << "The number of qualified applicants for your project is: " << membersVec.size() << endl;
	cout << "The list of the qualified applicants: " << endl;
	cout << fixed << showpoint << setprecision(2);
	for (int i = 0; i < membersVec.size(); i++)
	{
		cout << membersVec[i].name << "\t" << membersVec[i].major << "\t" << membersVec[i].GPA << endl;
	}
	
	//User choice for narrowing members
	cout << "\t1.\t" << "Accept ALL applicants listed" << endl;
	cout << "\t2.\t" << "Make further selections" << endl;
	cin >> choice;
	
	//Option 1: All accepted
	if (choice == 1)
	{
		//Display the members again
		cout << "Your members for project " << givID << ": " << endl;
		for (int i = 0; i < membersVec.size(); i++)
		{
			for (int j = 0; j < numOfApplicants; j++)
			{
				if (membersVec[i].name == appList[j].name) //Give members the project ID in the original applicant list
				{
					appList[j].projectID = givID;
					cout << membersVec[i].name << "\t" << membersVec[i].major << "\t" << membersVec[i].GPA << "\t" << appList[j].projectID << endl;
				}
			}
		}
		cout << endl;
	}

	//Option 2: Narrowing
	if (choice == 2)
	{
		//Display each member one by one
		for (int i = 0; i < membersVec.size(); i++)
		{
			int choiceII;
			cout << membersVec[i].name << "\t" << membersVec[i].major << "\t" << membersVec[i].GPA << endl;
			cout << "\t1.\t" << "Accept" << endl;
			cout << "\t2.\t" << "Reject" << endl;
			cin >> choiceII;

			//If accepted, add member to final cut vector
			if (choiceII == 1)
			{
				finalCutVec.push_back(membersVec[i]);
			}
		}
		cout << endl;

		//Display final cut vector
		cout << "Your members for project " << givID << ":" << endl;
		for (int i = 0; i < finalCutVec.size(); i++)
		{
			for (int j = 0; j < numOfApplicants; j++)
			{
				if (finalCutVec[i].name == appList[j].name)//Give members the project ID in the original applicant list
				{
					appList[j].projectID = givID;
					cout << finalCutVec[i].name << "\t" << finalCutVec[i].major << "\t" << finalCutVec[i].GPA << "\t" << appList[j].projectID << endl;

				}
			}	
		}
		cout << endl;
	}

	//Display the original list of applicants w the chosen members having the ID 
	cout << "The complete list of applicants:" << endl;
	for (int i = 0; i < numOfApplicants; i++)
	{
		cout << appList[i].name << "\t" << appList[i].major << "\t" << appList[i].GPA << "\t" << appList[i].projectID << endl;
	}
	return 0;
}