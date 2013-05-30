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

/**
 * @class InputValidator
 * @brief A class whose objects validate user input in order to deliver it to a CopyChecker object
 *
 *
 */
class InputValidator {

protected:

//	string dbPath;
//	vector<string> dbFilesList;
//	string filePath;
	CopyChecker *checker;
public:

	/**
	 * @brief A simple construnctor for the InputValidator class
	 *
	 */
	InputValidator():checker(new CopyChecker()){}

	/**
	 * @brief A method that should check if a given filePath is a valid one and depending on it deliever it to the checker or tell the user the path was an invalid one.
	 * @param filePath the path to file that is supposed to be added to the checker in case it's a valid one
	 *
	 *
	 */
	virtual void setFileToTest(string filePath)=0;

	/**
	 * @brief A method that should check if a given dbPath is a valid one and depending on it deliever it to the checker.
	 * @param dbPath the path to the new directory
	 *
	 */
	virtual void setDBdirectory(string dbPath)=0;
	/**
	 * @brief A function that issues the compare order to the checker if it's ready for it
	 * @param print a bool that should be true if the output of the comparision should be printed to the stdout. False otherwise
	 * @param nr the new number of minimum chars to be consideres a match. -1 represents no change to the previous value inserted or stored.
	 *
	 *
	 */
	virtual void compare(bool print=true,int nr=-1)=0;
	/**
	 *
	 * @brief A function that should set the minimum number of characters for a match to a given value
	 * @param m a number bigger or equal to zero
	 *
	 */
	virtual void setMinimum(int m) = 0;
	/**
	 * @brief A simple destructor for the InputValidator class
	 *
	 *
	 */
	virtual ~InputValidator(){
		delete checker;
	}
};



/**
 * @class InputExeption
 * @brief A class that represents an exception to be thrown in case of a bad input from user
 *
 *
 */
class InputException{
public:
	string path;
public:
	InputException(string p):path(p){}
};

/**
 * @class InvalidDBaseFolder
 * @brief A class that represents an exception to be thrown when the user inserts a non valid data base folder
 *
 *
 */
class InvalidDBaseFolder:public InputException
{
public:
	InvalidDBaseFolder(string p):InputException(p) {}
};

/**
 * @class InvalidFile
 * @brief A class that represents an exception to be thrown when the user inserts a non valid file path
 *
 */
class InvalidFile: public InputException
{
public:
	InvalidFile(string p):InputException(p) {}

};
#endif /* INPUTVALIDATOR_H_ */
