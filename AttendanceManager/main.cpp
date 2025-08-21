#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "player.cpp"
#include "manager.cpp"

using namespace std;

void inputByFile(Manager& manager) {
	const int INPUT_NUM = 500;
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int i = 0; i < INPUT_NUM; i++) {
		string name, day;
		fin >> name >> day;
		manager.countAttendance(name, day);
	}
}

#ifdef _DEBUG
#include "gmock/gmock.h"

using namespace testing;

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#else
int main() {
	Manager manager;

	inputByFile(manager);
	manager.checkAttendance();
}
#endif

