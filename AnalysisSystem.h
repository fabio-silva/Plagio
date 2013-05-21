/*
 * filePath.h
 *
 *  Created on: 20 de Mai de 2013
 *      Author: fabio
 */

#ifndef FILEPATH_H_
#define FILEPATH_H_

#include <fstream>
#include <iostream>
#include <windows.h>
#include <cstdlib>

using namespace std;

class AnalysisSystem
{
string base,file;
string firstFile;
WIN32_FIND_DATA FindData;
HANDLE hFind;

public:
AnalysisSystem();
AnalysisSystem(string base, string file);
void setBase(string b);
void setFile(string f);
string getNextFile();
string getFirstFile();
};

#endif /* FILEPATH_H_ */


class invalidBase
{
public:
	invalidBase(string p) { }
};

class invalidFile
{
public:
	invalidFile(string p){ }

};
