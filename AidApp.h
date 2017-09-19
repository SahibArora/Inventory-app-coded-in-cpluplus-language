// this class provides you different options to enter a product into the inventory, write it into the file, 
// search a product and many more... 

#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include"Product.h"
#include"AmaPerishable.h"
#include"general.h"
namespace sict
{
	class AidApp
	{
	private:
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		std::fstream datafile_;
		int noOfProducts_;
		void pause() const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts() const;
		int SearchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);

	public:
		AidApp(const char* filename);
		AidApp(AidApp& app) = delete;
		AidApp& operator=(const AidApp& a) = delete;
		int run();
	};
}
#endif
