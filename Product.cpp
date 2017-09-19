// this class keep record of the products we have and its specs...

#include<iostream>
#include<cstring>
#include"Streamable.h"
#include"Product.h"
using namespace std;

namespace sict
{
	
	// default constructor will initialize the objects value to its default value,
	Product::Product()  
	{
		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0;
		taxed_ = true;
		quantity_ = 0;
		qtyNeeded_ = 0;

	}
	// constructor with two parameters setting the value of name and sku, made because other one with default values was not working...
	Product::Product(const char* sku1, const char* name1)
	{
		sku(sku1);
		name(name1);
		price_ = 0;
		quantity_ = 0;
		qtyNeeded_ = 0;

		/*int len = strlen(sku);
		strncpy(sku_, sku, len);
		sku_[len] = '\0';*/
		
		/*int len1 = strlen(name);
		name_ = new char[len1+1];
		strncpy(name_,name,len1+1);
		name_[len1] = '\0';*/

	}

	// Constructor with 5 argument  
	Product::Product(const char* sku1,const char* name1, bool taxed1 = true, double price1 = 0 , int qtyNeeded1 = 0)
	{
		sku(sku1);
		name(name1);
		quantity(0);
		taxed(taxed1);
		price(price1);
		qtyNeeded(qtyNeeded1);

		// Other Way

		/*int len = strlen(sku);
		for (int i = 0; i < len; i++)
		{
			sku_[i] = sku[i];
		}*/
		
		/*int n = strlen(name);
		name_ = new char[n+1];
		strncpy(name_,name,n+1);
		name_[n] = '\0';*/
		
		/*quantity_ = 0;
		taxed_ = taxed;
		price_ = price;
		qtyNeeded_ = qtyNeeded;
		*/	
	
	}

	Product::Product(Product& p)
	{
		name_ = nullptr;
		*this = p;
	}

	// setters functions...

	// all these functions sets the values of specs of the products..

	void Product::sku(const char* sku)
	{
		for (int i = 0; i < MAX_SKU_LEN + 1; i++)
		{
			sku_[i] = sku[i];
		}
		sku_[MAX_SKU_LEN] = '\0';
	}
	
	void Product::price(double price)
	{
		price_ = price;
	}
	
	void Product::name(const char* name)
	{
		int n = strlen(name);
		name_ = new char[n+1];
		strncpy(name_, name, n+1);
		name_[n] = '\0';
	}
	
	void Product::taxed(bool taxed)
	{
		taxed_ = taxed;
	}
	
	void Product::quantity(int qty)
	{
		quantity_ = qty;
	}
	
	void Product::qtyNeeded(int qtyNeeded)
	{
		qtyNeeded_ = qtyNeeded;
	}

	// getters function

	// these functions returns the specs of the products...
	const char* Product::sku() const
	{
		return sku_;
	}
	
	double Product::price() const
	{
		return price_;
	}
	
	const char* Product::name() const
	{
		return name_;
	}
	
	bool Product::taxed() const
	{
		return taxed_;
	}
	
	int Product::quantity() const
	{
		return quantity_;
	}
	
	int Product::qtyNeeded() const
	{
		return qtyNeeded_;
	}

	double Product::cost() const
	{
		double cost = 0;
		if (taxed_ == true)
		{
			cost = price_ + (price_ * TAX);
		}
		else
			cost = price_;
		return cost;
	}

	bool Product::isEmpty() const                 // it tells if thier is any product in the inventory or not
	{
		if (sku_[0] == '\0' && name_ == nullptr && price_ == 0 && taxed_ == true && quantity_ == 0 && qtyNeeded_ == 0)
			return true;
		else
			return false;
	}

	// assignment operator
	Product& Product::operator=(Product& p)
	{
		if (this != &p)     // checking if the two objects are not same
		{
			delete[] name_; 
			name_ = nullptr;   // assigning a safe empty state...
	
			sku(p.sku_);
			name(p.name_);
			
			// other Way

			/*int len = strlen(p.sku_);
			for (int i = 0; i < len; i++)
			{
				sku_[i] = p.sku_[i];
			}
			sku_[len] = '\0';*/
			
			/*int len1 = strlen(p.name_);
			name_ = new char[len1+1];
			strncpy(name_,p.name_,len1+1);
			name_[len1] = '\0';*/

			price(p.price_);
			taxed(p.taxed_);
			quantity(p.quantity_);
			qtyNeeded(p.qtyNeeded_);
		}
			return *this;
	}
	//copy Constructor
	Product::Product(Product& p)
	{
		*this = p;                   // calling assignment operator inside the constructor..
	}

	// overloading == operator
	bool Product::operator==(const char* sku)
	{
		bool n = true;
		if (sku != nullptr)
		{
			if (strcmp(sku, sku_) == 0)  // checking if the to sku's are same or not...
			{
				n = true;
			}
			else
				n = false;
		}
		return n;
	}

	// overloading += opeartor
	int Product::operator+=(int qty)
	{
		int sum;
		sum = quantity_ + qty;
		quantity_ = sum;       // adding quantity to product...
		return sum;
	}

	// overloading -= operator
	int Product::operator-=(int qty)
	{
		int sub;
		if (quantity_ > qty)
		{
			sub = quantity_ - qty;
		}
		else
		{
			sub = 0;
		}
		quantity_ = sub;
		return sub;
	}

	// destructor
	Product::~Product()
	{
	//	name_ = nullptr;  
		delete[] name_;     // releasing memory
	}
	
	// overloading non member += operator
	double operator+=(double &n, const Product& p)
	{
		n = n + (p.cost() * p.quantity()); // adding more quantity to product...
		return n;
	}

	//overloading >> operator
	std::istream& operator >> (std::istream& istr, Product& p)
	{
		p.read(istr);
		return istr;
	}

	//overloading << operator
	std::ostream& operator << (std::ostream& ostr, const Product& p)
	{
		bool n = true;
		p.write(ostr,n);
		return ostr;
	}
}
