#pragma once
#include "Database.h"

//force classes to use the database manager to control (and limit) access to the database object as per project specification

class DatabaseManager {

public:
	DatabaseManager(Database* myDatabase, int project_limit_pick);
	virtual ~DatabaseManager();
	void printListOfProjects();
	int getProjectPickLimit();
	Project* findProjectByTitle(std::string title);  //format both strings as lower/upper to not make case sensitive
	Project* findProjectByModcode(int modcode);


private:
	Database* database{ nullptr };
	int project_limit_pick = 0;


};
