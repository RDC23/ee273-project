#include "Project.h"
#

Project::Project(std::string title, int module_code, std::string description, int capacity)
{
	this->title = title;
	this->module_code = module_code;
	this->description = description;
	this->maxCapacity = capacity;
}

Project::Project(const std::string& csvline)
{
	// constructor implementation goes here
}

Project::~Project()
{
	// destructor implementation goes here
}

std::string Project::getDescription() {
	
	return this->description;
}

int Project::getMaxCapacity() {
	// function implementation goes here
	return this->maxCapacity;
}

std::vector<Student*>& Project::getStudents() {
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
	this->module_code = module_code;
}

void Project::setDesciption(std::string new_description)
{
	this->description = new_description;
}

void Project::addStudent(Student* to_add)
{
	this->getStudents().push_back(to_add);
}
std::vector<Student*>::iterator Project::findStudent(Student* to_find) {

	auto ptr = this->getStudents();
	return find(ptr.begin(), ptr.end(), to_find);
}
void Project::removeStudent(Student* to_remove)
{
	this->getStudents().erase(this->findStudent(to_remove)); //double check this
}

void Project::setSupervisor(Supervisor* supervisor)
{
	this->supervisor = supervisor;
}

bool Project::isFull() {
	return (std::size(this->students) >= this->maxCapacity);
}

