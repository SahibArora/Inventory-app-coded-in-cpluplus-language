
#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include<iostream>
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
using namespace std;
namespace sict
{
	
	class Date
	{
	private:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;
		int value() const;
		void errCode(int errorCode);
		
	public:
		Date();
		Date(int C_year, int C_month, int C_day);

		bool operator == (const Date& D)const;
		bool operator != (const Date& D)const;
		bool operator < (const Date& D)const;
		bool operator > (const Date& D)const;
		bool operator <= (const Date& D)const;
		bool operator >= (const Date& D)const;
		
		int mdays() const;
		bool bad() const;
		int errCode()const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
	};
	std::istream& operator>>(std::istream& istr, Date& D);
	std::ostream& operator<<(std::ostream& ostr, Date& D);
}

#endif
