//Sydney Lowe 2181244
//COSC 1137 Lab 10
//Class Implementation file

#include "NumArray.h"

NumArray::NumArray(int size) //Constructor allocates memory for an array of given size
{
	list = new float[size];
}

NumArray::~NumArray() //Destructor frees memory created
{
	delete[] list;
	list = nullptr;
}

//Sets an element of the array to given value
void NumArray::setNum(float num, int index)
{
	list[index] = num;
}

//Returns the contents of an array element
float NumArray::getNum(int index)
{
	return list[index];
}

//Finds and returns the max number in array
float NumArray::getMax(int size)
{
	float max = list[0];
	for (int i = 1; i < size; i++)
	{
		if (list[i] > max)
		{
			max = list[i];
		}
	}

	return max;
}

//Finds and returns the min number in array
float NumArray::getMin(int size)
{
	float min = list[0];
	for (int i = 1; i < size; i++)
	{
		if (list[i] < min)
		{
			min = list[i];
		}
	}

	return min;
}

//Calculates the average of the numbers in the array
float NumArray::getAvg(int size)
{
	float average, total = 0;
	for (int i = 0; i < size; i++)
	{
		total += list[i];
	}
	average = total / size;

	return average;
}