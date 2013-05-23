//============================================================================
// Name        : plagiarism.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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

string database="/home/mppl/Desktop/db";
string doc="/home/mppl/Desktop/file1.txt";
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

void menuLoop(){
	int opcao = 0;
	while(1){
		cout << "Directorio base: " << database << endl;
		cout << "Ficheiro a analisar: " << doc << endl;

		cout << "1. OK, comparar" << endl;
		cout << "2. Trocar ordem " << endl;
		cout << "3. Mudar caminho para base de dados" << endl;
		cout <<"4. Mudar caminho para ficheiro a testar" << endl;
		cin >> opcao;



		if(opcao==1){
			try {
				validator.setDBdirectory(database);
				validator.setFileToTest(doc);
			} catch (InputExeption & e) {
				cout<<"Invalid path given: "<<e.path<<endl;
			}
			validator.compare();
		}

		else if(opcao == 2){swap();}
		else if(opcao== 3){
			cout <<"Introduza o novo caminho para a base de dados: ";
			cin>> database;
			try {
				validator.setDBdirectory(database);
			} catch (InputExeption & e) {
				cout<<"Invalid path given: "<<e.path<<endl;
			}

		}
		else if(opcao== 4){
					cout <<"Introduza o novo caminho para o ficheiro: ";
					cin>> doc;
					try {
						validator.setFileToTest(doc);
					} catch (InputExeption & e) {
						cout<<"Invalid path given: "<<e.path<<endl;
					}

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





//system("pause");

}


