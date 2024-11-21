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
	NoPolinomio* getHead() const {
		return head;
	}

	void display() {
		simplificar();
		NoPolinomio* atual = head;
		while (atual != nullptr) {
			cout << *atual;
			atual = atual->getProximo();
			if (atual != nullptr && atual->getBase() > 0) {
				cout << "+";
			}

		}
		cout << endl;
	}
	int returnGrau() {
		if (head == nullptr) return 0;
		NoPolinomio* atual = head;
		int grauVar = 0;
		while (atual != nullptr) {
			if (grauVar < atual->getPotencia()) grauVar = atual->getPotencia();
			atual = atual->getProximo();
		}
		grau = grauVar;
		return grau;
	}
	void Inserir(NoPolinomio* monomio) {
		monomio->setProximo(head);
		head = monomio;
		tamanho += 1;
	}

	//sobrecarga inserir
	void Inserir(int base, int expoente) {


		if (base == 0)
			return;

		NoPolinomio* node = new NoPolinomio(base, expoente);

		if (!head || node->getPotencia() > head->getPotencia()) {
			node->setProximo(head);
			head = node;
		}
		else {
			NoPolinomio* current = head;

			while (current->getProximo() != nullptr && node->getPotencia() < current->getProximo()->getPotencia()) {
				current = current->getProximo();
			}

			node->setProximo(current->getProximo());
			current->setProximo(node);
		}



		//NoPolinomio* monomio = new NoPolinomio(base, expoente);
		//monomio->setProximo(head);
		//head = monomio;
		//tamanho += 1;
	}

	ListaPolinomio() {
		head = nullptr;
		cauda = nullptr;
		grau = 0;
		tamanho = 0;
	}

	~ListaPolinomio() {
		while (head != nullptr) {
			NoPolinomio* temp = head;
			head = head->getProximo();
			delete temp;
		}
	}
	void AlterarNo(NoPolinomio* no, int base, int potencia) {
		no->setBase(base);
		no->setPotencia(potencia);
	}
	void Remover(NoPolinomio* no) {
		if (no == nullptr || head == nullptr) {
			return;
		}

		if (head == no) {
			head = head->getProximo();
		}

		NoPolinomio* temp = head;
		NoPolinomio* previous = nullptr;
		while (temp != nullptr) {
			if (temp == no) {

			}
		}
		tamanho -= 1;
	}

	void simplificar() {
		if (head == nullptr) return;

		NoPolinomio* atual = head;

		while (atual != nullptr) {
			NoPolinomio* atual2 = atual;

			while (atual2->getProximo() != nullptr) {
				if (atual2->getProximo()->getPotencia() == atual->getPotencia()) {
					atual->setBase(atual->getBase() + atual2->getProximo()->getBase());
					NoPolinomio* temp = atual2->getProximo();
					atual2->setProximo(atual2->getProximo()->getProximo());
					delete temp;
				}
				else {
					atual2 = atual2->getProximo();
				}
			}
			atual = atual->getProximo();
		}

	}
	double evaluate(double x) {
		double resultado = 0.0;
		NoPolinomio* atual = head;

		while (atual != nullptr) {
			resultado += atual->getBase() * pow(x, atual->getPotencia());
			atual = atual->getProximo();
		}

		return resultado;
	}

	void sortList() {
		if (head == nullptr || head->getProximo() == nullptr) {
			return;
		}

		NoPolinomio* ordenada = nullptr;
		NoPolinomio* atual = head;

		while (atual != nullptr) {
			NoPolinomio* proximo = atual->getProximo();
			atual->setProximo(nullptr);

			if (ordenada == nullptr || ordenada->getPotencia() < atual->getPotencia()) {
				atual->setProximo(ordenada);
				ordenada = atual;
			}
			else {
				NoPolinomio* temp = ordenada;
				while (temp->getProximo() != nullptr && temp->getProximo()->getPotencia() > atual->getPotencia()) {
					temp = temp->getProximo();
				}
				atual->setProximo(temp->getProximo());
				temp->setProximo(atual);
			}
			atual = proximo;
		}
		head = ordenada;
	}

	// sobrecargas da lista
	ListaPolinomio& operator+=(ListaPolinomio& lista2) {
		NoPolinomio* atual = lista2.getHead();
		while (atual != nullptr) {
			this->Inserir(atual->getBase(), atual->getPotencia());
			atual = atual->getProximo();
		}
		this->simplificar();
		return *this;
	}

	ListaPolinomio& operator+(ListaPolinomio& lista2) {
		ListaPolinomio lista = *this;
		lista += lista2;
		return lista;
	}

	ListaPolinomio& operator-=(ListaPolinomio& lista2) {
		NoPolinomio* atual = lista2.getHead();
		while (atual != nullptr) {
			this->Inserir(atual->getBase() * -1, atual->getPotencia());
			atual = atual->getProximo();
		}
		this->simplificar();
		return *this;
	}

	ListaPolinomio& operator-(ListaPolinomio& lista2) {
		ListaPolinomio lista = *this;
		lista -= lista2;
		return lista;
	}

	ListaPolinomio& operator*=(ListaPolinomio& lista2) {
		ListaPolinomio final;

		NoPolinomio* atual = lista2.getHead();
		while (atual != nullptr) {
			NoPolinomio* atual2 = lista2.getHead();
			while (atual2 != nullptr) {
				int baseFinal = atual->getBase() * atual2->getBase();
				int potenciaFinal = atual->getPotencia() + atual2->getPotencia();
				final.Inserir(baseFinal, potenciaFinal);
				atual2 = atual2->getProximo();
			}
			atual = atual->getProximo();
		}
		this->simplificar();
		*this = final;
		return *this;
	}




};

ListaPolinomio operator*(const ListaPolinomio& lista1, const  ListaPolinomio& lista2) {
	ListaPolinomio ListaFinal;

	NoPolinomio* atual = lista1.getHead();
	while (atual != nullptr) {
		NoPolinomio* atual2 = lista2.getHead();
		while (atual2 != nullptr) {
			int baseFinal = atual->getBase() * atual2->getBase();

			int potenciaFinal = atual->getPotencia() + atual2->getPotencia();
			ListaFinal.Inserir(baseFinal, potenciaFinal);

			atual2 = atual2->getProximo();
		}
		atual = atual->getProximo();
	}

	return ListaFinal;
}
