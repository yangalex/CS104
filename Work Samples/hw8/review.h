#ifndef REVIEW_H
#define REVIEW_H
#include <string>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(), rating(), username(), date(), reviewText()
  { }
  Review(std::string& prod, 
	 int& rate, 
	 std::string& user_name,
	 std::string& d, 
	 std::string& review_text) :
    prodName(prod), 
    rating(rate), 
	username(user_name),
    date(d), 
    reviewText(review_text)
  { }
  
  std::string prodName;
  int rating;
  std::string username;
  std::string date;
  std::string reviewText;
};

#endif
