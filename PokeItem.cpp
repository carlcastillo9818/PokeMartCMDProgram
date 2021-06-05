// IMPLEMENTATION FILE

#include "PokeItem.h"
#include <iostream>
#include <string>
using namespace std;


// constructor
PokeItem::PokeItem()
{
	item_name = "default";
	item_cost = 0;
	quantity = 0;
	next = nullptr;
}


// destructor
PokeItem::~PokeItem()
{
}

// set the name of the item
void PokeItem::set_item_name(const string &name)
{
	// use the this pointer if parameter has same name as data member
	item_name = name;
}

// set the cost of the item
void PokeItem::set_item_cost(const int &cost)
{
	item_cost = cost;
}

// set the number of the item (for use in a list)
void PokeItem::set_item_number(const int &num)
{
	item_number = num;
}

// set the next pointer
void PokeItem::set_next_item(PokeItem*nextitem)
{
	next = nextitem;
}

// set the item quantity
void PokeItem::set_item_quantity(const int &q)
{
	quantity = q;
}

// get the next pointer
PokeItem* PokeItem::get_next_item() const
{
	return next;
}

// get the item number
int PokeItem::get_item_number() const
{
	return item_number;
}

// get the item name
string PokeItem::get_item_name() const
{
	return item_name;
}

// get the item cost
int PokeItem::get_item_cost() const
{
	return item_cost;
}

// get the item quantity
int PokeItem::get_item_quantity() const
{
	return quantity;
}




