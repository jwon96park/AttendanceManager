#include "gmock/gmock.h"
using namespace testing;
using namespace std;

#include "manager.cpp"
#include "player.cpp"

class ManagerTest : public Test {
	protected:
	Manager manager;
	void SetUp() override {
	}
	void TearDown() override {
		// Clean up after each test if necessary
	}
};

TEST_F(ManagerTest, CountAttendance_FirstTimePlayer) {
	string name = "Alice";
	string day = "monday";
	manager.countAttendance(name, day);
	PlayerInfo player = manager.getPlayerInfo(1);
	// Check if the player was added correctly
	EXPECT_EQ(player.getPoint(), 1);
}