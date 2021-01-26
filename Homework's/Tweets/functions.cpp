#include <iostream>
#include <string>
using namespace std;

#include "functions.h"



/* readTweet
 * Parameters:
 *      line: string containing the tweet information received by the function
 *      isRetweet: reference to bool; function will update it with true if retweet
 *      nb_htags: reference to int; function will update with number of hashtags
 *                in the tweet.
 *      array_of_htags: reference to an array of strings; function will allocate
 *                      the array and store the hashtag in it
 * Return value:
 *      none
 * Functionality:
 *     Processes the string in order to find out hashtags and identify if it is Retweet
 */
void readTweet(string line, bool& isRetweet, int& nb_htags, string*& array_of_htags) {
	isRetweet = false;
	nb_htags = 0;
	for (int i = 0; i < line.length(); ++i) {
		if ((line[i] == 'R') && (line[i+1] == 'T')) {
			isRetweet = true;
		}
		else {
			continue;
		}
	}
	for (int i = 0; i < line.length(); ++i) {
		if (line[i] == '#') {
			nb_htags++;
		}
	}
	array_of_htags = new string[nb_htags];
	int pos = 0;
	for (int i = 0; i < line.length(); ++i) {
		if (line[i] == '#') {
			string s = "#";
			char c = line[++i];
			while(isalpha(c) || isdigit(c)) {
				c = tolower(c);
				s.push_back(c);
				c = line[++i];
			}
			array_of_htags[pos] = s;
			pos++;
		}
		else {
			continue;
		}
	}
}

/* insertHashtag
 * Parameters:
 *      ht: string
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      true if insertion succeeds, false if memory allocation
 *      fails.
 * Functionality:
 *      See prompt for specification and examples.
 */

bool insertHashtag(string ht, OrderedHashtagList& hashlist) {
	bool inList = false;
	for (int i = 0; i < ht.length(); ++i) {
		ht[i] = tolower(ht[i]);
	}
	for (int i = 0; i < hashlist.size; ++i) {
		if (ht == hashlist.list[i].name) {
			inList = true;
			hashlist.list[i].counter++;
			int j = i;
			while ((j > 0) && (hashlist.list[i - 1].counter < hashlist.list[i].counter)) { //////// - 1?
				Hashtag temp = hashlist.list[i - 1];
				hashlist.list[i - 1] = hashlist.list[i];
				hashlist.list[i] = temp;
				j--;
			}
		}
		else {
			continue;
		}
	}		
	if (inList == false) {
		if (hashlist.size + 1 > hashlist.capacity) {
			int size = hashlist.size;
			Hashtag* array = new Hashtag[hashlist.capacity * 2];
			for (int i = 0; i < hashlist.size; ++i) {
				array[i] = hashlist.list[i];
			}
			hashlist.capacity *= 2;
			delete [] hashlist.list;
			hashlist.list = array;
		}
		hashlist.list[hashlist.size].name = ht;
		hashlist.list[hashlist.size].counter = 1;
		hashlist.size++;
	}
    return true;
}

/* showMostPopularHashtags
 * Parameters:
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      none
 * Functionality:
 *      Prints the k most popular hashtags.
 *      See prompt for formatting details.
 */
void showMostPopularHashtags(OrderedHashtagList hashlist, int k) {
	if (hashlist.size < k) {
		for (int i = 0; i < hashlist.size; ++i) {
			cout << "Tag " << hashlist.list[i].name << " - " << hashlist.list[i].counter << " occurrence(s)" << endl;
		}
	}
	else {
		for (int i = 0; i < k; ++i) {
			cout << "Tag " << hashlist.list[i].name << " - " << hashlist.list[i].counter << " occurrence(s)" << endl;
		}
	}
}


