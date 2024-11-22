#include "ListaPolinomio.h"

NoPolinomio* ListaPolinomio::getHead() const {
	return head;
}

int ListaPolinomio::getSize() const {
	return tamanho;
}

void ListaPolinomio::display() {
	simplificar();
	sortList();
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

int ListaPolinomio::returnGrau() {
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

/* void ListaPolinomio::Inserir(NoPolinomio monomio) {
	
	NoPolinomio no(monomio.getBase(), monomio.getPotencia());
	no.setProximo(head);
	head = &no;
	tamanho += 1;
} */

void ListaPolinomio::Inserir(int base, int expoente) {


	if (base == 0)
		return;

	/*
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
	} */



	NoPolinomio* monomio = new NoPolinomio(base, expoente);
	monomio->setProximo(head);
	head = monomio;
	tamanho += 1;
}

ListaPolinomio::ListaPolinomio() {
	head = nullptr;
	cauda = nullptr;
	grau = 0;
	tamanho = 0;
}
ListaPolinomio::~ListaPolinomio() {
	while (head != nullptr) {
		NoPolinomio* temp = head;
		head = head->getProximo();
		delete temp;
	}
}

void ListaPolinomio::AlterarNo(NoPolinomio* no, int base, int potencia) {
	no->setBase(base);
	no->setPotencia(potencia);
}

void ListaPolinomio::Remover(NoPolinomio* no) {
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

void ListaPolinomio::simplificar() {
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

double ListaPolinomio::evaluate(double x) {
	double resultado = 0.0;
	NoPolinomio* atual = head;

	while (atual != nullptr) {
		resultado += atual->getBase() * pow(x, atual->getPotencia());
		atual = atual->getProximo();
	}

	return resultado;
}

void ListaPolinomio::sortList() {
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

ListaPolinomio& ListaPolinomio::operator+=(ListaPolinomio& lista2) {
	NoPolinomio* atual = lista2.getHead();
	while (atual != nullptr) {
		this->Inserir(atual->getBase(), atual->getPotencia());
		atual = atual->getProximo();
	}
	this->simplificar();
	return *this;
}

ListaPolinomio& ListaPolinomio::operator-=(ListaPolinomio& lista2) {
	NoPolinomio* atual = lista2.getHead();
	while (atual != nullptr) {
		this->Inserir(atual->getBase() * -1, atual->getPotencia());
		atual = atual->getProximo();
	}
	this->simplificar();
	return *this;
}

ListaPolinomio& ListaPolinomio::operator*=(ListaPolinomio& lista2) {
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
	ListaFinal.simplificar();
	return ListaFinal;
}


ListaPolinomio operator+(const ListaPolinomio& lista1, const ListaPolinomio& lista2) {
	
	ListaPolinomio resultado;
	NoPolinomio* no1 = lista1.getHead();
	NoPolinomio* no2 = lista2.getHead();

	while (no1 != nullptr) {
		resultado.Inserir(no1->getBase(), no1->getPotencia());
		no1 = no1->getProximo();
	}

	while (no2 != nullptr) {
		resultado.Inserir(no2->getBase(), no2->getPotencia());
		no2 = no2->getProximo();
	}
	
	resultado.simplificar();
	return resultado;
}

ListaPolinomio operator-(const ListaPolinomio& lista1, const ListaPolinomio& lista2) {
	ListaPolinomio resultado;
	NoPolinomio* no1 = lista1.getHead();
	NoPolinomio* no2 = lista2.getHead();

	while (no1 != nullptr) {
		resultado.Inserir(no1->getBase(), no1->getPotencia());
		no1 = no1->getProximo();
	}

	while (no2 != nullptr) {
		resultado.Inserir(no2->getBase()*(-1), no2->getPotencia());
		no2 = no2->getProximo();
	}

	resultado.simplificar();
	return resultado;
}

