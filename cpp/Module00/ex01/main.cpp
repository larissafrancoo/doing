#include "Contact.h"
#include "PhoneBook.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

namespace cmdProgram {
	void intro() {
		std::cout << "*******************************************" << std::endl;
		std::cout << "* Welcome to the ft_PhoneBook.            *" << std::endl;
		std::cout << "*******************************************" << std::endl;
		std::cout << "* Menu:                                   *" << std::endl;
		std::cout << "*                                         *" << std::endl;
		std::cout << "* ADD    - add a new contact;             *" << std::endl;
		std::cout << "* SEARCH - search for a contact;          *" << std::endl;
		std::cout << "* EXIT   - exit the ft_PhoneBook;         *" << std::endl;
		std::cout << "*                                         *" << std::endl;
		std::cout << "*******************************************" << std::endl;
	}
}

namespace contactsManager {
	PhoneBook phoneBook;

	void add_contact(int idx){phoneBook.inputInfo(idx);}
	void search_contact(){
		if (phoneBook.contactsLen() == 0){
			std::cout << "The contact list is empty." << std::endl;
			return;
		}
		std::string cmd;
		int idx;
start:
		std::cout << "-------------------------------------------" << std::endl;
		phoneBook.outHomeContact();
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Select one of the indices above to proceed." << std::endl;
		std::cin >> cmd;
		if (!cmd[0] or cmd[1]) cmd = "0";
		idx = cmd[0] - '0';
		if (!(idx > 0 && idx <= phoneBook.contactsLen())){
			std::cout << "Invalid Command." << std::endl;
			goto start;
		}
		phoneBook.outOneContact(idx - 1);
	}

}

int main(){
	cmdProgram::intro();
	std::string comand;
	int i = 0;
	while (comand != "EXIT") {
		std::cout << "write a command: ";
		std::getline(std::cin, comand);
		if (comand == "ADD") {
			contactsManager::add_contact(i);
			(i == 7) ? i = 0 : i++;
		}
		else if (comand == "SEARCH") {
			contactsManager::search_contact();
			if (std::cin.peek() == '\n') std::cin.ignore();
		}
	}
	std::cout << "End of the program." << std::endl;
	return (0);
}
