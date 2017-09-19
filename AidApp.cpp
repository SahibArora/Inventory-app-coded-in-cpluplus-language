// this class provides you different options to enter a product into the inventory, write it into the file, 
// search a product and many more... 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AidApp.h"
#include "AmaPerishable.h"
#include "Product.h"
using namespace std;
namespace sict
{
	AidApp::AidApp(const char* filename)                 // one argument constructor giving a filename and assigning a safe empty state to its every member...
	{
		strncpy(filename_, filename, 256);
		filename_[255] = '\0';
		for (int i = 0; i < MAX_NO_RECS; i++)
		{
			product_[i] = nullptr;
		}
		noOfProducts_ = 0;
		loadRecs();
	}

	void AidApp::pause()const                            // pauses the execution, until enter is hitted...
	{
		char c;
		cout << "Press Enter to continue..." << endl;
		do
		{
			cin.get(c);

		}while(c!='\n');

	}

	int AidApp::menu()                         // gives u the list of actions you can perform...
	{
		int n;
		
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> n;
        
		if (n >= 0 || n < 6)
		{
			return n;
		}
		else
		{
			return -1;
		}
		
	}

	void AidApp::loadRecs()                               // Loads data into the file
	{
		int index = 0;
		char file;

		datafile_.open(filename_, std::ios::in);         // opening the file...

		if (datafile_.fail())                            // checking if cursor is not at EOF
		{
			datafile_.close();
		}
		else
		{
			while (datafile_.good())                // loop continues till it does not reach EOF.
			{
				delete[] product_[index];         // deleting all the memory at index -> index... ( as product_ is a **pointer so it contains pointers at its index which can have their own memroy through memory alloctaion)
				product_[index] = nullptr;    
				datafile_ >> file;				 // reading whether file is perishable or not...	
				if (datafile_.good())
				{
					if (file == 'P')
					{
						product_[index] = new AmaPerishable();         // pointing that object inside product_ array to amaperishable class...
					}
					else if (file == 'N')
					{
						product_[index] = new AmaProduct();           // pointing that object inside product_ array to amaproduct class...
					}
					if (file == 'P' || file == 'N')
					{         
						datafile_.ignore();
						product_[index]->load(datafile_);              // loading every data into file...
						index++;
					}
				}
			}
		}
		noOfProducts_ = index;
		datafile_.close();
	}
	void AidApp::saveRecs()                                        // saving all the data into file...
	{
		datafile_.open(filename_, std::ios::out);                     

		for (int i = 0; i < noOfProducts_; i++)
		{
			product_[i]->store(datafile_);              // calling store function to store data in file..
		}
		datafile_.close();

	}
	void AidApp::listProducts()const                 
	{
		double total = 0;
		cout << endl;
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

		for (int i = 0; i < noOfProducts_; i++)
		{
			cout.fill(' ');
			cout.setf(ios::right, ios::adjustfield);
			cout.width(4);
			//cout << setfill(' ') << setw(4) << right << i + 1 << " | ";  // other way could be this to set the display of row number...
			cout << i + 1 << " | ";
			product_[i]->write(cout, true);                 // calling write function in both the classes accordingly...
			//cout << *product_[i] << endl;
			cout << endl;
			total += *product_[i];                         // calculating total (*product_[i] uses += operator to calculate the price), here *product[i] has the address of the one of the objects of the product class...  
			
			if (i == 10)
			{
				pause();
			}


		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << fixed << setprecision(2)  << total;
	}
	int AidApp::SearchProducts(const char* sku)const                    // searches the sku inside all the objects of products in the array of product_
	{
		int index = -1;
		for (int i = 0; i < noOfProducts_; i++)
		{
			if (*product_[i] == sku)                               // uses == opertor defined in the product class...
			{
				index = i;
			}
		}
		return index;
	}


	void AidApp::addQty(const char* sku)                    // checks the sku through above seacrh. fucntion and adds the quantity after checking the restrictions...
	{
		int found = SearchProducts(sku);
		int qty1;
		if (found == -1)
		{
			cout << "Not found!" << endl;
		}
		else
		{
			cout << "Please enter the number of purchased items: ";
			cin >> qty1;
			if (cin.fail())
			{
				cout << "Invalid quantity value!" << endl;
			}
			else
			{
				int qtyNeeded = product_[found]->qtyNeeded();
				int qty = product_[found]->quantity();
				int needed = (qtyNeeded - qty);
				if (qty1 <= needed)
				{
					product_[found]->operator+=(qty1);               // calling the overloaded += operator in product
					cin.ignore(1000, '\n');
				}
				else
				{
					cout << "Too many items; only " << needed << " is needed, please return the extra " << qty1 - needed << " items." << endl;
				}
				cout << endl << "Updated!" << endl << endl;
			}
		}
		cin.clear();
	}

	void AidApp::addProduct(bool isPerishable)                    // adds another Product into the file and product_ array
	{
		if (isPerishable== true)
		{
			product_[noOfProducts_] = new AmaPerishable();
			product_[noOfProducts_]->read(cin);
			noOfProducts_++;
		}
		else
		{
			product_[noOfProducts_] = new AmaProduct();
			product_[noOfProducts_]->read(cin);
			noOfProducts_++;
		}
		saveRecs();
		cout << endl << "Product added" << endl << endl;
	}

	int AidApp::run()// execute the menu ui
	{
		char sku[MAX_SKU_LEN];
		int option;
		int found;
		do {
			option = menu();
			switch (option)
			{
			case 1:
				listProducts();
				cout << endl;
				cout << endl;
				cin.clear();
				pause();
				cout << endl;
				break;

			case 2:
				cout << endl << "Please enter the SKU: ";
				cin >> sku;
				cout << endl;
				found = SearchProducts(sku);
				if (found != -1)
				{
					product_[found]->write(cout, false);
				}
				else
				{
					cout << "Not found!" << endl;
				}
				cout << endl;
				cout << endl;
				pause();
				cout << endl;
				break;

			case 3:
				cout << endl;
				addProduct(false);
				break;

			case 4:
				cout << endl;
				addProduct(true);
				break;

			case 5:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> sku;
				cout << endl;
				found = SearchProducts(sku);
				if (found != -1)
				{
					product_[found]->write(cout, false);
				}
				else
				{
					cout << "Not found!" << endl;
				}
				cout << endl;
				cout << endl;
				addQty(sku);
				break;
			case 0:
				break;
			default:
				cout << "===Invalid Selection, try again.==="<<endl;;
				pause();
				break;
			}
		} while (option != 0);
		
		cout << endl << "Goodbye!!" << endl;

		return 0;
	}
}
