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
#include "AnalysisSystem.h"
using namespace std;

int main(int argc, char** argv)
{
	int opcao = 0;
	string database, doc;
	AnalysisSystem Asystem;

	if(argc == 3)
	{

		database = argv[1];
		doc = argv[2];
		do{
			cout << "Directorio base: " << database << endl;
			cout << "Ficheiro a analisar: " << doc << endl;

			cout << "1. OK, prosseguir" << endl;
			cout << "2. Trocar ordem " << endl;
			cout << "3. Introduzir manualmente os caminhos" << endl;

			cin >> opcao;

			if(opcao == 2)
			{
				string swap = database;
				database = doc;
				doc = swap;
			}



		}while(opcao != 1 && opcao != 3);

		Asystem.setBase(database);
		Asystem.setFile(doc);
	}

	if(opcao == 3 || argc == 1)
	{
		bool go;
		do{
			go = true;
			cout << "Insira o caminho do directorio base: " ;
			cin >> database;


			try{
				Asystem.setBase(database);
			}
			catch(invalidBase &base)
			{
				go = false;
				cout << "Directorio invalido ou sem ficheiros .txt" << endl;

			}


		}while(!go);

		do{
				go = true;
				cout << "Insira o caminho do ficheiro a analisar: " ;
				cin >> doc;


				try{
					Asystem.setFile(doc);
				}
				catch(invalidFile &file)
				{
					go = false;
					cout << "Caminho ou ficheiro invalido" << endl;

				}


			}while(!go);

	}


system("pause");

}


