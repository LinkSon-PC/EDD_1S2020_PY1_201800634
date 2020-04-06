#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#include "Ficha.h"
#include "Matriz.h"

using namespace std;

Matriz* Matriz::_Tablero = NULL;
Matriz* Matriz::_Aux = NULL;

Matriz::Matriz() {
	this->Dimension = 0;
	this->setX(0);
	this->setY(0);
	this->_Ficha = NULL;
	this->_Inicio = NULL;
}

Matriz::Matriz(int _Dimension) {
	this->Dimension = _Dimension;
	this->setX(0);
	this->setY(0);
	this->_Ficha = NULL;
	this->_Inicio = NULL;
}

Matriz::Matriz(int _x, int _y, Ficha* Ficha) {
	this->setX(_x);
	this->setY(_y);
	this->setFicha(Ficha);
	this->setPunto(1);


	this->_Abajo = NULL;
	this->_Arriba = NULL;
	this->_Izquierda = NULL;
	this->_Dercha = NULL;
}


void Matriz::GenerarMatriz() {

	this->_Inicio = new Matriz(0, 0, new Ficha(0+'0',0));
	/*this->_Inicio = Celdas(this->_Inicio);*/

	Matriz* aux = this->_Inicio;

	for (int i = 1; i < this->Dimension; i++)
	{
		Matriz* _Nuevo = new Matriz(i, 0, new Ficha( i+'32', 0));
		aux->_Dercha = _Nuevo;
		_Nuevo->_Izquierda = aux;

		cout << "Derecha (" << aux->getX() << "," << aux->getY() << ") ->" << " (" << _Nuevo->getX() << "," << _Nuevo->getY() << ") " << endl;
		aux = _Nuevo;
	}

	aux = this->_Inicio;

	for (int i = 1; i < this->Dimension; i++)
	{
		Matriz* _Nuevo = new Matriz(0, i, new Ficha(i + '32', 0));
		aux->_Abajo = _Nuevo;
		_Nuevo->_Arriba = aux;

		cout << "ABAJO (" << aux->getX() << "," << aux->getY() << ") ->" << " (" << _Nuevo->getX() << "," << _Nuevo->getY() << ") " << endl;
		aux = _Nuevo;
	}

	Matriz* _fila = this->_Inicio->_Abajo;
	for (int i = 0; i < this->Dimension-1; i++)
	{

		Matriz* _columna = _fila;

		for (int i = 0; i < this->Dimension-1; i++)
		{

			Matriz* _Nuevo = new Matriz(_columna->getX()+1, _fila->getY(), NULL);
			_columna->_Dercha = _Nuevo;
			_Nuevo->_Izquierda = _columna;


			_columna->_Arriba->_Dercha->_Abajo = _Nuevo;
			_Nuevo->_Arriba = _columna->_Arriba->_Dercha;


			cout <<  " (" << _Nuevo->getX() << "," << _Nuevo->getY() << ") <-->" ;

			_columna = _Nuevo;
		}

		cout << endl;
		_fila = _fila->_Abajo;
	}
}

void Matriz::CeldaPuntos(int _x, int _y, Matriz* _Celda, int puntos) {
	if (_x > _Celda->getX())
	{
		CeldaPuntos(_x,_y,_Celda->_Dercha, puntos);
	}
	else if (_y > _Celda->getY())
	{
		CeldaPuntos(_x, _y, _Celda->_Abajo, puntos);
	}
	else if (_x == _Celda->getX() && _y == _Celda->getY())
	{
		_Celda->setPunto(puntos);
		return;
	}
}


void Matriz::CeldasFichas(int _x, int _y, Matriz* _Celda, Ficha* Ficha) {
	if (_x > _Celda->getX())
	{
		CeldasFichas(_x, _y, _Celda->_Dercha, Ficha);
	}
	else if (_y > _Celda->getY())
	{
		CeldasFichas(_x, _y, _Celda->_Abajo, Ficha);
	}
	else if (_x == _Celda->getX() && _y == _Celda->getY())
	{
		_Celda->setFicha(Ficha);
	}
}



Matriz* Matriz::InicioPalabra(int _x, int _y, Matriz* _Celda) {
	if (_x > _Celda->getX())
	{
		InicioPalabra(_x, _y, _Celda->_Dercha);
	}
	else if (_y > _Celda->getY())
	{
		InicioPalabra(_x, _y, _Celda->_Abajo);
	}
	else if (_x == _Celda->getX() && _y == _Celda->getY())
	{
		return _Celda;
	}
}

string Matriz::ObtenerPalabra(int _x, int _y) {
	string _palabra = "";

	Matriz* _aux = InicioPalabra( _x,  _y, this->_Inicio);

	if ( (_aux->_Dercha->getFicha() != NULL ) &&   (_aux->_Arriba->getFicha() == NULL && _aux->_Abajo->getFicha() == NULL && _aux->_Izquierda->getFicha() == NULL)  )
	{
		while (_aux->getFicha() != NULL)
		{
			_palabra += _aux->getFicha()->GetLetra();

			_aux = _aux->_Dercha;
		}
	}

	else if ((_aux->_Abajo->getFicha() != NULL) && (_aux->_Arriba->getFicha() == NULL && _aux->_Izquierda->getFicha() == NULL && _aux->_Dercha->getFicha() == NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			_palabra += _aux->getFicha()->GetLetra();

			_aux = _aux->_Abajo;
		}
	}

	else if ((_aux->_Dercha->getFicha() != NULL && _aux->_Izquierda->getFicha() == NULL) && (_aux->_Arriba->getFicha() != NULL || _aux->_Abajo->getFicha() != NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			_palabra += _aux->getFicha()->GetLetra();

			_aux = _aux->_Dercha;
		}
	}

	else if ((_aux->_Abajo->getFicha() != NULL && _aux->_Arriba->getFicha() == NULL ) && ( _aux->_Izquierda->getFicha() != NULL	|| _aux->_Dercha->getFicha() != NULL ))
	{
		while (_aux->getFicha() != NULL)
		{
			_palabra += _aux->getFicha()->GetLetra();

			_aux = _aux->_Abajo;
		}
	}

	else {
		_palabra = _aux->getFicha()->GetLetra();
	}
	cout << "LA PALABRA FORMADA ES: " << _palabra<<endl;

	return _palabra;
}


