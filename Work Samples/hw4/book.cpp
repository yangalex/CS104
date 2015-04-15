#include <iostream>
#include <fstream>
#include <sstream>
#include "book.h"

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author)
 : Product("book", name, price, qty), isbn_(isbn), author_(author) 
 {

 }

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> keywordSet;
	std::set<std::string> nameSet = parseStringToWords(name_);
	std::set<std::string> authorSet = parseStringToWords(author_);
	// Add title of book to set
	keywordSet = setUnion(keywordSet, nameSet);
	// Add author name to set
	keywordSet = setUnion(keywordSet, authorSet);
	// Add ISBN to set
	keywordSet.insert(isbn_);

	return keywordSet;
}

std::string Book::displayString() const
{
	std::string info = name_;
	std::string strPrice;
	std::string strQty;

	// convert price and qty to strings
	std::stringstream ss;
	ss << price_;
	ss >> strPrice;
	ss.clear();
	ss.str("");
	ss << qty_;
	ss >> strQty;

	info = info + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_
			+ "\n" + strPrice + " " + strQty + " left.";

	return info;
}

void Book::dump(std::ostream& os) const
{
	os << "book" << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << isbn_ << std::endl;
	os << author_ << std::endl;
}

std::string Book::getIsbn() const
{
	return isbn_;
}

std::string Book::getAuthor() const
{
	return author_;
}