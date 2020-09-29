/*
Assigned by:
shir bata 208573501 #ID
*/
#include<iostream>
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial()//creating Node linked list that every node points to a monomial object
{
	head = (Node *)malloc(sizeof(Node));//first node=DUMMY
	assert(head);
	head->data = new Monomial(0, 0);
	Monomial::countMono--;//we need to decrease the countMono because we don't want to include the dummy as Mono
	head->next = NULL;//the next of the last node is NULL
}
void Polynomial::add(const Monomial &a)//adding a Monomial object to the linked list
{
	Node *curr = head->next;//initialize curr to be the next of head
	Node *prev = head;//initialize prev to be head
	if (a.Co == 0) { return; }
	while (curr != NULL) {
		if (a.degree > curr->data->degree) //we need to add a new node
			break;
		else if (a.degree < curr->data->degree)// if the degree is bigger than we want to continue searching on the list
		{
			prev = curr;
			curr = curr->next;
		}
		else if (a.degree == curr->data->degree)//if they are equal we want to combine the parameters
		{
			curr->data->Co += a.Co;
			if (curr->data->Co == 0)//if the parameter became 0 we need to reduce the countMono twice
			{
				delete curr->data;//countMono--
				prev->next = curr->next;//we need to free curr because he had 0
				free(curr);
				return;
			}
			return;
		}
	}
	prev->next = (Node *)malloc(sizeof(Node));//we need to add a new node with "a" values
	prev->next->data = new Monomial(a.Co, a.degree);
	//allocating a new Monomial that will get "a" values
	prev->next->next = curr;
	return;
}
void Polynomial::print() const//printing the linked list
{
	if (head->next == NULL) {
		cout << "0";
		return;
	}
	Node *curr = head->next;
	while (curr != NULL) {
		curr->data->print();//using print function of Mono's class because each node points to a Mono's object
		curr = curr->next;//continue at the list
		if (curr != NULL) cout << "+";
	}
}
void Polynomial::operator=(const Polynomial &p2)//replacing the data of the current polynomial with p2
{
	Node *curr = this->head->next;
	Node *curr2 = p2.head->next;
	Node *temp = curr;
	while (curr != NULL)//we want to delete the data that current polynomial had
	{
		delete (curr->data);
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	this->head->next = NULL;
	while (curr2 != NULL)//copy the new data from the polynomial p2 that we got and add it to the current polynomial
	{
		this->add(*(curr2->data));//using add function that gets a Monomial
		curr2 = curr2->next;
	}
}
Polynomial Polynomial::operator+(const Polynomial &a) const // current poly + polynomial a = summing 2 polynomials into 1 polynomial
{
	Polynomial *temp = new Polynomial;//we want to make a new polynomial with the data from current+a
	Node *curr = this->head->next; // points to the first node after the dummy
	Node *curr2 = a.head->next;// same
	while (curr
		!= NULL)//first we will copy all the data that the current poly and add it to the final poly by using add function
	{
		temp->add(*(curr->data));//copy each Monomial of the current poly and put it at the third polynomial
		curr = curr->next;
	}
	while (curr2 != NULL)//we will do the same with the second polynomial
	{
		temp->add(*(curr2->data));
		curr2 = curr2->next;
	}
	return (*temp);//the third polynomial will return
}
Polynomial Polynomial::operator+(const Monomial &a) const//summing polynomial and Monomial
{
	Polynomial *temp = new Polynomial;//the final result we will put in a polynomial
	Node *curr = this->head->next;
	while (curr != NULL)//we want to copy the data from the current polynomial and add it to the final polynomial
	{
		temp->add(*(curr->data));//each monomial of the current polynomial will be added
		curr = curr->next;
	}
	temp->add(a);//and finally we will add the Monomial we got
	return (*temp);//return the final poly
}
Polynomial Polynomial::operator-(Polynomial &a)//we want to sub between 2 polynomials
{
	Polynomial *temp = new Polynomial;//final polynomial that we will return
	Node *curr = this->head->next;
	Node *curr2 = a.head->next;
	while (curr != NULL)//adding all the data that the current polynomial has
	{
		temp->add(*(curr->data)); // using add function that adding each monomial to the final polynomial temp
		curr = curr->next;
	}
	while (curr2 != NULL) {
		curr2->data->Co *= -1;//we want to sub the polynomials so we will need to negate all Monos before we add
		temp->add(*(curr2->data));// now we can add to final polynomial
		curr2->data->Co *= -1;//we need to get the right signs back as before
		curr2 = curr2->next;
	}
	return *temp;
}
Polynomial Polynomial::operator-(Monomial &a) // sub Monomial from a polynomial 
{
	Polynomial *temp = new Polynomial;//final polynomial that we will return
	Node *curr = this->head->next;
	while (curr != NULL)//copying all the data that current poly has to the final poly
	{
		temp->add(*(curr->data));
		curr = curr->next;
	}
	a.Co *= -1;//we want to sub the monomial with the polynomial so we will negate the Mono
	temp->add(a); // now we can add the Monomial to the final poly
	a.Co *= -1;//need to reverse it back to the right sign
	return *temp;
}
void Polynomial::operator+=(const Polynomial &a)// adding one polynomial to the current polynomial
{
	*this = (*this
		+ a); //using the "=" and "+" function from before. it will replace the current poly with a new data after summing
}
void Polynomial::operator+=(const Monomial &a)//adding Monomial to the current polynomial by using add function
{
	this->add(a);
}
void Polynomial::operator-=(Polynomial &a) // sub one polynomial from the current polynomial
{
	*this = (*this
		- a);// using the "=" and "-" function from before. it will replace the current poly with a new data after subbing
}
void Polynomial::operator-=(Monomial &a)// sub a Monomial from polynomial
{
	a.Co *= -1;//we want to sub the Monomial from the polynomial, that's why we need to negate the data
	this->add(a);// now we can add to current polynomial
	a.Co *= -1;//we need to get it back to the original sign it had
}
void Polynomial::operator-()// negate polynomial
{
	Node *curr = this->head->next;
	while (curr != NULL)// each node of the poly points to a monomial so we want to change the sign for each one
	{
		curr->data->Co *= -1;
		curr = curr->next;
	}
}
bool Polynomial::operator==(const Polynomial &a) const//checing if 2 polynomials are equal
{
	Node *curr = this->head->next;
	Node *curr2 = a.head->next;
	while (curr != NULL && curr2 != NULL) {
		if ((*curr->data) == (*curr2->data))//using the function == from the monomial class that compares 2 monomials
		{
			curr = curr->next;
			curr2 = curr2->next;
			if (curr == NULL && curr2 == NULL)//2 polynomials are at the same size
				return true; // then they must be equal
		}
		else
			return false;
	}
	return false; //if they aren't at the same size ,then they must be not equal
}
bool Polynomial::operator!=(const Polynomial &a) const//checking if 2 polynomials are not equal
{
	return !(*this == a);//using the == function from polynomial class
}
bool Polynomial::operator==(const Monomial &a) const {
	Node *curr = this->head->next;
	if (curr == NULL)//empty list
	{
		if (a.Co != 0)
			return false;
		else
			return true;
	}
	else if (curr->next == NULL && curr != NULL)//one monomial
	{
		if (curr->data->Co == a.Co && a.degree == curr->data->degree)
			return true;
		else return false;

	}
	return false;

}
bool Polynomial::operator!=(const Monomial &a) const// checking if a polynomial is equal to a Monomial
{
	return !(*this == a);
}
double Polynomial::operator()(double r) const//calculate p(r)
{
	double sum = 0;
	Node *curr = this->head->next;
	while (curr != NULL) {
		sum += (*curr->data)(r); //using the m(r) function from monomial class,we will sum each m(r) of the poly linked list
		curr = curr->next;
	}
	return sum;
}
double &Polynomial::operator[](double r)//calculate p[r] , change and return the coefficent of the degree r
{
	Node *curr = this->head->next;
	while (curr != NULL) {
		if (curr->data->degree == r) {
			return (curr->data)->getref();
		}
		else
			curr = curr->next;
	}
	return this->head->data->getref(); // return as a reference , so we can change it if we want
}
istream &operator>>(istream &in, Polynomial &a)//input of a new polynomial
{
	int i;
	Node *curr = a.head->next;
	Node *temp = curr;
	while (curr != NULL)//if the polynomial isn't empty,we need to delete his data before the new input
	{
		delete (curr->data);
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	a.head->next = NULL;
	char *s = new char[100];
	do {
		s[0] = getchar();
	} while (s[0] == '\n');
	for (i = 1; s[i - 1] != ','; i++) {
		s[i] = getchar();
	}
	i = 0;
	int j, k;
	double p;
	unsigned int d;
	char *buffer;
	while (true) {
		if (s[i] == ',') break;
		k = 0;
		k++;
		i++;
		while (s[i] != '+' && s[i] != '-' && s[i] != ',') {
			i++;
			k++;
		}
		i -= k;

		buffer = new char[k];
		j = 0;
		buffer[j] = s[i];
		i++;
		j++;
		for (; s[i] != '+' && s[i] != '-' && s[i] != ','; i++, j++) {
			buffer[j] = s[i];
		}
		Monomial::extDegCof(&p, &d, buffer);//calling exDegCof to get the cof and degree from buffer
		Monomial *m = new Monomial(p, d);//creating a new Monomial with the real cof and deg
		a.add(*m);//adding a new Mono to the poly by using add function
		delete[](buffer);
		delete (m);
	}
	delete[](s);
	return in;
}
ostream &operator<<(ostream &out, const Polynomial &a)//printing the polynomial
{
	a.print();
	return out;
}
Polynomial::~Polynomial()//free the linked list
{
	Node *curr = head->next;
	Node *next = head->next;
	while (curr != NULL) {
		next = curr;
		curr = curr->next;
		delete (next->data);
		free(next);
	}
}