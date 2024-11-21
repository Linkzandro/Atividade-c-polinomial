#include "ListaPolinomio.h"
#include <iostream>

using namespace std;


int main() {
	ListaPolinomio lista;
	ListaPolinomio lista2;
	lista.Inserir(2, 2);
	lista.Inserir(2, 8);
	lista.Inserir(2, 3);
	lista2.Inserir(4, 3);
	lista2.Inserir(-2, 4);

	//lista*=lista2;
	ListaPolinomio lista3 = lista * lista2;
	//lista = lista * lista2;
	lista3.display();




	return 0;
}