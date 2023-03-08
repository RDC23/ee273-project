#include <unordered_map>
#include <thread>
#include "Database.h"

Database::Database() {
	//when the database is created, load in all the pre-existing data
	this->LoadDB_THREAD();
}

Database::~Database() {
	this->saveDBtoCSV();

	//FREE ALL DYNAMIC MEMORY!!!!!!!!
}

void Database::loadDBfromCSV() {
	//initialise stream variables and strings to hold intermediate strings for object constructors
	std::string student, project, supervisor;
	std::ifstream StudentStream("Student.csv");
	std::ifstream ProjectStream("Project.csv");
	std::ifstream SupervisorStream("Supervisor.csv");

	//initialise a map of student, project, and staff identifier to object for o(n) lookup
	std::unordered_map<int, Supervisor*> id_to_supervisor;
	std::unordered_map<int, Student*> id_to_student;
	std::unordered_map<int, Project*> id_to_project;

	//instantiate each student and add to map
	while (std::getline(StudentStream, student)) {
		studentDB.push_back(new Student(student));
		//add id and student to map
		id_to_student[studentDB.back()->getID()] = studentDB.back();
	}

	//instantiate each supervisor and add to map

	while (std::getline(SupervisorStream, supervisor)) {
		supervisorDB.push_back(new Supervisor(supervisor));
		//add id and supervisor to map
		id_to_supervisor[supervisorDB.back()->getID()] = supervisorDB.back();
	}

	//instantiate each project and add to map
	while (std::getline(ProjectStream, project)) {
		projectDB.push_back(new Project(project));
		//add id and supervisor to map
		id_to_project[projectDB.back()->getModuleCode()] = projectDB.back();
	}

	//map the associations for students
	for (auto& student : this->studentDB) {
		//set the allocated project attribute
		if (id_to_project.count(student->getAllocatedIdenifier())) { //project still exists
			student->setAllocatedProject(id_to_project[student->getAllocatedIdenifier()]);
		}
		else {
			student->setAllocatedProject(nullptr);
		}
		//set the preferred projects if they still exist
		for (auto& id : student->getPreferenceIdentifiers()) {
			if (id_to_project.count(id)) {
				student->addProjectToPreferences(id_to_project[id]);
			}
		}
	}

	//map the associations for supervisors
	for (auto& supervisor : this->supervisorDB) {
		//set the oversee project attribute
		for (auto& id : supervisor->getProjectIdentifiers()) {
			if (id_to_project.count(id)) {
				supervisor->addProjectWorkload(id_to_project[id]);
			}
		}
	}

	//map the associations for projects
	for (auto& project : projectDB) {
		//set the supervisor oversee attribute
		project->setSupervisor(id_to_supervisor[project->getSupervisorIdentifier()]);
		//set the students taking attribute
		for (auto& id : project->getStudentIdentifiers()) {
			if (id_to_student.count(id)) {
				project->addStudent(id_to_student[id]);
			}
		}
	}
}

User* Database::findUserWithCredentials(int username, std::string password) {
	User* person = nullptr;
	//check the student database for a match
	for (auto& student : this->studentDB) {
		if ((student->getID() == username) && (student->getPassword() == password) ){
			return student;
		}
	}
	//check the supervisor database for a match
	for (auto& supervisor : this->supervisorDB) {
		if ((supervisor->getID() == username) && (supervisor->getPassword() == password)) {
			return supervisor;
		}
	}
	//check if these match the admin credentials
	if ((username == this->systemAdmin.getID()) && (password == this->systemAdmin.getPassword())){
		return &(this->systemAdmin);
	}
	//no match, return a nullptr
	return nullptr;
}

void Database::saveDBtoCSV() {
	std::ofstream StudentStream("Student.csv"); //open files streams for each user class
	std::ofstream ProjectStream("Project.csv");
	std::ofstream SupervisorStream("Supervisor.csv");

	for (auto& n : this->getStudents()) {  //go through each object of each vector and assign them as  serialised strings 
		                                   //to the corresponding file stream
		StudentStream << n->Serialise() << "\n";
	}
	for (auto& n : this->getProjects()) {

		ProjectStream << n->Serialise() << "\n";
	}
	for (auto& n : this->getSupervisors()) {

		SupervisorStream << n->Serialise() << "\n";
	}
}
Student* Database::getStudent(std::string name) {
	auto& student_db = this->studentDB;
	auto stud_loc = std::find_if(student_db.begin(), student_db.end(), [&](Student* student) {
		return student->getName() == name; });
	if (stud_loc != student_db.end()) {
		return *stud_loc;
	}
	return nullptr;	
}

Supervisor* Database::getSupervisor(std::string name) {
	auto& sup_db = this->supervisorDB;
	auto sup_loc = std::find_if(sup_db.begin(), sup_db.end(), [&](Supervisor* supervisor) {
		return supervisor->getName() == name; });
	if (sup_loc != sup_db.end()) {
		return *sup_loc; //deref iterator and return adderess of project in project DB vector
	}
	return nullptr;
}

