#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <vector>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  void swap(int lhs, int rhs);
  void heapify(int loc);
  std::vector<T> heapArray;
  Comparator comp;
  int m_;

};

// Add implementation of member functions here
template<typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c) :
  comp(c), m_(m)
{
}


template<typename T, typename Comparator>
Heap<T, Comparator>::~Heap()
{

}


template<typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item)
{
  heapArray.push_back(item);

  // TrickleUp
  int loc = heapArray.size()-1;
  int parent = (loc-1)/m_;

  while(parent >= 0 && comp(heapArray[loc], heapArray[parent])) {
    swap(loc, parent);
    loc = parent;
    parent = (loc-1)/m_;
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heapArray[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  heapArray[0] = heapArray[heapArray.size()-1];
  heapArray.pop_back();

  // TrickleDown
  heapify(0);
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int loc)
{
  if(loc*m_ + 1 >= heapArray.size()) {
    return;
  }

  int smallestChild = loc*m_ + 1;
  for(int i=2; i <= m_; i++) {
    if(loc*m_+i < heapArray.size()){
      if(comp(heapArray[loc*m_+i], heapArray[smallestChild])) {
        smallestChild = loc*m_ + i;
      }
    }
  }

  if(comp(heapArray[smallestChild], heapArray[loc])) {
    swap(loc, smallestChild);
    heapify(smallestChild);
  }
}


template<typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const
{
  return heapArray.empty();
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::swap(int lhs, int rhs)
{
  T temp = heapArray[lhs];
  heapArray[lhs] = heapArray[rhs];
  heapArray[rhs] = temp;
}



#endif

