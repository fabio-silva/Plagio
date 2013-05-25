/*
 * CopyChecker.h
 *
 *  Created on: May 20, 2013
 *      Author: root
 */
#ifndef _max
	#define _max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef _min
	#define _min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif




#ifndef COPYCHECKER_H_
#define COPYCHECKER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>
#include <sstream>
#include <stack>


#include <sys/types.h>
#include <dirent.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif



using namespace std;

typedef enum{
	NoFileError,
	NoDBFilesError,
	NoError

}CheckErrorType;

class CopyChecker {

	ifstream fileToCheck;
	string fileToCheckPath;
	vector<string> dbFileList;
	vector<double> repetedCharsArray;
	int minNrRepetedChars;
	int validMatches;
	double LCSTime;

	/**
	 * @brief A function that sets the first row and collumn of a given matrix to zero
	 * @param matrix the matrix to be filled
	 * @param lenF1 the first dimension of the matrix
	 * @param lenF2 the second dimension of the matrix
	 *
	 */
	void makeFirstRowAndCollumnsZero(int** matrix,int lenF1, int lenF2);

	/**
	 *
	 * @brief A method that extracts the content of a file to a string
	 * @param f an ifstream with the desired file opened
	 * @return a string with the contents of the file
	 *
	 */
	string extractString(ifstream &f);

	/**
	 * @brief A method that preforms the LCS algorithm on two given files. A string with the edited content of the first file is returned. An integer is filled with the number of chars that are equal
	 * @param file1 an ifstream with the first file opened
	 * @param file2 an ifstream with the second file opened
	 * @param sizeOfMatch a pointer to an integer to be filled with the number of matches
	 * @return a string with the contents of file1 edited in a way that it is clear which parts could be matched with the second file
	 *
	 */
	string longestCommonSubsequence(ifstream & file1,ifstream & file2,int *sizeOfMatch);
	/**
	 * @brief A method that preforms the LCS algorithm on two given string. A string with the edited content of the first one is returned. An integer is filled with the number of chars that are equal
	 * @param str1 a string to be matched with the second
	 * @param str2 a string to be used as a pattern
	 * @param sizeOfMatch a pointer to an integer to be filled with the number of matches
	 * @return a string with the contents of str1 edited in a way that it is clear which parts could be matched with the second file
	 *
	 */
	string longestCommonSubsequence(const string &str1,const string &str2,int *sizeOfMatch);

	/**
	 * @brief A method that edits a string according to the matrix outcomming from the LCS algorithm to make it visually perceptible the common parts between the two strings tested.
	 * @param matrix the output matrix of the LCS algorithm
	 * @param str1 the string tested in the LCS algorithm
	 * @param str2 the string used as a pattern in the LCS algorithm
	 * @param pos1 the x position of the matrix where the algorithm should start. Usually this parameter should be the length of str1 +1.
	 * @param pos2 the y position of the matrix where the algorithm should start. Usually this parameter should be the length of str2 +1.
	 * @param charsWaitingForPrint a parameter used in the recursion that should have the value of the nr of characters that should be printed at the end of the string without further processing. This parameter should be consistent with pos1 and pos2 or undefined behaviour will happen. Usually this vector should be 0
	 * @param s a stringstream where the edited contents of str1 will be placed after processing
	 * @return returns the number of matched chars between the two strings
	 */
	int computeDiff(int **matrix,const string &str1,const string &str2,int pos1,int pos2,int charsWaitingForPrint,stringstream &s);

	/**
	 * @brief A method that finds the longest common substring between two strings
	 * @param file1 an ifstream with the first file opened
	 * @param file2 an ifstream with the second file opened
	 * @return a string with the biggest common substring found
	 *
	 */
	string longestCommonSubstring(ifstream & file1,ifstream & file2);
	/**
	 * @brief A function that returns the number of chars a given file has
	 * @param in an ifstream with the desired file opened
	 * @return the number of chars the passed file has
	 *
	 */
	int nrOfCharsInFile(ifstream & in);

	/**
	 * @brief A method that returns an x*y matrix of integers.All the contents of the matrix are malloced
	 * @param x the first dimention of the matrix
	 * @param y the second dimention of the matrix
	 * @return the matrix start
	 *
	 */
	int ** getMatrix(int x,int y);
	/**
	 * @brief A method that frees all the memory used to store a given integer matrix
	 * @param matrix the matrix
	 * @param y the number of rows the matrix has
	 *
	 */
	void deleteMatrix(int **matrix,int y);
	/**
	 * @brief A method that prints a given integer matrix to the stdout
	 * @param matrix the matrix to be printed
	 * @param x the number of columns the matrix has
	 * @param y the number of rows the matrix has
	 *
	 */
	void printMatrix(int **matrix,int x,int y);
	/**
	 * @brief A function that prints the statistics extracted from the LCS algorithm
	 * @param result the resulting string coming from the computeDiff function
	 * @param i the index of the file used as pattern in the dbFileList array
	 * @param originalFile a string containing the initial contents of the tested file
	 * @param pattern a string containing the initial contents of the file used as pattern
	 * @param value the number of matched characters returned from the computeDiff function.
	 *
	 */
	void printStatistics(const string& result, unsigned int i, const string& originalFile,const string & pattern,
			int value);

	/**
	 * @brief A method used to retrieve an high resolution time of the system.
	 * @return a double with the current system time with great resolution
	 *
	 */
	double get_time();
public:

	/**
	 * @brief A simple constructor for the CopyChecker class that initializes the fileToCheck parameter as well as sets some internal parameters to default values.
	 * @param filePath the path of the file the CopyChecker object should test
	 *
	 *
	 */
	CopyChecker(string filePath);

	/**
	 *
	 * @brief An empty constructor that sets the internal parameters to the default values.
	 *
	 *
	 */
	CopyChecker();

	/**
	 * @brief A setter for the filePath. No verification is done inside the method. If the file provided is not a good one the program will not execute the comparision.
	 * @param filePath the path of the new file to be later tested
	 *
	 */
	void setFilePath(string filePath);
	/**
	 *
	 * @brief A method that sets the database files path to the ones passed
	 * @param files a vector containing the path to all the files to be used as patterns
	 *
	 */
	void setDB(vector<string> &files);
	/**
	 * @brief A function that compares the file set as the file to be tested with the database
	 * @param print True should be passed if the output and statistics of the comparision are to be written to the stdout. True is passed by default
	 * @param minMatch a value that is to be used as the minimum number of consecutive characters that are supposed to be considered a match between any two files.This value is persistent between calls. The default value is -1 which means that the value that is already stored for this variable should not be altered
	 * @return the Error code reporting any possible error occurred while comparing files.
	 */
	CheckErrorType compareFile(bool print=true,int minMatch=-1);
	/**
	 * @brief A function that sets the minimum number of consecutive chars that should be considered a match between two files
	 * @param nr a positive number to be the new minimum number of consecutive chars to be considered a match between two files
	 *
	 */
	void setMinNrRepetedChars(int nr);

	void copyToStream(const string &str, int startPos, int nrElements, stringstream &s,
			bool marked);

	int generateDiff(int ** matrix,const string & file,const string & pattern,stringstream &s);
	void setCells(int &leftCell,int &topCell,int **matrix,int pos1,int pos2);
	int flushSavedChars(string &buff,stack<char> & theStack);
	string getRepetedSectionStartMarker();
	string getRepetedSectionEndMarker();
	void transferToStack(string &str,stack<char> & stack,bool reversedOrder);

};

#endif /* COPYCHECKER_H_ */
