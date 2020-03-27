#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//#include "Usuario.h"
using namespace std;

class Score
{
	int _Puntos;
	string _Nombre;

	Score* Next;
public:
	static Score* _Scores;

	int Contador;

	Score* First;
	Score* Last;

	inline int getPuntos(){ return this->_Puntos; };
	inline void setPuntos(int Puntos) { this->_Puntos = Puntos; };

	inline string getNombre() { return this->_Nombre; };
	inline void setNombre(string Nombre) { this->_Nombre = Nombre; };

	inline void IngresarInicio(string,int);
	inline void IngresarFinal(string,int);

	inline void Agregar_Ordenar(string,int);

	inline void Imprimir();

	Score();
	Score(string _Nombre, int _Puntos);

};

Score* Score::_Scores = NULL;

Score::Score() {
	this->Contador = 0;
	this->_Puntos = 0;
	this->Next = NULL;
	this->First = NULL;
	this->Last = NULL;
	Score::_Scores = this;
}

Score::Score(string _Nombre, int _Puntos) {
	setNombre(_Nombre);
	setPuntos(_Puntos);
	this->Next = NULL;
	this->First = NULL;
	this->Last = NULL;
}


void Score::IngresarInicio(string _Nombre, int _Valor) {
	Score* _nuevo = new Score(_Nombre, _Valor);
	if (Score::_Scores->First == NULL)
	{
		Score::_Scores->First = _nuevo;
		Score::_Scores->Last = _nuevo;
	}
	else
	{
		_nuevo->Next = Score::_Scores->First;
		Score::_Scores->First = _nuevo;
	}

	this->Contador++;
}

void Score::IngresarFinal(string _Nombre,int _Punteo) {
	Score* _nuevo = new Score(_Nombre,_Punteo);
	if (Score::_Scores->Last == NULL)
	{
		Score::_Scores->First = _nuevo;
		Score::_Scores->Last = _nuevo;
	}
	else
	{
		this->Last->Next = _nuevo;
		this->Last = _nuevo;
	}
	this->Contador++;
}


void Score::Agregar_Ordenar(string _Nombre,int _Punteo) {

	Usuario::_Usuarios.AgregarScore(_Nombre,_Punteo);
	if (Score::_Scores->First == NULL)
	{
		IngresarInicio(_Nombre,_Punteo);
	}
	else
	{
		if (Score::_Scores->First->getPuntos() < _Punteo)
		{
			IngresarInicio(_Nombre,_Punteo);
		}
		else if (Score::_Scores->Last->getPuntos() > _Punteo)
		{
			IngresarFinal(_Nombre,_Punteo);
		}
		else {
			Score* _nuevo = new Score(_Nombre,_Punteo);

			Score* _aux = Score::_Scores->First;
			for (int i = 0; i < this->Contador; i++)
			{
				if (_aux->Next->getPuntos() < _Punteo)
				{
					_nuevo->Next = _aux->Next;
					_aux->Next = _nuevo;

					this->Contador++;
					return;
				}
				_aux = _aux->Next;
			}
		}

	}

}

void Score::Imprimir() {
	Score* _aux = Score::_Scores->First;

	for (int i = 0; i < this->Contador; i++)
	{
		cout << _aux->getNombre() +" "<< to_string(_aux->getPuntos()) << " -> ";
		_aux = _aux->Next;
	}

}