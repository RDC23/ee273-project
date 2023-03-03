#include "Database.h"

//instantiate the singleton instance of the database 
Database* db = Database::getInstance();

Database* Database::getInstance(){ 
	if (instance == nullptr) {
		instance = new Database();
		instance->loadDBfromCSV();
	}
	return instance;
}

void Database::loadDBfromCSV() {
	std::string student, project, supervisor;
	std::ifstream StudentStream("Student.csv");
	std::ifstream ProjectStream("Project.csv");
	std::ifstream SupervisorStream("Supevisor");

	while (std::getline(StudentStream, student)) { // instantiate each student,project,teacher object 
		this->studentDB.push_back(Student(student));
	}
	while (std::getline(ProjectStream, project)) {
		this->projectDB.push_back(Project(project));
	}
	while (std::getline(StudentStream, supervisor)) {
		this->supervisorDB.push_back(Supervisor(supervisor));
	}

	for (auto &n : this->studentDB) {
		while (std::getline(StudentStream, student)) { // for each object in the vector, find the corresponding csv data
			if (Student(student).getName() == n.getName()) {                                        //and map association
				n.Associate(student);
			 }
		}
	}
	for (auto& n : this->projectDB) {
		while (std::getline(ProjectStream, project)) {
			if (Project(project).getTitle() == n.getTitle()) {      //this is genuinely the worst code ever written
				n.Associate(project);
			}
		}
	}
	for (auto& n : this->supervisorDB) {
		while (std::getline(SupervisorStream, supervisor)) { 
			if (Supervisor(supervisor).getName() == n.getName()) {                                        
				n.Associate(supervisor);
			}
		}
	}
}

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