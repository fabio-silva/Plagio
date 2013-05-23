/*
 * LinuxInputValidator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: root
 */
#ifndef _WIN32
#include "LinuxInputValidator.h"


void LinuxInputValidator::setDBdirectory(string db) {


	vector<string> dbFilesList;
	if(db[db.size()-1]!='/'){	db+='/';}



	DIR *d=opendir(db.c_str());
	if(d==NULL){throw InvalidDBaseFolder(db);}//couldn't open it

	struct dirent *dir_entry;
	bool firstOne=true;

	while((dir_entry=readdir(d))!=NULL){
		if(dir_entry->d_type==DT_REG && isTXT(string(dir_entry->d_name))){
			string fileName=db+dir_entry->d_name;
			fstream fileStream;
			fileStream.open(fileName.c_str());

			if(fileStream.good()){
				if(firstOne){
					firstOne=false;
				}
				dbFilesList.push_back(fileName);

			}
			fileStream.close();
		}
	}
	if(firstOne){throw InvalidDBaseFolder(db);}//if we didn't get at least one

	checker->setDB(dbFilesList);
}

bool LinuxInputValidator::isTXT(string fileName) {
	string extension=fileName.substr(fileName.length()-4);
	string pattern=".txt";
	return(extension.compare(pattern)==0);
}

void LinuxInputValidator::setFileToTest(string fPath) {
	fstream f;
	f.open(fPath.c_str());
	if(f.good() && isTXT(fPath)){//if it's good and it's a txt
		f.close();
		checker->setFilePath(fPath);
		return;
	}
	throw InvalidFile(fPath);
}

LinuxInputValidator::LinuxInputValidator() {
	checker=new CopyChecker();
}

void LinuxInputValidator::compare() {
	int ret=checker->compareFile();
}
#endif
