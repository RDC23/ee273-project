#include "Database.h"

//declare singleton instance of the database 
Database* db = Database::getInstance();

Database* Database::getInstance(){ 
	if (instance == nullptr) {
		instance = new Database();
		instance->loadDBfromCSV();
	}
	return instance;
}

void loadDBfromCSV();

Student* Database::getStudent(std::string name) {
	std::vector<Student>* ptr = &this->studentDB;
	return &*std::find_if(ptr->begin(), ptr->end(), [&](Student student) {
		return student.getName() == name; });
	
}
Supervisor* Database::getSupervisor(std::string name) {
	std::vector<Supervisor>* ptr = &this->supervisorDB;
	return &*std::find_if(ptr->begin(), ptr->end(), [&](Supervisor supervisor) {
		return supervisor.getName() == name; });

}
Project* Database::getProject(std::string name) {
	std::vector<Project>* ptr = &this->projectDB;
	return &*std::find_if(ptr->begin(), ptr->end(), [&](Project project) {
		return project.getTitle() == name; });
}