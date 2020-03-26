
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class Punteo
{
	int Puntos;
	Punteo* Next;
public:
	int Contador;
	Punteo* First;
	Punteo* Last;
	
	int getPunteo() { return this->Puntos; }
	void setPunteo(int _Punteo) { this->Puntos = _Punteo; }

	inline Punteo();
	inline Punteo(int);


	inline void IngresarInicio(int);
	inline void IngresarFinal(int);

	inline void Agregar_Ordenar(int);

	inline void Imprimir();
};

Punteo::Punteo() {
	this->Puntos = 0;
	this->Contador = 0;
	this->First = NULL;
	this->Last = NULL;
	this->Next = NULL;
}

Punteo::Punteo(int _Puntos) {
	setPunteo( _Puntos );
	this->Next = NULL;
	this->First = NULL;
	this->Last = NULL;
}



void Punteo::Agregar_Ordenar(int _Punteo) {

	if (this->First == NULL)
	{
		IngresarInicio(_Punteo);
	}
	else
	{
		if (this->First->getPunteo() < _Punteo)
		{
			IngresarInicio(_Punteo);
		}
		else if (this->Last->getPunteo() > _Punteo)
		{
			IngresarFinal(_Punteo);
		}
		else {
			Punteo* _nuevo = new Punteo(_Punteo);

			Punteo* _aux = this->First;
			for (int i = 0; i < this->Contador; i++)
			{
				if (_aux->Next->getPunteo() < _Punteo)
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


void Punteo::IngresarInicio(int _Punteo) {
	Punteo* _nuevo = new Punteo(_Punteo);
	if (this->First == NULL)
	{
		this->First = _nuevo;
		this->Last = _nuevo;
	}
	else
	{
		_nuevo->Next = this->First;
		this->First = _nuevo;
	}

	this->Contador++;
}

//ESTRUCTURA FIFO (COLA)
void Punteo::IngresarFinal(int _Punteo) {
	Punteo* _nuevo = new Punteo(_Punteo);
	if (this->Last == NULL)
	{
		this->First = _nuevo;
		this->Last = _nuevo;
	}
	else
	{
		this->Last->Next = _nuevo;
		this->Last = _nuevo;
	}
	this->Contador++;
}

void Punteo::Imprimir() {
	Punteo* _aux = this->First;

	for (int i = 0; i < this->Contador; i++)
	{
		cout <<  _aux->getPunteo()<<" -> ";
		_aux = _aux->Next;
	}
	cout << "CONTADOR " << this->Contador <<endl;
}