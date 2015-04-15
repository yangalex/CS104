#ifndef MYSTORE_H
#define MYSTORE_H
#include "datastore.h"
#include "util.h"
#include <map>

class MyStore : public DataStore {
	public:
		MyStore();
		~MyStore();
		void addProduct(Product* p);
		void addUser(User* u);
		void addReview(Review* r);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		int addToCart(std::string username, Product* p);
		void removeFromCart(std::string userName, int itemIndex);
		int viewCart(std::string username);
		int buyCart(std::string username);
		const std::map<std::string, User*> getUsers();
		const std::vector<Product*> getCart(std::string userName);
	private:
		std::map<User*, std::vector<Product*>*> carts;
		std::map<std::string, User*> users;
		std::vector<Product*> products;
		std::map<std::string, std::set<Product*>*> keywords;
		std::vector<Review*> reviewList; // for easier dumping

};
#endif