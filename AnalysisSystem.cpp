#include "AnalysisSystem.h"


AnalysisSystem::AnalysisSystem(){}
AnalysisSystem::AnalysisSystem(string base, string file)
{
	fstream baseStream, fileStream;
	baseStream.open(base.c_str());
	fileStream.open(file.c_str());

	if(!baseStream) throw  invalidBase(base);
	if(!fileStream) throw  invalidFile(file);
	this->base = base;
	this->file = file;
}

void AnalysisSystem::setBase(string b)
{


	string fullSearchPath = b + "\\*.txt";
	hFind = FindFirstFile( fullSearchPath.c_str(), &FindData );

	if( hFind == INVALID_HANDLE_VALUE ) throw  invalidBase(b);

	base = b;
	firstFile = b + "\\" + FindData.cFileName;
}


string AnalysisSystem::getFirstFile()
{
	return firstFile;
}
void AnalysisSystem::setFile(string f)
{
	fstream aux;

	aux.open(f.c_str());

	if(!aux) throw invalidFile(f);
	file = f;
}

string AnalysisSystem::getNextFile()
{
    if(FindNextFile(hFind, &FindData) > 0)
    {
        string filePath = base + "\\" + FindData.cFileName;
        ifstream in( filePath.c_str() );
        if( in ) return filePath;


    }

     return "";

}

