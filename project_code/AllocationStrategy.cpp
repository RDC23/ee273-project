/*EE273 Group Project
Name: AllocationStrategy.cpp
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/


#include "AllocationStrategy.h"
#include "Database.h"

void simpleAllocate::allocate(Database* db) { 
	//random project allocations
	std::vector < Student**> students;
	std::vector <Project**> projects;
	for (auto& student : db->getStudents()) { //load locations of students in the database
		students.push_back(&student); //add student** pointers
	}
	for (auto& project : db->getProjects()) { //load projects
		projects.push_back(&project); //add project** pointers
	}
	std::random_shuffle(students.begin(), students.end()); //shuffle students

	for (auto& student : students) { //assign projects in random order

		if ((*student)->getAllocatedProject() == nullptr) {
			
			std::random_shuffle(projects.begin(), projects.end());
			for (auto& project : projects) {
				if (!(*project)->isFull()) { //is current project full, go to next
					(*student)->setAllocatedProject(*project); //association goes both ways
					(*project)->addStudent(*student);          // add student to project and vise versa.
					break;
				}
			}

		}

  }
}

void galesShapely::allocate(Database* db) {



	for (auto& student : db->getStudents()) { //for every student

		if (student->getAllocatedProject() == nullptr) { // if no project allocated

			for (auto& preference : student->getMyProjectChoices()) { // in preferences

				if (!(preference->isFull())) { // if top preference isn't full
					student->setAllocatedProject(preference); //assign highest preference
					preference->addStudent(student); //add student to this preferered project
					break; // break; if preference is full, go down to the next preference

				}

			}
			if (student->getAllocatedProject() == nullptr) { //if still no project allocated
				for (auto& project : db->getProjects()) { //go through project database ordinally
					if (!(project->isFull())) { //if project isn't full
						student->setAllocatedProject(project); //assign both wayus
						project->addStudent(student);
						break;
					}
				}

			}

		}
	}
}