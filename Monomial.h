#pragma once
/*
Assigned by:
shir bata 208573501 #ID
*/
#ifndef Monomial_H
#define Monomial_H
#include <stdio.h>
#include <iostream>
#include "Polynomial.h"
using namespace std;
class Polynomial;
class Monomial
{
	friend istream & operator >>(istream&, Monomial&);//input of a Monomial 
	friend ostream & operator <<(ostream&, const Monomial&);//output , printing a Monomial
private:
	unsigned int degree;
	double Co;
	static unsigned int countMono;
public:
	Monomial();//default constructor
	Monomial(double);//constructer
	Monomial(double, unsigned int);// constructer
	static unsigned int getNumberOfMonomials();//return the quantity of objectes wev'e created by the constructers
	void print() const;//print the object
	static void extDegCof(double*, unsigned int*,char*);//getting the Deg and Cof for each Mono 
	bool add(const Monomial&);//adding to the current object another Monomial object if they both have the same degree
	~Monomial();//decreasing the static monoCount whenever an object is being deleted
	Monomial& operator=(const Monomial&);// m1=m2 - the p1 Monomial gets the value of p2 
	Monomial operator+(const Monomial&);//m1+m2 - summing 2 Monomials
	Monomial operator-(const Monomial&);// m1-m2 - sub 2 Monomials
	Monomial operator*(const Monomial&);// m1*m2 - multiply 2 Monomials
	void operator+=(const Monomial&);// m1+=m2 - adding m2 to m1
	void operator-=(const Monomial&);// m1-=m2 - sub m2 from m1
	void operator*=(const Monomial&);// m1*=m2 - multiply m1 with m2
	void operator-();// -m1 : negate m1
	bool operator==(const Monomial&)const;// checking if 2 Monomials are equal
	bool operator!=(const Monomial&)const;//checking if 2 Monomials are not equal
	double operator()(double)const;// m(r) - calculate the value of the monomial with the input r value
	double& getref() { return Co; } // return parameter as a reference 
	friend class Polynomial;
};
#endif