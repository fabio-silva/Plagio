
/**
 * @file plagiarism
 * @brief A file containing the main function and some other basic functions
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

string database="/home/mppl/Desktop/newDB";
string doc="/home/mppl/Desktop/db/500k.txt";
#ifdef _WIN32
	WindowsInputValidator validator;
#else
	LinuxInputValidator validator;
#endif



/**
 * @fn A function that swaps the value of the database and doc strings
 *
 */
void swap(){
	string temp=database;
	database=doc;
	doc=temp;
}

/**
 * @fn A function that implements the compare command of the program
 *
 */
void compare(){
	try {
		validator.setDBdirectory(database);
		validator.setFileToTest(doc);
		validator.compare();
	} catch (InputException & e) {
		cout<<"Invalid path given: "<<e.path<<endl;
	}
}

/**
 * @fn A function that implements the change data base folder functionality of this program
 *
 *
 */
void changeDB(){cout <<"Introduza o novo caminho para a base de dados: " << endl;
string temp=database;
cin>> database;
try {
	validator.setDBdirectory(database);
} catch (InputException & e) {
	cout<<"Invalid path given: "<<e.path<<endl;
	database=temp;
}
}

/**
 * @fn A function that implements the change file path functionality of this program
 *
 *
 */
void changeFilePath(){
	cout <<"Introduza o novo caminho para o ficheiro: " << endl;
	string temp=doc;
	cin>> doc;
	try {
	validator.setFileToTest(doc);
	} catch (InputException & e) {
		cout<<"Invalid path given: "<<e.path<<endl;
		doc=temp;
	}

}

/**
 * @fn A function that implements the change minimum number of necessary chars for a match functionality of this program
 *
 *
 */

void setMinimum(){
	int minimo;
	cout <<"Introduz o novo numero minimo: ";
	cin >> minimo;
	validator.setMinimum(minimo);
}

/**
 * @fn A function with an infinite loop that prompts the user with a menu and asks it for input
 *
 *
 */

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
		cout <<"6. Exit"<<endl;
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

			case 6:
				exit(0);
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


