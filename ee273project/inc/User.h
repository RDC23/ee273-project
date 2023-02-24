#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "AllocationStrategy.h"
class User  { 

public:
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
	void displayProjectChoices();	
	void displyAllocatedProject();
	std::vector<Project*> getProjectChoices(); //again, make const ref as the client code shouldn't directly modify this?
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


private:
	std::string department;
	std::vector<Project> projects_oversee;

};

class Admin :public User {

private:
	AllocationStrategy* allocate_strategy{ nullptr };
};


//define function overloads for cout?