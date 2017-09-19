// Date class handles the dates of the products and check if the user enters a valid date...

#include<iostream>
#include"Date.h"
#include"general.h"

using namespace std;

namespace sict
{
	Date::Date()                           //  default constructor (Initializing data members)
	{
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	Date::Date(int C_year,int C_month, int C_day) // constructor with three parameters which sets the values of day,month,year;
	{
		if (C_year != 0 && C_month != 0 && C_day != 0)
		{
			year_ = C_year;
			mon_ = C_month;
			day_ = C_day;
			readErrorCode_ = NO_ERROR;
		}
		else
		{
			year_ = 0;
			mon_ = 0;
			day_ = 0;
			readErrorCode_ = NO_ERROR;
		}
	}

	void Date::errCode(int errorCode)        // sets the value of readerrorcode_;
	{
		readErrorCode_ = errorCode;
	}
	
	bool Date::bad()const                      // checks if there is any error while reading date
	{
		if (readErrorCode_ != NO_ERROR)
			return true;
		else
			return false;
	}

	int Date::errCode()const                 // returns the error, if any 
	{
		return readErrorCode_;
	}

	int Date::value()const            // returns the largest value = latest date;
	{
		return year_ * 372 + mon_ * 31 + day_;
	}

	int Date::mdays()const	            // returns the number of days in that month; 
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}

	bool Date::operator==(const Date& D)const // compare the dates through value function which one is bigger and which one is smaller.
	{
		if (this->value() == D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator!=(const Date& D)const //same as above.
	{
		if (this->value() != D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator<(const Date& D)const // same as above
	{
		if (this->value() < D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator>(const Date& D)const // same as above
	{
		if (this->value() > D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator<=(const Date& D)const // same as above
	{
		if (this->value() <= D.value())
			return true;
		else
			return false;
	}
	
	bool Date::operator>=(const Date& D)const // same as above
	{
		if (this->value() >= D.value())
			return true;
		else
			return false;
	}

	std::istream& Date::read(std::istream& istr) // reads the code from input stream and than validate it through conditions.
	{
		istr >> year_;
		istr.ignore(5,'/');
		istr >> mon_;
		istr.ignore(3,'/');
		istr >> day_;
		if (istr.fail() == true)  // checks if the values in the output stream is successfully transfered to the values of the object. 
		{
			readErrorCode_ = CIN_FAILED;
		}
		else
		{
			if (year_ < MIN_YEAR || year_ > MAX_YEAR )
			{
				readErrorCode_ = YEAR_ERROR;
				return istr;
			}
			if (mon_ < 1 || mon_ > 12 )
			{
				readErrorCode_ = MON_ERROR;
				return istr;
			}
			if (day_ > mdays() || day_ < 0 )    // check the valid number of days for that month.
			{
				readErrorCode_ = DAY_ERROR;
				return istr;
			}
		}
		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr) const // displays the content which is inside the input stream and fill the empty state with zeros with setted width.
	{
		ostr.setf(ios::fixed);
		ostr.width(1);   //setting the width of output.
		ostr.fill('0');  // filling that empty place with zeros, which we set with the width. 
		ostr << year_ ;
		ostr << "/" ;
		ostr.width(2);
		ostr.fill('0');
		ostr<< mon_ ;
		ostr << "/" ;
		ostr.width(2);
		ostr.fill('0');
		ostr << day_ ;
		ostr.unsetf(ios::fixed);
		return ostr;
	}
	
	std::istream& operator>> (std::istream& istr, Date& D) // it will overload >> which will help us to call object through cout >> object. 
	{
		D.read(istr);
		return istr;
	}
	std::ostream& operator<< (std::ostream& ostr, Date& D) // it will overload << .
	{
		D.write(ostr);  // calling the write  function of the object. 
		return ostr;    // returing the values inside the output stream.
	}
}
