/*EE273 Group Project
Name: AllocationStrategy.cpp
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/


#include "AllocationStrategy.h"
#include "Database.h"

void simpleAllocate::allocate(Database* db) {
	
	std::vector < Student**> students;
	std::vector <Project**> projects;
	for (auto& student : db->getStudents()) { //load locations of students in the database
		students.push_back(&student);
	}
	for (auto& project : db->getProjects()) { //load projects
		projects.push_back(&project);
	}
	std::random_shuffle(students.begin(), students.end());

	for (auto& student : students) {

		if ((*student)->getAllocatedProject() == nullptr) {
			
			std::random_shuffle(projects.begin(), projects.end());
			for (auto& project : projects) {
				if (!(*project)->isFull()) {
					(*student)->setAllocatedProject(*project);
					(*project)->addStudent(*student);
					break;
				}
			}

		}

  }
}

void galesShapely::allocate(Database* db) {



	for (auto& student : db->getStudents()) { //for every student

		if (student->getAllocatedProject() == nullptr) { // if no project allocated

			for (auto& preference : student->getMyProjectChoices()) {

				if (!(preference->isFull())) {
					student->setAllocatedProject(preference);
					preference->addStudent(student);
					break;

				}

			}

			for (auto& project : db->getProjects()) {
				if (!(project->isFull())) {
					student->setAllocatedProject(project);
					project->addStudent(student);
					break;
				}
			}

		}
		else { return; }

	}
}