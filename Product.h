// this class keep record of the products we have and its specs...

#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__

#include"Streamable.h"
#include"general.h"
namespace sict
{
	class Product : public Streamable
	{
	private:
		char sku_[MAX_SKU_LEN+1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
	public:
		// constructors
		Product();
		Product(const char* sku, const char* name);
		Product(const char* sku, const char* name,bool taxed,double price, int qtyNeeded);
		Product(Product& p);
		// setters
		void sku(const char* sku);
		void price(double price);
		void name(const char* name);
		void taxed(bool taxed);
		void quantity(int qty);
		void qtyNeeded(int qtyNeeded);

		// getters
		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost()const;
		bool isEmpty()const;

		// operators
		Product& operator=(Product& p);
		bool operator==(const char* sku);
		int operator+=(int qty);
		int operator-=(int qty);

		// prototypes of read and write function
		//std::istream& read(std::istream& istr);
		//std::ostream& write(std::ostream& ostr);

		// destructors
		virtual ~Product();
	};

	// Non-member operators
	double operator+=(double &n, const Product& p);
	std::istream& operator>>(std::istream& istr,Product& p);
	std::ostream& operator<<(std::ostream& ostr,const Product& p);
}
#endif
