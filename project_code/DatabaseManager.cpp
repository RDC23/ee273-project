#include <algorithm>
#include <cctype>
#include "DatabaseManager.h"
#include "Project.h"
#include "User.h"

DatabaseManager::DatabaseManager(Database* myDatabase, int project_limit_pick) : database(myDatabase), project_limit_pick(project_limit_pick) {}

DatabaseManager::~DatabaseManager() {
	delete this->database;
}

void DatabaseManager::printProjectsNotSelected(Student* student) {
	const auto& all_projects = this->getAllProjectsReadOnly();
	const auto& student_picks = student->getMyProjectChoices();

	for (auto& project : all_projects) {
		if (std::find(student_picks.begin(), student_picks.end(), &project)==student_picks.end()){
			//the student already hasn't already selected this project so print it
			project.simplePrint();
		}
	}
}

void DatabaseManager::printListOfProjects() {
	const auto& all_projects = this->getAllProjectsReadOnly();
	for (auto& proj : all_projects) {
		proj.simplePrint();
	}
}

int DatabaseManager::getProjectPickLimit() {
	return this->project_limit_pick;
}

const std::vector<Project>& DatabaseManager::getAllProjectsReadOnly() {
	return this->database->getProjects();
}

Project* DatabaseManager::findProjectByTitle(std::string title) {
	auto& all_projects = this->database->getProjects();
	//compare the strings both in lowercase for best search compatibility
	std::string s = title;
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });

	for (auto& proj : all_projects) {
		std::string proj_name = proj.getTitle();
		std::transform(proj_name.begin(), proj_name.end(), proj_name.begin(), [](unsigned char c) { return std::tolower(c); });
		
		if (s == proj_name) {
			return &proj;
		}
	}
	//no project with this name found so return null pointer
	return nullptr;
}

Project* DatabaseManager::findProjectByModcode(int modcode) {
	auto& all_projects = this->database->getProjects();
	for (auto& proj : all_projects) {
		if (proj.getModuleCode() == modcode) {
			return &proj;
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
		std::string proj_name = proj.getTitle();
		std::transform(proj_name.begin(), proj_name.end(), proj_name.begin(), [](unsigned char c) { return std::tolower(c); });
	
		if (s == proj_name) {
			return true;
		}
	}
	//no project with this name found so return false
	return false;

}