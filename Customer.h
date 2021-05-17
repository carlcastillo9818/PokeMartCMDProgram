// HEADER (SPECIFICATION FILE)

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
using namespace std;

class Customer // the parent class (the child class will be the poketrainer class later)
{
	protected: // allows data members to be accessed by CHILD CLASS
		string name;
	public:
		Customer(); // constructor (called when the child class object is created)
		~Customer();
		
};
#endif
