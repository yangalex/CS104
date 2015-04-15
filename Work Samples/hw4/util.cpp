#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord)
{
	std::set<std::string> wordSet;
	std::stringstream ss(rawWord);
	std::string buf;

	while(ss >> buf) {
		// convert to lower
		buf = convToLower(buf);

		// Remove any punctuations from beginning
		while(ispunct(buf[0])) {
			buf = buf.substr(1, buf.length());
		}

		// Remove any punctuations from end
		while(ispunct(buf[buf.length()-1])) {
			buf = buf.substr(0, buf.length()-1);
		}

		// In case of hyphens
		if(buf.find('-') != std::string::npos) {
			while(buf.find('-') != std::string::npos) {
				string hyphenWord = buf.substr(0, buf.find('-'));
				buf = buf.substr(buf.find('-')+1, buf.length());
				if(hyphenWord.length() >= 2) {
					wordSet.insert(hyphenWord);
				}
			}
			if(buf.length() >= 2) {
				wordSet.insert(buf);
			}
		}
		// In case of apostrophes
		else if(buf.find('\'') != std::string::npos) {
			string apostropheWord = buf.substr(0, buf.find('\''));
			if(apostropheWord.length() >=2) {
				wordSet.insert(apostropheWord);
			}
			apostropheWord = buf.substr(buf.find('\'')+1, buf.length());
			if(apostropheWord.length() >= 2) {
				wordSet.insert(apostropheWord);
			}
		}
		// insert word to set (no hyphens and no apostrophes)
		else {
			if(buf.length() >= 2) {
				wordSet.insert(buf);
			}
		}

	}

	return wordSet;

}
