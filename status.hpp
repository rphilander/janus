// error.hpp

#ifndef JANUS_STATUS_H
#define JANUS_STATUS_H

#include <string>

class Status
{
public:
	enum class Code
	{
		OK = 0,
		ERROR_OTHER = 1,
		END_OF_INPUT = 2,
		BAD_INPUT = 3
	};
	Status(Code = Code::OK, const std::string message = "");
	Code get_code() const;
	void set_code(Code);
	std::string get_message() const;
	void set_message(const std::string &);
	operator bool() const;
	bool eoi() const;
private:
	Code m_code;
	std::string m_message;
};

#endif // JANUS_STATUS_H
