#include <iostream>
#include <fstream>
#include <sstream>
#include "clothing.h"


Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand)
 : Product("clothing", name, price, qty), size_(size), brand_(brand)
{

}

Clothing::~Clothing() 
{
	
}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> keywordSet;
	std::set<std::string> nameSet = parseStringToWords(name_);
	std::set<std::string> brandSet = parseStringToWords(brand_);

	// Add name of clothing
	keywordSet = setUnion(keywordSet, nameSet);
	// Add brand name
	keywordSet = setUnion(keywordSet, brandSet);

	return keywordSet;
}

std::string Clothing::displayString() const
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

	info = info + "\n" + "Size: " + size_ + " " + "Brand: " 
		   + brand_ + "\n" + strPrice + " " + strQty + " left.";

	return info;
}

void Clothing::dump(std::ostream& os) const
{
	os << "clothing" << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << size_ << std::endl;
	os << brand_ << std::endl;
}

std::string Clothing::getSize() const
{
	return size_;
}

std::string Clothing::getBrand() const
{
	return brand_;
}



