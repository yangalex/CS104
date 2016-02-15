#include "mystore.h"
#include <iostream>

MyStore::MyStore() : DataStore(), users(6, std::string("zzzzzzzzzzzzzzzzzzzzzz"))
{

}

MyStore::~MyStore()
{

	// deallocate sets in keywords
	SplayTree<std::string, std::set<Product*>*>::iterator keyIt;
	for(keyIt = keywords.begin(); keyIt != keywords.end(); ++keyIt) {
		delete keyIt->second;	
	}
	
	// deallocate vectors in carts
	std::map<User*, std::vector<Product*>*>::iterator cartIt;
	for(cartIt = carts.begin(); cartIt != carts.end(); ++cartIt) {
		delete cartIt->second;
	}
	
	// deallocate users
	SkipList<std::string, User*>::iterator userIt;
	for(userIt = users.begin(); userIt != users.end(); ++userIt) {
		delete userIt->second;
	}

	// deallocate products
	for(unsigned int i=0; i < products.size(); i++) {
		delete products[i];
	}
	
	// deallocate reviews
	for(unsigned int i=0; i < reviewList.size(); i++) {
		delete reviewList[i];
	}

}

void MyStore::addProduct(Product* p)
{
	products.push_back(p);

	// Operations to add product's keywords to map
	std::set<std::string> productKeywords = p->keywords();
	std::set<std::string>::iterator it;

	// iterate through set and check to see if keyword is already in map of keywords
	// if not, then add it with the corresponding product pointer
	for(it = productKeywords.begin(); it != productKeywords.end(); ++it) {
		// Keyword is already mapped
		if(keywords.find(*it) != keywords.end()) {
			SplayTree<std::string, std::set<Product*>*>::iterator splayIt = keywords.find(*it);
			splayIt->second->insert(p);
		}
		// Keyword is not yet mapped
		else {
			keywords.insert(std::make_pair(*it, new std::set<Product*>));
			SplayTree<std::string, std::set<Product*>*>::iterator splayIt = keywords.find(*it);
			splayIt->second->insert(p);
		}
	}
}

void MyStore::addUser(User* u)
{
	// Add user to users map
	std::pair <std::string, User*> tempPair = std::make_pair(u->getName(), u);
	users.insert(tempPair);

	// Add user to carts map and accompanying vector (as pointer) to represent a cart
	std::vector<Product*>* newCart = new std::vector<Product*>;
	carts.insert(std::make_pair(u, newCart));
}

std::vector<Product*> MyStore::search(std::vector<std::string>& terms, int type)
{
	// initialize vector of hits
	std::vector<Product*> hits;

	// iterator for set of products
	std::set<Product*>::iterator it;

	// intialize set to hold intersections and unions
	std::set<Product*> tempSet;

	// have to create a loop until we find a term that exists in keyword bank to use
	// as initial value to our set
	bool foundFirstSet = false;
	unsigned int termsCount = 0;
	while(foundFirstSet == false) {
		if(termsCount >= terms.size()) {
			return hits;
		}

		if(keywords.find(terms[termsCount]) != keywords.end()) {
			SplayTree<std::string, std::set<Product*>*>::iterator splayIt = keywords.find(terms[termsCount]);	
			tempSet = *(splayIt->second);
			foundFirstSet = true;
		}
		else {
			termsCount++;
		}
	}

	// iterate through list of terms
	for(unsigned int i=termsCount+1; i < terms.size(); i++) {
		// first check to see if term is a valid keyword 
		if(keywords.find(terms[i]) != keywords.end()) {
			SplayTree<std::string, std::set<Product*>*>::iterator it = keywords.find(terms[i]);		
			// if type 0 (AND) check to see if product is found on all keywords
			if(type == 0) {
				tempSet = setIntersection(tempSet, *(it->second));
			} 
			// if type 1 (OR) check to see if product is found in any of the keywrods
			else if(type == 1) {
				tempSet = setUnion(tempSet, *(it->second));
			}
		}
	}

	// convert set to vector form
	for(it = tempSet.begin(); it != tempSet.end(); ++it) {
		hits.push_back(*it);
	}


	return hits;

}


void MyStore::addReview(Review* r)
{
	std::string productName = r->prodName;
	Product* tempProduct;

	// find product
	for(unsigned int i=0; i < products.size(); i++) {
		if(products[i]->getName() == r->prodName) {
			tempProduct = products[i];
		}
	}

	// Add to username's product review list
	//users[r->username]->addProductReviewed(tempProduct);

	reviewList.push_back(r);
	tempProduct->reviews.push_back(r);
}


void MyStore::dump(std::ostream& ofile)
{
	// dump products
	ofile << "<products>" << std::endl;
	for(unsigned int i=0; i < products.size(); i++) {
		products[i]->dump(ofile);
	}
	ofile << "</products>" << std::endl;

	// dump users
	ofile << "<users>" << std::endl;
	SkipList<std::string, User*>::iterator it;
	for(it = users.begin(); it != users.end(); ++it) {
		it->second->dump(ofile);
	}
	ofile << "</users>" << std::endl;

	// dump reviews
	ofile << "<reviews>" << std::endl;
	for(unsigned int i=0; i < reviewList.size(); i++) {
		ofile << reviewList[i]->prodName << std::endl;
		ofile << reviewList[i]->rating << " " << reviewList[i]->date << " " << reviewList[i]->reviewText << std::endl;
	}
	ofile << "</reviews>" << std::endl;
}

int MyStore::addToCart(std::string username, Product* p)
{
	if(users.find(username) != users.end()) {
		User* u = users[username];
		carts[u]->push_back(p);
		return 0;
	}
	else {
		return 1; // username does not exist
	}



}

void MyStore::removeFromCart(std::string userName, int itemIndex)
{
	User* tempUser = users[userName];
	carts[tempUser]->erase(carts[tempUser]->begin()+itemIndex);
	std::vector<Product*> tempCart = *(carts[tempUser]);
}

int MyStore::viewCart(std::string username)
{
	if(users.find(username) != users.end()) {
		User* u = users[username];

		std::vector<Product*> tempCart = *(carts[u]);
		for(unsigned int i=0; i < tempCart.size(); i++) {
			std::cout << "Item " << i+1 << std::endl;
			std::cout << tempCart[i]->displayString();
			std::cout << std::endl;
			std::cout << std::endl;
		}

		return 0;
	}
	else {
		return 1; // username does not exist
	}

}

int MyStore::buyCart(std::string username)
{
	if(users.find(username) != users.end()) {
		User* u = users[username];

		
		std::vector<Product*> tempCart = *(carts[u]);

		unsigned int head = 0;
		while(head != tempCart.size()) {
			if(tempCart[head]->getQty() != 0 && u->getBalance()-tempCart[head]->getPrice() >=0) {
				carts[u]->erase(carts[u]->begin()+head);
				tempCart[head]->subtractQty(1);
				u->deductAmount(tempCart[head]->getPrice());
				tempCart.erase(tempCart.begin()+head);
			}
			else {
				head++;
			}
		}

		return 0;
	}
	else {
		return 1;
	}

}

const SkipList<std::string, User*> MyStore::getUsers() {
	return users;
}

const std::vector<Product*> MyStore::getCart(std::string userName) 
{
	User* selectedUser = users[userName];
	return *(carts[selectedUser]);
}
