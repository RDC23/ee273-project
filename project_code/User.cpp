/*EE273 Group Project
Name: User.cpp
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/

#include "User.h"
#include <stdio.h>

//METHODS FOR THE USER CLASS 

User::User() = default;

User::User(std::string name, std::string password, int id) {
	this ->full_name = name;
	this->password = password;
	this->myID = id;
}

User::~User() = default;

void Supervisor::removeProject(Project* to_remove) {
	auto& my_projs = this->projects_oversee; //get projects by ref
	//binary stl search through these projects and append if project matches the input arguments.
	auto it = std::remove_if(my_projs.begin(), my_projs.end(), [&](Project* rem) {return rem == to_remove; });
	//delete appended project.
	my_projs.erase(it, my_projs.end());
}

std::string User::getName() {
	return this->full_name;
}

std::string User::getPassword() {
	return this->password;
}

int User::getID() {
	return this->myID;
}

void User::setName(std::string name) {
	this->full_name = name;
}

void User::setPassword(std::string password) {
	this->password = password;
}

void User::setID(int id) {
	this->myID = id;
}

//METHODS FOR THE STUDENT CLASS

Student::Student(std::string name, std::string password, int id, std::string degree) : User(name, password, id) { 
	this->degree = degree;
}

Student::Student(const std::string& csvline) {
	int member_num{ 1 }; //keep track of string position.
	std::string member; //holds the csv position.
	std::stringstream ss(csvline); //holds csvline
	while (std::getline(ss, member, ',')) { //go through each csvline
		switch (member_num) { //depending on position:
		case 1:
			this->setName(member);
			break;

		case 2:
			this->setPassword(member);
			break;
		case 3:
			this->setID(stoi(member));
			break;
		case 4:
			this->setDegree(member);
			break;
		case 5:
			this->allocated_identifier = stoi(member);
			break;
		default:
			this->preference_identifiers.push_back(stoi(member));
		}
		member_num++; //increment string position 
	}
}

Student::~Student() = default;

void Student::displayMyProjectChoices() {
	if (getMyProjectChoices().size() == 0) {
		std::cout << "No projects have been added to your preferences list yet." << std::endl;
	}
	int counter = 1;
	for (auto& project : this->getMyProjectChoices()) {
		std::cout << counter << ". " << project->getTitle() << std::endl;
		counter++;
	}
}

void Student::displayAllocatedProject() {
	std::cout << this->getAllocatedProject();
}

std::vector<Project*>& Student::getMyProjectChoices() {
	return this->projects_choices;
}

std::string Student::getDegree() {
	return this->degree;
}

void Student::setDegree(std::string degree) {
	this->degree = degree;
}

Project* Student::getAllocatedProject() {
	return this->allocated;
}

Project* Student::findProject(Project* to_find) {
	auto& my_projects = this->getMyProjectChoices();
	for (auto& proj : my_projects) {
		if (proj == to_find) {
			return proj;
		}
	}
	return nullptr;
}

void Student::addProjectToPreferences(Project* project) {
	this->getMyProjectChoices().push_back(project);
}

void Student::setAllocatedProject(Project* to_allocate) {
	this->allocated = to_allocate;
	
}

bool Student::hasProject(std::string project_name){
	for (auto n : this->getMyProjectChoices()) {
		//make both lowercase to increase match chances?

		if (n->getTitle() == project_name) {
			return true;
		}
	}
	return false;
}

void Student::removeProjectFromPreferences(Project* to_remove) {
	auto& proj = this->getMyProjectChoices();//retrieve projects
	proj.erase(std::find(proj.begin(), proj.end(), to_remove));
}

void Student::removeProjectFromPreferences(std::string to_remove) {
	auto& myproj = this->getMyProjectChoices();//fetch choices
	myproj.erase(std::remove_if(myproj.begin(), myproj.end(), [&](Project* project) {
		return project->getTitle() == to_remove;
		}), myproj.end()); //find project with argument name, return iterator and
	                       //delete at this location
}

Project* Student::findProject(std::string project_name) {
	auto& ptr = this->getMyProjectChoices();
	return *std::find_if(ptr.begin(), ptr.end(), [&](Project* project) {
		return project->getTitle() == project_name;
		}); //return dereferenced iterator if project name matches argument
}

std::string Student::Serialise() {
	std::string student_string = this->getName() + ',' +
		this->getPassword() + ',' +
		std::to_string(this->getID()) + ',' +
		this->getDegree();
	
	//add an identifier for an allocated project, 0 if none exist
	if (this->getAllocatedProject() != nullptr) {
		student_string += ",";
		student_string += std::to_string(this->getAllocatedProject()->getModuleCode());
	}
	else {
		student_string += ",";
		student_string += "0";
	}
	//add the module code for each of the preferences
	for (auto& project : this->getMyProjectChoices()) {
		student_string += ",";
		student_string += std::to_string(project->getModuleCode());
	}
	return student_string;
}

int Student::getAllocatedIdenifier() {
	return this->allocated_identifier;
}

std::vector<int>& Student::getPreferenceIdentifiers() {
	return this->preference_identifiers;
}

//METHODS FOR THE SUPERVISOR CLASS

Supervisor::Supervisor(std::string name, std::string password, int id, std::string department) {
	this->setName(name); 
	this->setPassword(password);
	this->setID(id);
	this->department = department;
} 

Supervisor::Supervisor(const std::string& csvline) {
	int member_num{ 1 }; //track string position
	std::string member; 
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		switch (member_num) {

		case 1:
			this->setName(member);
			break;

		case 2:
			this->setPassword(member);
			break;
		case 3:
			this->setID(stoi(member));
			break;
		case 4:
			this->setDepartment(member);
			break;
		default:
			this->project_identifiers.push_back(stoi(member));			
		}//depending on position pass data members into new supervisor
		member_num++; //increment position
	}
} 

Supervisor::~Supervisor() {}

void Supervisor::setDepartment(std::string department_name) {
	this->department = department_name;
}

void Supervisor::addProjectWorkload(Project* project_to_add) {
	this->getProjectsOversee().push_back(project_to_add);
}

std::string Supervisor::getDepartment() {
	return this->department;
}

 std::vector<Project*>& Supervisor::getProjectsOversee() {
	 return this->projects_oversee;
}

 std::string Supervisor::Serialise() {
	 std::string supervisor_string  = this->getName() + ',' +
		 this->getPassword() + ',' +
		 std::to_string(this->getID()) + ',' +
		 this->getDepartment();

	 for (auto proj : this->getProjectsOversee()) {
		 supervisor_string += ',' + std::to_string(proj->getModuleCode());
	 }
	 return supervisor_string;
 }

 std::vector<int>& Supervisor:: getProjectIdentifiers() {
	 return this->project_identifiers;
 }

 //METHODS FOR ADMIN CLASS //only one exists!
 Admin::Admin() : User("Admin", "totalpower", 999) { //<-- this password
	 this->setAllocationStrategy(new galesShapely); // default gale shapely
 } //default admin 

 Admin::Admin(std::string name, std::string password, int id, AllocationStrategy::Strategy strat = AllocationStrategy::SIMPLE) {
	 this->setName(name);
	 this->setPassword(password);
	 this->setID(id);
	 this->setAllocationStrategy(strat);
 }

 Admin::~Admin() {
	 delete this->allocate_strategy;
 }

 void Admin::setAllocationStrategy(AllocationStrategy* strategy) {
	 if (this->allocate_strategy != nullptr) {
		 delete this->allocate_strategy;	
	 }
	 this->allocate_strategy = strategy;
 }

 void Admin::setAllocationStrategy(AllocationStrategy::Strategy strategy_type) {
	 switch (strategy_type) {
		case AllocationStrategy::GALESHAPELY:
			this->setAllocationStrategy(new galesShapely);
			break;
		case AllocationStrategy::SIMPLE:
			this->setAllocationStrategy(new simpleAllocate);
			break;
		default:
			this->setAllocationStrategy(nullptr);
	 }
 }

 AllocationStrategy* Admin::getAlloactionStrategy() {
	 return this->allocate_strategy;
 }

 std::string Admin::getStratID() {
	 return this->strategy_identifier;
 }

 

