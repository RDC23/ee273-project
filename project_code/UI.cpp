#include <algorithm>
#include "UI.h"

//User UI methods
UserUI::UserUI(DatabaseManager* dbm) {
	this->dbm = dbm;
}

//Student UI methods
StudentUI::StudentUI(Student* myStudent, DatabaseManager* dbm) : UserUI(dbm) {
	this->myStudent = myStudent;
}

void StudentUI::displayUI() {
	std::cout << "Welcome to the Project Selection Portal for Students!\n" << std::endl;
	//show all options offered in the student options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int StudentUI::getNumOptions() {
	//allows main to validate the choice of doSomething() entered by the user
	int n_options = 0;
	for (auto& option : this->options) {
		n_options++;
	}
	return n_options;
}

std::string StudentUI::getOptionName(int choice) {
	std::string optionName;
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "Invalid option.";
}

void StudentUI::doSomething(int choice) {
	switch (choice) {
		case 1:
			this->addProjectToPreferences();
			break;
		case 2:
			this->removeProject();
			break;
		case 3:
			this->viewMyProjectChoices();
			break;
		case 4:
			this->findOutMoreProject();
			break;
		case 5:
			this->reOrderProjects();
			break;
		case 6:
			this->viewAssignedProject();
			break;
		default:
			std::cout << "Invalid action..." << std::endl;
			return;
	}
}

void StudentUI::addProjectToPreferences() {
	//ensure that there is still room to add another preference
	if (!(std::size(this->myStudent->getProjectChoices()) < (this->dbm)->getProjectPickLimit()) ){
		std::cout << "You don't have space to make another project selection! The maximum number "
			"of choices is " << (this->dbm)->getProjectPickLimit() << std::endl;
		return;
	}
	std::cout << "The available projects to choose from are as follows:\n" << std::endl;
	this->dbm->printListOfProjects();
	std::string project_title;
	Project* to_find = nullptr;

	//infinite loop to get valid input data
	while (!(this->dbm->findProjectByTitle(project_title))){
		std::cout << "\nEnter the name of the project you wish to select: ";
		std::cin >> project_title;
	}
	//we have found the project, assign it to mystudent
	to_find = this->dbm->findProjectByTitle(project_title);
	this->myStudent->addProjectToPreferences(to_find);
	std::cout << "Successfully added " << to_find->getTitle() << "to your project preferences list." << std::endl;

}

void StudentUI::removeProject() {
	std::cout << "Which project would you like to remove from preferences? The projects currently selected are: \n" << std::endl;
    this->myStudent->displayProjectChoices();
	std::string choice;
	//loop until the user enters a valid project name
	while (!(this->myStudent->hasProject(choice))) {
		std::cout << "\nEnter the name of the project to remove: ";
		std::cin >> choice;
	}
	//delegate the deletion of the project to the Student class
	this->myStudent->removeProjectFromPreferences(choice);	
	std::cout << "Successfully removed project " << choice << " from your preferences." << std::endl;
}

void StudentUI::viewMyProjectChoices() {
	std::cout << "Current selected projects are:\n " << std::endl;
	this->myStudent->displayProjectChoices();
	std::cout << "\n";
}

void StudentUI::findOutMoreProject() {

}

void StudentUI::reOrderProjects() {

}


void StudentUI::viewAssignedProject() {


}