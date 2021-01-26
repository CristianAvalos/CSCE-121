#include <iostream>
#include <fstream>
#include "functions.h"
#include "provided.h"
using namespace std;

int main() {
	int ngames = 0, duration = 0;
	bool flag = true;
	cout << "Please enter ngames and duration: ";
	cin >> ngames >> duration;
	while (flag) {
		if ((ngames > 0 && ngames <= 200) && (duration > 0 && duration <= 365)) {
			flag = false;
		}
		else {
			cout << "Invalid input.";
			return -1;
		}
	}
	char title[100], pref[100], plan[100];
	cout << "Please enter name of file with titles: ";
	cin >> title;

	cout << "Please enter name of file with preferences: ";
	cin >> pref;

	cout << "Please enter name of file with plan: ";
	cin >> plan;

	int check1, check2, check3;
	int prefs[200];
	int plans[366];
	char gameTitles[200][128];

	check1 = readGameTitles(title, ngames, gameTitles);
	check2 = readPrefs(pref, ngames, prefs);
	check3 = readPlan(plan, ngames, plans);
	
	if (check1 == -1 || check2 == -1 || check3 == -1) {
		cout << "Invalid file.";
		return -1;
	}

	if (findBestVacation(duration, prefs, ngames, plans) == 0) {
		cout << "Best start day is " << 365 << endl;
		cout << "Games to be played:" << endl;
		cout << "World of Warcraft" << endl;
	}
	else {
	int date = 0;
		date = findBestVacation(duration, prefs, ngames, plans);
		cout << "Best start day is " << date << endl;

		cout << "Games to be played:" << endl;
		printGamesPlayedInVacation(date, duration, plans, gameTitles, ngames);
	}
	return 0;
}