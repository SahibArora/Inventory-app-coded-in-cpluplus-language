// this class writes the product of inventory into the file and read at the same time..
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include <iomanip>
#include"AmaProduct.h"
#include"general.h"
using namespace std;
namespace sict
{
	AmaProduct::AmaProduct(const char filetag)        // a parameterized constructor (having the filename in the parameter)
	{
		if (filetag != '\0')
		fileTag_ = filetag;
	}
	
	const char* AmaProduct::unit()const       // returns the unit of the product measured in..
	{
		return unit_;
	}
	
	void AmaProduct::unit(const char* value)     // copies the passed value into the unit of the product
	{  
		if (value != nullptr)
		{
			strncpy(unit_, value, 11);
			unit_[11] = '\0';
		}
	}

	fstream& AmaProduct::store(fstream& file, bool addNewLine)const     // writes data into the file..
	{
		if(addNewLine)
			file << fileTag_ << coma << sku() << coma << name() << coma << price() << coma << taxed() << coma << quantity() << coma << unit() << coma << qtyNeeded() << '\n';
		else
			file << fileTag_ << coma << sku() << coma << name() << coma << price() << coma << taxed() << coma << quantity() << coma << unit() << coma << qtyNeeded() ;
		return file;
	}

	fstream& AmaProduct::load(fstream& file)   // loads the data from the file..
	{
		char sku1[MAX_SKU_LEN + 1];
		char name1[20];
		double price1;
		bool taxed1;
		int quantity1;
		char unit1[11];
		int qtyNeeded1;
		file.getline(sku1, 120, ',');                  // reads sku of the product..
		file.getline(name1, 120, ',');                 // reads name1 of the product..
		file >> price1;									// reads price of the product..
		file.ignore();				// ignores the next one character
		file >> taxed1;								// reads taxed variable(if taxed or not) of the product..
		file.ignore();
		file >> quantity1;                    // reads quantity of the product..
		file.ignore();
		file.getline(unit1,11,',');              // reads the unit of the product..
		file >> qtyNeeded1;               // reads the qtyNeeded for the product...
		file.ignore();

		// coping all the extracted data from file to Product inventory...

		sku(sku1);
		name(name1);
		price(price1);
		taxed(taxed1);
		quantity(quantity1);
		unit(unit1);
		qtyNeeded(qtyNeeded1);
		
		return file;
	}

	ostream& AmaProduct::write(ostream& os, bool linear)const        // Prints the data onto the screen...
	{
		if (!err_.isClear())
		{
			os << err_;
		}
		if (err_.isClear())
		{
			if (linear)
			{
				os.width(MAX_SKU_LEN);
				os.setf(ios::left, ios::adjustfield);
				os << sku() << '|';
				os.width(20);
				os.setf(ios::left, ios::adjustfield);
				os << name() << '|';
				os.width(7);
				os.setf(ios::right, ios::adjustfield);
				os.setf(ios::fixed);
				os.precision(2);
				os << cost() << '|';
				os.width(4);
				os.setf(ios::right, ios::adjustfield);
				os << quantity() << '|';
				os.width(10);
				os.setf(ios::left, ios::adjustfield);
				os << unit() << '|';
				os.width(4);
				os.setf(ios::right, ios::adjustfield);
				os << qtyNeeded() << '|';
			}
			else
			{
				os << "Sku: " << sku() << endl;
				os << "Name: " << name() << endl;
				os << "Price: " ;
				os.setf(ios::fixed);
				os.precision(2);
			        os << price() << endl;
				if (taxed())
					os << "Price after tax: " << cost() << endl;
				else
					os << "Price after tax: " << "N/A" << endl;
				os << "Quantity On Hand: ";
				os.precision(2);
				os << quantity() << " " << unit() << endl;
				os << "Quantity Needed: " << qtyNeeded();
			}
		}
		return os;
	}

	istream& AmaProduct::read(istream& istr)       // prompts reader to enter the input..
	{
		char sku1[MAX_SKU_LEN + 1];
		char name1[20];
		char unit1[34];
		double price1;
		char taxed1;
		int quantity1;
		int qtyNeeded1;
		
		err_.clear(); // will clear prevoius stored message 
		if (!istr.fail())
		{
			cout << "Sku: ";
			istr >> sku1;
			//cout << endl;
			sku(sku1);
			cin.ignore();
			cout << "Name: ";
			istr.getline(name1,256);
			//cout << endl;
			name(name1);
			cout << "Unit: ";
			istr.getline(unit1,11);
			/*if (unit1[0] == '\n')
			{
				unit1[0] = '\0';
			}*/
			//cout << endl;
			unit(unit1);
			// Taxed istr fail

			cout << "Taxed? (y/n): ";
			istr >> taxed1;
			if (taxed1 == 'y' || taxed1 == 'Y' || taxed1 == 'n' || taxed1 == 'N')
			{
				if (taxed1 == 'y' || taxed1 == 'Y')
					taxed(true);
				else
					taxed(false);
				//cout << endl;
			}
			else
			{
				err_.clear();
				err_.message("Only (Y)es or (N)o are acceptable");
				istr.setstate(ios::failbit);
			}
			
			// this is after taxed fail
			if (!istr.fail())
			{
				cout << "Price: ";
				istr >> price1;
				//cout << endl;
				price(price1);
				if (istr.fail())
				{
					err_.message("Invalid Price Entry");
					istr.setstate(ios::failbit);
				}

				if (!istr.fail())
				{
					cout << "Quantity On hand: ";
					istr >> quantity1;
					//cout << endl;
					quantity(quantity1);
					if (istr.fail())
					{
						err_.message("Invalid Quantity Entry");
						istr.setstate(ios::failbit);
					}

					if (!istr.fail())
					{
						cout << "Quantity Needed: ";
						istr >> qtyNeeded1;
						//cout << endl;
						qtyNeeded(qtyNeeded1);
						if (istr.fail())
						{
							err_.message("Invalid Quantity Needed Entry");
							istr.setstate(ios::failbit);
						}
					}
				}
			}
		}
		return istr;
	}
	
}
