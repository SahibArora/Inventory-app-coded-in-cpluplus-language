// This Class keeps tracks of errors we got anywhere in the app, and record those errors in its variables...

#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include<iostream>

namespace sict
{
	class ErrorMessage
	{
	private:
		char* message_;
	public:
		ErrorMessage();
		ErrorMessage(const char* errorMessage);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const char* errorMessage);
		virtual ~ErrorMessage();
		void clear();
		bool isClear()const;
		void message(const char* value);
		const char* message() const;
		std::ostream& write(std::ostream& ostr) const;
	};
		std::ostream& operator<<(std::ostream& ostr,const ErrorMessage& em);
}
#endif
