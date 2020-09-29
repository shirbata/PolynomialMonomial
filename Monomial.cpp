/*
Assigned by:
shir bata 208573501 #ID
*/

#include<iostream>
#include"Monomial.h"

unsigned int Monomial::countMono = 0;//whenever we create an object we will increase the static var
Monomial::Monomial() //Optional default constructer
{
	degree = 0;
	Co = 1;
	countMono++;
}
Monomial::Monomial(double a) //optional constructer
{
	degree = 0;
	Co = a;
	countMono++;
}
Monomial::Monomial(double a, unsigned int b) //optional constructer
{
	degree = b;
	Co = a;
	countMono++;
}
unsigned int Monomial::getNumberOfMonomials()//static function that returns the static var countMono
{
	return countMono;
}
void Monomial::print() const//printing each object
{
	if (Co != 0)//because if it's 0 we don't want to print it
	{
		if (degree == 0)//print only the parameter because it the degree is not effecting
			cout << Co;
		else if (Co == 1)
			if (degree != 1)
				cout << "x^" << degree;
			else
				cout << "x";
		else
			if (degree != 1)
				cout << Co << "*x^" << degree;
			else
				cout << Co << "*x";
	}
}
bool Monomial::add(const Monomial &a)//if the degrees are equal we can combine between the parameters
{
	if (this->degree == a.degree)
	{
		this->Co += a.Co;
		return true;
	}
	else//if they are not equal we can not add a to the current object
		return false;
}
Monomial& Monomial::operator=(const Monomial&a)//replacing the value of current Mono with the value of the poly we got
{
	this->degree = a.degree;//copy the degree of the poly we got
	this->Co = a.Co;//copy the parameter of the poly we got
	return *this;
}
Monomial Monomial::operator+(const Monomial &a)//summing 2 Monomials
{
	Monomial *temp = new Monomial;
	if (this->degree == a.degree)
	{
		temp->Co = this->Co + a.Co;
		temp->degree = a.degree;
		return *temp;
	}
	else
		return *this;
}
Monomial Monomial::operator-(const Monomial&a)// sub a Mono from current Mono
{
	Monomial *temp = new Monomial;
	if (this->degree == a.degree)
	{
		temp->Co = this->Co - a.Co;
		temp->degree = a.degree;
		return *temp;
	}
	else
		return *this;
}
Monomial Monomial::operator*(const Monomial&a)//a*currentMono ; multiply 2 polynomials; we multiply their private fields
{
	Monomial *temp = new Monomial;
	temp->Co = this->Co * a.Co;
	temp->degree = this->degree + a.degree;
	return *temp;
}
void Monomial::operator+=(const Monomial &a) // we add Monomial a to the current Mono
{
	if (this->degree == a.degree)//if degrees are equal we only need to add Monomial a to the current Mono
	{
		this->Co += a.Co;
	}
}
void Monomial::operator-=(const Monomial &a)//we sub a from current Mono
{
	if (this->degree == a.degree)//if degrees are equal we only need to sub Monomial a from the current Mono
	{
		this->Co -= a.Co;
	}
}
void Monomial::operator*=(const Monomial&a) // multiply the fields of Monomial a with the fields of current Mono 
{
	this->Co *= a.Co;
	this->degree += a.degree;
}
void Monomial::operator-()//negate current Monomial
{
	this->Co *= (-1);

}
bool Monomial::operator==(const Monomial &a)const //checking if 2 Monomials are equal by comparing their fields
{
	return (this->degree == a.degree && this->Co == a.Co);

}
bool Monomial::operator!=(const Monomial &a)const//checking if 2 Monomials are not equal by using = function
{
	return !(*this == a);
}
istream &operator>>(istream & in, Monomial&p)//input from the user of the Monomial
{
	int i = 0, k = 0;
	bool validInput = true;
	char *str = new char[100];
	cin.getline(str, 100); //gets a new array of chars

	while (str[i] == ' ' || str[i] == '^' || str[i] == '+' ||
		str[i] == '-' || str[i] == 'x' || (str[i] >= '0' && str[i] <= '9')) {
		k++;
		i++;
	}
	char *s = new char[k + 1];
	for (i = 0; i < k; i++) {
		s[i] = str[i];
	}
	s[k] = 0;
	do {
		validInput = true;
		for (i = 0; s[i] != 0; i++) { //looking for invalid input,if so ask again for an input
			if (s[i] != ' ' && s[i] != '^' && s[i] != '+' && s[i] != '-' && s[i] != 'x' && (s[i]<'0' || s[i] > '9')) {
				validInput = false;
				cout << "invalid input, please enter a new monomial: " << endl;
				cin.getline(s, 100);
				break;
			}
		}
	} while (!validInput); // until it is a valid input
	Monomial::extDegCof(&(p.Co), &(p.degree), s); //calling extdegcof to get the right degree and Co for each Mono
	delete[](str);
	delete[](s);
	return in;
}

