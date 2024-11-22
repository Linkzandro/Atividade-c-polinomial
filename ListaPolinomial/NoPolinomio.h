
#pragma once

#include <iostream>
#include <cmath>
using namespace std;
class NoPolinomio
{
	private:
		float base;
		int potencia;

		NoPolinomio* proximo;

	public:
		NoPolinomio(float b, int p);
		
		NoPolinomio* getProximo();
		
		void setProximo(NoPolinomio* p);

		float getBase() const;
		
		void setBase(float p);
		
		int getPotencia() const;

		void setPotencia(int p);
		
		NoPolinomio& operator+=(NoPolinomio& no);
		
		friend NoPolinomio operator+(const NoPolinomio& no1, const NoPolinomio& no2);
		

		bool operator==(NoPolinomio& no) {
			return (base == no.getBase() && potencia==no.getPotencia());
		}
		

		friend ostream& operator<<(ostream& os, NoPolinomio& monomio);
		
};