#include <iostream>
#include "User.h"
#include "UI.h"
#include "Utils.h"



int main() {
	
	Database* db = new Database;  //the constructor manages to successfully load and map associations
	DatabaseManager dbm(db, 3);

	UserUI* ui = new StudentUI(db->getStudent("Ross"), &dbm);
	ui->displayUI();


	while (true) {
		int option = 0;
		option = getValidInteger("Enter an option number: ");
		if (option > 0 && option < ui->getNumOptions()) {
			ui->doSomething(option);
		}
		
	}
	
	


}