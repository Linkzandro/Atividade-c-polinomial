#include "ListaPolinomio.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


int main() {
	
	setlocale(LC_ALL, "portuguese");

	ifstream comando("../comandos.txt");
	if (comando.is_open() == false) {
		cout << "erro em execução"; 
		return 100;
	}
	
	int numero=0;
	string linha;
	string polinomio;


	while (getline(comando, linha)) {
		numero +=1;
		if (linha == "+") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);

			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista2;
			lista2 = *lista2.ListaString(polinomio);

			ListaPolinomio lista3 = lista1 + lista2;
			

			cout << "resultado da soma dos polinomios passados nas linhas " << numero - 1 << " e " << numero << endl;
			lista3.display();

			//valores passados foram salvos no heap, usando desconstrutor pra liberar a memória
			lista1.~ListaPolinomio();
			lista2.~ListaPolinomio();
		}
		else if (linha == "-") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);

			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista2;
			lista2 = *lista2.ListaString(polinomio);

			ListaPolinomio lista3 = lista1 - lista2;


			cout << "resultado da subtração dos polinomios passados nas linhas "<<numero-1<<" e "<<numero << endl;
			lista3.display();

			//valores passados foram salvos no heap, usando desconstrutor pra liberar a memória
			lista1.~ListaPolinomio();
			lista2.~ListaPolinomio();

		}else if (linha == "*") {
			getline(comando, polinomio);
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);

			getline(comando, polinomio);
			ListaPolinomio lista2;
			lista2 = *lista2.ListaString(polinomio);

			ListaPolinomio lista3 = lista1 * lista2;


			cout << "resultado da multiplicação dos polinomios passados nas linhas " << numero - 1 << " e " << numero << endl;
			lista3.display();

			//valores passados foram salvos no heap, usando desconstrutor pra liberar a memória
			lista1.~ListaPolinomio();
			lista2.~ListaPolinomio();
		}

		else if (linha == "g" || linha=="G") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1=*lista1.ListaString(polinomio);
			cout << "o polinomio passado na linha "<<numero<<" tem grau " << lista1.returnGrau()<<endl;
			lista1.~ListaPolinomio();
		}

		else if (linha == "d" || linha == "D") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);
			cout << "Polinomio da linha " << numero;
			lista1.display();
			lista1.~ListaPolinomio();

		}else if (linha == "a" || linha == "A") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);
			cout << "passe um valor x para calcular o polinomio da linha "<<numero<<", veja abaixo" << endl;
			lista1.display();
			double x = 0;
			cin >> x;
			lista1.evaluate(x);
			lista1.~ListaPolinomio();

		}else if (linha == "t" || linha == "T") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);
			cout << "o tamanho da lista passada na linha " <<numero<< " é: " << lista1.getSize()<<endl;
			lista1.~ListaPolinomio();

		}else if (linha == "p" || linha == "P") {
			getline(comando, polinomio);
			numero += 1;
			ListaPolinomio lista1;
			lista1 = *lista1.ListaString(polinomio);
			cout << "imprimindo lista passada na linha "<<numero<<endl;
			lista1.display();
			lista1.~ListaPolinomio();

		}
		else {
			cout << "valores da linha " << numero << " não estão conforme o esperado" << endl;
		}

		cout << "" << endl;
		cout << "" << endl;

	}
	
	

	
	


	/*
	ListaPolinomio lista;
	ListaPolinomio lista2;
	lista.Inserir(2, 2);
	lista.Inserir(2, 8);
	lista.Inserir(2,3);
	lista2.Inserir(4, 3);
	lista2.Inserir(-2, 4);

	//lista*=lista2;
	ListaPolinomio lista3 = lista - lista2;
	//lista = lista * lista2;
	lista3.sortList();
	lista3.display();
	*/



	return 0;
}