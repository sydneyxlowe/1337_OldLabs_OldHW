//Sydney Lowe
// COSC1137 - Lab4
// Fall 2022
// Complete this program based on the instructions

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int binarySearch(int[], int, int);
bool isSubSet(vector <int>, vector <int>);

// Fully define the following functions after main and use them where instructed
void displayVector(vector <int>);

ofstream outfile;  // Declared globally so that binary search function
                   // can have access to it for writing data to the log file

int main()
{
    int number;
    const int SIZE = 33;
    int searchArray[SIZE];
    vector <int> iterations;
    vector <int> values;
    vector <int> nonListedVec;
    vector <int> maxIterVec;


    outfile.open("Lab4_LogFile.txt");  


    // Fill array with text file values
    ifstream infile("Lab4_input.txt");

    for (int i = 0; i < SIZE; i++)
    {
        infile >> searchArray[i];
    }

    // Generate random values and use binary search function to find number in array.
    for (int i = 0; i < 51; i++)
    {
        number = rand() % 100 + 1;
        if (binarySearch(searchArray, SIZE, number) == -1) // Puts value in nonListed vector if number is not found in array.
        {
            nonListedVec.push_back(number);
        }
        
    }

    outfile.close();

    // Find max and min iteration values
    ifstream inlog("Lab4_LogFile.txt");
    int i, j;
    int max = 0;
    int min = 1;

    while (inlog >> i && inlog >> j)
    {
        if (j < min)
        {
            min = j;
        }

        if (j > max)
        {
            max = j;
        }

    }

    inlog.close();

    // Fill vector of values with max iterations
    ifstream inlogI("Lab4_LogFile.txt");
    
    while (inlogI >> i && inlogI >> j)
    {
        if (j == max)
        {
            maxIterVec.push_back(i);
        }
    }
  
    //Displays
    cout << min << "-" << max << endl;
    displayVector(nonListedVec);
    displayVector(maxIterVec);
    isSubSet(maxIterVec, nonListedVec);
    cout << "The number of iterations cannot be a determining factor in whether the item is listed or not." << endl;

    return 0;
}


// Binary search function, modified
int binarySearch(int array[], int size, int value)
{
    int first = 0,              // First array element
        last = size - 1,        // Last array element
        middle,                 // Mid point of search
        iterations = 0,         // iteration counter
        position = -1;          // Position of search value

    bool found = false;         // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2;    // Calculate mid point
        if (array[middle] == value)    // If value is found at mid
        {
            found = true;
            position = middle;
            iterations++;
            outfile << value << " " << iterations << endl;
        }

        else if (array[middle] > value && first != last) // If value is in lower half
        {
            last = middle - 1;
            iterations++;
        }

        else if (array[middle] < value && first != last) // If value is in upper half
        {
            first = middle + 1;         
            iterations++;
        }

        else if (array[middle] != value && first == last) // If value is not found
        {
            found = true;
            iterations++;
            outfile << value << " " << iterations << endl;
        }

    }

    return position;
}

// Display vector function
void displayVector(vector <int> vec)
{
    for (int val : vec)
        cout << val << " ";

    cout << endl;
}

// Check if max iteration values vector is a subset of unfound values vector
bool isSubSet(vector <int> maxV, vector <int> unlistV)
{
    bool result = false;
    int count = 0;

    for (int num : unlistV)
    {
        for (int numM : maxV)
        {
            if (numM == num)
                count++;
                break;
        }
    }

    if (count == maxV.size())
    {
        result = true;
        cout << "The values of max iterations were a subset of the unfound values." << endl;
    }

    else
    {
        result = false;
        cout << "The values of max iterations were NOT a subset of the unfound values." << endl;
    }

    return result;
}