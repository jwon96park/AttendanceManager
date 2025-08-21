#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "player.cpp"

using namespace std;

const int MAX_PLAYER_NUM = 100;
const int WEEKDAY_NUM = 7;

enum Grade {
	NORMAL,
	SILVER,
	GOLD
};

class Manager {
private:
	map<string, int> playerID;
	PlayerInfo playerList[MAX_PLAYER_NUM];

	bool isFirstTime(const std::string& name)
	{
		return playerID.count(name) == 0;
	}

	void insertPlayer(const std::string& name)
	{
		int id = playerID.size() + 1;
		playerID.insert({ name, id });
		playerList[id].setName(name);
	}

	void addDayCount(const std::string& name, const std::string& day)
	{
		int id = playerID[name];
		playerList[id].addDayCount(day);
	}

	void addPoint(const std::string& name, const std::string& day)
	{
		int id = playerID[name];
		if (day == "monday") {
			playerList[id].addPoint(1);
		}
		if (day == "tuesday") {
			playerList[id].addPoint(1);
		}
		if (day == "wednesday") {
			playerList[id].addPoint(3);
		}
		if (day == "thursday") {
			playerList[id].addPoint(1);
		}
		if (day == "friday") {
			playerList[id].addPoint(1);
		}
		if (day == "saturday") {
			playerList[id].addPoint(2);
		}
		if (day == "sunday") {
			playerList[id].addPoint(2);
		}
	}

	void printRemovedplayer(const Grade grade[MAX_PLAYER_NUM])
	{
		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";
		for (int id = 1; id <= playerID.size(); id++) {
			if (isRemovedPlayer(grade[id], id)) {
				std::cout << playerList[id].getName() << "\n";
			}
		}
	}

	void addBonusPoint()
	{
		for (int id = 1; id <= playerID.size(); id++) {
			if (playerList[id].getDayCount("wednesday") >= 10) {
				playerList[id].addPoint(10);
			}

			const int weekendCount = playerList[id].getDayCount("saturday") + playerList[id].getDayCount("sunday");
			if (weekendCount >= 10) {
				playerList[id].addPoint(10);
			}
		}
	}

	void setGrade(Grade grade[MAX_PLAYER_NUM])
	{
		for (int id = 1; id <= playerID.size(); id++) {
			if (playerList[id].getPoint() >= 50) {
				grade[id] = GOLD;
			}
			else if (playerList[id].getPoint() >= 30) {
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
			std::cout << "NAME : " << playerList[id].getName() << ", ";
			std::cout << "POINT : " << playerList[id].getPoint() << ", ";
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

	bool isRemovedPlayer(const Grade grade, int id)
	{
		return grade != GOLD && grade != SILVER
			&& playerList[id].getDayCount("wednesday") == 0
			&& (playerList[id].getDayCount("saturday") + playerList[id].getDayCount("sunday")) == 0;
	}
public:
	void countAttendance(string name, string day) {
		if (isFirstTime(name))
			insertPlayer(name);

		addDayCount(name, day);
		addPoint(name, day);
	}

	void checkAttendance() {
		Grade grade[MAX_PLAYER_NUM] = { NORMAL };

		addBonusPoint();

		setGrade(grade);

		printScoreEachPlayer(grade);

		printRemovedplayer(grade);
	}

	PlayerInfo getPlayerInfo(const int id) {
		return playerList[id];
	}
};