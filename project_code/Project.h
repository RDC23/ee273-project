#pragma once
#include <vector>
#include <string>
#include "Project.h"

class Student;
class Supervisor;

class Project { 

public:
	Project(std::string title, int module_code, std::string description, int capacity);
	Project(const std::string& csvline); //for object construction from csv - only one supervisor but N students ...
	virtual ~Project(); //no need to free memory as database object manages lifetime of the Student, Supervisors etc
	std::string getDescription();
	int getMaxCapacity();
    std::vector<Student*>& getStudents(); //possibly return this by const ref? Force other classes to use add/remove methods for encapsulation
	std::vector<Student*>::iterator findStudent(Student* to_find);
	Supervisor* getSupervisor();
	std::string getTitle();
	int getModuleCode();
	void setTitle(std::string title);
	void setModuleCode(int module_code);
	void setDesciption(std::string new_description);
	void addStudent(Student* to_add);
	void removeStudent(Student* to_remove);
	void setSupervisor(Supervisor* supervisor);
	bool isFull();

private:
	std::string title{ "" };
	int module_code{ 0 };
	std::string description{ "" };
	int maxCapacity{ 0 };
	std::vector<Student*> students;
	Supervisor* supervisor{ nullptr };
};



