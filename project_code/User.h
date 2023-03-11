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
	std::string Serialise();
	void displayAllocatedProject();
	void displayMyProjectChoices();
    std::vector<Project*>& getMyProjectChoices(); 
	std::string getDegree();
	void setDegree(std::string degree);
	Project* getAllocatedProject();
	Project* findProject(Project* to_find); // O(logn)
	Project* findProject(std::string project_name);   //O(logn)
	void addProjectToPreferences(Project* project);  
	void setAllocatedProject(Project* to_allocate);
	void removeProjectFromPreferences(Project* to_remove);
	void removeProjectFromPreferences(std::string to_remove);
	bool hasProject(std::string project_name);
	int getAllocatedIdenifier();
	std::vector<int>& getPreferenceIdentifiers();


private:
	std::vector<int> preference_identifiers; //for assisting the serialisation process as pointer cannot be saved
	int allocated_identifier{ 0 }; //for assisting the serialisation process as pointer cannot be saved
	std::string degree;
	Project* allocated{ nullptr };
	std::vector<Project*> projects_choices;
};

class Supervisor :public User {

public:
	Supervisor(std::string name, std::string password, int id, std::string department); //call User constructor
	Supervisor(const std::string& csvline); //constructor for reading from csv - ... = unknown num parameters
	virtual ~Supervisor();
	std::string Serialise();
	void setDepartment(std::string department_name);
	void addProjectWorkload(Project* project_to_add);
	void removeProject(Project* to_remove);
	std::string getDepartment();
	std::vector<Project*>& getProjectsOversee();
	std::vector<int>& getProjectIdentifiers();


private:
	std::vector<int> project_identifiers; //for assisting the serialisation process as pointer cannot be saved
	std::string department;
	std::vector<Project*> projects_oversee;

};
class Admin :public User {

public:
	Admin();
	Admin(std::string name, std::string password, int id, AllocationStrategy::Strategy strat);
	virtual ~Admin(); //do DELETE the strategy object as admin controls this lifecycle
	void setAllocationStrategy(AllocationStrategy* strategy);
	void setAllocationStrategy(AllocationStrategy::Strategy strategy_type);
	AllocationStrategy* getAlloactionStrategy();
	std::string getStratID();

private:
	std::string strategy_identifier; //for assisting the serialisation process as pointer cannot be saved
	AllocationStrategy* allocate_strategy{ nullptr };
};


