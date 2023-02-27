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
	std::string getName() { return this->full_name; }
	std::string getPassword() { return this->password; }
	int getID() { return this->myID; }
	void setName(std::string name) { this->full_name = name; }
	void setPassword(std::string password) { this->password = password; }
	void setID(int id) {this->myID = id;}

private:
	std::string full_name;
	std::string password;
	int myID;
};

class Student :public User { 

public:
	Student(std::string name, std::string password, int id, std::string degree); //call the User constructor
	Student(std::string name, std::string password, int id, std::string degree, int allocatedID, ...); //constructor for reading from csv
	virtual ~Student(); //no need to free memory as lifetime of pointed to object managed by Database
	void displayProjectChoices();	
	void displayAllocatedProject();
	const std::vector<Project*>& getProjectChoices(); //again, make const ref as the client code shouldn't directly modify this?
	std::string getDegree() { return this->degree; }
	Project* getAllocatedProject() { return this->allocated; }
	void addProjectToPreferences(Project* project);
	void setAllocatedProject(Project* to_allocate) { this->allocated = to_allocate; }

private:
	std::string degree;
	Project* allocated;
	std::vector<Project*> projects_choices;
};

class Supervisor :public User {

public:
	Supervisor(std::string name, std::string password, int id, std::string department); //call User constructor
	Supervisor(std::string name, std::string password, int id, std::string department, ...); //constructor for reading from csv - ... = unknown num parameters
	virtual ~Supervisor();
	void setDepartment(std::string department_name) { this->department = department_name; }
	void addProjectWorkload(Project* project_to_add);
	std::string getDepartment() { return this->department; }
	const std::vector<Project*>& getProjectsOversee() { return this->projects_oversee; }

private:
	std::string department;
	std::vector<Project*> projects_oversee;

};

class Admin :public User {

public:
	Admin(std::string name, std::string password, int id, AllocationStrategy::Strategy strat);
	virtual ~Admin(); //do DELETE the strategy object as admin controls this lifecycle
	void setAllocationStrategy(AllocationStrategy* strategy) { this->allocate_strategy = strategy; }
	AllocationStrategy* getAlloactionStrategy() { return this->allocate_strategy; }

private:
	AllocationStrategy* allocate_strategy{ nullptr };
};


