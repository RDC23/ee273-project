#pragma once
#include <string>
#include <vector>
#include "Project.h"
class User  { //All need methods


private:
	std::string name;
	std::string password;
	int regID;
};

class Student :public User {

	

private:
	std::vector<Project*> projects_choices;
	std::string degree;
	Project allocated;
};

class Supervisor :public User {


private:
	std::string department;
	std::vector<Project> projects_oversee;

};

class Admin :public User {

private:
	//Allocation Strategy??
};