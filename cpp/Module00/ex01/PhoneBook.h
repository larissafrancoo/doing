#ifndef PHONEBOOK_H
# define PHONEBOOK_H
# include <string>
# include "Contact.h"

class PhoneBook
{
private:
	Contact contacts[9];
	int count;

public:
	PhoneBook();
	~PhoneBook();
	int contactsLen();
	std::string defineMsg(int idx);
	void inputInfo(int idx);
	void outHomeContact();
	void oneHomeContact(Contact c, int idx);
	void outOneContact(int idx);
};

#endif
