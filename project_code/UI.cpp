/*EE273 Group Project
Name: UI.cpp
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/


#include <algorithm>
#include <unordered_map>
#include <thread>
#include "UI.h"
#include "Utils.h"

//User UI methods
//---------------------------------------------------------------------------------------------------------------

UserUI::UserUI(DatabaseManager* dbm) {
	this->dbm = dbm;
}

//Student UI methods
//---------------------------------------------------------------------------------------------------------------

StudentUI::StudentUI(Student* myStudent, DatabaseManager* dbm) : UserUI(dbm), myStudent(myStudent) {};

void StudentUI::displayUI() {
	//print customised welcome message and loop through available options
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
	//allows main to validate the range of the choice of doSomething() entered by the user
	return int((this->options).size());
}

std::string StudentUI::getOptionName(int choice) {
	//indexes the hash map using the second (numeric value) to return the first string value (option name)
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "Invalid option.";
}

void StudentUI::doSomething(int choice) {
	//acts as a multiplexer to call the appropriate UI function based on the user input
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
			//exit statement to return to main menu
			std::cout << "See you again!" << std::endl;
			return;
		default:
			std::cout << "Invalid action..." << std::endl;
			return;
	}
}

void StudentUI::addProjectToPreferences() {
	//loops through the current projects the student has and provides a numerical method
	//for adding new projects

	int projectPickLimit = dbm->getProjectPickLimit();
	auto& currentPreferences = myStudent->getMyProjectChoices();

	//ensure that the student has room for another project
	if (currentPreferences.size() >= projectPickLimit) {
		std::cout << "\nYou have reached the maximum number of project choices ("
			<< projectPickLimit << ")\n.\nReturning to the main menu.\n" << std::endl;
		pause();
		return;
	}

	//create a map (associative array) of int to project
	auto projects_available = dbm->getProjectsNotSelected(this->myStudent);
	std::unordered_map<int, Project*> int_to_project;

	//populate the map for easy indexing
	for (int i = 1; i <= projects_available.size(); i++) {
		int_to_project[i] = projects_available[i - 1];
	}
	//show the number and respective project
	std::cout << "\n";
	for (auto& enumerated_project : int_to_project) {
		std::cout << enumerated_project.first << ". " << enumerated_project.second->getTitle() << std::endl;
	}

	//loop till quit
	bool exit = false;
	while (!exit) {
		//get valid integer and print the details or an error message if non valid
		int choice = getValidInteger("\nEnter the number corresponding with the project you want to add to your preferences (or '0' to quit): ");
		if (int_to_project.count(choice)) {
			myStudent->addProjectToPreferences(int_to_project[choice]);
			std::cout << "\nSucessfully added \"" << int_to_project[choice]->getTitle() << "\" to your preferences" << std::endl;
			pause();
			return;
		}
		if (choice == 0) {
			std::cout << "\nExiting to main menu." << std::endl;
			exit = true;
			pause();
			break;
		}
		else {
			std::cout << "That isn't a valid project number. " << std::endl;
		}
	}
}

void StudentUI::removeProject() {
	//provides an enumerated method of removing a project from those in preference list

	//make sure choices are not empty
	if (myStudent->getMyProjectChoices().size() == 0) {
		std::cout << "\nYou have not selected any projects so there are none to remove." << std::endl;
		pause();
		return;
	}
	//create a map (associative array) of int to project
	auto& my_projects = myStudent->getMyProjectChoices();
	std::unordered_map<int, Project*> int_to_project;

	//populate the map for easy indexing
	for (int i = 1; i <= my_projects.size(); i++) {
		int_to_project[i] = my_projects[i - 1];
	}
	//show the number and project
	std::cout << "\n";
	for (auto& enumerated_project : int_to_project) {
		std::cout << enumerated_project.first << ". " << enumerated_project.second->getTitle() << std::endl;
	}

	//loop till quit
	bool exit = false;
	while (!exit) {
		//get valid integer and print the details or an error message if non valid
		int choice = getValidInteger("\nEnter the number corresponding with the project you want to remove from your preferences (or '0' to quit): ");
		if (int_to_project.count(choice)) {
			myStudent->removeProjectFromPreferences(int_to_project[choice]);
			std::cout << "\nSucessfully removed \"" << int_to_project[choice]->getTitle() << "\" from your preferences" << std::endl;
			pause();
			return;
		}
		if (choice == 0) {
			std::cout << "\nExiting to main menu." << std::endl;
			exit = true;
			pause();
			break;
		}
		else {
			std::cout << "That isn't a valid project number. " << std::endl;
		}
	}
}

void StudentUI::viewMyProjectChoices() {
	//loop through project preferences and display these to the console
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
	//displays a more detailed description of the selected project (e.g. the name, description)
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
	//allows the user to edit the order of projects in their preferences list

	auto& myprojects = myStudent->getMyProjectChoices();
	//handle no choices case + early return
	if (myprojects.size() < 1) {
		std::cout << "\nNo projects have been selected." << std::endl;
		return;
	}
	//only one choice, no swaps possible
	if (myprojects.size() == 1) {
		std::cout << "\nYou have only got one project in your preferences list. No swaps are possible." << std::endl;
		return;
	}
	std::cout << "\nYour currently selected projects, in order of preference are:\n " << std::endl;
	myStudent->displayMyProjectChoices();

	int from{ 0 };
	int to{ 0 };

	//get from location
	while (from <= 0 || from > myprojects.size()) {
		from = getValidInteger("\nEnter the number of the project you wish to swap: ");
		if (from <= 0 || from > myprojects.size()) {
			std::cout << "\nYou don't have a project choice number " << from << ". Please try again." << std::endl;
		}		
	}
	//get to location
	while (to <= 0 || to > myprojects.size()) {
		to = getValidInteger("\nEnter the number of the project you wish to swap it with: ");
		if (to <= 0 || to > myprojects.size()) {
			std::cout << "\nYou don't have a project choice number " << to << ". Please try again." << std::endl;
		}
	}

	//perform the swap (decrement index due to 0 indexed vector)
	std::swap(myprojects.at(--from), myprojects.at(--to));
	std::cout << "\nSuccessfully swapped \"" << myprojects.at(to)->getTitle()  << "\" and \"" << myprojects.at(from)->getTitle() << "\".";
	pause();
}	

void StudentUI::viewAssignedProject() {
	//display the name of the assigned project (or inform user that none have been allocated)
	if (myStudent->getAllocatedProject() == nullptr) {
		std::cout << "\nYou have not yet been allocated any project yet. Please check back later!" << std::endl;
		pause();
		return;
	}
	std::cout << "\nYou have been assigned to \"" << myStudent->getAllocatedProject()->getTitle() << "\"." << std::endl;
	pause();
}

//Supervisor UI methods
//------------------------------------------------------------------------------------------------------------------------------

SupervisorUI::SupervisorUI(Supervisor* mySupervisor, DatabaseManager* dbm) : UserUI(dbm), mySupervisor(mySupervisor) {};

void SupervisorUI::displayUI() {
	//print customised welcome message and loop through available options
	std::cout << "Welcome to the Project Selection Portal for Supervisors, " << mySupervisor->getName() << "!\n" << std::endl;
	//show all options offered in the supervisor options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int SupervisorUI::getNumOptions() {
	//returns the number of available options
	return int((this->options).size());
};

std::string SupervisorUI::getOptionName(int choice) {
	//return string key in map (project name from number)
	std::string optionName;
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "\nInvalid option.";
}

void SupervisorUI::doSomething(int choice) {
	//call function based on the user input
	switch (choice) {
		case 1:
			this->showProjectsOversee();
			break;
		case 2:
			this->getProjectToEdit();
			break;
		case 3:
			std::cout << "\nSigning out..." << std::endl;
			pause();
			return;
		default:
			std::cout << "\nAn invalid choice was entered" << std::endl;
			pause();
	}
}

void SupervisorUI::showProjectsOversee() {
	//display the name and students in the projects overseen by the supervisor
	std::cout << "\nYou are currently a supervisor for the following projects:\n" << std::endl;
	const auto& my_projs = mySupervisor->getProjectsOversee();
	//print project and students taking
	for (int i = 0; i < my_projs.size(); i++) {
		std::cout << i + 1 << ". " << (my_projs[i])->getTitle() << std::endl;
		std::cout << "\nStudents Assigned:";
		my_projs[i]->printStudents();
		std::cout << "\n";
	}
	std::cout << "\n";
	pause();
}

void SupervisorUI::editProjectMetadata(Project* to_edit) { 
	//provides a method to edit a projects' metadata
	std::unordered_map<int, std::string> attributes{ { 1, "Title" }, {2, "Max Capacity"}, {3, "Module code"}, {4,"Description"} };
	std::cout << "\n";
	for (auto& attribute : attributes) {
		std::cout << attribute.first << ": " << attribute.second << std::endl;
	}
	int choice = 0;
	bool exit = false;
	while (!exit) {
		int edit_num = getValidInteger("\nEnter the number corresponding to the project data you want to edit (or '0' to exit):");
		if (edit_num <0 || edit_num>attributes.size()) {
			std::cout << "That's not a valid number, please try again." << std::endl;
		}
		switch (edit_num) {

		case(0):
			std::cout << "Exiting the project editor and returning to the main menu." << std::endl;
			exit = true;
			pause();
			return;

			return;

			case(1):
				to_edit->setTitle(getValidString("\nEnter the new title for this project: "));
				std::cout << "\nChange to module title successful." << std::endl;
				pause();
				return;
			case(2):
				std::cout << "This project can currently hold " << to_edit->getMaxCapacity() << " students.\n" << std::endl;
				to_edit->setMaxCapacity(getValidInteger("\nEnter the new maximum limit of students who can take this module: ")); 
				std::cout << "\nChange to module capacity successful." << std::endl;
				pause();
				return;
			case(3):
				std::cout << "The current module code for this project is '" << to_edit->getModuleCode() << "'.\n" << std::endl;
				to_edit->setModuleCode(getValidInteger("\nEnter the new module code of this module: "));
				std::cout << "\nChange to module code successful." << std::endl;
				pause();
				return;
			case(4):
				std::cout << "The current description for this project is: '" << to_edit->getDescription() << "'.\n" << std::endl;
				to_edit->setDesciption(getValidString("\nEnter the new description for this project: "));
				std::cout << "\nChange to module description successful." << std::endl;
				pause();
				return;
		}
	}
}

void SupervisorUI::getProjectToEdit() {
	//provides a numerical method of retrieving the project to edit

	std::cout << "\nYou are currently supervising the following projects:\n" << std::endl;
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
			pause();
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
//-----------------------------------------------------------------------------------------------------------------------

AdminUI::AdminUI(Admin* admin, DatabaseManager* dbm, Database* db) : UserUI(dbm), myAdmin(admin), db(db) {};

void AdminUI::displayUI() {
	//show the admin welcome message and available options
	std::cout << "Welcome to the Project Selection Portal for Admins!\n" << std::endl;
	//show all options offered in the admin options vector attribute
	for (auto& option : this->options) {
		std::cout << option.second << ". " << option.first << std::endl;
	}
}

int AdminUI::getNumOptions() {
	//return the options count which are available
	return int((this->options).size());
};

std::string AdminUI::getOptionName(int choice) {
	//return the key of the hash map
	std::string optionName;
	for (auto& option : this->options) {
		if (option.second == choice) {
			return option.first;
		}
	}
	return "Invalid option.";
}

void AdminUI::doSomething(int choice) {
	//call the function based on the choice entered by the user
	switch (choice) {
	case 1:
		this->automaticAllocate();
		break;	
	case 2:
		this->swapAllocationStrategy();
		break;
	case 3:
		this->resetStudentAllocation();
		break;
	case 4:
		this->editStudent();
		break;
	case 5:
		this->editSupervisor();
		break;
	case 6:
		this->editProject();
		break;
	case 7:
		this->createNew();
		break;
	case 8:
		this->showStudentsAndAllocations();
		break;
	case 9:
		std::cout << "See you again!" << std::endl;
		pause();
		return;
	default:
		std::cout << "Invalid action..." << std::endl;
		pause();
		return;
	}

}

void AdminUI::resetStudentAllocation() {
	//for every student, remove the project allocated field. For every project, remove the allocated students

	//clear the students allocated field
	for (auto& student : db->getStudents()) {
		student->setAllocatedProject(nullptr);
	}
	//clear the project allocated students field
	for (auto& proj : db->getProjects()) {
		proj->getStudents().clear();
	}
	std::cout << "\nSuccessfully reset the project allocation.\n" << std::endl;
	pause();
}

void AdminUI::swapAllocationStrategy() {
	//allow the user to select a new method of allocating students from those provided
	auto allocation_current = myAdmin->getAlloactionStrategy();

	if (allocation_current == nullptr) {
		//the admin has no strategy so none to swap (this should never happen)
		std::cout << "\nYou don't have any preferred method for sorting the students." << std::endl;
		return;
	}

	std::cout << "\nWhich allocation approach would you like to use? The options are:" << std::endl;
	std::cout << "\n1. Optimal allocation\n2. Simple allocation\n" << std::endl;
	int choice = 0;
	while (choice != 1 && choice != 2) {
		choice = getValidInteger("Enter the number of the allocation type you wish to use: ");

		if (choice < 1 || choice >2) {
			std::cout << "That number doesn't correspond with any allocation approach. Please try again.\n" << std::endl;
		}
	}
	switch (choice) {
	case 1:
		myAdmin->setAllocationStrategy(new galesShapely);
		std::cout << "\nSuccessfully swapped your allocation strategy!\n" << std::endl;
		pause();
		return;
	case 2:
		myAdmin->setAllocationStrategy(new simpleAllocate);
		std::cout << "\nSuccessfully swapped your allocation strategy!\n" << std::endl;
		pause();
		return;
	}
}

Project* AdminUI::getValidProject(std::string prompt) {
	//search for a project by name. Return a pointer to this if found, or null otherwise
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
	//allow an editable student to be edited using the setters of the student
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
				std::cout << "\n" << student_to_edit->getName() << " has been allocated: ";
				if (student_to_edit->getAllocatedProject() == nullptr) {
					std::cout << "No project.\n";
				}
				else {
					std::cout << student_to_edit->getAllocatedProject()->getTitle() << "\n";
				}
				std::cout << "\nWhat should the new project allocation be? The available choices are:\n";
				printLineSep();
				dbm->printListOfProjects();
				student_to_edit->setAllocatedProject(getValidProject("\nEnter the name of a project to allocate this student: "));
				std::cout << "\nSuccessfully allocated " << student_to_edit->getName() << " to"
					" '" << student_to_edit->getAllocatedProject()->getTitle() << "'." << std::endl;
				pause();
				return;
		}
	}
}

void AdminUI::editStudent() {
	//locate a student to edit and pass this to the attributes editor function above
	clearScreen();
	std::cout << "\nWhich student would you like to edit? The students currently in the database are: " << std::endl;
	printLineSep();
	for (auto& student : this->db->getStudents()) {
		std::cout << student->getName() << " : " << student->getID();
		if (student->getAllocatedProject() == nullptr) {
			std::cout << " (No allocated project)" << std::endl;
		}
		else {
			std::cout << " (" << student->getAllocatedProject()->getTitle() << ")" << std::endl;
		}
	}
	bool exit = false;
	while (!exit) {
		int reg = getValidInteger("\nEnter the ID of the student you want to edit (or '0' to exit): ");

		if (reg == 0) { //return early
			std::cout << "Returning to the main menu." << std::endl;
			pause();
			return;
		}

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

void AdminUI::editSupervisorMetadata(Supervisor* supervisor_to_edit) {
	//edit the fields of the supervisor class using the setters 
	clearScreen();
	std::vector<std::string> options = { "Name", "Password", "ID", "Swap projects overseen" };

	std::cout << "What data belonging to " << supervisor_to_edit->getName() << " would you like to edit?\n" << std::endl;
	for (int i = 0; i < options.size(); i++) {
		std::cout << i + 1 << ". " << options[i] << std::endl;
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
			std::cout << "\nWhat should " << supervisor_to_edit->getName() << "'s name be changed to?" << std::endl;
			supervisor_to_edit->setName(getValidString("\nEnter the new name: "));
			return;
			break;
		case(2):
			//edit the password
			std::cout << "\nWhat should " << supervisor_to_edit->getName() << "'s password be changed to?" << std::endl;
			supervisor_to_edit->setPassword(getValidString("\nEnter the new password: "));
			return;
			break;
		case(3):
			//edit the ID
			std::cout << "\nWhat should " << supervisor_to_edit->getName() << "'s ID be changed to (integer code only) ?" << std::endl;
			supervisor_to_edit->setID(getValidInteger("\nEnter the new password: "));
			return;
			break;
		case(4):
			//edit the project allocated
			std::cout << "\n" << supervisor_to_edit->getName() << " oversees the following projects:\n " << std::endl;
			if (supervisor_to_edit->getProjectsOversee().size() == 0) {
				std::cout << "This supervisor doesn't oversee any projects currently.\n";
				pause();
				return;
			}
			else {
				//get and display current projects overseen
				auto& projs = supervisor_to_edit->getProjectsOversee();
				for (int i = 0; i < projs.size(); i++) {
					std::cout << i + 1 << ". " << projs[i]->getTitle() << std::endl;
				}
				//get project FROM which to swap...
				int from = 0;
				Project* from_swap = nullptr;
				while (from <= 0 || from > projs.size()) {
					from = getValidInteger("\nWhich project should be swapped out for another one? Enter the corresponding number: ");
					if (from <= 0 || from > projs.size()) {
						std::cout << "That isn't a valid project number. Please try again." << std::endl;
					}
				}
				from_swap = projs[from - int(1)];
				clearScreen();

				//get projects TO swap with..
				int to = 0;
				Project* to_swap = nullptr;
				auto all_projs = dbm->getProjectsNotOverseen(supervisor_to_edit);
				std::cout << "\n";
				for (int j = 0; j < all_projs.size(); j++) {
					std::cout << j + 1 << ". " << all_projs[j]->getTitle() << std::endl;
				}
				printLineSep();
				while (to <= 0 || to > all_projs.size()) {
					to = getValidInteger("\nWhich project should this supervisor now oversee?: ");
					if (to <= 0 || to > all_projs.size()) {
						std::cout << "That isn't a valid project number. Please try again." << std::endl;
					}
				}
				to_swap = all_projs[to - int(1)];

				//correct the supervisor pointers and correct the supervisors pointed at by the projects
				Supervisor* old_supervisor_to_project = to_swap->getSupervisor();
				to_swap->setSupervisor(supervisor_to_edit);
				from_swap->setSupervisor(old_supervisor_to_project);

				//correct the projects pointed at by the supervisors
				old_supervisor_to_project->removeProject(to_swap);
				old_supervisor_to_project->addProjectWorkload(from_swap);
				supervisor_to_edit->removeProject(from_swap);
				supervisor_to_edit->addProjectWorkload(to_swap);


				std::cout << "\nSuccessfully swapped '" << from_swap->getTitle() << "' with '" << to_swap->getTitle() << "'. " << std::endl;
				pause();
				return;


			}			
		}
	}
}

void AdminUI::showStudentsAndAllocations() {
	//display all students with allocated project (or none if allocation not taken place)
	clearScreen();
	std::cout << "Current Allocations" << std::endl;
	printLineSep();
	for (auto& student : db->getStudents()) {
		std::cout << student->getName() << "(" << student->getDegree() << ") : ";
		if (student->getAllocatedProject() != nullptr) {
			std::cout << student->getAllocatedProject()->getTitle() << std::endl;
					}
		else {
			std::cout << "No project allocation" << std::endl;
		}
	}
	pause();
	return;
}

void AdminUI::editSupervisor() {
	//find the supervisor to edit then pass this to the edit metadata function
	clearScreen();
	std::cout << "\nWhich supervisor would you like to edit? The supervisors currently in the database are: " << std::endl;
	printLineSep();
	for (auto& sup : this->db->getSupervisors()) {
		std::cout << sup->getName() << " : ID-" << sup->getID();
		if (sup->getProjectsOversee().size() == 0) {
			std::cout << "(No projects overseen)" << std::endl;
		}
		else {
			std::cout << " (";
			auto& sup_projects = sup->getProjectsOversee();
			for (int i = 0; i <sup_projects.size()-1; i++) {
				std::cout << sup_projects[i]->getTitle();
				std::cout << ", ";
			}
			std::cout << sup_projects[sup_projects.size() - 1]->getTitle() << ")" << std::endl;
		}
	}
	bool exit = false;
	while (!exit) {
		int reg = getValidInteger("\nEnter the ID of the supervisor you want to edit (or 0 to exit): ");
		Supervisor* sup_to_loc = db->findSupervisorByRegnum(reg);

		if (reg == 0) {
			std::cout << "Exiting to the main menu." << std::endl;
			exit = true;
			pause();
			return;
			break;

		}
		if (sup_to_loc) {
			editSupervisorMetadata(sup_to_loc); //delegate the editing
			break;
		}
		else {
			std::cout << "Unable to locate a supervisor with that registration number." << std::endl;
		}
	}
}


void AdminUI::editProjectMetadata(Project* to_edit) {
	//edit a projects' metadata using the setters

	std::unordered_map<int, std::string> attributes{ { 1, "Title" }, {2, "Max Capacity"}, {3, "Module code"}, {4,"Description"} };
	std::cout << "\n";
	for (auto& attribute : attributes) {
		std::cout << attribute.first << ": " << attribute.second << std::endl;
	}
	int choice = 0;
	bool exit = false;
	while (!exit) {
		int edit_num = getValidInteger("\nEnter the number corresponding to the project data you want to edit (or '0' to exit):");
		if (edit_num <0 || edit_num>attributes.size()) {
			std::cout << "That's not a valid number, please try again." << std::endl;
		}
		switch (edit_num) {
		case(1):
			to_edit->setTitle(getValidString("\nEnter the new title for this project: "));
			std::cout << "Change to module title successful." << std::endl;
			pause();
			return;
		case(2):
			std::cout << "This project can currently hold " << to_edit->getMaxCapacity() << " students.\n" << std::endl;
			to_edit->setMaxCapacity(getValidInteger("Enter the new maximum limit of students who can take this module: "));
			std::cout << "Change to module capacity successful." << std::endl;
			pause();
			return;
		case(3):
			std::cout << "The current module code for this project is '" << to_edit->getModuleCode() << "'.\n" << std::endl;
			to_edit->setModuleCode(getValidInteger("\nEnter the new module code of this module: "));
			std::cout << "Change to module code successful." << std::endl;
			pause();
			return;
		case(4):
			std::cout << "The current description for this project is: '" << to_edit->getDescription() << "'.\n" << std::endl;
			to_edit->setDesciption(getValidString("\nEnter the new description for this project: "));
			std::cout << "Change to module description successful." << std::endl;
			pause();
			return;
		}
	}

}
void AdminUI::editProject() {
	//find a project to edit then pass this to the attribute/ metadata editing method
	clearScreen();
	auto& projects = db->getProjects();
	for (int i = 0; i < projects.size(); i++) {
		std::cout << i+1 << ": " << projects[i]->getTitle() << std::endl;
	}
	int choice=-1;
	while (choice<0 || choice>projects.size()) {
		choice = getValidInteger("\nEnter the number corresponding with the project you wish to edit (or '0') to exit:");
		if (choice == 0) {
			std::cout << "\nReturning to the main menu..." << std::endl;
			pause();
			return;
		}

		else if (choice<0 || choice>projects.size()) {
			std::cout << "\nThe number you entered doesn't match any of those listed above." << std::endl;
		}
		else {
			editProjectMetadata(projects[choice - 1]);
		}
	}
}


void AdminUI::automaticAllocate() {
	//perform automatic allocation

	std::cout << "Allocating students automatically...\n" << std::endl;
	//call the allocation strategy class, passing it the database
	myAdmin->getAlloactionStrategy()->allocate(db);

	std::cout << "Allocation complete!" << std::endl;
	pause();
	return;
}

 Student *AdminUI::createStudent() {
	 //create a new student and add them to the database

	 std::string name = getValidString("Enter Name: ");
	 std::string password = getValidString("Enter Password: ");
	 
	 //force a non zero regnum as this key is used to exit a menu (so would not allow search)
	 int id = 0;
	 while (!id) {
		 id = getValidInteger("Enter Student ID: ");
		 if (!id) {
			 std::cout << "\nPlease enter a longer registration number - starting in 20** (** = year of start) then 5 extra digits." << std::endl;
		 }
	 }

	 std::string degree = getValidString("Enter Degree: ");

	 if (this->db->findStudentByRegnum(id) == nullptr) {
		 Student* newStudent = new Student(name, password, id, degree);
		 auto& students = this->db->getStudents();
		 students.push_back(newStudent);
		 printLineSep();
		 std::cout << "New Student Created! : " << newStudent->getName() << "\n" << std::endl;
		 return newStudent;
	 }

	 else {
		 
		 std::cout << "The student " << 
			 this->db->findStudentByRegnum(id)->getName()<<
           "already exists!" << "\n" << std::endl;
		 return this->db->findStudentByRegnum(id);

	 }

}

 Supervisor *AdminUI::createSupervisor() {
	 //create a new supervisor then add them to the database

	 std::string name = getValidString("Enter Name: ");
	 std::string password = getValidString("Enter Password: ");
	 int id = getValidInteger("Enter Supervisor ID: ");
	 std::string department = getValidString("Enter Department: ");
	 if (this->db->findSupervisorByRegnum(id) == nullptr) {
		 Supervisor* newSupervisor = new Supervisor(name, password, id, department);
		 auto& supervisors = this->db->getSupervisors();
		 supervisors.push_back(newSupervisor);
		 printLineSep();
		 std::cout << "New Student Created! : " << newSupervisor->Serialise() << "\n" << std::endl;
		 return newSupervisor;
	 }

	 else {
		 std::cout << "The supervisor " <<
			 this->db->findSupervisorByRegnum(id)->getName() <<
			 "already exists!" << "\n" << std::endl;
		 return this->db->findSupervisorByRegnum(id);
	 }

 }

 void AdminUI::resetAllocated() {
	 //reset the allocated fields using threading

	 std::thread eraseFromStudent([&] {
		 for (auto& student : this->db->getStudents()) {
			 student->setAllocatedProject(nullptr);
		 }
	 }
	 );

	 std::thread eraseFromProjects([&] {
		 for (auto& project : this->db->getProjects()) {
			 for (auto& student : project->getStudents()) {
				 project->removeStudent(student);
			 }
		 }
	 }
	 );
 
	 eraseFromStudent.join();
	 eraseFromProjects.join();
 }

 void AdminUI::createNew() {
	 //provides a portal for creating new new users (calls the correct creation class function)
	 
	 clearScreen();
	 std::vector<std::string> options = { "Student", "Supervisor","Project" };

	 std::cout << "What would you like to add?\n" << std::endl;
	 for (int i = 0; i < options.size(); i++) {
		 std::cout << i + 1 << ". " << options[i] << std::endl;
	 }
	 bool exit = false;
	 while (!exit) {
		 int choice = getValidInteger("\nEnter the number of the field to edit (or 0 to exit): ");
		 if (choice < 0 || choice > options.size()) {
			 std::cout << "\nThe number you entered does not match any provided in the options. Please try again." << std::endl;
		 }

		 switch (choice) {

		 case 0:
			 std::cout << "Exiting to the main menu." << std::endl;
			 exit = true;
			 pause();
			 return;
			 break;
		 case 1:
			 createStudent();
			 pause();
			 return;
			 break;
		 case 2:
			 createSupervisor();
			 pause();
			 return;
			 break;
		 case 3:
			 createProject();
			 pause();
			 return;
			 break;
		 default:
			 std::cout << "Invalid action..." << std::endl;
			 pause();
			 return;

		 }
	 }
 }

 Project* AdminUI::createProject() {
	 //provides an interface for creating new projects

	 std::string title = getValidString("Enter Title: ");
	 int code = getValidInteger("Enter Module Code: ");
	 std::string desc = getValidString("Enter Description: ");
	 int capacity = getValidInteger("Enter Capacity:  ");

	 if (this->db->getProject(title) == nullptr) {
		 Project* newProject = new Project(title, code, desc, capacity);
		 auto& projects = this->db->getProjects();
		 projects.push_back(newProject);
		 printLineSep();
		 std::cout << "New Project Created! : " << newProject->getTitle() << "\n" << std::endl;
		 return newProject;
	 }

	 else {
		 std::cout << "The project " <<
			 this->db->getProject(title)->getTitle() <<
			 "already exists!" << "\n" << std::endl;
		 return this->db->getProject(title);
	 }

 }