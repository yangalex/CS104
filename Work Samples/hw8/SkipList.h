#ifndef SKIP_LIST
#define SKIP_LIST
#include <stdlib.h>
#include <time.h>
#include <deque>

template<class K, class V>
struct SkipNode {
	K key;
	V value;
	int nodeHeight;
	SkipNode** forward;
	std::pair<const K, V> _item;

	SkipNode() {

	}

	SkipNode(K k, V v, int level) : _item(k, v) {
		key = k;
		value = v;
		nodeHeight = level; // for debugging
		forward = new SkipNode*[level+1];
		for(int i=0; i < level+1; i++) {
			forward[i] = NULL;
		}
	}

};

template<class K, class V>
class SkipList {
	private:
		int maxLevel;
		SkipNode<K, V>* head;
		SkipNode<K, V>* tail;
		int randomLevel();

	public:
		SkipList(int max, K maxKey) {
			srand(time(NULL)); // seed rand
			maxLevel = max;
			K dummyKey;
			V dummyValue;
			// create head with dummy variables
			head = new SkipNode<K, V>(dummyKey, dummyValue, maxLevel);

			// set head's pointers to the end node
			tail = new SkipNode<K, V>(maxKey, dummyValue, maxLevel);
			
			for(int i=0; i < maxLevel+1; i++) {
				head->forward[i] = tail;
			}
		}

		SkipNode<K, V>* search(const K& key);

		void insert(const std::pair<K, V> new_item);
		
		V operator[](K& key); 
	
		class iterator {
			public:
				iterator() : curr(NULL) { };

				iterator(SkipNode<K, V>* ptr) : curr(ptr) { };

				std::pair<const K, V>& operator*() {
					return curr->_item;
				}

				std::pair<const K, V>* operator->()
				{ return &(curr->_item); }

				bool operator==(const iterator& rhs) const {
					return this->curr == rhs.curr;
				}

				bool operator!=(const iterator& rhs) const {
					return this->curr != rhs.curr;
				}

				iterator& operator++() {
					curr = curr->forward[0];
					return *this;
				}
				
				protected:
					SkipNode<K, V>* curr;

		};

		iterator begin() {
			return iterator(head->forward[0]);
		}

		iterator end() {
			return tail;
		}

		iterator find(const K & key) {
			SkipNode<K, V>* curr = search(key);
			iterator it(curr);
			return it;
		}	
};

template<class K, class V>
SkipNode<K, V>* SkipList<K, V>::search(const K& key) 
{

	SkipNode<K, V>* current = head;
	for(int i=maxLevel; i >= 0; i--) {
		while(current->forward[i]->key < key) {
			current = current->forward[i];
			//std::cout << "Moved to: " << current->key << std::endl;
		}
	}	

	//std::cout << "current stopped at: " << current->key << std::endl;
	current = current->forward[0];
	if(current->key == key) {
		return current;
	}
	else {
        return tail;
	}
}

template<class K, class V>
V SkipList<K, V>::operator[](K& key) 
{
	SkipNode<K, V>* foundNode = search(key);
	if(foundNode != NULL) {
		return foundNode->value;
	}
	else {
		std::cout << "Found NULL when looking for: " << key << std::endl;
		return head->forward[0]->value;
	}
}

template<class K, class V>
void SkipList<K, V>::insert(const std::pair<K, V> new_item)
{
	SkipNode<K, V>* current = head;
	std::deque<SkipNode<K, V>* > update;	
    
	for(int i=maxLevel; i >= 0; i--) {
		while(current->forward[i]->key < new_item.first) {
			current = current->forward[i];
		}

		update.push_front(current);
	}

	// update value if key already exists
	if(current->forward[0]->key == new_item.first) {
		current->forward[0]->value = new_item.second;
		return;
	}
	else {
		int height = randomLevel();
		// allocate new node
		SkipNode<K, V>* newNode = new SkipNode<K, V>(new_item.first, new_item.second, height);
		for(int i=0; i <= height; i++) {
			// set new node's forward to update's forward
            newNode->forward[i] = update[i]->forward[i];
			// set update's forward to newNode
			update[i]->forward[i] = newNode;
		}
	}	
}

template<class K, class V>
int SkipList<K, V>::randomLevel()
{
	int height = 0;

	while(rand()%100 < 50 && height < maxLevel) {
		height++;
	}
	return height;
}

#endif
