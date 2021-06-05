// IMPLEMENTATION FILE
#include "PokeMart.h" // for header file
#include <iostream>
#include <string> // for string methods
#include <fstream> // for file input output stuff
#include <iomanip> // for setw func and precision
#include <vector> // for creating a vector (a nicer data structure compared to an array)
#include <cctype> // for character data type methods
using namespace std;

// constructor
PokeMart::PokeMart() //: item_count(0) // member initialization list can go here optionally
{
	head_ptr = nullptr; // set head ptr to nullptr in the function
	// OR use member initalization list (after header, do a : and write headptr(nullptr)
	Unload_Truck(); // call this method to load all pokeitems from the poketruck into the pokemart (the BAG in this case) 
	storeInVector(); // call this method to load all the pokeitems into the vector
}


// this method pushes the pokeitem data from the filled linked list bag into a vector created by yours truly
void PokeMart::storeInVector()
{
	PokeItem*tempPtr = head_ptr;
	
	while(tempPtr != nullptr)
	{
		pricesvector.push_back(tempPtr->get_item_cost());
		tempPtr = tempPtr->get_next_item();
	}
	
}

/* This method compares the incoming customers balance to the stores item costs to see if they have enough to keep buying
 returns true if they have enough money, or false if they are broke */
bool PokeMart::checkCustomerBalance(const int &balance)
{
	bool hasEnoughMoney = false;
	
	for(int x = 0; x < pricesvector.size(); x++) // loop through the vector of prices
	{
		if(balance >= pricesvector[x]) // check if the customers balance is >= to the prices of any of the items
		{
			cout << "You have enough to buy something!" << endl; 
			hasEnoughMoney = true; // customer has enough money to buy something so end this loop
			break; // break out of the loop
		}
	}
	
	return hasEnoughMoney;
}


// this method reads data from a file into the bag (linked list based)
void PokeMart::Unload_Truck()
{
	// ifstream reads data from file
	// ofstream writes data from file
	ifstream ifile("pokeitems.txt");
	string iname;
	int icost;
	int inumber;// DECLARE ITEM NUMBER VAR HERE
	
	if(!ifile)
	{
		cout << "File not found! Error!" << endl;
	}
	else
	{
		PokeItem *temp;
		while(ifile)
		{ 	
			ifile >> inumber;
			ifile.ignore();
			getline(ifile, iname);
			ifile >> icost;
			ifile.ignore();

		
			if(head_ptr == nullptr) // head pointer is pointing to nullptr (nothing)
			{
				head_ptr = new PokeItem(); // assign address of new node to the head ptr
				head_ptr->set_item_number(inumber); // set all the info for the FIRST node
				head_ptr->set_item_name(iname);
				head_ptr->set_item_cost(icost);	
			}
			else // linked list already has at least one node, so add the new node to the end of linked list
			{
				PokeItem *curPtr = head_ptr;
				while(curPtr->get_next_item() != nullptr) // traverse until you reach the last node (its next ptr should be nullptr)
				{
					curPtr = curPtr->get_next_item(); // move forward in the linked list
				}
				
				PokeItem *newNode = new PokeItem(); // create the new node in memory
				newNode->set_item_number(inumber); // set all the info for the CURRENT node (it wont be first, it'll be the second node or the third node or so on)
				newNode->set_item_name(iname);
				newNode->set_item_cost(icost);	
				curPtr->set_next_item(newNode); // after creating the new node and setting its info, then set it as the last node in the linked list
				newNode = nullptr;  // set the temporary pointer to nullptr bc you arent using it anymore after this
				curPtr = nullptr;
			}	
		}
		
		temp = nullptr; // set the pointer to nullptr as you arent using it anymore after this point
		
		ifile.close(); // close the file
	}
	
}


//display all the items in a menu format
// its a const method because its not modifying any data members
void PokeMart::Display_All_Items() const
{
	PokeItem *curPtr = head_ptr; //curptr is used to navigate through the linked list to display each nodes contents
	
	while(curPtr != nullptr) // go through the entire linked list until your pointer reaches nullptr
	{
		cout << "\t\t" << curPtr->get_item_number() << ". " << curPtr->get_item_name() << "\t" << "$" << curPtr->get_item_cost() << endl;
		curPtr = curPtr->get_next_item();
	}
	
	
}

