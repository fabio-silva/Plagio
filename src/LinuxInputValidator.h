/*
 * LinuxInputValidator.h
 *
 *  Created on: May 23, 2013
 *      Author: root
 */

#ifndef LINUXINPUTVALIDATOR_H_
#define LINUXINPUTVALIDATOR_H_
#include "InputValidator.h"
#include <sys/types.h>
#include <dirent.h>
#include <fstream>

class LinuxInputValidator: public InputValidator {



	bool isTXT(string fileName);

public:

	string getDBdirectory();
	string getFileToTest();
	void setDBdirectory(string dbPath);
	void setFileToTest(string filePath);
	vector<string> getDBFilesList();
	void compare();

};

#endif /* LINUXINPUTVALIDATOR_H_ */
