// this is same as AmaProduct class but keeps tracks of the perishable Product's expiry Date...

#include<iostream>
#include<fstream>
#include"AmaPerishable.h"
#include"Date.h"

namespace sict 
{
	AmaPerishable::AmaPerishable(const char p):AmaProduct(p)          //default Constructor
	{}

	const Date& AmaPerishable::expiry()const                 // Returns the expiry date of the product..
	{
		return expiry_;
	}

	void AmaPerishable::expiry(const Date &value)                 // sets the expiry date of the product..
	{
		expiry_ = value;
	}

	fstream& AmaPerishable::store(fstream& file, bool addNewLine)const     // enters expiry_date into the file with data...
	{
		AmaProduct::store(file, false);             // calling store function of the AmaProduct...
		if (addNewLine)
		{
			file << coma;
			//file << expiry_;
			expiry_.write(file);
			file << '\n';
		}
		else
		{
			file << coma;
			//file << expiry_;
			expiry_.write(file);
		}
		return file;
	}

	fstream& AmaPerishable::load(fstream& file)        //  reads the data from the file with expiry Date..
	{
		Date D;
		AmaProduct::load(file);            // calling load function of AmaProduct to reads the rest data...
		file >> D;
		//D.read(file);
		file.ignore();
		expiry(D);
		return file;
	}

	ostream& AmaPerishable::write(ostream& ostr, bool linear)const      // prints the data on the screen..
	{
		AmaProduct::write(ostr, linear);
		if (err_.isClear() && !isEmpty())
		{
			if (linear)
				expiry().write(ostr);
			else
			{
				ostr << '\n' << "Expiry date: ";
				expiry().write(ostr);
			}
		}
		return ostr;
	}

	istream& AmaPerishable::read(istream& istr)         // prompts user to enter data of the product...
	{
		Date D1;
		AmaProduct::read(istr);
		if (err_.isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";
			istr >> D1;
			if (D1.bad()) {
				if (D1.errCode() == CIN_FAILED) {
					err_.message("Invalid Date Entry");
					istr.setstate(ios::failbit);
				}
				else if (D1.errCode() == YEAR_ERROR) {
					err_.message("Invalid Year in Date Entry");
					istr.setstate(ios::failbit);
				}
				else if (D1.errCode() == MON_ERROR) {
					err_.message("Invalid Month in Date Entry");
					istr.setstate(ios::failbit);
				}
				else if (D1.errCode() == DAY_ERROR) {
					err_.message("Invalid Day in Date Entry");
					istr.setstate(ios::failbit);
				}
			}
			expiry(D1);
		}
		return istr;
	}
}
