#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "attendance.h"

using namespace std;

const int MAX_PLAYER_NUM = 100;
const int WEEKDAY_NUM = 7;

struct Node {
	string name;
	string day;
};

map<string, int> playerID;

int playerData[MAX_PLAYER_NUM][WEEKDAY_NUM];
int playerPoint[MAX_PLAYER_NUM];
int grade[MAX_PLAYER_NUM];
string playerName[MAX_PLAYER_NUM];

int wednesdayRecords[MAX_PLAYER_NUM];
int weekendRecords[MAX_PLAYER_NUM];

int main() {
	inputByFile();
	checkAttendance();
}

void inputByFile() {
	const int INPUT_NUM = 500;
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int i = 0; i < INPUT_NUM; i++) {
		string name, day;
		fin >> name >> day;
		countAttendance(name, day);
	}
}

void countAttendance(string name, string day) {
	if (playerID.count(name) == 0) {
		int id = playerID.size() + 1;
		playerID.insert({ name, id });
		playerName[id] = name;
	}
	int id = playerID[name];

	int point = 0;
	int index = 0;
	if (day == "monday") {
		index = 0;
		point += 1;
	}
	if (day == "tuesday") {
		index = 1;
		point += 1;
	}
	if (day == "wednesday") {
		index = 2;
		point += 3;
		wednesdayRecords[id] += 1;
	}
	if (day == "thursday") {
		index = 3;
		point++;
	}
	if (day == "friday") {
		index = 4;
		point += 1;
	}
	if (day == "saturday") {
		index = 5;
		point += 2;
		weekendRecords[id] += 1;
	}
	if (day == "sunday") {
		index = 6;
		point += 2;
		weekendRecords[id] += 1;
	}

	playerData[id][index] += 1;
	playerPoint[id] += point;
}

void checkAttendance() {
	for (int i = 1; i <= playerID.size(); i++) {
		if (playerData[i][2] > 9) {
			playerPoint[i] += 10;
		}

		if (playerData[i][5] + playerData[i][6] > 9) {
			playerPoint[i] += 10;
		}

		if (playerPoint[i] >= 50) {
			grade[i] = 1;
		}
		else if (playerPoint[i] >= 30) {
			grade[i] = 2;
		}
		else {
			grade[i] = 0;
		}

		cout << "NAME : " << playerName[i] << ", ";
		cout << "POINT : " << playerPoint[i] << ", ";
		cout << "GRADE : ";

		if (grade[i] == 1) {
			cout << "GOLD" << "\n";
		}
		else if (grade[i] == 2) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int i = 1; i <= playerID.size(); i++) {
		if (grade[i] != 1 && grade[i] != 2 && wednesdayRecords[i] == 0 && weekendRecords[i] == 0) {
			std::cout << playerName[i] << "\n";
		}
	}
}