#include "datastore.h"
#include "util.h"
#include <map>

class MyStore : public DataStore {
	public:
		MyStore();
		~MyStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		int addToCart(std::string username, Product* p);
		int viewCart(std::string username);
		int buyCart(std::string username);
	private:
		std::map<User*, std::vector<Product*>*> carts;
		std::map<std::string, User*> users;
		std::vector<Product*> products;
		std::map<std::string, std::set<Product*>*> keywords;

};