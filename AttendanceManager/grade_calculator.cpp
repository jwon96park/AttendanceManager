#pragma once

enum Grade {
	NORMAL,
	SILVER,
	GOLD
};

class GradeCalculator {
public:
	static GradeCalculator& getInstance() {
		static GradeCalculator instance;
		return instance;
	}

	Grade calculateGrade(int point) const {
		if (point >= 50) {
			return GOLD;
		} else if (point >= 30) {
			return SILVER;
		}
		return NORMAL;
	}

	bool isRemovedPlayer(const Grade grade)
	{
		return grade != GOLD && grade != SILVER;
	}

	GradeCalculator() {

	}
	GradeCalculator(const GradeCalculator&) = delete;
	GradeCalculator& operator=(const GradeCalculator&) = delete;
};