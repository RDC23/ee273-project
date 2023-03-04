#include "Project.h"
#include "User.h"
#include "Utils.h"

Project::Project(std::string title, int module_code, std::string description, int capacity)
{
	this->title = title;
	this->module_code = module_code;
	this->description = description;
	this->maxCapacity = capacity;
}

Project::Project(const std::string& csvline) {
	int member_num{ 1 };
	std::string member;
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		switch (member_num) {

		case 1:
			this->setTitle(member);
			break;

		case 2:
			this->setModuleCode(stoi(member));
			break;
		case 3:
			this->setDesciption(member);
			break;
		case 4:
			this->setMaxCapacity(stoi(member));
			break;
		case 5:
			this->supervisor_identifier = stoi(member);
			break;
		default:
			this->student_identifiers.push_back(stoi(member));
		}
		member_num++;
	}
}

Project::~Project()
{
	// destructor implementation goes here
}

std::string Project::getDescription() {
	
	return this->description;
}

int Project::getMaxCapacity() {
	return this->maxCapacity;
}

std::vector<Student*>& Project::getStudents() {
	return this->students;
}

Supervisor* Project::getSupervisor() {
	return this->supervisor;
}

std::string Project::getTitle() const{
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

void Project::setDesciption(std::string new_description){
	this->description = new_description;
}
void Project::setMaxCapacity(int capacity) {
	this->maxCapacity = capacity;
}

void Project::addStudent(Student* to_add){
	this->getStudents().push_back(to_add);
}

Student* Project::findStudent(Student* to_find) {
	auto& ptr = this->getStudents();
    return *find(ptr.begin(), ptr.end(), to_find);
}

void Project::removeStudent(Student* to_remove){
	auto& ptr = this->getStudents();
	this->getStudents().erase(std::find(ptr.begin(),ptr.end(),to_remove)); //double check this
}

void Project::setSupervisor(Supervisor* supervisor) {
	this->supervisor = supervisor;
}

bool Project::isFull() {
	return (std::size(this->students) >= this->maxCapacity);
}

std::string Project::Serialise() {
	//save all the definite fields in comma seperated format
	std::string serial_string = this->getTitle() + ',' +
		std::to_string(this->getModuleCode()) + ',' +
		this->getDescription() + ',' +
		std::to_string(this->getMaxCapacity()) + ',' +
		std::to_string(this->getSupervisor()->getID());

	//save the remaining projects
	for (auto& student : this->getStudents()) {
		serial_string += ',' + std::to_string(student->getID());
	}
	return serial_string;
}

void Project::simplePrint() const {
	std::cout << this->title << std::endl;
}

void Project::prettyPrint() {
	std::cout << this->getTitle() << " : (Module Code " << this->getModuleCode() << ")" << std::endl;
	printLineSep();
	std::cout << "Supervisor: " << this->getSupervisor()->getName() << std::endl;
	std::cout << "Project description: ";
	std::cout << this->getDescription() << std::endl;
	std::cout << "Capacity: " << this->getMaxCapacity() << " students.\n" << std::endl;
}

int Project::getSupervisorIdentifier() {
	return this->supervisor_identifier;
}


std::vector<int> Project::getStudentIdentifiers() {
	return this->student_identifiers;
}



