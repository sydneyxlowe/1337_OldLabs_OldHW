//Sydney Lowe 2181244
//COSC 1137 Lab 9

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

//enum type initilizations
enum Snacks { CHIPS = 0, PRETZELS = 1, NUTS = 2 };
enum Drinks {COKE = 3, SPRITE = 4, WATER = 5};

//structure declarations
struct drinkRecord
{
	Drinks dType;
	int dCount;
};

struct snackRecord
{
	Snacks sType;
	int sCount;
};

//function prototypes
void displayDVector(vector <drinkRecord>);
void displaySVector(vector <snackRecord>);
string toDrink(Drinks);
string toSnack(Snacks);
string toDrinkorSnack(int);
void bestSellers(int[]);
void runResults(vector <drinkRecord>, vector <snackRecord>, int[], vector <double>, double[]);

//Main
int main()
{
	//variable declarations
	double prices[6];
	int code, tranNum, amount, count = 0;
	double priceX, linePrice = 0;
	int tally[6];
	snackRecord snackX;
	drinkRecord drinkX;
	vector <drinkRecord> drinksVec;
	vector <snackRecord> snacksVec;
	vector <double> transactionCharges;

	//Open pricelist text, assign each price to the index corresponding to the enum value
	ifstream infile("priceList.txt"); 
	for (int i = 0; i < 6; i++)
	{
		infile >> code >> priceX;
		prices[code] = priceX;
		tally[i] = 0;
	}
	
	//Open and assign transaction file
	ifstream infileII("transactions.txt");
	while (infileII >> tranNum)
	{
		//transactionCharges.push_back(linePrice); //for each transaction, create space in transactionCharges vector
		
		for (int i = 0; i < tranNum; i++) //loop for each item in the transaction
		{
			infileII >> amount >> code;

			//if the item is a snack .... couldv'e done a switch statement
			if (code <= 2) 
			{
				//assign values to snack structure
				snackX.sType = Snacks(code);
				snackX.sCount = amount;

				//add structure to vector
				snacksVec.push_back(snackX);

				//add the cost of the items bought to charges vector
				transactionCharges.push_back(prices[code] * amount);

				//add the amount of items bought to tally array
				tally[code] += amount;
			}

			//if item is a drink, same process
			else
			{
				drinkX.dType = Drinks(code);
				drinkX.dCount = amount;

				drinksVec.push_back(drinkX);

				transactionCharges.push_back(prices[code]*amount);

				tally[code] += amount;
			}
		}
		//count++; //keep track of each transaction
	}

	//call of runResults function
	runResults(drinksVec, snacksVec, tally, transactionCharges, prices);

	return 0;
}


//function to display the drink records vector
void displayDVector(vector <drinkRecord> dVec)
{
	for (drinkRecord drink : dVec)
	{
		cout << toDrink(drink.dType) << "\t" << drink.dCount << endl;
	}
	cout << endl;
}

//function to display the snack records vector
void displaySVector(vector <snackRecord> sVec)
{
	for (snackRecord snack : sVec)
	{
		cout << toSnack(snack.sType) << setw(5) << "\t" << snack.sCount << endl;
	}
	cout << endl;
}

//convert a drinks enum to a string
string toDrink(Drinks enumD)
{
	string theDrink;
	switch (enumD)
	{
		case COKE:
			theDrink = "COKE";
			break;
		case SPRITE:
			theDrink = "SPRITE";
			break;
		case WATER:
			theDrink = "WATER";
			break;
	}

	return theDrink;
}

//convert a snack enum to a string
string toSnack(Snacks enumS)
{
	string theSnack;
	switch (enumS)
	{
		case CHIPS:
			theSnack = "CHIPS";
			break;
		case PRETZELS:
			theSnack = "PRETZELS";
			break;
		case NUTS:
			theSnack = "NUTS";
			break;
	}

	return theSnack;
}

//convert either a drinks or snacks enum to a string
string toDrinkorSnack(int num)
{
	string theItem;

	if (num <= 2)
	{
		theItem = toSnack(static_cast<Snacks>(num));
	}

	else if (num > 2)
	{
		theItem = toDrink(static_cast<Drinks>(num));
	}

	return theItem;
}

//compute and display most bought drink and snack
void bestSellers(int list[])
{
	int bestS = 0, bestD = 0, snackI, drinkI;

	//loop to find best selling items
	for (int i = 0; i < 6; i++)
	{
		//snack
		if (i <= 2 && list[i] > bestS)
		{
			bestS = list[i];
			snackI = i;
		}

		//drink
		else if (i > 2 && list[i] > bestD)
		{
			bestD = list[i];
			drinkI = i;
		}
	}

	//display best sellers
	cout << "The most popular item in the Snack category is: " << toDrinkorSnack(static_cast<Snacks>(snackI)) << endl;
	cout << "The most popular item in the Drink category is: " << toDrinkorSnack(static_cast<Drinks>(drinkI)) << endl;
}

//function to display all the results
void runResults(vector <drinkRecord> drinkV, vector <snackRecord> snackV, int list[], vector <double> tranChar, double prices[])
{
	//Drinks and snacks records
	cout << "Drinks Record: " << endl;
	displayDVector(drinkV);
	cout << "Snacks Record: " << endl;
	displaySVector(snackV);

	//List of prices
	cout << "The list of prices: " << endl;
	cout << fixed << showpoint << setprecision(2);
	for (int i = 0; i < 6; i++)
	{
		cout << toDrinkorSnack(i) << setw(5) << "\t" << prices[i] << endl;
	}
	cout << endl;

	//Cost per transaction
	cout << "Cost associated with each transaction in file: " << endl;
	for (double charge : tranChar)
	{
		cout  << charge << endl;
	}
	cout << endl;

	//Tally of each item sold
	cout << "The tally results: " << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "Total " << toDrinkorSnack(i) << " sold is: " << setw(5) << "\t" << list[i] << endl;
	}
	cout << endl;

	//Best selling drink and snack
	bestSellers(list);
}