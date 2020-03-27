#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class Diccionario
{
	string _Palabra;
	Diccionario* _Prev;
	Diccionario* _Post;
public:
	static Diccionario _Diccionario;

	Diccionario* First;
	Diccionario* Last;

	int contado;

	inline string getPalabra() { return this->_Palabra; };
	inline void setPalabra(string Palabra) { this->_Palabra = Palabra; };

	inline Diccionario* getPrev() { return this->_Prev; };
	inline void setPrev(Diccionario* Prev) { this->_Prev = Prev; };

	inline Diccionario* getPost() { return this->_Post; };
	inline void setPost(Diccionario* Post) { this->_Post = Post; };

	Diccionario();
	Diccionario(string Palabra);

	inline void Agregar(string _Palabra);
	inline void Impimir();
};

Diccionario Diccionario::_Diccionario = Diccionario();

Diccionario::Diccionario() {
	this->setPalabra("");
	this->setPost(NULL);
	this->setPost(NULL);
	this->First = NULL;
	this->Last = NULL;
}

Diccionario::Diccionario(string Palabra) {
	this->setPalabra(Palabra);
	this->setPost(NULL);
	this->setPost(NULL);
}

void Diccionario::Agregar(string _Palabra){
	if (this->First == NULL)
	{
		Diccionario* _nuevo = new Diccionario(_Palabra);

		this->First = _nuevo;
		this->Last = _nuevo;

		this->First->setPrev(this->Last);
		this->Last->setPost(this->First);

		this->Last->setPrev(this->First);
		this->First->setPost(this->Last);
		cout << "PIRMERO " << _nuevo->getPalabra() <<endl;
	}
	else
	{
		Diccionario* _nuevo = new Diccionario(_Palabra);

		_nuevo->setPost(this->Last->getPost());
		this->Last->getPost()->setPrev(_nuevo);

		this->Last->setPost(_nuevo);
		_nuevo->setPrev(this->Last);
		
		this->Last = _nuevo;
		cout << _nuevo->getPalabra()<<endl;
	}
}

void Diccionario::Impimir() {
	Diccionario* aux = Diccionario::First;

	cout << "DICCIONARIO"<< endl;
	do
	{
		if (aux!=NULL)
		{
			cout << aux->getPalabra() << " -> ";
			aux = aux->getPost();
		}
	} while (aux != Diccionario::First);
}