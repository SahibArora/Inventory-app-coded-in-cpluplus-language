// This Class keeps tracks of errors we got anywhere in the app, and record those errors in its variables...

#include<iostream>
#include<cstring>
#include"ErrorMessage.h"
using namespace std;

namespace sict
{
	ErrorMessage::ErrorMessage()    // Constructor made to initialize its data member .
	{
		message_ = nullptr;
	}

	ErrorMessage::ErrorMessage(const char* errorMessage) // first it assign safe empty state to message_ and then inserts data in it through message function.
	{
		message_ = nullptr;
		message(errorMessage);
	}

	void ErrorMessage::message(const char* value) // this function first delete the memory of message to ensure if the message_ is not pointed to some garbage value, than it inserts value to message.
	{
		if (value != nullptr)
			delete[] message_;       // deleting the memory of message to ensure if its not pointed to some random memory. 
		int n = strlen(value);
		message_ = new char[n + 1];
		strncpy(message_, value, n + 1);
		message_[n] = '\0';
	}


	ErrorMessage& ErrorMessage::operator=(const char* errorMessage) // it takes value from its right operand and assign that value to data member of ErrorMessage class i.e message_   .
	{
		//message_ = nullptr;
		//this->message(errorMessage);
		//return *this;

		if (errorMessage != nullptr)
		{
			delete[] message_;
		}
		int n = strlen(errorMessage);
		message_ = new char[n + 1];
		strncpy(message_, errorMessage, n + 1);
		message_[n] = '\0';
		return *this;
	}

	ErrorMessage:: ~ErrorMessage()  // at last deletes the memory, which was allocated dynamically to ensure no memory is leaked. 
	{
		delete[] message_;
	}

	void ErrorMessage::clear() // checks if something is there in message_ or not., if yes it will delete it and direct it to nuothing means equates it to nullptr.
	{
		if (message_ != nullptr)
			delete[] message_;

		message_ = nullptr;
	}

	bool ErrorMessage::isClear() const // checks if the data member of class i.e message is in safe empty state or not.
	{
		if (message_ == nullptr)
			return true;
		else
			return false;
	}


	const char* ErrorMessage::message() const // returns the value inside message_;
	{
		return message_;
	}
	
	std::ostream& ErrorMessage::write(std::ostream& ostr) const // this function just writes the value of message onto screen and we have to create this function because we cant just write that from overloding << function because message_ is a private member and only function of that class can access it. 
	{
		if (!isClear())
		{
			ostr << message_;
		}
		return ostr;
	}

	std::ostream & operator<<(std::ostream & ostr, const ErrorMessage & em) // overloading << function so that we can print object on screen through object name;
	{

		em.write(ostr);
		return ostr;
	}
}
