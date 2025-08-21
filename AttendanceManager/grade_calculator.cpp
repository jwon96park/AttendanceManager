#pragma once

enum Grade {
	NORMAL,
	SILVER,
	GOLD
};

class GradeCalculator {
public:
	Grade calculateGrade(int point) const {
		if (point >= 50) {
			return GOLD;
		} else if (point >= 30) {
			return SILVER;
		} else {
			return NORMAL;
		}
	}

	bool isRemovedPlayer(const Grade grade)
	{
		return grade != GOLD && grade != SILVER;
	}
};