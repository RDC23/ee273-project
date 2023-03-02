#include "User.h"
#include <stdio.h>


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

Student::Student(const std::string& csvline) {
	int member_num{ 1 };
	std::string member;
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		switch (member_num) {

		case 1:
			this->setName(member);
			break;

		case 2:
			this->setPassword(member);
			break;
		case 3:
			this->setID(stoi(member));
			break;
		case 4:
			this->setDegree(member);
			break;
		default:
			break;
		}
		member_num++;
	}
}

Student::~Student() = default;

void Student::displayMyProjectChoices() {
	if (getMyProjectChoices().size() == 0) {
		std::cout << "No projects have been added to your preferences list yet." << std::endl;
	}
	for (auto& project : this->getMyProjectChoices()) {
		std::cout << project->getTitle() << std::endl;
	}
}

void Student::displayAllocatedProject() {
	std::cout << this->getAllocatedProject();
}

std::vector<Project*>& Student::getMyProjectChoices() {
	return this->projects_choices;
}

std::string Student::getDegree() {
	return this->degree;
}
<<<<<<< HEAD
void Student::setDegree(std::string degree) {
=======

std::string Student::setDegree(std::string degree) {
>>>>>>> c45b9bbb6c253bfccd16fdb7f98c0be99c6eb360
	this->degree = degree;
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

void Student::removeProjectFromPreferences(Project* to_remove) {
	auto& proj = this->getMyProjectChoices();
	proj.erase(std::find(proj.begin(), proj.end(), to_remove));
}

void Student::removeProjectFromPreferences(std::string to_remove) {
	auto& myproj = this->getMyProjectChoices();
	myproj.erase(std::remove_if(myproj.begin(), myproj.end(), [&](Project* project) {
		return project->getTitle() == to_remove;
		}), myproj.end());
}

Project* Student::findProject(std::string project_name) {
	auto& ptr = this->getMyProjectChoices();
	return *std::find_if(ptr.begin(), ptr.end(), [&](Project* project) {
		return project->getTitle() == project_name;
		});
}
void Student::Associate(const std::string& csvline) {
	int member_num{ 1 };
	std::string member;
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		if (member_num == 5) {
			this->setAllocatedProject(DB.getProject(member));
		}
		else if(member_num > 5) {
			this->addProjectToPreferences(DB.getProject(member));
		}
		member_num++;
	}
}
std::string Student::Serialise() {
	std::string ans = this->getName() + ',' +
		this->getPassword() + ',' +
		std::to_string(this->getID()) + ',' +
		this->getDegree();
	for (auto n : this->getMyProjectChoices()) {
		ans += ',' + n->getTitle();
 }
	return ans;

}

Supervisor::Supervisor(std::string name, std::string password, int id, std::string department) {
	this->setName(name);
	this->setPassword(password);
	this->setID(id);
	this->department = department;
} 

Supervisor::Supervisor(const std::string& csvline) {
	int member_num{ 1 };
	std::string member;
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		switch (member_num) {

		case 1:
			this->setName(member);
			break;

		case 2:
			this->setPassword(member);
			break;
		case 3:
			this->setID(stoi(member));
			break;
		case 4:
			this->setDepartment(member);
			break;
		default:
			break;
		}
	}
} 

Supervisor::~Supervisor() {

}

void Supervisor::setDepartment(std::string department_name) {
	this->department = department;
}

void Supervisor::addProjectWorkload(Project* project_to_add) {
	this->getProjectsOversee().push_back(project_to_add);
}

std::string Supervisor::getDepartment() {
	return this->department;
}

 std::vector<Project*>& Supervisor::getProjectsOversee() {
	 return this->projects_oversee;
}
 void Supervisor::Associate(const std::string& csvline) {
	 int member_num{ 1 };
	std::string member;
	std::stringstream ss(csvline);
	while (std::getline(ss, member, ',')) {
		if (member_num < 4) {
			this->addProjectWorkload(DB.getProject(member));
		}
		member_num++;
	}
 }
 std::string Supervisor::Serialise() {
	 std::string ans = this->getName() + ',' +
		 this->getPassword() + ',' +
		 std::to_string(this->getID()) + ',' +
		 this->getDepartment();
	 for (auto n : this->getProjectsOversee()) {
		 ans += ',' + n->getTitle();
	 }
	 return ans;

 }
 Admin::Admin(std::string name, std::string password, int id, AllocationStrategy::Strategy strat) {
	 this->setName(name);
	 this->setPassword(password);
	 this->setID(id);
	 //this->allocate_strategy->SIMPLE;  //not sure what to assign here...

 }

 Admin::~Admin() {
	 delete this->allocate_strategy;
 }

 void Admin::setAllocationStrategy(AllocationStrategy* strategy) {
	 this->allocate_strategy = strategy;
 }

 void Admin::setAllocationStrategy(AllocationStrategy::Strategy strategy_type) {
	 switch (strategy_type) {
		case AllocationStrategy::GALESHAPELY:
			this->setAllocationStrategy(new galesShapely);
			break;
		case AllocationStrategy::SIMPLE:
			this->setAllocationStrategy(new simpleAllocate);
			break;
		default:
			this->setAllocationStrategy(nullptr);
	 }
 }

 AllocationStrategy* Admin::getAlloactionStrategy() {
	 return this->allocate_strategy;
 }

 std::string Project::Serialise() {
	 Supervisor* p = this->getSupervisor();
	 std::string ans = this->getTitle() + ',' +
		 std::to_string(this->getModuleCode()) + ',' +
		 this->getDescription() + ',' +
		 std::to_string(this->getMaxCapacity()) + ',' +
		 this->getSupervisor()->getName();
	 for (auto n : this->getStudents()) {
		 ans += ',' + n->getName();
	 }
	 return ans;
 }
 void Project::Associate(const std::string& csvline) {
	 int member_num{ 1 };
	 std::string member;
	 std::stringstream ss(csvline);
	 while (std::getline(ss, member, ',')) {
		 if (member_num == 5) {
			 this->setSupervisor(DB.getSupervisor(member));
		 }
		 else if (member_num > 5) {
			 this->addStudent(DB.getStudent(member));
		 }
		 member_num++;
	 }

 }

