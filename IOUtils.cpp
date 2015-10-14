#include "IOUtils.h"

int IOUtils::getUserAction(std::vector<std::string>* options) {
	int input = 0;
	//log out is always the final option, so add 1
	int numOptions = options->size() + 1;

	std::cout << "What would you like to do?" << std::endl;

	int i = 1;
	for(std::vector<std::string>::iterator it = options->begin(); it != options->end(); ++it) {
		std::cout << i << ". " << *it << std::endl;
		i++;
	}
	std::cout << numOptions << ". Log out" << std::endl;

	while(!(std::cin >> input) || input < 1 || input > numOptions|| std::cin.peek() != '\n') {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Not a valid input. Enter 1-" << numOptions << " only: " << std::flush;
	}
	std::cout << std::endl;
	return input;
}

//prints msg, asks for a response from the two options.
//returns true if they select the first option, false if they select the second
bool IOUtils::getUserResponse(std::string msg, const char option1, const char option2) {
	Admin::logExecutionTrace("Getting user response");
	std::cout << msg << " [" << option1 << "/" << option2 << "] : " << std::flush;
	//loop until option1 or option2 is given, upon which the function returns
	while(true) {
		char c;
		if(std::cin >> c && std::cin.peek() == '\n') {
			if(c == option1)
				return true;
			else if(c == option2)
				return false;
		}
		//bad input or not one of the options
		std::cout << "Enter only " << option1 << " or " << option2 << ": ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	//never executed
	return true;
}
