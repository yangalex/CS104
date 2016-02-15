
/**
 * splayTree.h
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }

  // Helper function to see if Node is a left child
  bool amILeftChild() {
  	if(getParent() == NULL) {
  		return false;
  	}

  	Node<KeyType, ValueType>* tempParent = getParent();
  	if(tempParent->getKey() > this->getKey()) {
  		return true;
  	}
  	else {
  		return false;
  	}
  }

  // Helper function to check if Node is a right child
  bool amIRightChild() {
  	if(getParent() == NULL) {
  		return false;
  	}

  	Node<KeyType, ValueType>* tempParent = getParent();
  	if(tempParent->getKey() < this->getKey()) {
  		return true;
  	}
  	else {
  		return false;
  	}

  }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
  Splay Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class SplayTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  SplayTree () { root = NULL; }

  /**
   * Destructor
   */
  ~SplayTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  // insert
  void insert (const std::pair<const KeyType, ValueType>& new_item) {

    // If tree is empty
    if(this->root == NULL) {
      // Add new item as root node
      Node<KeyType, ValueType>* rootNode = new Node<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      this->root = rootNode;
      return;
    }

    // Create variable to traverse the tree
    Node<KeyType, ValueType>* temp = (Node<KeyType, ValueType>*) this->root;
    // Create variable to hold newNode
    Node<KeyType, ValueType>* newNode;

    // Create bool to check if newNode has been correctly placed
    bool locationFound = false;

    while(!locationFound) {
      // new item's key is smaller than temp
      if(new_item.first < temp->getKey()) {
        // Check if temp has a left child
        if(temp->getLeft() == NULL) {
          // Attach new node to it
          newNode = new Node<KeyType, ValueType>(new_item.first, new_item.second, temp);
          temp->setLeft(newNode);
          locationFound = true;
        }
        // If not go to the left child
        else {
          temp = temp->getLeft();
        }
      }
      // New item's key is bigger than temp
      else if(new_item.first > temp->getKey()) {
        // Check if temp has a right child
        if(temp->getRight() == NULL) {
          // Attach new node as temp's right child
          newNode = new Node<KeyType, ValueType>(new_item.first, new_item.second, temp);
          temp->setRight(newNode);
          locationFound = true;
        }
        // If not go to the right child
        else {
          temp = temp->getRight();
        }
      }
      // new_item is equal to temp, so replace value of temp with new_item's
      else {
        temp->setValue(new_item.second);
        locationFound = true;
        return;
      }
    }

    // At this point, node has already been correctly placed, run fixTree
    splay(newNode);
  }
    
  /**
   * An In-Order iterator
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */

    iterator() : curr(NULL) { };

    iterator(Node<KeyType,ValueType>* ptr) : curr(ptr) {

    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const {
 		return this->curr == rhs.curr;
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const {
    	return this->curr != rhs.curr;
    }

    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++() {
    	curr = getCurrentSuccessor();
    	return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;

    // Function to get the current iterator's successor
    Node<KeyType, ValueType>* getCurrentSuccessor() {
    	// First check if current node has a right child
    	if(curr->getRight() != NULL) {
    		// Go to the leftmost node in the right subtree
    		Node<KeyType, ValueType>* temp = curr->getRight();
    		while(temp->getLeft() != NULL) {
    			temp = temp->getLeft();
    		}
    		// Return the successor
    		return temp;
    	}
    	// Start going up the ancestor chain
    	else {
    		// Only do this if node actually has a parent
    		if(curr->getParent() != NULL) {
	    		Node<KeyType, ValueType>* tempParent = curr->getParent();
	    		// While the node being traversed is not a left child
	    		// or we stil haven't reached the root
	    		while(tempParent->amILeftChild() == false && tempParent->getParent() != NULL) {
	    			tempParent = tempParent->getParent();
	    		}

	    		// Check to see if we reached the root node
	    		// Return root node if it is bigger than current node
	    		if(tempParent->getParent() == NULL) {
	    			if(tempParent->getKey() > curr->getKey()) {
	    				return tempParent;
	    			}
	    		}

	    		// Get the parent of the left child
	    		if(tempParent->amILeftChild() == true) {
	    			return tempParent->getParent();
	    		}
    		}
    	}

    	// only reach here if node is the biggest node, in which case return NULL
    	// same thing as reaching end()
    	return NULL;

    }


  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin() {
  	Node<KeyType, ValueType>* temp = root;
  	while(temp->getLeft() != NULL) {
  		temp = temp->getLeft();
  	}

  	return iterator(temp);
  }

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end() {
  	return NULL;
  } 

  /**
   * Returns an iterator to the item with the given key, k
   * or the end iterator if k does not exist in the tree
   */
  iterator find (const KeyType & k)  
  {
    Node<KeyType, ValueType> *curr = internalFind(k);
    iterator it(curr);
	if(curr != NULL) {
		splay(curr);
	}
    return it;
  }
  
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }


// Helper function to rotate node to the right
  void rightRotate(Node<KeyType, ValueType>* c) {

    // do nothing if child is right child
    if(c->amIRightChild() == true) {
      return;
    }

    // create node for parent
    Node<KeyType, ValueType>* p = c->getParent();

    // Change c's parent to grandparent (p's parent)
    c->setParent(p->getParent());

    // Change p's parent to c
    p->setParent(c);

    // Make c's right child's parent p, if it exists
    if(c->getRight() != NULL) {
      c->getRight()->setParent(p);
    }

    // Make p's left child c's right child; can be NULL
    p->setLeft(c->getRight());

    // Make c's right child p
    c->setRight(p);

    // Change c's new parent's left or right child
    // If NULL, make c the new root
    if(c->getParent() != NULL) {
      if(c->amIRightChild() == true) {
        c->getParent()->setRight(c);
      }
      else if(c->amILeftChild() == true) {
        c->getParent()->setLeft(c);
      }
    }
    else {
      // set c to be the new root
      this->root = c;
    }

  }


// Helper function to rotate left
  void leftRotate(Node<KeyType, ValueType>* c) {
    
    // do nothing if child is left child
    if(c->amILeftChild()) {
      return;
    }

    // create node for parent
    Node<KeyType, ValueType>* p = c->getParent();

    // change c's parent
    c->setParent(p->getParent());

    // change p's parent
    p->setParent(c);

    // change c's left child's parent to p, if it exists
    if(c->getLeft() != NULL) {
      c->getLeft()->setParent(p);
    }

    // make p's right child c's left child
    p->setRight(c->getLeft());

    // make c's left child p
    c->setLeft(p);

    // change c's new parent's left or right child
    // if parent is NULL, make c the new root
    if(c->getParent() != NULL) {
      if(c->amIRightChild() == true) {
        c->getParent()->setRight(c);
      }
      else if(c->amILeftChild() == true) {
        c->getParent()->setLeft(c);
      }
    }
    else {
      this->root = c;
    }
  }

// Splay tree, uses recursion
void splay(Node<KeyType, ValueType>* c)
{
	// base case
	if(c->getParent() == NULL) {
		return;
	}

	// get pointer of parent
	Node<KeyType, ValueType>* p = c->getParent();

	// root/zig cases
	if(p->getParent() == NULL) {
		if(c->amILeftChild()) {
			rightRotate(c);
		}
		else if(c->amIRightChild()) {
			leftRotate(c);
		}
		return;
	}	
	// zig zig and zig zag cases
	else {
		// left left
		if(c->amILeftChild() &&  p->amILeftChild()) {
			// rotate parent
			rightRotate(p);
			// rotate child
			rightRotate(c);
		}
		// right right
		else if(c->amIRightChild() && p->amIRightChild()) {
			// rotate parent
			leftRotate(p);
			// rotaete child
			leftRotate(c);
		}
		// left right
		else if(p->amILeftChild() && c->amIRightChild()) {
			leftRotate(c);
			rightRotate(c);
		}
		// right left
		else if(p->amIRightChild() && c->amILeftChild()) {
			rightRotate(c);
			leftRotate(c);
		}
		
		// recurse
		splay(c);
	}
}


};

