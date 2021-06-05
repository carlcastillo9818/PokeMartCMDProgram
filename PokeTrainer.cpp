// IMPLEMENTATION FILE
#include "PokeTrainer.h"
#include <iostream>
#include <string>
using namespace std;


// constructor
PokeTrainer::PokeTrainer()
{
	trainer_head_ptr = nullptr; // set head pointer to nullptrptr initially
	item_count = 0; // set initial item count to 0
	setAllInfo();// call the set method to set the trainers name and their amount of money
}


/* this method recieves a pointer to the PokeItem object that the user bought, 
adds it to the front of the linked list (front of the trainers bag), and 
also updates item count and pokedollar amount. */
void PokeTrainer::addItem(PokeItem *customerItem)
{
	PokeItem * myNewNode = new PokeItem(); // dynamic allocate new object in memory
	myNewNode->set_item_name(customerItem->get_item_name()); // set item name
	myNewNode->set_item_cost(customerItem->get_item_cost()); // set item cost
	myNewNode->set_item_quantity(customerItem->get_item_quantity()); // set item quantity
	myNewNode->set_next_item(trainer_head_ptr); // give address of headptr to new node
	trainer_head_ptr = myNewNode; // make head pointer point to the new node (new pokeitem added recently)

	if(myNewNode->get_item_quantity() > 1) // check if the quantity is greater than 1
	{
		// reduce amount by the num of items multiplied by the base cost
		pokedollars = (pokedollars - (myNewNode->get_item_quantity() * myNewNode->get_item_cost()));
	}
	else // quantity is only 1 so just reduce amount by the items base cost
	{
		pokedollars = (pokedollars - myNewNode->get_item_cost()); // reduce the pokedollars amount after trainer buys an item
	}
		
	item_count++; // increase item count of the customer

	myNewNode = nullptr; // this pointer wont be used anymore so set it to nullptrptr (dont delete it bc then youre deleting the data it points to
}

// goes through the entire linked list and deletes each pokeitem node
void PokeTrainer::clearList()
{
	
	PokeItem*prevPtr;
	while(trainer_head_ptr != nullptr)
	{
		prevPtr = trainer_head_ptr; // follow the current ptr with the prevptr
		trainer_head_ptr = trainer_head_ptr->get_next_item(); // move to next node
		delete prevPtr; // deallocate memory
		prevPtr = nullptr; // set the pointer to nullptrptr afterwards
	}
}


// goes through the entire link list and displays each pokeitem node
void PokeTrainer::showMyItems()
{
	PokeItem *traversalPtr; 
	traversalPtr = trainer_head_ptr;
		
	if(item_count != 0)// only display items list if your item count is > 0
	{
		cout << "\nHere are all the items in your bag : " << endl; // show the user the items they bought today (if any)

		while(traversalPtr!= nullptr) // loop through the linked list until the pointer hits nullptrptr
		{
			cout << traversalPtr->get_item_name() << " x" << traversalPtr->get_item_quantity() << endl;
			traversalPtr = traversalPtr->get_next_item();
		}
	}
	else
	{
		cout << "You have no items in your bag!" << endl;
	}

	
	/* alternate way of doing it (kinda weird but it should work)
	for(int x = 0; x< item_count;x++)
	{
		cout << traversalPtr->get_item_name() << endl;
		traversalPtr = traversalPtr->get_next_item();
	}	
	*/
}

	
// function that calls all the setter funcs 
// parent setter func (my name for it)
void PokeTrainer::setAllInfo()
{
	string temp_name;
	int dollars;
	
	
	cout << "Enter your name here : ";
	getline(cin, temp_name);
	
	cout << "How much money do you have from your adventures : ";
	cin >> dollars;
	
	setName(temp_name);
	setDollarAmount(dollars);
}

// set the trainers name
void PokeTrainer::setName(const string &n)
{
	name = n;	
}

// set the trainers money amount
void PokeTrainer::setDollarAmount(const int &d)
{
	pokedollars = d;
}

// return the trainers name
string PokeTrainer::getName() const
{
	return name;
}

// return the trainers amount of money
int PokeTrainer::getDollarAmount() const
{
	return pokedollars;
}

// destructor
PokeTrainer::~PokeTrainer()
{
	if(trainer_head_ptr != nullptr) // if there are ANY nodes in the linked list, call the clear list func
		clearList();
	// otherwise assume the head pointer is nullptrptr which means the linked list is empty
} 
