#include <stdio.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <filesystem>
#include <stdlib.h>





std::vector<std::string> splitArgs(const std::string& input)
{
	std::vector<std::string> args;
	std::string current;
	bool inQuotes = false;

	for (char c : input)
	{
		if (c == '"') {
			inQuotes = !inQuotes; // zmiana stanu cytatu
			continue; // nie dodawaj " do argumentu
		}

		if (c == ' ' && !inQuotes)
		{
			if (!current.empty())
			{
				args.push_back(current);
				current.clear();
			}
		}
		else
		{
			current += c;
		}
	}

	if (!current.empty())
		args.push_back(current);

	return args;
}



int main()
{
	std::string input = "";
	printf("Welcome to SYSTEM M PROMPT. Type 'help' to list CMDS.\n");
	int zero = 0;
	int enabled = 1;
	bool debugMode = false;
	std::string pth;


	while (enabled) {
		std::string input = "";
		std::cout << "SM |" << std::filesystem::current_path().string() << "> ";
		std::getline(std::cin, input);

		std::vector<std::string> args = splitArgs(input);
		if (args.empty()) continue;


		if (args.size() == 0) continue;

		std::string cmd = args[0];


		if (debugMode) {
			std::cout << "\033[33mCommand sent:\033[0m\t" << input;
		}

		if (debugMode) {
			std::cout << "ARGS:" << args[0] << args[1] << args[2];
		}






		printf("\n");

		if (cmd == "exit") {
			enabled = 0;
			std::cout << "\n";
			continue;
		}

		else if (cmd == "help") {
			printf("---------------- HELP SYSTEM M ----------------\n");
			printf("Commands:\n");
			printf(" -   - help : Show help\n");
			printf(" -   - exit : Disable and exit\n");
			printf("");
			printf("\n");
			printf("");


			std::cout << "\n";
			continue;
		}

		else if (cmd == "d") {
			std::cout << "Current Working Directory:\033[31m\t" << std::filesystem::current_path().string() << "\033[0m";


			std::cout << "\n";
			continue;
		}

		else if (cmd == "dir") {
			std::string pth = (args.size() > 1) ? args[1] : std::filesystem::current_path().string();

			try {
				for (const auto& entry : std::filesystem::directory_iterator(pth)) {
					std::cout << (entry.is_directory() ? "<DIR> " : "       ")
						<< entry.path().filename().string() << "\n";
				}
			}
			catch (const std::filesystem::filesystem_error& e) {
				std::cout << "Exception Occured.";
			}

			std::cout << "\n";
		}

	// CD COMMAND

		else if (cmd == "cd") {
			if (args.size() < 2)
			{
				std::cout << "Usage: cd <folder>\n";
				continue;
			}
			try {
				std::filesystem::current_path(args[1]);
			}


			catch (...) {
				std::cout << "An error occured.";
			}



			std::cout << "\n";
			continue;
		}

		// MKDIR COMMAND

		else if (cmd == "mkdir") {

			if (args.size() < 2) {
				std::cout << "Usage: mkdir <dir name>\n";
				continue;
			}

			try {


				if (std::filesystem::create_directory(args[1])) {
					std::cout << "\033[42mDirectory created successfully.\033[0m\n";
				}
				else {
					std::cout << "\033[41mFailed to create directory.\033[0m Check if it arleady exists.\n";
				}
			}
			catch(...) {
				std::cout << "An error occured.";
			}
			std::cout << "\n";

		}




		else if (cmd == "debugMode") {
			if (args[1] == "TRUE") {
				
				debugMode = true;
				std::cout << "Debug mode has been Enabled. Errors may occur";
			}

			if (args[1] == "FALSE") {
				debugMode = false;
				std::cout << "Debug mode has been Disabled.";
			}


			std::cout << "\n";
			continue;
		}



		else {

			std::cout << "Unknown command. Type 'help' for list\n";
		}
		

	}



	return 0;
	
	
}