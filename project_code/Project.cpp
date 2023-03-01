#include "Project.h"
#

Project::Project(std::string title, int module_code, std::string description, int capacity)
{
	// constructor implementation goes here
}

Project::Project(std::string title, int module_code, std::string description, int capacity, int supervisorID, int studentID, ...)
{
	// constructor implementation goes here
}

Project::~Project()
{
	// destructor implementation goes here
}

std::string Project::getDescription() {
	// function implementation goes here
	return "";
}

int Project::getMaxCapacity() {
	// function implementation goes here
	return 1;
}

std::vector<Student*> Project::getStudents() {
	return this->students;
}

Supervisor* Project::getSupervisor() {
	return this->supervisor;
}

std::string Project::getTitle(){
	return this->title;
}

int Project::getModuleCode(){
	return this->module_code;
}

void Project::setTitle(std::string title) {
	this->title = title;
}

void Project::setModuleCode(int module_code)
{
	// function implementation goes here
}

void Project::setDesciption(std::string new_description)
{
	// function implementation goes here
}

void Project::addStudent(Student* to_add)
{
	// function implementation goes here
}

void Project::removeStudent(Student* to_remove)
{
	// function implementation goes here
}

void Project::setSupervisor(Supervisor* supervisor)
{
	// function implementation goes here
}

bool Project::isFull() {
	return (std::size(this->students) >= this->maxCapacity);
}

