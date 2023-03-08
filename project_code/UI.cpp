#include <algorithm>
#include <unordered_map>
#include "UI.h"
#include "Utils.h"

//User UI methods

UserUI::UserUI(DatabaseManager* dbm) {
	this->dbm = dbm;
}

//Student UI methods

StudentUI::StudentUI(Student* myStudent, DatabaseManager* dbm) : UserUI(dbm), myStudent(myStudent) {};

void StudentUI::displayUI() {
	clearScreen();
	std::cout << "Welcome to the Project Selection Portal for Students, " <<myStudent->getName()<< std::endl;
	printLineSep();
	//show all options offered in the student options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
	printLineSep();
}

int StudentUI::getNumOptions() {
	//allows main to validate the choice of doSomething() entered by the user
	return int((this->options).size());
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
		case 7:
			std::cout << "See you again!" << std::endl;
			return;
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
		return;
	}
	//show the available projects to pick from
	std::cout << "\nThe available projects to choose from are as follows:\n" << std::endl;
	dbm->printProjectsNotSelected(this->myStudent);

	//loop until valid data is provided checking for quit or invalid data
	bool quit = false;
	while (!quit) {
		std::string projectTitle;
		projectTitle = getValidString("\nEnter the title of a project to add (or 'Q' to quit): ");
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
		return; //omit this line for infinite loop, check with Kishan

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
	std::cout << "Successfully removed project \"" << choice << "\" from your preferences." << std::endl;
}

void StudentUI::viewMyProjectChoices() {
	if ((myStudent->getMyProjectChoices()).size() < 1) {
		std::cout << "\nYou haven't added any projects to your preferences list yet" << std::endl;
		pause();
		return;
	}

	std::cout << "\nCurrently selected projects are:\n " << std::endl;
	myStudent->displayMyProjectChoices();
	pause();
}

void StudentUI::findOutMoreProject() {
	std::cout << "\nWhich project would you like to find out more details about?"
		" The projects currently being offered are:\n" << std::endl;
	//create a map (associative array) of int to project
	auto& projects_available = dbm->getAllProjectsReadOnly();
	std::unordered_map<int, Project*> int_to_project;	

	//populate the map for easy indexing
	for (int i = 1; i <= projects_available.size(); i++){
		int_to_project[i] = projects_available[i-1];
	}
	//show the number and project
	for (auto& enumerated_project : int_to_project) {
		std::cout << enumerated_project.first << ". " << enumerated_project.second->getTitle() << std::endl;
	}

	//loop till quit
	bool exit = false;
	while (!exit) {
		//get valid integer and print the details or an error message if non valid
		int choice = getValidInteger("\nEnter the number corresponding with the project you want to view more details about (or '0' to quit): ");
		if (int_to_project.count(choice)) {
			int_to_project[choice]->prettyPrint();
			pause();
			return; //omit this line for infinite loop, check with Kishan
		}
		if (choice == 0) {
			std::cout << "Exiting to main menu." << std::endl;
			exit = true;
			pause();
			break;
		}
		else{
			std::cout << "That isn't a valid project number. " << std::endl;
		}
	}
}

