#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//#include "Punteo.h"

using namespace std;

class Usuario
{
	string Nombre;
	Usuario* Left;
	Usuario* Right;

	Punteo *_Punteo;
public:
	static Usuario _Usuarios;

	Usuario* Start;

	Usuario();
	Usuario(string _Nombre);

	inline string getNombre(){ return this->Nombre; };
	inline void setNombre(string _Nombre) { this->Nombre = _Nombre; };

	inline Punteo* getClassPunteo() { return this->_Punteo; };
	inline void setClassPunteo(Punteo* punteo) { this->_Punteo = punteo; };


	inline void AgregarUsurio( string _Nombre);
	inline Usuario* AgregarSig(Usuario* _Nodo, string _Nombre);


	inline void AgregarScore(string _Nombre, int _Putnteo);
	inline void Buscar(Usuario* _Nodo, string _Nombre, int Punteo);

	inline void Imprimir();
	inline void PreOrder(Usuario* _Nodo);
	inline void InOrder(Usuario* _Nodo);
	inline void PostOrder(Usuario* _Nodo);

};

Usuario Usuario::_Usuarios = Usuario();

Usuario::Usuario() {
	this->Nombre = "";
	this->Left = NULL;
	this->Right = NULL;
	this->Start = NULL;
}

Usuario::Usuario(string _Nombre){
	this->setClassPunteo( new Punteo());
	this->setNombre(_Nombre);
	this->Left = NULL;
	this->Right = NULL;
	this->getClassPunteo();
}

void Usuario::AgregarUsurio( string _Nombre) {
	if (Usuario::_Usuarios.Start == NULL)
	{
		Usuario::_Usuarios.Start = new Usuario(_Nombre);
		cout << "AGREGAR INICIO " << _Nombre << endl;
	}
	else
	{
		Usuario::_Usuarios.Start = AgregarSig(Usuario::_Usuarios.Start, _Nombre);
	}
}

Usuario* Usuario::AgregarSig(Usuario* _Nodo, string _Nombre) {
	if (_Nodo != NULL)
	{
		int select = strcmp(_Nombre.c_str(), _Nodo->getNombre().c_str());
		//cout << _Nombre + " -- " + _Nodo->getNombre()<< " ";
		//cout << select;

		switch (select)
		{
		case 0:
			cout << "USUARIO YA REGISTRADO"<< endl;
			return _Nodo;
			break;
		case 1:
			_Nodo->Right = AgregarSig(_Nodo->Right, _Nombre);
			return _Nodo;
			//cout << "AGREGAR DERECHA " << _Nombre << endl;
			break;
		default:
			_Nodo->Left = AgregarSig(_Nodo->Left, _Nombre);
			return _Nodo;
			//cout << "AGREGAR IZQUEIRDA " << _Nombre << endl;
			break;
		}
	}
	return new Usuario(_Nombre);
}



void Usuario::Imprimir() {
	cout <<endl<< "PREORDER" << endl;
	PreOrder(Usuario::_Usuarios.Start);

	/*cout << endl << "INORDER" << endl;
	InOrder(Usuario::_Usuarios.Start);

	cout << endl << "POSTORDER" << endl;
	PostOrder(Usuario::_Usuarios.Start);*/
}

void Usuario::PreOrder(Usuario* _Nodo){
	if (_Nodo!=NULL)
	{
		PreOrder(_Nodo->Left);
		cout << _Nodo->getNombre() << " LISTA DE PUNTOES:"<<endl;
		_Nodo->getClassPunteo()->Imprimir();
		PreOrder(_Nodo->Right);
	}
}

void Usuario::InOrder(Usuario* _Nodo) {
	if (_Nodo != NULL)
	{
		cout << _Nodo->getNombre() << endl;
		PreOrder(_Nodo->Left);
		PreOrder(_Nodo->Right);
	}
}

void Usuario::PostOrder(Usuario* _Nodo) {
	if (_Nodo != NULL)
	{
		PreOrder(_Nodo->Right);
		cout << _Nodo->getNombre() << endl;
		PreOrder(_Nodo->Left);
	}
}



void Usuario::AgregarScore(string _Nombre, int _Punteo) {

	Buscar(Usuario::_Usuarios.Start, _Nombre, _Punteo);
}

void Usuario::Buscar(Usuario* _Nodo, string _Nombre, int _Punteo) {
	if (_Nodo != NULL)
	{
		int select = strcmp(_Nombre.c_str(), _Nodo->getNombre().c_str());

		switch (select)
		{
		case 0:
			_Nodo->getClassPunteo()->Agregar_Ordenar(_Punteo);
			break;
		case 1:
			Buscar(_Nodo->Right, _Nombre, _Punteo);
			//cout << "AGREGAR DERECHA " << _Nombre << endl;
			break;
		default:
			Buscar(_Nodo->Left, _Nombre, _Punteo);
			break;
		}
	}
}

