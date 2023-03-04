#include <iostream>
#include "User.h"



int main() {
	Project lmao = Project("class1", 1, "the worst f*cking class in existence", 10);
	Project lmao1 = Project("class2", 2, "the worst f*cking class in existence", 10);
	Project lmao2 = Project("class3", 3, "the worst f*cking class in existence", 10);
	Project lmao3 = Project("class4", 4, "the worst f*cking class in existence",10 );
	Student Kishan = Student("Kishan Maharaj", "mypassword", 202129516, "MENG EEE");
	Kishan.addProjectToPreferences(&lmao);
	Kishan.addProjectToPreferences(&lmao1);
	Kishan.addProjectToPreferences(&lmao2);
	Kishan.addProjectToPreferences(&lmao3);
	std::cout << Kishan.Serialise(); //WORKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}