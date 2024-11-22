#include "NoPolinomio.h"

NoPolinomio::NoPolinomio(float b, int p) {
	base = b;
	potencia = p;
	proximo = nullptr;
}

NoPolinomio* NoPolinomio:: getProximo() {
	if(this->proximo!=nullptr)
		return this->proximo;
	return nullptr;
}

void NoPolinomio::setProximo(NoPolinomio* p) {
	this->proximo = p;
}

float NoPolinomio::getBase() const{
	return this->base;
}

void NoPolinomio::setBase(float p) {
	this->base = p;
}

int NoPolinomio::getPotencia() const{
	return this->potencia;
}


void NoPolinomio::setPotencia(int p) {
	this->potencia = p;
}

NoPolinomio& NoPolinomio::operator+=(NoPolinomio& no) {
	if (potencia == no.getPotencia()) {
		base += no.getBase();
	}

	return *this;

}

NoPolinomio operator+(const NoPolinomio& no1, const NoPolinomio& no2) {
	if (no1.getPotencia()!=no2.getPotencia()) {
		return no1;
	}
	return NoPolinomio(no1.getBase() + no2.getBase(), no1.getPotencia());
}



ostream& operator<<(ostream& os, NoPolinomio& monomio) {
	os << monomio.getBase() << "x^" << monomio.getPotencia();
	return os;
}