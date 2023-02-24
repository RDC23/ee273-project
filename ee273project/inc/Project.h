#pragma once
#include "User.h"
class Project { 

public:
	Project(std::string description, int capacity);
	Project(std::string description, int capacity, int supervisorID, int studentID, ...); //for object construction from csv - only one supervisor but N students ...
	std::string getDescription();
	int getMaxCapacity();
	std::vector<Student*> getStudents(); //possibly return this by const ref? Force other classes to use add/remove methods for encapsulation
	Supervisor* getSupervisor();
	void setDesciption(std::string new_description);
	void addStudent(Student* to_add);
	void removeStudent(Student* to_remove);
	void setSupervisor(Supervisor* supervisor);
	bool isFull();

private:
	std::string description;
	int maxCapacity;
	std::vector<Student*> students;
	Supervisor* supervisor;
};