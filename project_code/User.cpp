#include "User.h"
#include <vector>

User::User() = default;

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

//Student::Student(const std::string& csvline) {

	//TODO


//}
Student::~Student() = default;
void Student::displayAllocatedProject() {

	std::cout << this->getAllocatedProject();
}
void Student::displayProjectChoices() {
	for (auto n : *this->getProjectChoices()) {
		std::cout << n->getTitle();
	}
}

 std::vector<Project*>* Student::getProjectChoices() {
	return &this->projects_choices;
}
std::string Student::getDegree() {
	return this->degree;
}
Project* Student::getAllocatedProject() {
	return this->allocated;
}
 std::vector<Project*>::iterator Student::findProject(Project* to_find) { //double check this
	std::vector<Project*>* ptr = this->getProjectChoices();
	return std::find(ptr->begin(), ptr->end(), to_find);
}

 std::vector<Project*>::iterator Student::findProject(std::string to_find) {
	 std::vector<Project*>* ptr = this->getProjectChoices();
	 return std::find_if(ptr->begin(), ptr->end(), hasTitle(to_find));
 }
		
	

void Student::addProjectToPreferences(Project* project) {

	this->getProjectChoices()->push_back(project);
}
void Student::setAllocatedProject(Project* to_allocate) {

	this->allocated = to_allocate;
}
void Student::removeProjectFromPreferences(Project* to_remove) {
	
	this->getProjectChoices()->erase(this->findProject(to_remove));
	
}
bool Student::hasProject(std::string project_name){
	for (auto n : *this->getProjectChoices()) {

		if (n->getTitle() == project_name) {
			return true;
		}
	}
	return false;
}

void Student::removeProjectFromPreferences(std::string to_remove) {
	this->getProjectChoices()->erase(findProject(to_remove));
}


