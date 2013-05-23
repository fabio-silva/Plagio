/*
 * CopyChecker.cpp
 *
 *  Created on: May 20, 2013
 *      Author: root
 */

#include "CopyChecker.h"


string CopyChecker::longestCommonSubsequence(ifstream & file1,ifstream & file2,int *sizeOfMatch) {

	string s1=extractString(file1);
	string s2=extractString(file2);

	return longestCommonSubsequence(s1,s2,sizeOfMatch);

}

string CopyChecker::longestCommonSubsequence(const string& str1,const string& str2,int *sizeOfMatch) {
		int len1=str1.size()+1;
		int len2=str2.size()+1;

		int **LCSMatrix=getMatrix(len1,len2);

		makeFirstRowAndCollumnsZero(LCSMatrix,len1,len2);

		char char1,char2;
		for(int row=1;row<len2;row++){


			char2=str2[row-1];
			for(int col=1;col<len1;col++){
				int upperEl=LCSMatrix[row-1][col];
				int leftEl=LCSMatrix[row][col-1];

				char1=str1[col-1];

				if(char1==char2){
					LCSMatrix[row][col]=LCSMatrix[row-1][col-1]+1;
				}

				else{
					LCSMatrix[row][col]=_max(leftEl,upperEl);
				}
			}
		}
		//printMatrix(LCSMatrix,len1,len2);

		stringstream s;
		validMatches=0;
		(*sizeOfMatch)=computeDiff(LCSMatrix,str1,str2,str1.size(),str2.size(),0,s);
		deleteMatrix(LCSMatrix,len2);
		return s.str();

}




int CopyChecker::nrOfCharsInFile(ifstream & in) {
	int nr=0;
	in.seekg(0);//place file pointer at start

	while(in.peek()!=-1){
		in.get();
		nr++;
	}
	return nr;
}

int** CopyChecker::getMatrix(int x,int y) {
	int ** matrix= new int *[y];
	for(int i=0;i<y;i++){
		matrix[i]=new int[x];
	}
	return matrix;
}

void CopyChecker::deleteMatrix(int** matrix,int y) {
	for(int i=0;i<y;i++){
		delete [] matrix[i];
	}
	delete[] matrix;
}

CopyChecker::CopyChecker(string filePath):fileToCheckPath(filePath),minNrRepetedChars(10),validMatches(0) {
	fileToCheck.open(filePath.c_str());
}




void CopyChecker::makeFirstRowAndCollumnsZero(int ** matrix,int x, int y) {

	for (int i = 0; i < x; i++) {
		matrix[0][i] = 0;
	}
	for (int i = 0; i < y; i++) {
		matrix[i][0]=0;
	}
}

string CopyChecker::longestCommonSubstring(ifstream& file1, ifstream& file2) {
	int lenF1=nrOfCharsInFile(file1);
	int lenF2=nrOfCharsInFile(file2);
	int highestRecord=0;
	string s;

	int **matrix = getMatrix(lenF1 + 1, lenF2 + 1);
	makeFirstRowAndCollumnsZero(matrix,lenF1, lenF2);
	char file1Ch,file2Ch;

	file2.seekg(0);
	for(int row=1;row<lenF2+1;row++){

		while((file2Ch=file2.get())=='\n');//get next valid char

		file1.seekg(0);
		for(int col=1;col<lenF1+1;col++){
			while((file1Ch=file1.get())=='\n');//get next valid char

			if(file1Ch==file2Ch){
				matrix[row][col]=matrix[row-1][col-1]+1;
				int value=matrix[row][col];
				if(value>highestRecord){//if we got a new record
					highestRecord=value;
					file1.seekg(-value,ios_base::cur);//move value positions back
					s.clear();
					while(value){
						s+=file1.get();
						value--;

					}
				}
			}
			else{matrix[row][col]=0;}

		}
	}

	return s;


}

