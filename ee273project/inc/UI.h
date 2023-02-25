#pragma once
#include <string>
#include <utility> //for std::pair
#include <vector>
#include "User.h"
#include "DatabaseManager.h" //provide interfaces with access to the database

//Each UI need access to:
//	1) the object it provides a UI for so it can manipulate its attributes based on user input
//	2) the DatabaseManager wrapper which provides controlled access to the database should modification be necessary be classes


//Abstract base class to allow polymorphic UI use in main (rather than writing 3 seperate programs)
class UserUI {

public:
	UserUI(DatabaseManager& dbm);
	virtual void displayUI() = 0;
	virtual int getNumOptions() = 0;
	virtual std::string getOptionName() = 0;
	virtual void doSomething() = 0;

private:
	DatabaseManager dbm; //all interfaces need controlled access to the database

};

class StudentUI : public UserUI {

public:
	StudentUI(Student* myStudent, DatabaseManager& database); //call parent contructor and pass the database parameter
	void displayUI() override;  //custom message + iterate through options vector and display choices with number
	int getNumOptions() override; //allows main to handle user input (check option is in valid range without hardcoding this
	std::string getOptionName() override;
	void doSomething() override; //handles user choice via switch case and calls appropriate function to do action (functions below)
	void selectProject();
	void removeProject();
	void viewMyProjects();
	void findOutMoreProject();
	void reOrderProjects();

private:
	Student* myStudent{ nullptr }; //allows UI to act on the student object and call appropriate getters/setters

	std::vector<std::pair<std::string, int>> options = { //add more options as required
		{"Select a project", 1},
		{"Remove a project from my choices", 2},
		{"View my project preferences", 3},
		{"Find out more about a project", 4},
		{"Re-order my project preferences", 5},
		{"Exit application", 6}
	};

};

class SupervisorUI : public UserUI { //finish implementation as above...

public:
	SupervisorUI(Supervisor* mySupervisor, DatabaseManager& database); //call parent constructor
	void displayUI() override;
	int getNumOptions() override;
	std::string getOptionName() override;
	void doSomething() override;
	
private:
	Supervisor* mySupervisor{ nullptr };

	std::vector<std::pair<std::string, int>> options = {
		{"Show my projects", 1}
	};

};

//repeat for admin and their options...