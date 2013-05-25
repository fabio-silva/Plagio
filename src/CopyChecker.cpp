/*
 * CopyChecker.cpp
 *
 *  Created on: May 20, 2013
 *      Author: root
 */

#include "CopyChecker.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"



string CopyChecker::longestCommonSubsequence(ifstream & file1,ifstream & file2,int *sizeOfMatch) {

	string s1=extractString(file1);
	string s2=extractString(file2);

	return longestCommonSubsequence(s1,s2,sizeOfMatch);

}

string CopyChecker::longestCommonSubsequence(const string& str1,const string& str2,int *sizeOfMatch) {
		LCSTime=get_time();
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
		(*sizeOfMatch)=generateDiff(LCSMatrix,str1,str2,s);
		deleteMatrix(LCSMatrix,len2);
		LCSTime-=get_time();
		LCSTime=-LCSTime;
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
CopyChecker::CopyChecker(): minNrRepetedChars(10),validMatches(0),LCSTime(-1){

}

CopyChecker::CopyChecker(string filePath):fileToCheckPath(filePath),minNrRepetedChars(10),validMatches(0),LCSTime(-1) {
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
	bool marked=false;

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
				marked=true;
			}
			copyToStream(str1,0,charsWaitingForPrint,s,marked);
		}
	}

	else if(leftCell>topCell){

		if(pos1>0){computeDiff(matrix,str1,str2,pos1-1,pos2,0,s);}

		s<<str1[pos1-1];
		if(charsWaitingForPrint>0){
			if(charsWaitingForPrint>=minNrRepetedChars){//if it's a sequence meaningfull to be noticed as a copied one
				validMatches+=charsWaitingForPrint;
				marked=true;
			}
			copyToStream(str1,pos1,charsWaitingForPrint,s,marked);

		}
	}
	else if(topCell>=leftCell){

		if(pos2>0){computeDiff(matrix,str1,str2,pos1,pos2-1,0,s);}

		if(charsWaitingForPrint>0){

			if(charsWaitingForPrint>=minNrRepetedChars){//if it's a sequence meaningfull to be noticed as a copied one
				validMatches+=charsWaitingForPrint;
				marked=true;
			}
			copyToStream(str1,pos1,charsWaitingForPrint,s,marked);
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

void CopyChecker::setDB( vector<string> &files) {
	dbFileList.clear();
	for(unsigned int i=0;i<files.size();i++){
		dbFileList.push_back(files[i]);
	}
}

void CopyChecker::setFilePath(string filePath) {
	fileToCheckPath=filePath;
	fileToCheck.close();
	fileToCheck.open(filePath.c_str());
}

double CopyChecker::get_time() {
	#ifdef _WIN32
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	return (double)t.QuadPart/(double)f.QuadPart;
	#else
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec*1e-6;
	#endif


}

void CopyChecker::setMinNrRepetedChars(int nr) {
	if(nr>=0){
		minNrRepetedChars=nr;
	}
}

void CopyChecker::printStatistics(const string& result, unsigned int i,
		const string& testedFileContent,const string & pattern, int value) {
	double percentage=value/(double)testedFileContent.size()*100;
	cout << endl << "#########START##########" << endl << result << endl
			<< "#########END##########" << endl;
	cout << "|||||||||||||||Estatistica|||||||||||||||" << endl;
	cout << "Tested file name: "<<fileToCheckPath<<endl;
	cout << "Pattern file name: " << dbFileList[i] << endl;
	cout << "Tested File size: " << testedFileContent.size()<<" chars"<< endl;
	cout << "Pattern File size: " << pattern.size()<<" chars"<< endl;
	cout << "Min Matching size: " << minNrRepetedChars<<" chars"<<endl;
	cout << "Matched: " << validMatches <<" chars"<< endl;
	cout << "Similarity: " << percentage << "%" << endl;
	cout << "Time used: " << LCSTime<< " seconds"<<endl;
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

			ifstream patternFile;
			int value;
			patternFile.open(dbFileList[i].c_str());

			if(patternFile.good()){
				string pattern=extractString(patternFile);
				string result=longestCommonSubsequence(s,pattern,&value);
				double percentage=value*100/(double)s.size();
				repetedCharsArray.push_back(percentage);
				if(print){
				printStatistics(result, i, s,pattern, value);
				}


			}

		}
		if(repetedCharsArray.size()==0){return NoDBFilesError;}
		return NoError;
}

void CopyChecker::copyToStream(const string& str, int startPos, int nrElements,stringstream& s, bool marked) {
	string subStr=str.substr(startPos,nrElements);
	if(marked){

		s<<KRED<<subStr<<KNRM;
	}
	else{
		s<<subStr;
	}

}

int CopyChecker::generateDiff(int** matrix,const string& file,const string& pattern, stringstream &s) {

	stack<char> pile;
	string waitingStr;
	int file_position=file.size()-1;
	int pattern_position=pattern.size()-1;
	int leftCell,topCell;
	int matches=0;

	while(file_position>=0 && pattern_position>=0){

		setCells(leftCell,topCell,matrix,file_position+1,pattern_position+1);

		if(pattern_position<0){//if we reached the end of the pattern
			matches+=flushSavedChars(waitingStr,pile);
			while(file_position>=0){//place the remaining chars on the stack
				pile.push(file[file_position--]);
			}
			break;
		}

		else if(file[file_position]==pattern[pattern_position]){
			waitingStr+=file[file_position];//place it on a temp string
			file_position--;
			pattern_position--;
		}

		else if(leftCell>topCell){
			matches+=flushSavedChars(waitingStr,pile);//place all the chars waiting
			pile.push(file[file_position]);//place this char
			file_position--;//decrement the file_position
		}
		else if(topCell>=leftCell){
			matches+=flushSavedChars(waitingStr,pile);
			pattern_position--;
		}



	}
	matches+=flushSavedChars(waitingStr,pile);//some thing might still be waiting to go to the stack

	//now print every thing
	while(!pile.empty()){
		s<<pile.top();
		pile.pop();
	}
	return matches;

}

void CopyChecker::setCells(int& leftCell, int& topCell, int** matrix,
		int pos1, int pos2) {

	if(pos1<=0 || pos2<0){leftCell=-1;}
	else{leftCell=matrix[pos2][pos1-1];}

	if(pos2<=0 || pos1<0){topCell=-1;}
	else{topCell=matrix[pos2-1][pos1];}
}

int CopyChecker::flushSavedChars(string& buff, stack<char>& theStack) {
	int matched=0;
	if(!buff.empty()){
		int ptr=0;
		if(buff.size()>=minNrRepetedChars){

			string marker=getRepetedSectionEndMarker();
			transferToStack(marker,theStack,true);//true to reverse order since the string

			transferToStack(buff,theStack,false);

			marker=getRepetedSectionStartMarker();
			transferToStack(marker,theStack,true);
			matched=buff.size();

		}

		else{
			transferToStack(buff,theStack,false);
		}



	}
	buff.clear();//clear the buff
	return matched;
}



string CopyChecker::getRepetedSectionStartMarker() {
#ifdef _WIN32
	return "\n*******************";
#else
	return KRED;
#endif

}

string CopyChecker::getRepetedSectionEndMarker() {
#ifdef _WIN32
	return "*******************\n";
#else
	return KNRM;
#endif
}

void CopyChecker::transferToStack(string& str, stack<char>& stack,
		bool reversedOrder) {
	int ptr;
	if(reversedOrder){
		ptr=str.size()-1;
		while(ptr>=0){
			stack.push(str[ptr--]);
		}
	}
	else{
		ptr=0;
		while(ptr<str.size()){
			stack.push(str[ptr++]);
		}
	}


}
