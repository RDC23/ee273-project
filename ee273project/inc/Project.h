#pragma once
#include "User.h"
class Project { //needs methods

private:
	std::string description;
	int maxCapacity;
	std::vector<Student*> students;
	Supervisor* supervisor;
	bool full;


};