#include "Admin.h"

#define NUM_OPTIONS 4
#define LOGFILE "log.txt"

/**
*   This class handles Admin operations, which consist of toggling execution tracing, viewing the contents of the trace,
*   or clearing the trace. Also handles writing to the trace file.
**/
//on by default at startup.
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
		    //toggle exec trace
			case 1: {
				execTrace = !execTrace;
				std::cout << "Execution trace is now " << (execTrace ? "ON" : "OFF") << std::endl;
				break;
			}
			//echo the trace file
			case 2: {
				std::ifstream tracefile(LOGFILE);
				std::string line;
				//output file line-by-line
				while(getline(tracefile, line)) {
					std::cout << line << std::endl;
				}
				break;
			}
			//clear the file
			case 3: {
				//empty the contents of the file using ofstream::trunc
				std::ofstream tracefile(LOGFILE, std::ofstream::out | std::ofstream::trunc);
				std::cout << "Log file has been cleared." << std::endl;
				break;
			}
		}
	}
}

//writes the system time + s to LOGFILE if execution trace is toggled ON.
void Admin::logExecutionTrace(std::string s) {
	if(!execTrace)
		return;

    //get system time
	time_t rawtime;
	time(&rawtime);
	struct tm* now = localtime(&rawtime);
	char formattedTime[80];
	//format the time into a string
	strftime(formattedTime, 80, "[%D %R] ", now);

    //log it, in append mode
	std::ofstream tracefile(LOGFILE, std::ios_base::app);
	tracefile << formattedTime << s << std::endl;
}
