#include <fstream>
#include <sstream>
#include "movie.h"

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating)
 : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
	std::set<std::string> keywordSet;
	std::set<std::string> nameSet = parseStringToWords(name_);
	std::set<std::string> genreSet = parseStringToWords(genre_);

	// Add name of movie
	keywordSet = setUnion(keywordSet, nameSet);
	// Add genre to set
	keywordSet = setUnion(keywordSet, genreSet);

	return keywordSet;
}

std::string Movie::displayString() const
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

	info = info + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_
			+ "\n" + strPrice + " " + strQty + " left.";

	return info;
}

void Movie::dump(std::ostream& os) const
{
	os << "movie" << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << genre_ << std::endl;
	os << rating_ << std::endl;
}

std::string Movie::getGenre() const
{
	return genre_;
}

std::string Movie::getRating() const
{
	return rating_;
}
