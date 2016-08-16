// main.cpp

#include <string>
#include <iostream>

#include "stringutils.hpp"
#include "status.hpp"

void print_help()
{
	std::cout << "recognized commands: help (or h or ?), quit (or q)" << std::endl;
}

int main(int argc, char *argv[])
{
	bool stop = false;
	std::string line;
	while (not stop and readline("janus> ", line))
	{
		Status status;
		std::string command;
		status = get_token(command, line);

		if (not status)
		{
			std::cerr << "error getting token: " << status.get_message() << std::endl;
		}
		else
		{
			if (command == "?" or command == "h" or command == "help")
			{
				print_help();
			}
			else if (command == "quit" or command == "q")
			{
				std::cout << "bye!" << std::endl;
				stop = true;
			}
			else
			{
				std::cout << "unrecognized command: " << command << std::endl;
				print_help();
			}
		}
	}
	return 0;
}
