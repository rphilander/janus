// stringutils.cpp

#include "stringutils.hpp"

#include <cstdlib>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

Status readline(const std::string &prompt, std::string &line)
{
	Status status;
	char *c_line = readline(prompt.c_str());
	if (c_line)
	{
		line.assign(c_line);
		free(c_line);
	}
	else
	{
		status.set_code(Status::Code::END_OF_INPUT);
	}
	return status;
}

Status get_token(std::string &token, std::string &source)
{
	std::string::iterator begin = source.begin();

	// skip leading whitespace
	while (*begin == ' ') ++begin;

	// determine what will mark end of token
	char look_for = ' ';
	if (*begin == '\'' or *begin == '"')
	{
		look_for = *begin;
		// skip the open quote
		++begin;
	}

	// find end of token
	std::string::iterator end = begin;
	while (end != source.end() and *end != look_for)
	{
		++end;
	}

	Status status;
	if (end == source.end() and look_for != ' ')
	{
		// we ran out of input before the quoted string finished --
		// an error.
		status.set_code(Status::Code::BAD_INPUT);
		status.set_message("unfinished quoted string");
	}

	if (status)
	{
		token.assign(begin, end);
		if (look_for == ' ')
		{
			while (*end == ' ') ++end;
		}
		else
		{
			// skip the close quote
			++end;
		}
		source.assign(end, source.end());
		if (source.end() == end)
		{
			status.set_code(Status::Code::END_OF_INPUT);
		}
	}

	return status;
}