Student* Database::findStudentByRegnum(int regnum) {
	auto student_loc = std::find_if(studentDB.begin(), studentDB.end(), [&](Student* student) {return student->getID() == regnum;});
	//if we have not found student, return nullptr, else the student pointer
	if (student_loc != studentDB.end()) {
		return *student_loc;
	}
	return nullptr;
}

Project* Database::getProject(std::string name) {
	//returns a pointer to a project in the database
	auto& proj_db = this->projectDB;
	auto project_loc = std::find_if(proj_db.begin(), proj_db.end(), [&](Project* project) {
		return project->getTitle() == name; });
	if (project_loc != proj_db.end()) {
		//project has been found, return its address
		return *project_loc;
	}
	return nullptr; //we have not found the project
}

Admin* Database::getAdmin() {
	return &this->systemAdmin;
}

std::vector<Project*>& Database::getProjects() {
	return this->projectDB;
}

std::vector<Student*>& Database::getStudents() {
	return this->studentDB;
}
std::vector<Supervisor*>& Database::getSupervisors() {
	return this->supervisorDB;
}

void Database::LoadDB_THREAD() {
	//initialise stream variables and strings to hold intermediate strings for object constructors
	std::string student, project, supervisor;
	std::ifstream StudentStream("Student.csv");
	std::ifstream ProjectStream("Project.csv");
	std::ifstream SupervisorStream("Supervisor.csv");

	//initialise a map of student, project, and staff identifier to object for o(n) lookup
	std::unordered_map<int, Supervisor*> id_to_supervisor;
	std::unordered_map<int, Student*> id_to_student;
	std::unordered_map<int, Project*> id_to_project;

	//here, student,supervisor & project instantiation in the database in split into three parallel operations.
	// student instatiation thread.
	std::thread instantiateStudent([&] 
		{ while (std::getline(StudentStream, student)) {
		studentDB.push_back(new Student(student));
		//add id and student to map
		id_to_student[studentDB.back()->getID()] = studentDB.back();
	}
		}
	);

	
	//supervisor instantiation thread
	std::thread instantiateSupervisor([&] {
		while (std::getline(SupervisorStream, supervisor)) {
			supervisorDB.push_back(new Supervisor(supervisor));
			//add id and supervisor to map
			id_to_supervisor[supervisorDB.back()->getID()] = supervisorDB.back();
		}
		}
	);

	//instantiate each project and add to map
	std::thread instantiateProject([&] {
		while (std::getline(ProjectStream, project)) {
			projectDB.push_back(new Project(project));
			//add id and supervisor to map
			id_to_project[projectDB.back()->getModuleCode()] = projectDB.back();
		}
		}
	);
	// wait for all loops to execute, then merge processes into the main thread.
	instantiateStudent.join();
	instantiateSupervisor.join();
	instantiateProject.join();

	//map the associations for students
	std::thread AssociateStudents([&] {
		for (auto& student : this->studentDB) {
			//set the allocated project attribute
			if (id_to_project.count(student->getAllocatedIdenifier())) { //project still exists
				student->setAllocatedProject(id_to_project[student->getAllocatedIdenifier()]);
			}
			else {
				student->setAllocatedProject(nullptr);
			}
			//set the preferred projects if they still exist
			for (auto& id : student->getPreferenceIdentifiers()) {
				if (id_to_project.count(id)) {
					student->addProjectToPreferences(id_to_project[id]);
				}
			}
		}
		}
	);

	//map the associations for supervisors
	std::thread AssociateSupervisors([&] {
		for (auto& supervisor : this->supervisorDB) {
			//set the oversee project attribute
			for (auto& id : supervisor->getProjectIdentifiers()) {
				if (id_to_project.count(id)) {
					supervisor->addProjectWorkload(id_to_project[id]);
				}
			}
		}
		}
	);

	//map the associations for projects
	std::thread AssociateProjects([&] {
		for (auto& project : projectDB) {
			//set the supervisor oversee attribute
			project->setSupervisor(id_to_supervisor[project->getSupervisorIdentifier()]);
			//set the students taking attribute
			for (auto& id : project->getStudentIdentifiers()) {
				if (id_to_student.count(id)) {
					project->addStudent(id_to_student[id]);
				}
			}
		}
		}
	);
	AssociateStudents.join();
	AssociateSupervisors.join();
	AssociateProjects.join();
}

void Database::saveDB_THREAD() {
	std::ofstream StudentStream("Student.csv"); //open files streams for each user class
	std::ofstream ProjectStream("Project.csv");
	std::ofstream SupervisorStream("Supervisor.csv");

	std::thread saveStudents([&] {
		for (auto& n : this->getStudents()) {  //go through each object of each vector and assign them as  serialised strings 
			//to the corresponding file stream
			StudentStream << n->Serialise() << "\n";
		}
		}
	);
	std::thread saveProjects([&] {
		for (auto& n : this->getProjects()) {

			ProjectStream << n->Serialise() << "\n";
		}
		}
	);

	std::thread saveSupervisors([&] {
		for (auto& n : this->getSupervisors()) {

			SupervisorStream << n->Serialise() << "\n";
		}
		}
	);
	saveStudents.join();
	saveProjects.join();
	saveSupervisors.join();
}

