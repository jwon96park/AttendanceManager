#pragma once
using namespace std;

const int MAX_PLAYER_NUM = 100;
const int WEEKDAY_NUM = 7;

typedef struct PlayerData_ {
	string name;
	int point;
	map<string, int> dayCount;
} PlayerData;

enum Grade {
	NORMAL,
	SILVER,
	GOLD
};

void inputByFile();
void checkAttendance();
void addBonusPoint();
void setGrade(Grade grade[MAX_PLAYER_NUM]);
void printScoreEachPlayer(const Grade grade[MAX_PLAYER_NUM]);
bool isRemovedPlayer(const Grade grade, int id);
void printRemovedPlayers(const Grade grade[MAX_PLAYER_NUM]);
void countAttendance(string name, string day);

bool isFirstTime(const std::string& name);
void insertPlayer(const std::string & name);
void addDayCount(const std::string& name, const std::string& day);
void addPoint(const std::string & name, const std::string & day);
