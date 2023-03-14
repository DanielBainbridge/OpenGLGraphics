#include "Utility.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(std::string filename) {
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open()) {
		//while not end of file
		while (!file.eof()) {
			//read a line
			std::string thisLine;
			std::getline(file, thisLine);
			//add line to file so far
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else {
		//error to console and return empty string
		std::cout << "Cannot read file: " << filename << std::endl;
		return "";
	}
}