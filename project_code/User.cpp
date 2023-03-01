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

Student::Student(std::string name, std::string password, int id, std::string degree) : User(name, password, id) { 
	this->degree = degree;
}

Student::~Student() = default;

void Student::displayMyProjectChoices() {
	if (getMyProjectChoices().size() == 0) {
		std::cout << "No projects have been added to your preferences list yet." << std::endl;
	}
	for (auto n : this->getMyProjectChoices()) {
		std::cout << n->getTitle() << std::endl;
	}
}

std::vector<Project*>& Student::getMyProjectChoices() {
	return this->projects_choices;
}
std::string Student::getDegree() {
	return this->degree;
}
Project* Student::getAllocatedProject() {
	return this->allocated;
}

Project* Student::findProject(Project* to_find) { //double check this
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

		if (n->getTitle() == project_name) {
			return true;
		}
	}
	return false;
}

// erase remove idiom Scott Meyers effective c++
// Meyers, Scott (2001). Effective STL: 50 Specific Ways to Improve Your Use of the Standard Template Library. Addison-Wesley.
void Student::removeProjectFromPreferences(std::string to_remove) {
	auto& myproj = this->getMyProjectChoices();
	myproj.erase(std::remove_if(myproj.begin(), myproj.end(), [&](Project* project) {
		return project->getTitle() == to_remove;
		}), myproj.end());
}


