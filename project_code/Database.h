#pragma once
#include "Project.h"
#include "User.h"

//employ singleton design pattern to ensure only one database instance ever exists in program state
//https://refactoring.guru/design-patterns/singleton/cpp/example

class Database {

public:
	static Database getInstance(); //if instance null then call loadDBcsv function, else return instance as demonstrated below
	//	{
	// if (instance == nullptr) {
	//		instance = new Database();
	//		instance->loadDBfromCSV;
	//	}
	//	return instance;
	//}
	void loadDBfromCSV();
	Student* getStudent(std::string name);
	Supervisor* getSupervisor(std::string name);
	Project* getProject(std::string name);

private:
	static Database* instance;
	
	Database();
	virtual ~Database(); //implement logic to save all data to csv then free all pointer data
	Database(const Database&); //prevent multiple instances being created due to copy construction
	std::vector<Student> studentDB;
	std::vector<Supervisor> supervisorDB;
	std::vector<Project> projectDB;

};

//initialise the static instance variable as null in the Database.cpp file (doing so in header would create multiple instances
//for every #inlcude, defeating purpose of singleton pattern
Database DB; // this is just for now, it can go somewhere else later when load function is finished
