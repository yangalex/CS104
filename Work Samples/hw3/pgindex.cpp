#include <iostream>
#include <map>
#include <cctype>
#include <fstream>
#include "setint.h"

using namespace std;

int main(int argc, char* argv[]) {
	map<string, SetInt*> words;
	int pageNumber = 1;

	// Check number of arguments
	if(argc < 3) {
		cout << "Please pass input file and output file" << endl;
		return 1;
	}

	// Open file
	ifstream ifile(argv[1]);
	if(ifile.fail()) {
		cout << "Could not open file" << endl;
		return 1;
	}

	// buffer
	string buf;

	while(ifile >> buf) {
		// If the word is <pagebreak> increment page number
		if(buf == "<pagebreak>") {
			pageNumber++;
		}
		else {
			//Remove any punctuations
			while(ispunct(buf[0])) {
				buf = buf.substr(1, buf.length());
			}
			while(ispunct(buf[buf.length()-1])) {
				buf = buf.substr(0, buf.length()-1);
			}

			// change first letter to lower case
			buf[0] = tolower(buf[0]);

			// Case where word has a hyphen in it
			if(buf.find("-") != string::npos) {
				while(buf.find("-") != string::npos) {
					string hyphenWord = buf.substr(0, buf.find("-"));
					buf = buf.substr(buf.find("-"), buf.length()-1);
					if(hyphenWord.length() >= 2) {
						// Word is already in map
						if(words.find(hyphenWord) != words.end()) {
							// Add page number
							words[hyphenWord]->insert(pageNumber);
						}
						// Word is not in map
						else {
							// Allocate new SetInt
							SetInt* newSet = new SetInt;
							newSet->insert(pageNumber);
							// Add new entry to map
							words.insert(make_pair(hyphenWord, newSet));
						}
					}
				}	
			}
			else if(buf.find("\'") == string::npos) {
				// Word that is not punctuation and has 2 or more letters
				if(buf.length() >= 2) {
					// Word is already in map
					if(words.find(buf) != words.end()) {
						// Add page number
						words[buf]->insert(pageNumber);
					}
					// Word is not in map
					else {
						// Allocate new SetInt
						SetInt* newSet = new SetInt;
						newSet->insert(pageNumber);
						// Add new entry to map
						words.insert(make_pair(buf, newSet));

					}
				}
			}

		}
	}

	// open output file
	ofstream ofile(argv[2]);

	// Iterate through words given as argument
	for(int i=3; i < argc; i++) {
		char* currentWord = argv[i];
		currentWord[0] = tolower(currentWord[0]);
		if(words.find(currentWord) == words.end()) {
			ofile << "None" << endl;
		}
		else {
			const int* it = words[currentWord]->first();
			while(it != NULL) {
				ofile << *it << " ";
				it = words[currentWord]->next();
			}
			ofile << endl;
		}
	}

	// deallocate memory
	map<string, SetInt*>::iterator it;
	for(it = words.begin(); it != words.end(); ++it) {
		delete it->second;
	}

	ifile.close();
	ofile.close();

	return 0;
}