// remove (sell) an item from the shop inventory
// returns a pointer to a pokeitem object 
PokeItem *PokeMart::sellItem(const int & customerMoney) const
{
	int itemChoice; // var that holds the item choice that the user picked
	PokeItem *ptrToPokeItem = nullptr; // a pointer to a PokeItem object
	string customerChoice;  // var that holds users choice if they are ok with their current item picked 
	char customerChoiceLetter; // var that holds the letter (Y or N)
	int quantity; // var that holds the amount of the item the customer wants to buy (2 potions, 10 hyper potions, etc)
	
	do
	{
		cout << "\n\nWhich item would you like to buy? "; cin >> itemChoice; // get the item number (listed in the menu)
	
		// implement a search function that searches the entire link list for the item choice using the item  provided by customer
		ptrToPokeItem = searchForItem(itemChoice);  // should return a pointer to the node that contains the item the customer wants
		
		while(ptrToPokeItem == nullptr) // data validation for pokeitem pointer contents
		{
			cout << "Your item couldn't be found!" << endl;
			cout << "Try a different item : "; cin >> itemChoice;
			ptrToPokeItem = searchForItem(itemChoice);  // should return a pointer to the node that contains the item the customer wants
		}
				
		// ask customer how many of that item they want
		cout << "How many " << ptrToPokeItem->get_item_name() << "(s) would you like? " << endl;
		cin >> quantity;
		ptrToPokeItem->set_item_quantity(quantity);
		
		while(quantity <= 0) // keep asking for a quantity until customer enters a valid quantity
		{
			cout << "Please enter a valid quantity!\nHow many " << ptrToPokeItem->get_item_name() << "(s) would you like? " << endl;
			cin >> quantity;
			ptrToPokeItem->set_item_quantity(quantity);
		}
		
			
		while(ptrToPokeItem->get_item_cost() > customerMoney || (quantity * ptrToPokeItem->get_item_cost()) > customerMoney) // Items cost is more than the customers balance so they have to pick another item
		{
			cout << "You do not have sufficient funds for that item. Please pick another item!" << endl;
			cout << "\nWhich item would you like to buy? ";
			cin >> itemChoice;
			ptrToPokeItem = searchForItem(itemChoice);  // should return a pointer to the node that contains the item the customer wants
			
			while(ptrToPokeItem == nullptr) // data validation for pokeitem pointer contents
			{
				cout << "Your item couldn't be found!" << endl;
				cout << "Try a different item : "; cin >> itemChoice;
				ptrToPokeItem = searchForItem(itemChoice);  // should return a pointer to the node that contains the item the customer wants
			}
			
			// ask customer how many of that item they want
			cout << "How many " << ptrToPokeItem->get_item_name() << "(s) would you like? "; cin >> quantity;
			ptrToPokeItem->set_item_quantity(quantity);

			while(quantity <= 0) // keep asking for a quantity until customer enters a valid quantity
			{
				cout << "Please enter a valid quantity!\nHow many " << ptrToPokeItem->get_item_name() << "(s) would you like? " << endl;
				cin >> quantity;
				ptrToPokeItem->set_item_quantity(quantity);
			}
		}
		
		cin.ignore(); // clear input stream 
		
		if(quantity > 1) // quantity is greater than 1
		{
			// customer finally picked a set of an item that they can afford so display the name below
			cout << "\nYou want " << ptrToPokeItem->get_item_quantity() << " " << ptrToPokeItem->get_item_name() << "s.\nThat will be $" << ptrToPokeItem->get_item_cost() * quantity << ". Is that ok? "; // lets the customer know they bought the item successfully
			getline(cin, customerChoice);
		}
		else // quantity must be 1
		{
			// customer finally picked an item that they can afford so display the name below
			cout << "\nYou want " << ptrToPokeItem->get_item_quantity() << " " << ptrToPokeItem->get_item_name() << ".\nThat will be $" << ptrToPokeItem->get_item_cost() << ". Is that ok? "; // lets the customer know they bought the item successfully
			getline(cin, customerChoice);
		}
		
		customerChoiceLetter = toupper(customerChoice[0]); // convert the first character of the string to uppercase and store it in the var
		if(customerChoiceLetter == 'Y') // user decided to complete their purchase!
		{
			cout << "Here you go.  Thank you." << endl;
			break;
		}

		
	}while(customerChoiceLetter != 'Y'); // keep looping until the customer finally says YES to a purchase of an item
	

	return ptrToPokeItem; // RETURN THE ADDRESS IN THE POINTER
} 


// should return a pointer to the node that contains the item the customer wants
PokeItem * PokeMart::searchForItem(const int &itemNum) const
{
	PokeItem *ptrToNode = head_ptr; // pointer starts at the beginning of linked list
	bool foundItem = false;
	
	
	while((!foundItem) && ptrToNode != nullptr)  // go through the entire linked list until your pointer reaches nullptr or foundItem becomes true
	{
		if(itemNum == ptrToNode->get_item_number()) // check if the current node has the matching item number
		{
			foundItem = true;
		}
		else // current node doesnt have matching item number 
		{
			ptrToNode = ptrToNode->get_next_item(); // move to the next node in the linked list
		}
	}

	
	
	return ptrToNode; // return the pointer that points to the correct pokeitem!
}  



// goes through the entire link list and deletes each pokeitem node
void PokeMart::clearList()
{
	PokeItem*prevPtr;

	while(head_ptr != nullptr)
	{	
		prevPtr = head_ptr;
		head_ptr = head_ptr->get_next_item();
		delete prevPtr;
		prevPtr = nullptr;
	}
}


// destructor
PokeMart::~PokeMart()
{
	clearList();
}
