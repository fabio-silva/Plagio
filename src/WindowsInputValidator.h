/*
 * filePath.h
 *
 *  Created on: 20 de Mai de 2013
 *      Author: fabio
 */

#ifdef _WIN32

#include <fstream>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "InputValidator.h"

using namespace std;

class WindowsInputValidator: public InputValidator
{
	string base,file;
	string firstFile;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;

public:
	WindowsInputValidator();
	WindowsInputValidator(string base, string file);
	void setFileToTest(string filePath);
	void setDBdirectory(string dbPath);
	void compare();
	void setMinimum(int m);
	string getNextFile();
	string getFirstFile();
	string getDBDirectory();

};



#endif
