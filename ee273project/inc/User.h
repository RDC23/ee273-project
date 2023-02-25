#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "AllocationStrategy.h"

class User  { 

public:
	User(std::string name, std::string password, int id);
	virtual ~User(); //important so that correct destructor is called for derived classes
	std::string getName();
	std::string getPassword();
	int getID();
	void setName(std::string name);
	void setPassword(std::string password);
	void setID(int id);

private:
	std::string name;
	std::string password;
	int myID;
};

class Student :public User {

public:
	Student(std::string name, std::string password, int id, std::string degree); //call the User constructor
	Student(std::string name, std::string password, int id, std::string degree, int allocatedID, ...); //constructor for reading from csv
	virtual ~Student(); //no need to free memory as lifetime of pointed to object managed by Database
	void displayProjectChoices();	
	void displyAllocatedProject();
	const std::vector<Project*>& getProjectChoices(); //again, make const ref as the client code shouldn't directly modify this?
	std::string getDegree();
	Project* getAllocatedProject();
	void addProjectToPreferences(Project* project);
	void setAllocatedProject(Project* to_allocate);

private:
	std::vector<Project*> projects_choices;
	std::string degree;
	Project* allocated;
};

class Supervisor :public User {

public:
	Supervisor(std::string name, std::string password, int id, std::string department); //call User constructor
	Supervisor(std::string name, std::string password, int id, std::string department, ...); //constructor for reading from csv - ... = unknown num parameters
	virtual ~Supervisor();
	void setDepartment(std::string department_name);
	void addProjectWorkload(Project* project_to_add);
	void removeProjectWorkload(Project* project_to_remove);
	std::string getDepartment();
	const std::vector<Project*>& getProjectsOversee();

private:
	std::string department;
	std::vector<Project*> projects_oversee;

};

class Admin :public User {

public:
	Admin(std::string name, std::string password, int id, AllocationStrategy::Strategy strat);
	virtual ~Admin(); //do DELETE the strategy object as admin controls this lifecycle
	void setAllocationStrategy(AllocationStrategy* strategy);
	AllocationStrategy* getAlloactionStrategy();

private:
	AllocationStrategy* allocate_strategy{ nullptr };
};


//define function overloads for cout?