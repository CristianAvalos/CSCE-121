#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "functions.h"

/* Starter code: used by function printMenu */
void printLine(string msg) {
    cout << msg << endl;
}

/* Starter code: function printMenu() is ready for you */
void printMenu() {
    cout << endl;
    printLine("Welcome to Aggieland Twitter Feeds Stats");
    printLine("The options are:");
    printLine("1. load tweet data file and update stats");
    printLine("2. show overall stats (number of tweets, retweets, and hashtags)");
    printLine("3. show most popular hashtags");
    printLine("9. quit");
    cout << "--------> Enter your option: ";
}

/* Starter code: function to read option from the user is ready for you */
int getOption() {
    int option;
    cin >> option;
    if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		return -1;
    } 
	else {
		cin.ignore(256, '\n');
	}
    return option;
}

int main() {
	int option = 0;
	bool retweet = false;
	int tweetCount = 0, hashCount = 0, retweetCount = 0;
	string* hashtags;
	string tweet;
	OrderedHashtagList hashlist;
	while (option != 9) {
		printMenu();
		option = getOption();
		if (option == -1) {
			cout << "Invalid option" << endl; 
		}
		else if (option < 1 || (option > 3 && option < 9) || option > 9) {
			cout << "Invalid option" << endl;
		}
		else if (option == 1) {
			string filename = "";
			cout << "Enter filename: ";
			cin >> filename;
			ifstream ifs (filename);
			if (!ifs.is_open()) {
				cout << "File can't be open." << endl;
				continue;
			}
			else {
				ifs >> filename;
				while (!ifs.eof()) {
					getline(ifs, tweet);
					if(tweet == "") {
						continue;
					}
					readTweet(tweet, retweet, hashCount, hashtags);
					if (retweet) {
						retweetCount++;
					}
					tweetCount++;
					for (int i = 0; i < hashCount; ++i) {
						insertHashtag(hashtags[i], hashlist);
					}
					hashCount = hashlist.size;
				}	
			}
		}
		else if (option == 2) {
			cout << "Tweets: " << tweetCount << ", Retweets: " << retweetCount << ", Hashtags: " << hashCount << endl;
			continue;
		}
		else if (option == 3) {
			if (tweetCount == 0) {
				cout << "No hashtags." << endl;
			}
			showMostPopularHashtags(hashlist, 10);
			continue;
		}
		else if (option == 9) {
			break;
		}
		else {
			cout << "Invalid option" << endl;
			continue;
		}
	}
	if (option == 9) {
		return -1;
	}
	else {
		return 0;
	}
}
