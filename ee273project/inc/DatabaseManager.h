#pragma once
#include "Database.h"

//force classes to use the database manager to control (and limit) access to the database object as per project specification

class DatabaseManager {

public:
	DatabaseManager(Database& myDatabase);
	virtual ~DatabaseManager();
	Student* findStudentInDB(int ID);
	Student* findStudentInDB(std::string full_name);
	Project* findProject(int module_code);
	Project* findProject(std::string proj_name);


private:
	Database* database{ nullptr };


};