// this is same as AmaProduct class but keeps tracks of the perishable Product's expiry Date...

#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include"AmaProduct.h"
namespace sict
{
	class AmaPerishable: public AmaProduct
	{
	private:
		Date expiry_;
	public:
		AmaPerishable(const char p='N');
		const Date& expiry()const;  // returns reference to expiry_
		void expiry(const Date& value); // sets the expiry_ to coming value
		fstream& store(fstream& file, bool addNewLine = true)const;
		fstream& load(fstream& file);
		ostream& write(ostream& ostr, bool linear)const;
		istream& read(istream& istr);
	};
}
#endif
