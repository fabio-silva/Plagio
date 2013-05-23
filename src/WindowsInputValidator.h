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
	void setBase(string b);
	void setFile(string f);
	string getNextFile();
	string getFirstFile();
	string getDBDirectory();

};



#endif
