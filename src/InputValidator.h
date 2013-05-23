/*
 * InputValidator.h
 *
 *  Created on: May 23, 2013
 *      Author: root
 */

#ifndef INPUTVALIDATOR_H_
#define INPUTVALIDATOR_H_
#include <string>
#include <vector>
#include "CopyChecker.h"
using namespace std;

class InputValidator {

protected:

//	string dbPath;
//	vector<string> dbFilesList;
//	string filePath;
	CopyChecker *checker;
public:
	InputValidator():checker(new CopyChecker()){}
	virtual void setFileToTest(string filePath)=0;
	virtual void setDBdirectory(string dbPath)=0;
	virtual void compare(bool print=true,int nr=-1)=0;
	virtual void setMinimum(int m) = 0;
	virtual ~InputValidator(){
		delete checker;
	}
};


class InputExeption{
public:
	string path;
public:
	InputExeption(string p):path(p){}
};

class InvalidDBaseFolder:public InputExeption
{
public:
	InvalidDBaseFolder(string p):InputExeption(p) {}
};


class InvalidFile: public InputExeption
{
public:
	InvalidFile(string p):InputExeption(p) {}

};
#endif /* INPUTVALIDATOR_H_ */
