#include "AllocationStrategy.h"
#include "Database.h"

void galesShapely::allocate(Database* db) {
	


}

void simpleAllocate::allocate(Database* db) {

	

	for (auto& student : db->getStudents()) { //for every student
		
		if (student->getAllocatedProject() != nullptr) { // if no project allocated

			for (auto& preference : student->getMyProjectChoices()) {

				if (!preference->isFull()) {
					student->setAllocatedProject(preference);
					break;
				}
			}
			for (auto& project : db->getProjects()) {
				if (!project->isFull()){
					student->setAllocatedProject(project);
				}
			}
		}

	}


}