#pragma once
#include "Project.h"
#include "User.h"

class Database {

public:
	Database(); //implement logic to 'load' the database from a csv file
	virtual ~Database(); //save all data to csv then free all pointer data
	void showProjects();
	void listStudents();
	void listStaff();

private:
	std::vector<Student> studentDB;
	std::vector<Supervisor> supervisorDB;
	std::vector<Project> projectDB;

};