#pragma once
#include "Database.h"

//force classes to use the database manager to control (and limit) access to the database object as per project specification
//provides utility functions for classes to interact with the dataabase

class DatabaseManager {

public:
	DatabaseManager(Database* myDatabase, int project_limit_pick=3);
	virtual ~DatabaseManager();
	void printProjectsNotSelected(Student* student); //show all projects not in the student's preferences
	void printListOfProjects();
	int getProjectPickLimit();
	const std::vector<Project*>& getAllProjectsReadOnly();
	Project* findProjectByTitle(std::string title);  //format both strings as lower/upper to not make case sensitive
	Project* findProjectByModcode(int modcode);
	bool isValidProjectTitle(const std::string title);


private:
	Database* database{ nullptr };
	int project_limit_pick = 0;


};
