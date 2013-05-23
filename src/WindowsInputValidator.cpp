#ifdef _WIN32
#include "WindowsInputValidator.h"
#include "LinuxInputValidator.h"

WindowsInputValidator::WindowsInputValidator() {checker = new CopyChecker();}
WindowsInputValidator::WindowsInputValidator(string base, string file)
{
	fstream baseStream, fileStream;
	checker = new CopyChecker();
	baseStream.open(base.c_str());
	fileStream.open(file.c_str());

	if(!baseStream) throw InvalidDBaseFolder(base);
	if(!fileStream) throw InvalidFile(file);
	this->base = base;
	this->file = file;
}

void WindowsInputValidator::setDBdirectory(string dbPath)
{

	string fullSearchPath = dbPath + "\\*.txt";
	hFind = FindFirstFile( fullSearchPath.c_str(), &FindData );

	if( hFind == INVALID_HANDLE_VALUE ) throw InvalidDBaseFolder(dbPath);

	base = dbPath;
	firstFile = dbPath + "\\" + FindData.cFileName;

	vector<string> ficheiros;
	string f = getNextFile();
	ficheiros.push_back(firstFile);

	while(f.compare("") != 0)
	{
		ficheiros.push_back(f);
		f = getNextFile();
	}

	checker->setDB(ficheiros);
}

string WindowsInputValidator::getFirstFile()
{
	return firstFile;
}
void WindowsInputValidator::setFileToTest(string filePath)
{
	fstream aux;

	aux.open(filePath.c_str());

	if(!aux.good()) throw InvalidFile(filePath);
	file = filePath;

	checker->setFilePath(file);
}

void WindowsInputValidator:: setMinimum(int m)
{
	checker->setMinNrRepetedChars(m);
}

string WindowsInputValidator::getNextFile()
{
	if(FindNextFile(hFind, &FindData) > 0)
	{
		string filePath = base + "\\" + FindData.cFileName;
		ifstream in( filePath.c_str() );
		if( in ) return filePath;

	}

	return "";

}

void WindowsInputValidator::compare(bool print,int nr)
{

	setFileToTest(file);
	setDBdirectory(base);


	checker->compareFile(print,nr);
}
#endif