void StudentUI::reOrderProjects() {
	auto& myprojects = myStudent->getMyProjectChoices();
	//no choices
	if (myprojects.size() < 1) {
		std::cout << "No projects have been selected." << std::endl;
		return;
	}
	//only one choice, no swaps possible
	if (myprojects.size() == 1) {
		std::cout << "You have only got one project in your preferences list. No swaps are possible." << std::endl;
		return;
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
	std::swap(myprojects.at(--from), myprojects.at(--to));
}
	

void StudentUI::viewAssignedProject() {
	if (myStudent->getAllocatedProject() == nullptr) {
		std::cout << "You have not yet been allocated any project by a supervisor." << std::endl;
		return;
	}
	std::cout << "You have been assigned to \"" << myStudent->getAllocatedProject() << "\"." << std::endl;
}

//Supervisor UI methods

SupervisorUI::SupervisorUI(Supervisor* mySupervisor, DatabaseManager* dbm) : UserUI(dbm), mySupervisor(mySupervisor) {};

void SupervisorUI::displayUI() {
	std::cout << "Welcome to the Project Selection Portal for Supervisors!\n" << std::endl;
	//show all options offered in the supervisor options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int SupervisorUI::getNumOptions() {
	return int((this->options).size());
};

std::string SupervisorUI::getOptionName(int choice) {
	std::string optionName;
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "Invalid option.";
}

void SupervisorUI::doSomething(int choice) {
	switch (choice) {
		case 1:
			this->showProjectsOversee();
			break;
		case 2:
			this->getProjectToEdit();
			break;
		default:
			std::cout << "An invalid choice was entered" << std::endl;
	}
}

void SupervisorUI::showProjectsOversee() {
	std::cout << "You are currently a supervisor for the following projects:\n" << std::endl;
	const auto& my_projs = mySupervisor->getProjectsOversee();
	for (auto& proj : my_projs) {
		std::cout << proj->getTitle() << std::endl;
	}
}

void SupervisorUI::editProjectMetadata(Project* to_edit) {
	//implement this function
	std::cout << "Implement me!";
}

void SupervisorUI::getProjectToEdit() {
	std::cout << "You are currently supervising the following projects:\n" << std::endl;
	//create a map (associative array) of int to project
	auto& projects_available = mySupervisor->getProjectsOversee();
	std::unordered_map<int, Project*> int_to_project;

	//populate the map for easy indexing
	for (int i = 1; i <= projects_available.size(); i++) {
		int_to_project[i] = projects_available[i-1];
	}
	//show the number and project
	for (auto& enumerated_project : int_to_project) {
		std::cout << enumerated_project.first << ". " << enumerated_project.second->getTitle() << std::endl;
	}
	bool exit = false;
	while (!exit) {
		//get the project to edit
		int choice = getValidInteger("\nEnter the number of the project you wish to edit the metadata of (or '0' to exit):");
		if (choice == 0) {
			std::cout << "Exiting the project editor and returning to the main menu." << std::endl;
			exit = true;
			return;
		}
		if (int_to_project.count(choice)) { //it exists therefore a valid input 
			editProjectMetadata(int_to_project[choice]);
			return;
		}
		else {
			std::cout << "Project number entered isn't valid. Please try again or exit." << std::endl;
		}
	}
}

//Admin UI methods

AdminUI::AdminUI(Admin* admin, DatabaseManager* dbm, Database* db) : UserUI(dbm), myAdmin(admin), db(db) {};

void AdminUI::displayUI() {
	std::cout << "Welcome to the Project Selection Portal for Admins!\n" << std::endl;
	//show all options offered in the admin options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int AdminUI::getNumOptions() {
	return int((this->options).size());
};

std::string AdminUI::getOptionName(int choice) {
	std::string optionName;
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "Invalid option.";
}

void AdminUI::doSomething(int choice) {
	switch (choice) {
	case 1:
		this->automaticAllocate();
		break;	
	case 2:
		this->swapAllocationStrategy();
		break;
	case 3:
		this->editStudent();
		break;
	case 4:
		this->editSupervisor();
		break;
	case 5:
		this->editProject();
		break;
	case 6:
		std::cout << "See you again!" << std::endl;
		return;
	default:
		std::cout << "Invalid action..." << std::endl;
		return;
	}

}

void AdminUI::swapAllocationStrategy() {
	auto allocation_current = myAdmin->getAlloactionStrategy();

	if (allocation_current == nullptr) {
		//the admin has no strategy so none to swap (this should never happen)
		std::cout << "\nYou don't have any preferred method for sorting the students." << std::endl;
		return;
	}
	
	std::cout << "Which allocation approach would you like to use? The options are:\n" << std::endl;

	///FINISH
}

Project* AdminUI::getValidProject(std::string prompt) {
	Project* proj = nullptr;
	while (proj == nullptr) {
		std::string title = getValidString(prompt);
		proj = dbm->findProjectByTitle(title);
		if (proj == nullptr) {
			std::cout << "\nA project with that name wasn't found." << std::endl;
		}
	}
	return proj;
}

void AdminUI::editStudentMetadata(Student* student_to_edit) {
	clearScreen();
	std::vector<std::string> options = { "Name", "Password", "ID", "Allocated Project" };

	std::cout << "What data belonging to " << student_to_edit->getName() << " would you like to edit?\n" << std::endl;
	for (int i = 0; i<options.size(); i++){
		std::cout << i+1 << ". " << options[i] << std::endl;
	}
	bool exit = false;
	while (!exit) {
		int choice = getValidInteger("\nEnter the number of the field to edit (or 0 to exit): ");
		if (choice < 0 || choice > options.size()) {
			std::cout << "\nThe number you entered does not match any provided in the options. Please try again." << std::endl;
		}
		switch (choice) {
			case(0):
				std::cout << "Exiting to the main menu." << std::endl;
				return;
			case(1):
				//edit the name
				std::cout << "\nWhat should " << student_to_edit->getName() << "'s name be changed to?" << std::endl;
				student_to_edit->setName(getValidString("\nEnter the new name: "));
				return;
				break;
			case(2):
				//edit the password
				std::cout << "\nWhat should " << student_to_edit->getName() << "'s password be changed to?" << std::endl;
				student_to_edit->setPassword(getValidString("\nEnter the new password: "));
				return;
				break;
			case(3):
				//edit the ID
				std::cout << "\nWhat should " << student_to_edit->getName() << "'s ID be changed to (integer code only) ?" << std::endl;
				student_to_edit->setID(getValidInteger("\nEnter the new password: "));
				return;
				break;
			case(4):
				//edit the project allocated
				std::cout << student_to_edit->getName() << " has been allocated: ";
				if (student_to_edit->getAllocatedProject() == nullptr) {
					std::cout << "No project.";
				}
				else {
					std::cout << student_to_edit->getAllocatedProject()->getTitle();
				}
				std::cout << "\nWhat should the new project allocation be? The available choices are:\n";
				dbm->printListOfProjects();
				student_to_edit->setAllocatedProject(getValidProject("\nEnter the name of a project to allocate this student: "));
				return;
		}
	}
}

void AdminUI::editSupervisorMetadata(Supervisor* supervisor_to_edit) {

}

void AdminUI::editProjectMetadata(Project* project_to_edit) {

}

void AdminUI::editStudent() {
	clearScreen();
	std::cout << "\nWhich student would you like to edit? The students currently in the database are: " << std::endl;
	printLineSep();
	for (auto& student : this->db->getStudents()) {
		std::cout << student->getName() << " : " << student->getID() << std::endl;
	}
	bool exit = false;
	while (!exit) {
		int reg = getValidInteger("\nEnter the ID of the student you want to edit: ");
		Student* student_to_loc = db->findStudentByRegnum(reg);

		if (student_to_loc) {
			editStudentMetadata(student_to_loc); //delegate the editing
			break;
		}
		else {
			std::cout << "Unable to locate a student with that registration number." << std::endl;
		}
	}
}

void AdminUI::editSupervisor() {
	//implement
}

void AdminUI::editProject() {
	//implement
}


void AdminUI::automaticAllocate() {
	std::cout << "Allocating students automatically...\n" << std::endl;
	//call the allocation strategy class, passing it the database
	myAdmin->getAlloactionStrategy()->allocate(db);	
}


