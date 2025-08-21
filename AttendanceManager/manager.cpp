#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "player.cpp"
#include "grade_calculator.cpp"

using namespace std;

const int MAX_PLAYER_NUM = 100;
const int WEEKDAY_NUM = 7;

class Manager {
private:
	map<string, int> playerID;
	PlayerInfo playerList[MAX_PLAYER_NUM];
	GradeCalculator	gradeCalculator;

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

	void printRemovedplayer()
	{
		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";
		for (int id = 1; id <= playerID.size(); id++) {
			if (isRemovedPlayer(id) && gradeCalculator.isRemovedPlayer(playerList[id].getGrade())) {
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

	void setGrade()
	{
		for (int id = 1; id <= playerID.size(); id++) {
			Grade playerGrade = gradeCalculator.calculateGrade(playerList[id].getPoint());
			playerList[id].setGrade(playerGrade);
		}
	}

	void printScoreEachPlayer()
	{
		for (int id = 1; id <= playerID.size(); id++) {
			std::cout << "NAME : " << playerList[id].getName() << ", ";
			std::cout << "POINT : " << playerList[id].getPoint() << ", ";
			std::cout << "GRADE : ";

			if (playerList[id].getGrade() == GOLD) {
				std::cout << "GOLD" << "\n";
			}
			else if (playerList[id].getGrade() == SILVER) {
				std::cout << "SILVER" << "\n";
			}
			else {
				std::cout << "NORMAL" << "\n";
			}
		}
	}

	bool isRemovedPlayer(int id)
	{
		return playerList[id].getDayCount("wednesday") == 0
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

		addBonusPoint();

		setGrade();

		printScoreEachPlayer();

		printRemovedplayer();
	}

	PlayerInfo getPlayerInfo(const int id) {
		return playerList[id];
	}
};