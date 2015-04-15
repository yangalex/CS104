#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Item {
	Item(int v, Item* n);
	int val;
	Item* next;
};

Item::Item(int v, Item* n) {
	val = v;
	next = n;
}

void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

Item* concatenate(Item* head1, Item* head2);
void removeEvens(Item*& head);
double findAverage(Item* head);

//helper function for concatenate
void concatenate_helper(Item* head1, Item* head2, Item*& newHead, Item*& tempHead) {
	// First element to be copied (first funciton call)
	if(newHead == NULL) {
		newHead = new Item(head1->val, head1->next);
		tempHead = newHead;
		concatenate_helper(head1->next, head2, newHead, tempHead->next);
	}
	// while head1 is still not NULL
	else if(head1) {
		tempHead = new Item(head1->val, head1->next);
		concatenate_helper(head1->next, head2, newHead, tempHead->next);
	}
	// Once head1 has ended, start head2
	else if(head2 && head1 == NULL) {
		tempHead = new Item(head2->val, head2->next);
		concatenate_helper(head1, head2->next, newHead, tempHead->next);
	}
	// when everything has been copied over
	else if(head2 == NULL) {
		return;
	}
}

Item* concatenate(Item* head1, Item* head2) {
	Item* newHead = NULL;
	Item* trackerHead;

	concatenate_helper(head1, head2, newHead, trackerHead);
	return newHead;
}


void removeEvens_helper(Item*& head, bool isHead) {

	if(head->next == NULL) {
		return;
	}

	// If the first element is even
	if(isHead) {
		if(head->val % 2 == 0) {
			cout << "Head is even" << endl;
			Item* temp = head;
			head = head->next;
			delete temp;
			removeEvens_helper(head, true);
		}
		else {
			removeEvens_helper(head, false);
		}
	}
	else {
		if(head->next->val % 2 == 0) {
			Item* temp = head->next->next;
			delete head->next;
			head->next = temp;

			if(!head->next) {
				return;
			}
			// in cases where there are two or more even numbers in a row
			if(head->next->val % 2 == 0) {
				removeEvens_helper(head, false);
			}
			else {
				removeEvens_helper(head->next, false);
			}
		}
		else {
			removeEvens_helper(head->next, false);
		}	
	}
}

void removeEvens(Item*& head) {
	removeEvens_helper(head, true);
}

double findAverage_helper(Item* head, int total, int counter) {
	if(head == NULL) {
		return total/(double)counter;
	}
	else {
		findAverage_helper(head->next, total + head->val, ++counter);
	}
}

double findAverage(Item* head) {
	findAverage_helper(head, 0, 0);
}

void readLists(char* filename, Item*& head1, Item*& head2) {
	ifstream ifile(filename);

	if(ifile.fail()) {
		cout << "Could not read file name" << endl;
		return;
	}

	char buf[100];

	ifile.getline(buf, 80);

	stringstream ss(buf);
	int newVal;
	ss >> newVal;

	// Make first linked list
	head1 = new Item(newVal, NULL);

	Item* tempItem = head1;

	while(ss >> newVal) {
		tempItem->next = new Item(newVal, NULL);
		tempItem = tempItem->next;
	}

	// Reset stringstream
	ss.clear();
	ss.str("");

	// Make second linked list
	ifile.getline(buf, 80);
	ss << buf;
	ss >> newVal;
	head2 = new Item(newVal, NULL);
	tempItem = head2;

	while(ss >> newVal) {
		tempItem->next = new Item(newVal, NULL);
		tempItem = tempItem->next;
	}

	ifile.close();

}

int main(int argc, char *argv[]) {

	if(argc < 3) {
		cout << "Please give an input filename and output filename" << endl;
		return 1;
	}

	ofstream ofile(argv[2]);

	// Create heads
	Item* head1;
	Item* head2;

	readLists(argv[1], head1, head2);

	// Concatenate
	Item* head3 = concatenate(head1, head2);
	printList(ofile, head3);

	// Remove Evens
	removeEvens(head3);
	printList(ofile, head3);

	// Find Average
	double avg = findAverage(head3);
	printList(ofile, head3);	
	ofile << avg << endl;

	// delete linked lists
	Item* countHead = head1;
	while(countHead != NULL) {
		Item* tempNext = countHead->next;
		delete countHead;
		countHead = tempNext;
	}
	countHead = head2;
	while(countHead != NULL) {
		Item* tempNext = countHead->next;
		delete countHead;
		countHead = tempNext;
	}

	return 0;
}