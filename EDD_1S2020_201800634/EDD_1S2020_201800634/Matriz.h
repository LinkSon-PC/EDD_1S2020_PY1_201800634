#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#include "Ficha.h"

using namespace std;


class Matriz
{
	int y;
	int x;
	Ficha* _Ficha;
	int _Punto;


	 Matriz* _Arriba;
	 Matriz* _Abajo;
	 Matriz* _Izquierda;
	 Matriz* _Dercha;

public:
	static Matriz* _Tablero;
	static Matriz* _Aux;

	Matriz* _Inicio;

	ofstream RepTablero;

	int Dimension;

	inline int getY() { return this->y; };
	inline void setY(int _y) { this->y = _y; };

	inline int getX() { return this->x; };
	inline void setX(int _x) { this->x = _x; };

	inline int getPunto() { return this->_Punto; };
	inline void setPunto(int Punto) { this->_Punto = Punto; };

	inline Ficha* getFicha() { return this->_Ficha; };
	inline void setFicha(Ficha* Ficha) { this->_Ficha = Ficha; };

	Matriz();
	Matriz(int _Dimension);
	Matriz(int _y, int _x, Ficha* Ficha);

	void GenerarMatriz();
	Matriz* Celdas(Matriz* _Nodo);

	inline void ImprimirMatriz();
	inline void Tablero();

	//INSERTAR PUNTOS EN EL TABLERO
	void CeldaPuntos(int _x, int _y, Matriz* _Celda,int puntos);
	//INSERTAR FICHAS EN EL TABLREO
	void CeldasFichas(int _x, int _y, Matriz* _Celda, Ficha* Ficha);



	Matriz* InicioPalabra(int x, int y, Matriz* inicio);
	string ObtenerPalabra(int x, int y);
	int PuntosPalabra(int x, int y);

	void EliminarCelda(int x, int y, Matriz* inicio);

	//IMPIMIR FICHAS EN EL TABLERO
	/*void ImprimirTablero();
	void ImprinirFichas(int _x, int _y, Matriz* _Celda, Ficha* Ficha);

	bool VerAbajo(Matriz* _Celda);
	bool VerDerecha(Matriz* _Celda);*/
};



void Matriz::ImprimirMatriz() {


	RepTablero.open("RepTablero.dot", ios::out);
	if (RepTablero.fail()) {
		cout << "ERROR ARCHIVO NO ENCONTRADO" << endl;
	}
	else {

		RepTablero << "digraph G { style = filled; bgcolor = white; color = lightgrey; node[shape=box, style = filled];" << endl;

		Tablero();

		Matriz* _fila = this->_Inicio;
		for (int i = 0; i < this->Dimension; i++)
		{
			RepTablero << "{rank = same;";

			Matriz* _columna = _fila;
			for (int i = 0; i < this->Dimension; i++)
			{
				RepTablero << to_string((int)&*_columna) << " ";
				_columna = _columna->_Dercha;
			}
			RepTablero << "};";
			_fila = _fila->_Abajo;
		}

		RepTablero << "}";
		RepTablero.close();

		char  dotT[] = "dot -Tjpg RepTablero.dot -o RepTablero.jpg";
		system(dotT);
		char  dotI[] = "RepTablero.jpg";
		system(dotI);
	}

}

void Matriz::Tablero() {

	Matriz* _fila = this->_Inicio;
	for (int i = 0; i < this->Dimension; i++)
	{
		Matriz* _columna = _fila;
		for (int i = 0; i < this->Dimension; i++)
		{
			/*RepTablero << to_string((int)&*_columna) << "[label =\"" << "(" + to_string(_columna->getX()) + "," + to_string(_columna->getY()) + ")\"];";;*/

			/*RepTablero << to_string((int)&*_columna) << "[label =\"" << _columna->getPunto() << "\"];";*/

			RepTablero << to_string((int)&*_columna);
			if (_columna->getFicha() != NULL)
			{
				RepTablero << "[label =\"" << _columna->getFicha()->GetLetra()  << "\"];";
			}
			else
			{
				RepTablero << "[label =\"  \"];";
			}

			if (_columna->_Dercha!=NULL)
			{
				RepTablero << to_string((int)&*_columna) << "->" << to_string((int)&*_columna->_Dercha) << "[dir=both] ;" << endl;
			}
			
			_columna = _columna->_Dercha;
		}

		_fila = _fila->_Abajo;
	}

	Matriz* _columna = this->_Inicio;
	for (int i = 0; i < this->Dimension; i++)
	{
		_fila = _columna;
		for (int i = 0; i < this->Dimension; i++)
		{
			//RepTablero << to_string((int)&*_fila) << "[label =\"" << "(" + to_string(_fila->getX()) + "," + to_string(_fila->getY()) + ")\"];";
			/*RepTablero << to_string((int)&*_fila) << "[label =\"" << _fila->getPunto() << "\"];";*/

			RepTablero << to_string((int)&*_fila);
			if (_fila->getFicha() != NULL)
			{
				RepTablero << "[label =\"" <<  _fila->getFicha()->GetLetra()   << "\"];";
			}
			else
			{
				RepTablero << "[label =\"  \"];";
			}

			if (_fila->_Abajo != NULL)
			{
				RepTablero << to_string((int)&*_fila) << "->" << to_string((int)&*_fila->_Abajo)  << "[dir=both] ;" << endl;
			}

			_fila = _fila->_Abajo;
		}

		_columna = _columna->_Dercha;
	}
}





/// ========================== PENDIENTE ==============================

//void Matriz::ImprimirTablero() {
//
//	Matriz* aux = this->_Inicio->_Abajo;
//	for (int i = 0; i < this->Dimension; i++)
//	{
//		string rank = "{rank = same;";
//		if (VerDerecha(aux))
//		{
//
//			rank += "};";
//		}
//		else
//		{
//			aux->_Aux->_Abajo;
//			i++;
//		}
//
//		aux = aux->_Abajo;
//	}
//}
//
//bool Matriz::VerDerecha(Matriz* _Celda) {
//	if (_Celda!=NULL)
//	{
//		if (_Celda->getFicha()!=NULL )
//		{
//			return true;
//		}
//		else
//		{
//			return VerDerecha(_Celda->_Dercha);
//		}
//	}
//	return false;
//}
//
//bool Matriz::VerAbajo(Matriz* _Celda) {
//	if (_Celda != NULL)
//	{
//		if (_Celda->getFicha() != NULL)
//		{
//			return true;
//		}
//		else
//		{
//			return VerAbajo(_Celda->_Abajo);
//		}
//	}
//	return false;
//}