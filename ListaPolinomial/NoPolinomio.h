
#pragma once

#include <iostream>
#include <cmath>
using namespace std;
class NoPolinomio
{
	private:
		int base;
		int potencia;
		NoPolinomio* proximo;
		

	public:
		NoPolinomio(int b, int p) {
			base = b;
			potencia = p;
			proximo = nullptr;
		}

		NoPolinomio* getProximo() {
			return proximo;
		}
		void setProximo(NoPolinomio *p) {
			proximo=p;
		}
		int getBase() {
			return base;
		}
		void setBase(int p) {
			base=p;
		}
		int getPotencia() {
			return potencia;
		}
		void setPotencia(int p) {
			potencia = p;
		}
	
		NoPolinomio& operator+=(NoPolinomio& no) {
			if (potencia == no.getPotencia()) {
				base += no.getBase();
			}
			
			return *this;
			
		}

		NoPolinomio operator+(NoPolinomio& no) {
			if (potencia != no.getPotencia()) {
				return *this;
			}
			return NoPolinomio(base + no.getBase(), potencia);
		}

		bool operator==(NoPolinomio& no) {
			return (base == no.getBase() && potencia==no.getPotencia());
		}
		

		friend ostream& operator<<(ostream& os, NoPolinomio& monomio);
		
};


ostream& operator<<(ostream& os, NoPolinomio& monomio) {
	os << monomio.getBase() << "x^" << monomio.getPotencia();
	return os;
}


class ListaPolinomio {
private:
	NoPolinomio *head;
	NoPolinomio *cauda;
	int tamanho = 0;
	int grau = 0;

public:
	NoPolinomio* getHead() {
		return head;
	}

	void display() const {
		NoPolinomio* atual = head;
		while (atual != nullptr) {
			cout << *atual;
			atual = atual->getProximo();
			if (atual != nullptr && atual->getBase()>0) {
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
	void Inserir(NoPolinomio *monomio) {
		monomio->setProximo(head);
		head = monomio;
		sortList();
		simplificar();
		tamanho += 1;
	}

	//sobrecarga inserir
	void Inserir(int base,int expoente) {
		NoPolinomio* monomio = new NoPolinomio(base, expoente);
		monomio->setProximo(head);
		head = monomio;
		sortList();
		simplificar();
		tamanho += 1;
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
	void AlterarNo(NoPolinomio *no, int base, int potencia) {
		no->setBase(base);
		no->setPotencia(potencia);
	}
	void Remover(NoPolinomio* no) {
		if (no == nullptr || head == nullptr) {
			return;
		}

		if (head==no ) {
			head = head->getProximo();
		}

		NoPolinomio* temp = head;
		NoPolinomio* previous = nullptr;
		while (temp != nullptr) {
			if (temp==no) {
				
			}
		}
		tamanho -= 1;
	}

	void simplificar() {
		if (head == nullptr) return;

		NoPolinomio* atual=head;

		while (atual != nullptr) {
			NoPolinomio* atual2=atual;

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
			this->Inserir(atual);
			atual = atual->getProximo();
		}
		this->simplificar();
		return *this;
	}

	ListaPolinomio& operator+(ListaPolinomio& lista2) {
		ListaPolinomio lista = *this;
		lista += lista2;
		return lista2;
	}

	ListaPolinomio& operator-=(ListaPolinomio& lista2) {
		NoPolinomio* atual = lista2.getHead();
		while (atual != nullptr) {
			this->Inserir(atual->getBase()* -1,atual->getPotencia());
			atual = atual->getProximo();
		}
		this->simplificar();
		return *this;
	}

	ListaPolinomio& operator-(ListaPolinomio& lista2) {
		ListaPolinomio lista = *this;
		lista -= lista2;
		return lista2;
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

	ListaPolinomio& operator*(ListaPolinomio& lista2) {
		ListaPolinomio lista = *this;
		lista *= lista2;
		return lista2;
	}
};


int main() {
	ListaPolinomio lista;
	lista.Inserir(2, 2);
	lista.Inserir(2, 8);
	lista.Inserir(2, 3);
	lista.Inserir(4, 3);
	lista.Inserir(-2, 4);
	lista.display();
	cout << lista.evaluate(2);
	
	

	return 0;
}