#pragma once
#include <string>
#include <map>

#include "grade_calculator.cpp"

using namespace std;

class PlayerInfo {
private:
	string name;
	int id;
	int point;
	Grade grade;
	map<string, int> dayCount;
public:
	void setGrade(Grade playerGrade) {
		grade = playerGrade;
	}
	Grade getGrade() {
		return grade;
	}
	void setName(const string& playerName) {
		name = playerName;
	}
	void setId(int playerId) {
		id = playerId;
	}
	string getName() {
		return name;
	}

	int getId() {
		return id;
	}

	int getPoint() {
		return point;
	}

	void addDayCount(const string& day) {
		dayCount[day]++;
	}

	int getDayCount(const string& day) {
		return dayCount[day];
	}

	void addPoint(int addedPoint) {
		point += addedPoint;
	}

	PlayerInfo() = default;
};