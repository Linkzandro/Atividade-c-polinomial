#pragma once

#include "NoPolinomio.h"

class ListaPolinomio {
private:
	NoPolinomio* head;
	NoPolinomio* cauda;
	int tamanho = 0;
	int grau = 0;

	void clear() {
		NoPolinomio* atual = head;
		while (atual != nullptr) {
			NoPolinomio* temp = atual;
			atual = atual->getProximo();
			delete temp;
		}
		head = nullptr;
	}

	void copyLista(ListaPolinomio& outro) {
		if (outro.getHead() == nullptr) {
			head = nullptr;
			return;
		}

		head = new NoPolinomio(outro.getHead()->getBase(), outro.getHead()->getPotencia());
		NoPolinomio* atualOutro = outro.getHead()->getProximo();
		NoPolinomio* atualEsse = head;

		while (atualOutro != nullptr) {
			atualEsse->setProximo(new NoPolinomio(atualOutro->getBase(), atualOutro->getPotencia()));
			atualEsse = atualEsse->getProximo();
			atualOutro = atualOutro->getProximo();
		}
	}

public:
	NoPolinomio* getHead() const;
	
	void display();

	int returnGrau();

	void Inserir(NoPolinomio* monomio);

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

	friend ListaPolinomio& operator+(const ListaPolinomio& lista1, const ListaPolinomio& lista2);

	friend ListaPolinomio& operator-(const ListaPolinomio& lista1, const ListaPolinomio& lista2);

};

