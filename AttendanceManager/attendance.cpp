#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "attendance.h"

using namespace std;

PlayerData playerData[MAX_PLAYER_NUM];
map<string, int> playerID;

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
	playerData[id].name = name;
}

void addDayCount(const std::string& name, const std::string& day)
{
	int id = playerID[name];
	playerData[id].dayCount[day] += 1;
}

void addPoint(const std::string& name, const std::string& day)
{
	int id = playerID[name];
	if (day == "monday") {
		playerData[id].point += 1;
	}
	if (day == "tuesday") {
		playerData[id].point += 1;
	}
	if (day == "wednesday") {
		playerData[id].point += 3;
	}
	if (day == "thursday") {
		playerData[id].point += 1;
	}
	if (day == "friday") {
		playerData[id].point += 1;
	}
	if (day == "saturday") {
		playerData[id].point += 2;
	}
	if (day == "sunday") {
		playerData[id].point += 2;
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
		if (playerData[id].dayCount["wednesday"] >= 10) {
			playerData[id].point += 10;
		}

		const int weekendCount = playerData[id].dayCount["saturday"] + playerData[id].dayCount["sunday"];
		if (weekendCount >= 10) {
			playerData[id].point += 10;
		}
	}
}

void setGrade(Grade grade[MAX_PLAYER_NUM])
{
	for (int id = 1; id <= playerID.size(); id++) {
		if (playerData[id].point >= 50) {
			grade[id] = GOLD;
		}
		else if (playerData[id].point >= 30) {
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
		std::cout << "NAME : " << playerData[id].name << ", ";
		std::cout << "POINT : " << playerData[id].point << ", ";
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
			std::cout << playerData[id].name << "\n";
		}
	}
}

bool isRemovedPlayer(const Grade grade, int id)
{
	return grade != GOLD && grade != SILVER
		&& playerData[id].dayCount["wednesday"] == 0
		&& (playerData[id].dayCount["saturday"] + playerData[id].dayCount["sunday"]) == 0;
}
