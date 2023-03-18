/*EE273 Group Project
Name: Database.h
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/

#pragma once
#include <fstream>
#include "AllocationStrategy.h"
#include "User.h"
#include "Database.h"

class Database{

public:
	Database(); //load in from csv and then construct the associations for each object
	virtual ~Database(); //implement logic to save all data to csv then free all pointer data
	void loadDBfromCSV();
	void LoadDB_THREAD();
	void saveDB_THREAD();
	void saveDBtoCSV();
	Student* getStudent(std::string name);
	Supervisor* getSupervisor(std::string name);
	Project* getProject(std::string name);
	Student* findStudentByRegnum(int regnum);
	Supervisor* findSupervisorByRegnum(int regnum);
	std::vector<Student*>& getStudents();
	std::vector<Project*>& getProjects();
	std::vector<Supervisor*>& getSupervisors();
	Admin* getAdmin();
	User* findUserWithCredentials(int username, std::string password);

private:	
	Database(const Database&); //prevent multiple instances being created due to copy construction
	std::vector<Student*> studentDB;
	std::vector<Supervisor*> supervisorDB;
	std::vector<Project*> projectDB;
	Admin systemAdmin;
};