int Matriz::PuntosPalabra(int _x, int _y) {
	int puntos=0;

	Matriz* _aux = InicioPalabra(_x, _y, this->_Inicio);

	if (_aux->_Dercha->getFicha() != NULL && (_aux->_Arriba->getFicha() == NULL && _aux->_Abajo->getFicha() == NULL && _aux->_Izquierda->getFicha() == NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			puntos += (_aux->getFicha()->GetValor() * _aux->getPunto());

			_aux = _aux->_Dercha;
		}
	}

	else if ((_aux->_Abajo->getFicha() != NULL) && (_aux->_Arriba->getFicha() == NULL && _aux->_Izquierda->getFicha() == NULL && _aux->_Dercha->getFicha() == NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			puntos += (_aux->getFicha()->GetValor() * _aux->getPunto());

			_aux = _aux->_Abajo;
		}
	}

	else if ((_aux->_Dercha->getFicha() != NULL && _aux->_Izquierda->getFicha() == NULL) && (_aux->_Arriba->getFicha() != NULL || _aux->_Abajo->getFicha() != NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			puntos += (_aux->getFicha()->GetValor() * _aux->getPunto());

			_aux = _aux->_Dercha;
		}
	}

	else if ((_aux->_Abajo->getFicha() != NULL && _aux->_Arriba->getFicha() == NULL) && (_aux->_Izquierda->getFicha() != NULL || _aux->_Dercha->getFicha() != NULL))
	{
		while (_aux->getFicha() != NULL)
		{
			puntos += (_aux->getFicha()->GetValor() * _aux->getPunto());

			_aux = _aux->_Abajo;
		}
	}


	return puntos;
}


void Matriz::EliminarCelda(int _x, int _y, Matriz* _Celda) {
	if (_x > _Celda->getX())
	{
		EliminarCelda(_x, _y, _Celda->_Dercha);
	}
	else if (_y > _Celda->getY())
	{
		EliminarCelda(_x, _y, _Celda->_Abajo);
	}
	else if (_x == _Celda->getX() && _y == _Celda->getY())
	{
		_Celda->setFicha(NULL);
	}
}

//Matriz* Matriz::Celdas(Matriz* _Nodo) {
//
//	if (_Nodo->getX() <= this->Dimension && _Nodo->getY() <= this->Dimension)
//	{
//		if (_Nodo->_Arriba == NULL && _Nodo->_Izquierda == NULL)
//		{
//			_Nodo->_Dercha = Celdas(_Nodo);
//			_Nodo->_Abajo = Celdas(_Nodo);
//
//			cout << "INICIO ->";
//			return _Nodo;
//		}
//		else if (_Nodo->_Izquierda == NULL)		//MOVER HACIA ABAJO
//		{
//			Matriz* _Nuevo = new Matriz(_Nodo->getX(), _Nodo->getY()+1, NULL);
//			_Nuevo->_Arriba = _Nodo;
//			cout << "ABAJO ->";
//
//			_Nuevo->_Dercha = Celdas(_Nuevo);
//			_Nuevo->_Abajo = Celdas(_Nuevo);
//			return _Nuevo;
//		}
//		else if (_Nodo->_Arriba == NULL)	//MOVER HACIA DERECHA
//		{
//			Matriz* _Nuevo = new Matriz(_Nodo->getX()+1, _Nodo->getY(), NULL);
//			_Nuevo->_Izquierda = _Nodo;
//
//			cout << "DEREHCA ->";
//
//			_Nuevo->_Dercha = Celdas(_Nuevo);
//			_Nuevo->_Abajo = Celdas(_Nuevo);
//			return _Nuevo;
//		}
//		else if (_Nodo->_Arriba != NULL && _Nodo->_Arriba->_Dercha!= NULL)
//		{
//			Matriz* _Nuevo = new Matriz(_Nodo->getX()+1, _Nodo->_Arriba->_Dercha->getY() + 1, NULL);
//			_Nuevo->_Arriba = _Nodo->_Arriba->_Dercha;
//			_Nuevo->_Izquierda = _Nodo;
//			cout << "C.DERECHA ->";
//
//			_Nuevo->_Dercha = Celdas(_Nuevo);
//			_Nuevo->_Abajo = Celdas(_Nuevo);
//			return _Nuevo;
//		}
//		else if (_Nodo->_Abajo != NULL && _Nodo->_Abajo->_Izquierda != NULL)
//		{
//			Matriz* _Nuevo = new Matriz(_Nodo->_Abajo->getX() + 1, _Nodo->_Arriba->getY() + 1, NULL);
//			_Nuevo->_Arriba = _Nodo->_Arriba->_Dercha;
//			_Nuevo->_Izquierda = _Nodo;
//			cout << "C.ARRIBA ->";
//
//			_Nuevo->_Dercha = Celdas(_Nuevo);
//			_Nuevo->_Abajo = Celdas(_Nuevo);
//			return _Nuevo;
//		}
//	}
//		return NULL;
//}

