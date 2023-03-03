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
	auto& student_db = this->studentDB;
	auto stud_loc = std::find_if(student_db.begin(), student_db.end(), [&](Student& student) {
		return student.getName() == name; });
	if (stud_loc != student_db.end()) {
		return &*stud_loc;
	}
	return nullptr;	
}
Supervisor* Database::getSupervisor(std::string name) {
	auto& sup_db = this->supervisorDB;
	auto sup_loc = std::find_if(sup_db.begin(), sup_db.end(), [&](Supervisor& supervisor) {
		return supervisor.getName() == name; });
	if (sup_loc != sup_db.end()) {
		return &*sup_loc; //deref iterator and return adderess of project in project DB vector
	}
	return nullptr;
}

Project* Database::getProject(std::string name) {
	//returns a pointer to a project in the database
	auto& proj_db = this->projectDB;
	auto project_loc = std::find_if(proj_db.begin(), proj_db.end(), [&](Project& project) {
		return project.getTitle() == name; });
	if (project_loc != proj_db.end()) {
		//project has been found, return its address
		return &*project_loc;
	}
	return nullptr; //we have not found the project
}