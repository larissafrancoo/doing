#include "PhoneBook.h"
#include "Contact.h"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook(){
	this->count = 0;
}
PhoneBook::~PhoneBook(){}

int PhoneBook::contactsLen(){return this->count;}

std::string PhoneBook::defineMsg(int i){
	switch (i){
		case 1: return "First Name: ";
		case 2: return "Last Name: ";
		case 3: return "Nickname: ";
		case 4: return "Phone: ";
		case 5: return "Darkest Secret: ";
		default: break ;
	}
	return nullptr;
}

void PhoneBook::inputInfo(int idx) {
	Contact c;
	std::string cmd;
	for (int i = 1; i <= 5; i++) {
again:
		std::cout << defineMsg(i) << std::endl;
		std::getline(std::cin, cmd);
		if (!cmd[0] or std::isspace(cmd[0])){
			std::cout << "The input cannot be empty or space." << std::endl;
			goto again;
		}
		c.setContactInfo(cmd, i);
	}
	this->contacts[idx] = c;
	std::cout << "The contact was added.\n" << std::endl;
	if (this->count != 8) count++;
}

void PhoneBook::outHomeContact(){
	for (int idx = 0; idx < this->count; idx++) {oneHomeContact(contacts[idx], idx + 1);}
}

void PhoneBook::oneHomeContact(Contact c, int idx) {
	std::cout << idx << "         |";
	for (int i = 1; i <= 3; i++) {
		std::string str = c.getContactInfo(i);
		if (str.length() > 10) str[9] = '.';
		std::cout << std::setw(10) << std::left << str.substr(0,10);
		(i < 3) ? std::cout << "|" : std::cout << std::endl;
	}
}

void PhoneBook::outOneContact(int idx) {
	for (int i = 1; i <= 5; i++) {
		std::string str = contacts[idx].getContactInfo(i);
		std::cout << defineMsg(i) << str << std::endl;
	}
}
