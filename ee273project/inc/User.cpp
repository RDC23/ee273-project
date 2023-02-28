#include "User.h"

User::User(std::string name, std::string password, int id) {


}
virtual ~User() {

}//important so that correct destructor is called for derived classes
std::string User::getName() {

	return this->full_name;
}
std::string User::getPassword() {

	return this->password;
}
int User::getID() {

	return this->myID;

}
void User::setName(std::string name) {

	this->full_name = name;
}
void User::setPassword(std::string password) {


}
void User::setID(int id) {


}


