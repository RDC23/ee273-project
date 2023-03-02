#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "AllocationStrategy.h"

class User  { 

public:
	User();
	User(std::string name, std::string password, int id);
	virtual ~User(); //important so that correct destructor is called for derived classes
	std::string getName();
	std::string getPassword();
	int getID();
	void setName(std::string name);
	void setPassword(std::string password);
	void setID(int id);
private:
	std::string full_name;
	std::string password;
	int myID;
};

class Student :public User { 

public:
	Student(std::string name, std::string password, int id, std::string degree); //call the User constructor
	Student(const std::string& cvsline); //constructor for reading from csv
	virtual ~Student(); //no need to free memory as lifetime of pointed to object managed by Database	
	void Deserialise(const std::string& csvline);
	void displayAllocatedProject();
	void displayMyProjectChoices();
    std::vector<Project*>& getMyProjectChoices(); 
	std::string getDegree();
	std::string setDegree(std::string degree);
	Project* getAllocatedProject();
	Project* findProject(Project* to_find);
	Project* findProject(std::string project_name); //get project pointer to access in vector
	void addProjectToPreferences(Project* project);
	void setAllocatedProject(Project* to_allocate);
	void removeProjectFromPreferences(Project* to_remove);
	void removeProjectFromPreferences(std::string to_remove);
	bool hasProject(std::string project_name); //check if this is in the project_choices vector 

private:
	std::string degree;
	Project* allocated{ nullptr };
	std::vector<Project*> projects_choices;
};

class Supervisor :public User {

public:
	Supervisor(std::string name, std::string password, int id, std::string department); //call User constructor
	Supervisor(const std::string& csvline); //constructor for reading from csv - ... = unknown num parameters
	virtual ~Supervisor();
	void Deserialise(const std::string& csvline);
	void setDepartment(std::string department_name);
	void addProjectWorkload(Project* project_to_add);
	std::string getDepartment();
	std::vector<Project*>& getProjectsOversee();
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


