#include "UI.h"

UserUI::UserUI(DatabaseManager* dbm) {
	this->dbm = dbm;
}

StudentUI::StudentUI(Student* myStudent, DatabaseManager* dbm) : UserUI(dbm) {
	this->myStudent = myStudent;
}

void StudentUI::displayUI() {
	std::cout << "Welcome to the Project Selection Portal for Students!\n" << std::endl;

	for (auto option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int StudentUI::getNumOptions() {
	int n_options = 0;
	for (auto option : this->options) {
		n_options++;
	}
	return n_options;
}

std::string StudentUI::getOptionName(int choice) {
	std::string optionName;
	for (auto option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
}

void StudentUI::doSomething(int choice) {
	//switch
}