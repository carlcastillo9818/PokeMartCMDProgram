#include <iostream>
#include <string>
#include "PokeMart.h"
#include "PokeTrainer.h"
#include <cctype>
#include <windows.h> // for background music
#include <MMSystem.h> // for bg music
#pragma comment(lib, "Winmm.lib") // for bg music
using namespace std;

void PokeMart_Menu(PokeMart &, PokeTrainer &); 

int main()
{
	PokeMart pewterCity; // pokemart object
	PokeTrainer trainer1; // trainer object
	
	// create playsound object to play my music in the background in an endless loop!
	// in case another person downloads this on their computer, make sure that they have downloaded the wav file too so the music actually plays
	PlaySound("C:\\C++Projects\\PokeMart Program Linked List\\PokeMartCMDProgram\\pokemart.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	PokeMart_Menu(pewterCity,trainer1); // call the menu function!
	return 0;
}


/* this method greets the trainer, displays a menu of the stores items and
prompts them to buy something or leave */
void PokeMart_Menu(PokeMart &store, PokeTrainer &customer)
{
	char userChoice; // var that represents the customers choice to buy an item or quit the program
	char nextChoiceLetter; // var that stores customers choice whether they want to CONTINUE buying an item or leave the shop
	string nextChoice;
	bool customerBuying = true; // boolean flag var to check if the customer is buying items
	bool hasEnoughMoney; // boolean flag var to check if the customer has enough money to buy stuff
	PokeItem* itemForCustomer = nullptr; // this is the item that was sold by the store to the customer

	cout << "\nHello " << customer.getName() << "! Your Current Balance is $"<< customer.getDollarAmount() <<  "\nPlease select an option below." << endl;
	cout << "\t1. Buy items at the Pokemart\n\t2. Check your bag\n\t3. Close menu\nSelect your choice : "; cin >> userChoice;

	do
	{
		switch(userChoice) // switch is like the ( if elif else) statements
		{
			case '1':
				hasEnoughMoney = store.checkCustomerBalance(customer.getDollarAmount());
				
				if(hasEnoughMoney) // the customer has enough money to buy something so let them see the menu
				{
					system("cls"); // clear screen
					cout << "\t\tITEM NAME\tITEM COST" << endl;
					store.Display_All_Items(); // call the method to display all the stores items for sale
					cin.ignore(); // clear input stream of enter key presses
					itemForCustomer = store.sellItem(customer.getDollarAmount());   // store the customers item that was sold by the store for a certain amount of money
					customer.addItem(itemForCustomer);  // call method to add item to the customers BAG
				}
				else // the customer doesnt have enough to buy anything so give an error message and tell them to come back when they have enough money
				{
					cout << "You do not have enough money to buy anything!\nCome back when you have more money!" << endl;
					customerBuying = false;
					exit(0);  // end the program now
				}
				break; // close the case block
			case '2':
				customer.showMyItems(); // call method to display the items in the customers bag currently	
				cin.ignore();
				break;
			case '3':
				cout << "Okay, have a nice day!" << endl;
				exit(0); // end the program now
				break; // close the case block
			default:
				cout << "That is not a valid choice! Goodbye!" << endl;
				exit(0);  // end the program now
				break; // close the case block
		}; // end of switch
		
		cout << "\nIs there something else you\'d like to do? (Y/N) : "; getline(cin,nextChoice); // ask user if they want to continue shopping
		nextChoiceLetter = toupper(nextChoice[0]); // convert first letter to uppercase and store it in this var
		if(nextChoiceLetter != 'Y') 
		{
			system("cls"); // clear screen
			// user is finished shopping so tell them have a nice day and break out of the loop
			cout << "Before you go, here are all the items in your bag that you purchased today!" << endl;
			customer.showMyItems();
			cout << "\nOkay " << customer.getName() << " have a nice day!" << endl;
			exit(0); // end the program now
		}
		system("cls"); // clears the screen from text
		cout << "Your Current Balance is $"<< customer.getDollarAmount() << "\n\t1. Buy items at the Pokemart\n\t2. Check your bag\n\t3. Close menu\nSelect your choice " << customer.getName() << " : "; cin >> userChoice;

	}while(customerBuying); 
} // end of pokemart menu function
