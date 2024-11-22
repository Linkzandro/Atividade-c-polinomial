#pragma once

#include "NoPolinomio.h"
#include <sstream>

class ListaPolinomio {
private:
	NoPolinomio* head;
	NoPolinomio* cauda;
	int tamanho = 0;
	int grau = 0;

public:
	NoPolinomio* getHead() const;
	
	int getSize() const;

	void display();

	int returnGrau();

	//void Inserir(NoPolinomio monomio);

	//sobrecarga inserir
	void Inserir(int base, int expoente);
	
	ListaPolinomio();


	~ListaPolinomio();
		
	void AlterarNo(NoPolinomio* no, int base, int potencia);
	
	void Remover(NoPolinomio* no);

	void simplificar();

	double evaluate(double x);

	void sortList();
	
	ListaPolinomio& operator+=(ListaPolinomio& lista2);

	ListaPolinomio& operator-=(ListaPolinomio& lista2);
	
	ListaPolinomio& operator*=(ListaPolinomio& lista2);

	friend ListaPolinomio operator*(const ListaPolinomio& lista1, const  ListaPolinomio& lista2);

	friend ListaPolinomio operator+(const ListaPolinomio& lista1, const ListaPolinomio& lista2);

	friend ListaPolinomio operator-(const ListaPolinomio& lista1, const ListaPolinomio& lista2);

	static ListaPolinomio* ListaString(string linha) {
		ListaPolinomio* lista=new ListaPolinomio();

		float base=0;
		int expoente = 0;
		istringstream leitor(linha);
		istringstream leitor2(linha);
		int streamSizeCounter = 0;

		while (leitor >> base) {
			streamSizeCounter += 1;
		}

		while (leitor2 >> base >> expoente ) {
			if (base != 0 || expoente != 0) {
				lista->Inserir(base, expoente);
			}
		}
		if (streamSizeCounter % 2 == 1) {

			lista->Inserir(base, 0);
		}
		return lista;

	}

};

