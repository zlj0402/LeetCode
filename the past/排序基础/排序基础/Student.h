#pragma once
#ifndef SELECTIONSORT_STUUDENT_H
#define SELECTIONSORT_STUDENT_H

#include <iostream>
#include <string>

using namespace std;

struct Student {
	string name;
	int score;

	// 重载为成员函数
	bool operator<(const Student& otherStudent) {
		return score < otherStudent.score;
	}

	friend ostream& operator<<(ostream& os, const Student& student) {
		os << "Student: " << student.name << " " << student.score << endl;
		return os;
	}
};

#endif // SELECTIONSORT_STUDENT_H