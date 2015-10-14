#include "Admin.h"

#define NUM_OPTIONS 4
#define LOGFILE "log.txt"

//need to make this persist?
bool Admin::execTrace = true;
void Admin::adminOperations() {
	std::vector<std::string> actions;
	std::ostringstream oss;
	oss << "Toggle execution trace - Currently " << (execTrace ? "ON" : "OFF");

	actions.push_back(oss.str());
	actions.push_back("View the contents of the execution trace");
	actions.push_back("Clear the execution trace log");

	int input = 0;
	while(input != NUM_OPTIONS) {
		input = IOUtils::getUserAction(&actions);

		switch(input) {
			case 1:
				execTrace = !execTrace;
				std::cout << "Execution trace is now " << (execTrace ? "ON" : "OFF") << std::endl;
				break;
			case 2: {
				std::ifstream tracefile(LOGFILE);
				std::string line;
				while(getline(tracefile, line)) {
					std::cout << line << std::endl;
				}
				break;
			}
			case 3: {
				//empty the contents of the file using ofstream::trunc
				std::ofstream tracefile(LOGFILE, std::ofstream::out | std::ofstream::trunc);
				std::cout << "Log file has been cleared." << std::endl;
				break;
			}
		}
	}
}

void Admin::logExecutionTrace(std::string s) {
	if(!execTrace)
		return;

	time_t rawtime;
	time(&rawtime);
	struct tm* now = localtime(&rawtime);
	char formattedTime[80];
	strftime(formattedTime, 80, "[%D %R] ", now);

	std::ofstream tracefile(LOGFILE, std::ios_base::app);
	tracefile << formattedTime << s << std::endl;
}
