#include "gmock/gmock.h"
using namespace testing;
using namespace std;

#include "manager.cpp"
#include "player.cpp"
#include "grade_calculator.cpp"

class ManagerTest : public Test {
	protected:
	Manager manager;
	void SetUp() override {
	}
	void TearDown() override {
		// Clean up after each test if necessary
	}
};

TEST_F(ManagerTest, basic) {
	string name = "Alice";
	manager.countAttendance(name, "monday");
	manager.countAttendance(name, "tuesday");
	manager.countAttendance(name, "wednesday");
	manager.countAttendance(name, "thursday");
	manager.countAttendance(name, "friday");
	manager.countAttendance(name, "saturday");
	manager.countAttendance(name, "sunday");
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 11);
}

TEST_F(ManagerTest, Gold) {
	string name = "Alice";
	string day = "wednesday";
	for(int i = 0; i < 17; i++){
		manager.countAttendance(name, day);
	}
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 51);
}

TEST_F(ManagerTest, SILVER) {
	string name = "Alice";
	string day = "wednesday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 30);
}

TEST_F(ManagerTest, bonus_score) {
	string name = "Alice";
	string day = "wednesday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	manager.checkAttendance();
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 40);
}

TEST_F(ManagerTest, tentimes_week) {
	string name = "Alice";
	string day = "sunday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	manager.checkAttendance();
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 30);
}

TEST_F(ManagerTest, tentimes_week_and_gold) {
	string name = "Alice";
	string day = "sunday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	day = "wednesday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	manager.checkAttendance();
	PlayerInfo player = manager.getPlayerInfo(1);
	EXPECT_EQ(player.getPoint(), 70);
}

TEST_F(ManagerTest, removed_player) {
	string name = "Alice";
	string day = "sunday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	day = "wednesday";
	for(int i = 0; i < 10; i++){
		manager.countAttendance(name, day);
	}
	manager.countAttendance("lee", "monday");
	manager.checkAttendance();
	PlayerInfo player = manager.getPlayerInfo(2);
	EXPECT_EQ(player.getPoint(), 1);
}

TEST(GRADE, GradeCalculator) {
	GradeCalculator& gradeCalculator = GradeCalculator::getInstance();
	EXPECT_EQ(gradeCalculator.calculateGrade(10), NORMAL);
	EXPECT_EQ(gradeCalculator.calculateGrade(30), SILVER);
	EXPECT_EQ(gradeCalculator.calculateGrade(50), GOLD);
}