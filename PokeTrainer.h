// HEADER (SPECIFICATION FILE)
#ifndef POKETRAINER_H // guards
#define POKETRAINER_H
#include "PokeItem.h"
#include "Customer.h"
#include <iostream>
#include <string>
using namespace std;

class PokeTrainer : public Customer // poketrainer INHERITS from parent class Customer with PUBLIC access specification
{
	private:
		int pokedollars;
		PokeItem *trainer_head_ptr;
		int item_count;
	protected:
	public:
		PokeTrainer();
		void addItem( PokeItem *);// write a method that takes an object that the user bought, adds it to the linked list bag, and also updates item count and pokedollar amount
		void setDollarAmount(const int &);
		void setName(const string &);
		void setAllInfo();
		string getName() const;
		int getDollarAmount() const;
		void showMyItems(); // displays all the items in the list
		~PokeTrainer();
		void clearList(); // clear the linked list
};

#endif


