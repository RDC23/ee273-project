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
	void saveDBtoCSV();
	Student* getStudent(std::string name);
	Supervisor* getSupervisor(std::string name);
	Project* getProject(std::string name);
	Student* findStudentByRegnum(int regnum);
	std::vector<Student*>& getStudents();
	std::vector<Project*>& getProjects();
	std::vector<Supervisor*>& getSupervisors();
	Admin* getAdmin();

private:	
	Database(const Database&); //prevent multiple instances being created due to copy construction
	std::vector<Student*> studentDB;
	std::vector<Supervisor*> supervisorDB;
	std::vector<Project*> projectDB;
	Admin systemAdmin;
};