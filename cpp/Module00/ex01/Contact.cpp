#include "Contact.h"
#include <iostream>
#include <iomanip>

using namespace std;

Contact::Contact(){}
Contact::~Contact(){}

void Contact::setContactInfo(const std::string& str, int idx) {
	if (idx == 1) this->fname = str;
	else if (idx == 2) this->lname = str;
	else if (idx == 3) this->nick = str;
	else if (idx == 4) this->phone = str;
	else if (idx == 5) this->secret = str;
}

std::string Contact::getContactInfo(int idx) {
	if (idx == 1) return this->fname;
	else if (idx == 2) return this->lname;
	else if (idx == 3) return this->nick;
	else if (idx == 4) return this->phone;
	else if (idx == 5) return this->secret;
	return nullptr;
}
