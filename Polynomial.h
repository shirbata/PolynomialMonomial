/*
Assigned by:
shir bata 208573501 #ID
*/
#ifndef Polynomial_H
#define Polynomial_H
#include "Monomial.h"
#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;
class Monomial;
struct Node //our linked list struct
{
	Monomial* data;//every node will point to a Monomial object
	Node* next;
};
class Polynomial
{
	friend istream & operator >>(istream&, Polynomial&);
	friend ostream& operator <<(ostream&, const Polynomial&);
private:
	Node *head;//first node of the linked list
public:
	Polynomial();//constructer-> creating Node linked list that every node points to a monomial object
	void add(const Monomial &);//adding a Monomial object to the linked list
	void print()const;//printing a linked list
	void operator=(const Polynomial&);//p1=p2 - replacing p1 data with p2 data
	Polynomial operator+(const Polynomial&)const;//p1+p2 - summing 2 polynomials
	Polynomial operator+(const Monomial&)const;// p1+m1- summing Polynomial with Monomial
	Polynomial operator-(Polynomial&);//p1+p2 - sub 2 Polynomials
	Polynomial operator-(Monomial&);// p1-m1 - sub between polynomial and monomial
	void operator+=(const Polynomial&);// p1+=p2 - adding the data of p2 polynomial to the current p1 polynomial
	void operator+=(const Monomial&);// p1+=m1 - adding the data of Monomial m1 to Polynomial p1
	void operator-=(Polynomial&);// p1-=p2 - sub the data of p2 polynomial from the current p1 polynomial
	void operator-=(Monomial&);// p1-=p2 -  sub the data of Monomial m1 from the current p1  Polynomial
	void operator-();// negate current polynomial
	bool operator==(const Polynomial&)const;//checking if 2 polynomials are equal
	bool operator==(const Monomial&)const;//checking if  polynomial and monomial are equal
	bool operator!=(const Polynomial&)const;//checking if 2 polynomials are not equal
	bool operator!=(const Monomial&)const;// checking if polynomial and monomial are not equal
	double operator()(double)const;//calculate p(r)
	double& operator[] (double num);//change and return the coefficent of the degree r 
	~Polynomial();//destructer
};



#endif
#pragma once
