#pragma once
#include "Project.h"
#include "User.h"

class Database {

public:
	Database(); //implement logic to 'load' the database from a csv file
	virtual ~Database();
	void showProjects();
	void listStudents();
	void listStaff();

private:
	std::vector<Student> studentDB;
	std::vector<Supervisor> supervisorDB;
	std::vector<Project> projectDB;

	//provide the Admin with direct access to all attributes of Student and Supervisor
	friend class Admin;
};
