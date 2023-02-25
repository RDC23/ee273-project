#pragma once
#include "Database.h"

//force classes to use the database manager to control (and limit) access to the database object as per project specification

class DatabaseManager {

public:
	DatabaseManager(Database& myDatabase);
	virtual ~DatabaseManager();


private:
	Database database{ nullptr };


};
