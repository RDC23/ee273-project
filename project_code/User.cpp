#include "User.h"
#include <vector>
User::User(std::string name, std::string password, int id) {
	this ->full_name = name;
	this->password = password;
	this->myID;
}

User::~User() = default;

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

Student::Student(std::string name, std::string password, int id, std::string degree) { //unsure how to resolve?
	this->setName(name);
	this->setPassword(password);
	this->setID(id);
	this->degree = degree;
}

Student::Student(const std::string& csvline) {

	//TODO


}
Student::~Student() = default;
void Student::displayAllocatedProject();
void Student::displayProjectChoices();

std::vector<Project*>& Student::getProjectChoices() {
	return this->projects_choices;
}
std::string Student::getDegree() {
	return this->degree;
}
Project* Student::getAllocatedProject() {
	return this->allocated;
}
void Student::addProjectToPreferences(Project* project) {

	this->projects_choices.push_back(project); // not sure why this is accessible?
}
void Student::setAllocatedProject(Project* to_allocate) {

	this->allocated = to_allocate;
}
void Student::removeProjectFromPreferences(Project* to_remove) {
	
	
	
}
void Student::removeProjectFromPreferences(std::string to_remove);
bool Student::hasProject(std::string project_name);

