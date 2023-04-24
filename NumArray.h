//Sydney Lowe 2181244
//COSC 1137 Lab 10
//Class Header file

#ifndef NUMARRAY_H
#define NUMARRAY_H

class NumArray
{
private://attributes
	float* list;
public: //member functions
	NumArray(int);
	~NumArray();
	void setNum(float, int);
	float getNum(int);
	float getMax(int);
	float getMin(int);
	float getAvg(int);
};
#endif