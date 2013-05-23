
/**
 * @mainpage A simple plagiarism checker that searches common sequences of characters between a file and a database of files
 *
 *
 *
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef _WIN32
#include "WindowsInputValidator.h"
#else
#include "LinuxInputValidator.h"
#endif
using namespace std;

string database="C:\\Users\\fabio\\Desktop\\FEUP";
string doc="C:\\Users\\fabio\\Desktop\\f.txt";
#ifdef _WIN32
	WindowsInputValidator validator;
#else
	LinuxInputValidator validator;
#endif





void swap(){
	string temp=database;
	database=doc;
	doc=temp;
}

void compare(){
	try {
		validator.setDBdirectory(database);
		validator.setFileToTest(doc);
		validator.compare();
	} catch (InputExeption & e) {
		cout<<"Invalid path given: "<<e.path<<endl;
	}
}
void changeDB(){cout <<"Introduza o novo caminho para a base de dados: " << endl;
string temp=database;
cin>> database;
try {
	validator.setDBdirectory(database);
} catch (InputExeption & e) {
	cout<<"Invalid path given: "<<e.path<<endl;
	database=temp;
}
}
void changeFilePath(){
	cout <<"Introduza o novo caminho para o ficheiro: " << endl;
	string temp=doc;
	cin>> doc;
	try {
	validator.setFileToTest(doc);
	} catch (InputExeption & e) {
		cout<<"Invalid path given: "<<e.path<<endl;
		doc=temp;
	}

}
void setMinimum(){
	int minimo;
	cout <<"Introduz o novo numero minimo: ";
	cin >> minimo;
	validator.setMinimum(minimo);
}
void menuLoop(){
	int opcao = 0;
	while(1){
		cout << "Directorio base: " << database << endl;
		cout << "Ficheiro a analisar: " << doc << endl;

		cout <<"1. OK, comparar" << endl;
		cout <<"2. Trocar ordem " << endl;
		cout <<"3. Mudar caminho para base de dados" << endl;
		cout <<"4. Mudar caminho para ficheiro a testar" << endl;
		cout <<"5. Alterar numero minimo de caracteres para correspondencia" <<endl;
		cin >> opcao;


		switch (opcao) {
			case 1:
				compare();
				break;
			case 2:
				swap();
				break;
			case 3:
				changeDB();
				break;
			case 4:
				changeFilePath();
				break;
			case 5:
				setMinimum();
				break;

			default:
				break;
		}


	}


}

int main(int argc, char** argv)
{


	if(argc == 3){
		database = argv[1];
		doc = argv[2];
	}

	menuLoop();




}


