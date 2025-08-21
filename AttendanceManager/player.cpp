#include <string>
#include <map>

using namespace std;

class Player {
private:
	string name;
	int id;
	int point;
	map<string, int> dayCount;
public:
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

	Player() = default;
};