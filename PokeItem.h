// HEADER (SPECIFICATION FILE)

#ifndef POKEITEM_H // HEADER GUARDS
#define POKEITEM_H // PREVENT HEADER FILE FROM BEING INCLUDED MULTIPLE TIMES
#include <iostream>
#include <string>
using namespace std;

class PokeItem // node class
{
	private: // include data members here (variables)
		string item_name; // the name
		int item_cost; // the cost of the item
		PokeItem *next; // points to the next PokeItem node
		int item_number; // the number of the item that determines where it will go in an ordered list (link list, etc.)
		int quantity; // quantity of the current item
	public: // include setters,getters,constructor,destructor,etc.
		PokeItem();
		~PokeItem();
		void set_item_name(const string &); // const type & allows for pass by reference (modifications allowed)
		void set_item_cost(const int &);
		void set_item_number(const int &);
		void set_next_item(PokeItem*); // move to and set the next node (PokeItem)
		void set_item_quantity(const int &);
		string get_item_name() const; // const prevents modification
		int get_item_cost() const;
		int get_item_number() const;
		int get_item_quantity() const;
		PokeItem* get_next_item() const; // get the next node after the current one
};



#endif 
