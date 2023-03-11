#include <algorithm>
#include <cctype>
#include "DatabaseManager.h"
#include "Project.h"
#include "User.h"
#include "Utils.h"

DatabaseManager::DatabaseManager(Database* myDatabase, int project_limit_pick) : database(myDatabase), project_limit_pick(project_limit_pick) {}

std::vector<Project*> DatabaseManager::getProjectsNotOverseen(Supervisor* sup) {
	const auto& all_projects = this->getAllProjectsReadOnly();
	const auto& sup_oversee = sup->getProjectsOversee();
	std::vector<Project*> not_oversee;

	for (auto& project : all_projects) {
		if (std::find(sup_oversee.begin(), sup_oversee.end(), project) == sup_oversee.end()) {
			//the student already hasn't already selected this project so print it
			not_oversee.push_back(project);
		}
	}
	return not_oversee;
}

DatabaseManager::~DatabaseManager() {
	delete this->database;
}

std::vector<Project*> DatabaseManager::getProjectsNotSelected(Student* student) {
	const auto& all_projects = this->getAllProjectsReadOnly();
	const auto& student_picks = student->getMyProjectChoices();
	std::vector<Project*> not_selected;

	for (auto& project : all_projects) {
		if (std::find(student_picks.begin(), student_picks.end(), project)==student_picks.end()){
			//the student already hasn't already selected this project so print it
			not_selected.push_back(project);
		}
	}
	return not_selected;
}

void DatabaseManager::printListOfProjects() {
	const auto& all_projects = this->getAllProjectsReadOnly();
	for (auto& proj : all_projects) {
		proj->simplePrint();
	}
}

User* DatabaseManager::authenticateAndFindUser() {
	User* find_user = nullptr;
	while (!find_user) {
		clearScreen();
		std::cout << "LOGIN PORTAL" << std::endl;
		printLineSep();
		std::cout << "\nWelcome to the login portal for project selection." << std::endl;
		int login_id = getValidInteger("\nEnter your unique ID: ");
		std::string password = getValidString("\nEnter your password: ");
		find_user = this->database->findUserWithCredentials(login_id, password);

		if (!find_user) {
			std::cout << "\nLogin unsuccessful! Either your username or password are incorrect.\n";
			pause();
		}
	}
	return find_user;
}


int DatabaseManager::getProjectPickLimit() {
	return this->project_limit_pick;
}

const std::vector<Project*>& DatabaseManager::getAllProjectsReadOnly() {
	return this->database->getProjects();
}

Project* DatabaseManager::findProjectByTitle(std::string title) {
	auto& all_projects = this->database->getProjects();
	//compare the strings both in lowercase for best search compatibility
	std::string s = title;
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });

	for (auto& proj : all_projects) {
		std::string proj_name = proj->getTitle();
		std::transform(proj_name.begin(), proj_name.end(), proj_name.begin(), [](unsigned char c) { return std::tolower(c); });
		
		if (s == proj_name) {
			return proj;
		}
	}
	//no project with this name found so return null pointer
	return nullptr;
}

Project* DatabaseManager::findProjectByModcode(int modcode) {
	auto& all_projects = this->database->getProjects();
	for (auto& proj : all_projects) {
		if (proj->getModuleCode() == modcode) {
			return proj;
		}
	}
	return nullptr;
}

bool DatabaseManager::isValidProjectTitle(const std::string title) {
	auto& all_projects = this->getAllProjectsReadOnly();
	//compare the strings both in lowercase for best search compatibility
	std::string s = title;
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	for (auto& proj : all_projects) {
		std::string proj_name = proj->getTitle();
		std::transform(proj_name.begin(), proj_name.end(), proj_name.begin(), [](unsigned char c) { return std::tolower(c); });
	
		if (s == proj_name) {
			return true;
		}
	}
	//no project with this name found so return false
	return false;

}