void Monomial::extDegCof(double* parm, unsigned int* deg, char* s){ //function that gets the cof and deg for each Mono
	char cof[100], degree[100]; //array of chars for the cof and degree of each Mono
	double realcof = 1;
	int i;
	bool hasDeg = false; //for the case it has 0 deg
	bool degOne = true; //for the case it has 1 deg
	cof[0] = '1';
	for (i = 0; s[i] != 0; i++) { //if we find 'X' there must be a degree
		if (s[i] == 'x') hasDeg = true;
	}
	if (hasDeg) {
		for (i = 0; s[i] != 0; i++) { // only if it has a deg , we need to find out if deg!=1 by encountering '^'
			if (s[i] == '^') degOne = false;
		}
	}
	i = 0;
	for (int j = 0; s[i] != 'x' && s[i] != 0; i++, j++) {
		if (s[i] == ' ') {
			j--;
			continue;
		}
		if (j == 0 && (s[i] == '+' || s[i] == '-')) {
			if (s[i] == '-')
			{
				realcof = -1;
			}
			j--;
			continue;
		}
		cof[j] = s[i];
	}
	if (hasDeg && !degOne) {
		for (int j = 0; s[i] != 0; i++, j++) {
			if (s[i] == ' ' || s[i] == 'x' || s[i] == '^') {
				j--;
				continue;
			}
			degree[j] = s[i];
		}
		*deg = atoi(degree);//using atoi to get the real value of degree
	}
	else if (hasDeg && degOne) {
		*deg = 1;
	}
	else {
		*deg = 0;
	}
	double c = atoi(cof);//using atoi to get the real value of cof
	realcof *= c;
	*parm = realcof;
}
ostream &operator<<(ostream &out, const Monomial&p)//output of our Monomial 
{
	if (p.Co != 0)
	{
		if (p.degree == 0)
			out << p.Co;
		else if (p.Co == 1 || p.Co == -1)
		{
			if (p.degree != 1)
				if (p.Co == 1) {
					out << "x^" << p.degree;
				}
				else {
					out << "-x^" << p.degree;
				}
			else {
				if (p.Co == 1) {
					out << "x";
				}
				else {
					out << "-x";
				}
			}
		}
		else
		{
			if (p.degree != 1)
				out << p.Co << "*x^" << p.degree;
			else
				out << p.Co << "*x";
		}
	}
	else if (p.Co == 0)
		out << "0";
	return out;
}
double Monomial::operator()(double r)const//calculate m(r)
{
	double pow = 1;
	if (this->Co == 0)//then there is not to calculate ,we just return 0
		return 0;
	else //parameter!=0
	{
		if (this->degree == 0)
			return this->Co;
		else if (this->degree == 1)
			return (r * this->Co);
		else // degree!=0,1
		{
			for (unsigned int i = 0; i < this->degree; i++)
			{
				pow = pow * r;
			}
			return (pow * this->Co);
		}

	}

}
Monomial::~Monomial()//decreasing the static monoCount whenever an object is being deleted
{
	countMono--;
}