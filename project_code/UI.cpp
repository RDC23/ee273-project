#include <algorithm>
#include "UI.h"
#include "Utils.h"

//User UI methods
UserUI::UserUI(DatabaseManager* dbm) {
	this->dbm = dbm;
}

//Student UI methods
StudentUI::StudentUI(Student* myStudent, DatabaseManager* dbm) : UserUI(dbm), myStudent(myStudent) {};

void StudentUI::displayUI() {
	std::cout << "Welcome to the Project Selection Portal for Students!\n" << std::endl;
	//show all options offered in the student options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int StudentUI::getNumOptions() {
	//allows main to validate the choice of doSomething() entered by the user
	return (this->options).size();
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
	int projectPickLimit = dbm->getProjectPickLimit();
	auto& currentPreferences = myStudent->getMyProjectChoices();

	//ensure that the student has room for another project
	if (currentPreferences.size() >= projectPickLimit) {
		std::cout << "You have reached the maximum number of project choices ("
			<< projectPickLimit << ").\nReturning to the main menu." << std::endl;

		//show the available projects to pick from
		std::cout << "The available projects to choose from are as follows:" << std::endl;
		dbm->printProjectsNotSelected(this->myStudent);

		//loop until valid data is provided checking for quit or invalid data
		bool quit = false;
		while (!quit) {
			std::string projectTitle;
			std::cout << "Enter the title of a project to add (or 'Q' to quit): ";
			std::cin >> projectTitle;

			if (projectTitle == "Q" || projectTitle == "q") {
				std::cout << "Returning to the main menu." << std::endl;
				quit = true;
				continue;
			}
			if (!dbm->isValidProjectTitle(projectTitle)) {
				std::cout << "Invalid project title. Please try again." << std::endl;
				continue;
			}
			Project* project = dbm->findProjectByTitle(projectTitle);
			if (!project) {
				std::cout << "Unable to find project with title \"" << projectTitle << "\". Please try again." << std::endl;
				continue;
			}
			if (myStudent->hasProject(projectTitle)) {
				std::cout << "Project \"" << projectTitle << "\" is already in your project preferences." << std::endl;
				continue;
			}
			//project is found so add to student preferences
			this->myStudent->addProjectToPreferences(project);
			std::cout << "Successfully added project \"" << projectTitle << "\" to your preferences." << std::endl;
		}
	}
}

void StudentUI::removeProject(){
	//make sure choices are not empty
	if (myStudent->getMyProjectChoices().size() == 0) {
		std::cout << "You have not selected any projects so there are none to remove." << std::endl;
		return;
	}

	std::cout << "Which project would you like to remove from your preferences? The projects currently selected are: \n" << std::endl;
	myStudent->displayMyProjectChoices();	

	//loop until the user enters a valid project name from those in their selections
	std::string choice;
	bool valid_choice = false;
	while (!valid_choice) {
		choice = getValidString("Enter the name of the project you wish to remove from your preferences: ");
		if (choice == "Q" || choice == "q") {
			std::cout << "Returning to the main menu." << std::endl;
			return;
		}
		if (!this->myStudent->hasProject(choice)) {
			std::cout << "Invalid project name. Please try again." << std::endl;
		}
		else {
			valid_choice = true;
		}

	}
	//delegate the deletion of the project to the Student class
	myStudent->removeProjectFromPreferences(choice);
	std::cout << "Successfully removed project " << choice << " from your preferences." << std::endl;
}

void StudentUI::viewMyProjectChoices() {
	std::cout << "Current selected projects are:\n " << std::endl;
	myStudent->displayMyProjectChoices();
	std::cout << "\n";
}

void StudentUI::findOutMoreProject() {

}

void StudentUI::reOrderProjects() {
	auto& myprojects = myStudent->getMyProjectChoices();
	//no choices
	if (myprojects.size() < 1) {
		std::cout << "No projects have been selected." << std::endl;
	}
	//only one choice, no swaps possible
	if (myprojects.size() == 1) {
		std::cout << "You have only got one project in your preferences list. No swaps are possible." << std::endl;
	}
	std::cout << "Your currently selected projects, in order of preference are:\n " << std::endl;
	myStudent->displayMyProjectChoices();

	int from{ 0 };
	int to{ 0 };

	//get from location
	while (from <= 0 || from > myprojects.size()) {
		from = getValidInteger("Enter the number of the project you wish to swap: ");
		if (from <= 0 || from > myprojects.size()) {
			std::cout << "You don't have a project choice number " << from << ". Please try again." << std::endl;
		}		
	}
	//get to location
	while (to <= 0 || to > myprojects.size()) {
		to = getValidInteger("Enter the number of the project you wish to swap it with: ");
		if (to <= 0 || to > myprojects.size()) {
			std::cout << "You don't have a project choice number " << to << ". Please try again." << std::endl;
		}
	}

	//perform the swap (decrement index due to 0 indexed vector)
	std::swap(myprojects.at(from--), myprojects.at(to--));
}
	

void StudentUI::viewAssignedProject() {
	std::cout << "You have been assigned to \"" << myStudent->getAllocatedProject() << "\"." << std::endl;
}