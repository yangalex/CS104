#include "llistdbl.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
{
  // If list is empty
  if(empty()) {
    Item* newItem = new Item;
    newItem->val = val;
    newItem->next = NULL;
    newItem->prev = NULL;
    head_ = newItem;
    tail_ = newItem;
    size_++;
  }
  // If inserted anywhere except front or back
  else if(loc > 0 && loc < size_) {
    Item* temp = getNodeAt(loc);
    Item* newItem = new Item;
    newItem->val = val;
    newItem->next = temp; // Set newItem's next to temp's next
    newItem->prev = temp->prev;       // Set newItem's prev to temp
    temp->prev->next = newItem; // Set the item after temp's prev to newItem
    temp->prev = newItem;       // Set temp's next to newItem
    size_++;
  }
  // If inserted at head
  else if(loc == 0 && !empty()) {
    Item* newItem = new Item;
    newItem->val = val;
    newItem->prev = NULL;

    // Set head's prev to newItem
    head_->prev = newItem;
    // Set new Item's next as the current head
    newItem->next = head_;
    // Set newItem as the new head
    head_ = newItem;
    
    size_++;
  }
  // if inserted at tail
  else if(loc == size_) {
    Item* newItem = new Item;
    newItem->val = val;
    newItem->next = NULL;

    // Set tail's next to newItem
    tail_->next = newItem;
    // Set newItem's prev to tail
    newItem->prev = tail_;
    // Set newItem as the new tail
    tail_ = newItem;

    size_++;
  }

}

/**
 * Complete the following function
 */
void LListDbl::remove(int loc)
{
  // Check to see if list is empty
  if(empty()) {
    return;
  }

  // If removing head
  if(loc == 0) {
    // If only one item left
    if(size_ == 1) {
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else {
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = NULL;
      delete temp;
    }

    size_--;
  }

  // If removing item between head and tail
  else if(loc > 0 && loc < size_-1) {
    Item* temp = getNodeAt(loc);
    // Set its previous Item's next to its own next
    temp->prev->next = temp->next;
    // Set its next Item's prev to its own prev
    temp->next->prev = temp->prev;

    delete temp;
    size_--;
  }

  // If removing tail
  else if(loc == size_-1) {
    Item* temp = tail_;
    tail_ = tail_->prev;
    tail_->next = NULL;
    delete temp;
    size_--;
  }


}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
