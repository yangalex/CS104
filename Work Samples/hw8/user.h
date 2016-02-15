#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "review.h"
#include <set>
#include "product.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, int password);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  std::string getName() const;
  int getPassword() const;
  void deductAmount(double amt);
  virtual void dump(std::ostream& os);
  void addProductReviewed(Product* newProductReviewed);
  std::set<Product*> getProductsReviewed() const;

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  int password_;
  std::set<Product*> productsReviewed;
};
#endif
