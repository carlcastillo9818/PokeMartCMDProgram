// HEADER (SPECIFICATION FILE)
#include "PokeItem.h"
#include "PokeTrainer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#ifndef POKEMART_H // header guards
#define POKEMART_H

class PokeMart // acts like a linked bag class
{
	private:
		PokeItem *head_ptr; // pointer to first node also called the head pointer
		void Unload_Truck(); // loads PokeItems from a FILE into the bag (the truck in this scenario)
		vector<int> pricesvector; // vector to hold items (useful for comparing customer balance to the costs of all the items)

	public:
		// constructors,destructors, link list operations, etc.
		PokeMart();
		void Display_All_Items() const;// write a method to display all the items
		~PokeMart();
		PokeItem *sellItem(const int &) const; // this method removes an item from shops inventory (customer bought it)
		PokeItem *searchForItem(const int &) const;  // should return a pointer to the node that contains the item the customer wants
		void clearList(); // goes through the entire link list and deletes each pokeitem node	
		bool checkCustomerBalance(const int &); // compares the customers balance to the stores item costs to see if they have enough to keep buying
		void storeInVector(); // this method pushes the pokeitem data from the filled linked list bag into a vector created by yours truly	
};

#endif
