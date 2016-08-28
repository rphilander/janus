// Statuss.cpp

#include "Status.hpp"

Status::Status(Code code, const std::string message) :
	m_code(code),
	m_message(message)
{
}

Status::Code Status::get_code() const
{
	return m_code;
}

void Status::set_code(Code code)
{
	m_code = code;
}

std::string Status::get_message() const
{
	std::string msg = m_message;
	if (msg.empty())
	{
		switch (m_code)
		{
			case Code::OK:
				msg = "ok";
				break;
			case Code::ERROR_OTHER:
				msg = "other Status";
				break;
			case Code::END_OF_INPUT:
				msg = "end of input";
				break;
			case Code::BAD_INPUT:
				msg = "bad input";
				break;
		}
	}
	return msg;
}

void Status::set_message(const std::string &message)
{
	m_message = message;
}

Status::operator bool() const
{
	return Code::OK == m_code;
}

bool Status::eoi() const
{
	return Code::END_OF_INPUT == m_code;
}