int CopyChecker::computeDiff(int **matrix,const string &str1,const string &str2,int pos1,int pos2,int charsWaitingForPrint,stringstream &s) {

	int leftCell,topCell;

	if(pos1==0){leftCell=-1;}
	else{leftCell=matrix[pos2][pos1-1];}

	if(pos2==0){topCell=-1;}
	else{topCell=matrix[pos2-1][pos1];}

	if(str2[pos2-1]==str1[pos1-1]){//if we got a match
		if(pos1>0 && pos2>0){
			computeDiff(matrix,str1,str2,pos1-1,pos2-1,charsWaitingForPrint+1,s);//call printDiff and say we have a char waiting to be printed
		}
		else{
			if(charsWaitingForPrint>=minNrRepetedChars){
				validMatches+=charsWaitingForPrint;
				s<<"\n*****"<<str1.substr(0,charsWaitingForPrint)<<"*****\n";
			}
			else{
				s<<str1.substr(0,charsWaitingForPrint);

			}
		}
	}

	else if(leftCell>topCell){

		if(pos1>0){computeDiff(matrix,str1,str2,pos1-1,pos2,0,s);}

		s<<str1[pos1-1];
		if(charsWaitingForPrint>0){
			if(charsWaitingForPrint>=minNrRepetedChars){//if it's a sequence meaningfull to be noticed as a copied one
				validMatches+=charsWaitingForPrint;
				s<<"\n*****"<<str1.substr(pos1,charsWaitingForPrint)<<"*****\n";
			}
			else{//if it's not meaningfull
				s<<str1.substr(pos1,charsWaitingForPrint);
			}
		}
	}
	else if(topCell>=leftCell){

		if(pos2>0){computeDiff(matrix,str1,str2,pos1,pos2-1,0,s);}

		if(charsWaitingForPrint>0){

			if(charsWaitingForPrint>=minNrRepetedChars){//if it's a sequence meaningfull to be noticed as a copied one
				validMatches+=charsWaitingForPrint;
				s<<"\n*****"<<str1.substr(pos1,charsWaitingForPrint)<<"*****\n";
			}

			else{//if it's not meaningfull
				s<<str1.substr(pos1,charsWaitingForPrint);
			}
		}

	}

	return validMatches;

}

string CopyChecker::extractString(ifstream & f) {

	string s;
	if(!f.good()){
		return s;
	}

	f.seekg(0);
	while(f.peek()!=-1){
		s+=f.get();
	}
	return s;
}

void CopyChecker::printMatrix(int** matrix, int x, int y) {
	for(int i=0;i<y;i++){
		for(int f=0;f<x;f++){
			cout<<matrix[i][f]<<" ";
		}
		cout<<endl;
	}
}

void CopyChecker::setDB( vector<string> files) {
	dbFileList=files;
}

void CopyChecker::setMinNrRepetedChars(int nr) {
	if(nr>=0){
		minNrRepetedChars=nr;
	}
}

void CopyChecker::printStatistics(const string& result, unsigned int i,
		const string& s, int value) {
	double percentage=value/(double)s.size()*100;
	cout << endl << "#########START##########" << endl << result << endl
			<< "#########END##########" << endl;
	cout << "|||||||||||||||Estatistica|||||||||||||||" << endl;
	cout << "Tested file name: "<<fileToCheckPath<<endl;
	cout << "Pattern file name: " << dbFileList[i] << endl;
	cout << " Original size: " << s.size()<<" chars"<< endl;
	cout << " Min Matching size: " << minNrRepetedChars<<" chars"<<endl;
	cout << " Matched: " << value <<" chars"<< endl;
	cout << " Similarity: " << percentage << "%" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||"<<endl;
}

CheckErrorType CopyChecker::compareFile(bool print,int minMatch) {
	if(minMatch>=0){//if its valid
		minNrRepetedChars=minMatch;
	}



	if(!fileToCheck.good()){return NoFileError;}

		if(dbFileList.size()==0){return NoDBFilesError;}


		string s=extractString(fileToCheck);
		repetedCharsArray.clear();
		for(unsigned int i=0;i<dbFileList.size();i++){

			ifstream f2;
			int value;
			f2.open(dbFileList[i].c_str());

			if(f2.good()){
				string s2=extractString(f2);
				string result=longestCommonSubsequence(s,s2,&value);
				double percentage=value*100/(double)s.size();
				repetedCharsArray.push_back(percentage);
				if(print){
				printStatistics(result, i, s, value);
				}


			}

		}
		if(repetedCharsArray.size()==0){return NoDBFilesError;}
		return NoError;
}


