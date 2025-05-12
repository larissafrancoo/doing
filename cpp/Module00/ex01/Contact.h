#ifndef CONTACT_H
# define CONTACT_H

# include <string>

class Contact
{
private:
	std::string fname;
	std::string lname;
	std::string nick;
	std::string phone;
	std::string secret;

public:
	Contact();
	~Contact();
	void setContactInfo(const std::string& value, int idx);
	std::string getContactInfo(int idx);
};

#endif
