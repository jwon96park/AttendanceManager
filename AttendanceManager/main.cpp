#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "attendance.h"
#include "player.cpp"

using namespace std;

Player players[MAX_PLAYER_NUM];
map<string, int> playerID;

#ifdef _DEBUG
#include "gmock/gmock.h"

using namespace testing;

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#else
int main() {
	inputByFile();
	checkAttendance();
}
#endif

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
	if (isFirstTime(name))
		insertPlayer(name);

	addDayCount(name, day);
	addPoint(name, day);
}

bool isFirstTime(const std::string& name)
{
	return playerID.count(name) == 0;
}

void insertPlayer(const std::string& name)
{
	int id = playerID.size() + 1;
	playerID.insert({ name, id });
	players[id].setName(name);
}

void addDayCount(const std::string& name, const std::string& day)
{
	int id = playerID[name];
	players[id].addDayCount(day);
}

void addPoint(const std::string& name, const std::string& day)
{
	int id = playerID[name];
	if (day == "monday") {
		players[id].addPoint(1);
	}
	if (day == "tuesday") {
		players[id].addPoint(1);
	}
	if (day == "wednesday") {
		players[id].addPoint(3);
	}
	if (day == "thursday") {
		players[id].addPoint(1);
	}
	if (day == "friday") {
		players[id].addPoint(1);
	}
	if (day == "saturday") {
		players[id].addPoint(2);
	}
	if (day == "sunday") {
		players[id].addPoint(2);
	}
}

void checkAttendance() {
	Grade grade[MAX_PLAYER_NUM] = { NORMAL };

	addBonusPoint();

	setGrade(grade);

	printScoreEachPlayer(grade);

	printRemovedPlayers(grade);
}

void addBonusPoint()
{
	for (int id = 1; id <= playerID.size(); id++) {
		if (players[id].getDayCount("wednesday") >= 10) {
			players[id].addPoint(10);
		}

		const int weekendCount = players[id].getDayCount("saturday") + players[id].getDayCount("sunday");
		if (weekendCount >= 10) {
			players[id].addPoint(10);
		}
	}
}

void setGrade(Grade grade[MAX_PLAYER_NUM])
{
	for (int id = 1; id <= playerID.size(); id++) {
		if (players[id].getPoint() >= 50) {
			grade[id] = GOLD;
		}
		else if (players[id].getPoint() >= 30) {
			grade[id] = SILVER;
		}
		else {
			grade[id] = NORMAL;
		}
	}
}

void printScoreEachPlayer(const Grade grade[MAX_PLAYER_NUM])
{
	for (int id = 1; id <= playerID.size(); id++) {
		std::cout << "NAME : " << players[id].getName() << ", ";
		std::cout << "POINT : " << players[id].getPoint() << ", ";
		std::cout << "GRADE : ";

		if (grade[id] == GOLD) {
			std::cout << "GOLD" << "\n";
		}
		else if (grade[id] == SILVER) {
			std::cout << "SILVER" << "\n";
		}
		else {
			std::cout << "NORMAL" << "\n";
		}
	}
}

void printRemovedPlayers(const Grade grade[MAX_PLAYER_NUM])
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= playerID.size(); id++) {
		if (isRemovedPlayer(grade[id], id)) {
			std::cout << players[id].getName() << "\n";
		}
	}
}

bool isRemovedPlayer(const Grade grade, int id)
{
	return grade != GOLD && grade != SILVER
		&& players[id].getDayCount("wednesday") == 0
		&& (players[id].getDayCount("saturday") + players[id].getDayCount("sunday")) == 0;
}
