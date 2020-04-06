
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

//#include  "Ficha.h"

class Mano
{
	Ficha* _Ficha;
	Mano* _Siguiente;
	Mano* _Anterior;

public:
	int _Contador;

	Mano* Primero;
	Mano* Ultimo;

	Mano();
	Mano(Ficha* Ficha);

	inline Ficha* getFicha() { return this->_Ficha; };
	inline void setFicha(Ficha* Ficha) { this->_Ficha = Ficha; };

	inline int getContador() { return this->_Contador; };
	inline void setContador(int Contador) { this->_Contador = Contador; };

	inline Mano* getSiguiente() { return this->_Siguiente; };
	inline void setSiguiente(Mano* Siguiente) { this->_Siguiente = Siguiente; };

	inline Mano* getAnterior() { return this->_Anterior; };
	inline void setAnterior(Mano* Anterior) { this->_Anterior = Anterior; };


	void AgregarInicio(Ficha*);
	void AgregarFinal(Ficha*);

	 void AgregarMano();

	 ofstream RepManoLD;
	 void VerMano();
	 void ReporteManoLD();


	 void CambiarFicha();

	 void QuitarFicha(int Nodo);
	 Ficha* SeleccionarFicha(int Nodo);

	 void ColocarFicha(int Nodo);
};

Mano::Mano(){
	this->_Contador = 0;

	this->_Ficha = NULL;
	this->_Anterior = NULL;
	this->_Siguiente = NULL;

	this->Primero = NULL;
	this->Ultimo = NULL;
}

Mano::Mano(Ficha* Ficha) {
	this->_Contador = 0;

	this->_Ficha = Ficha;

	this->Primero = NULL;
	this->Ultimo = NULL;
}

void Mano::AgregarInicio(Ficha* Ficha) {
	Mano* _Nuevo = new Mano(Ficha);
	if (this->Primero ==NULL)
	{
		this->Primero = _Nuevo;
		this->Ultimo = _Nuevo ;
	}
	else
	{
		this->Primero->setAnterior(_Nuevo);
		_Nuevo->setSiguiente(this->Primero);
		this->Primero = _Nuevo;
	}

	this->_Contador++;
}

void Mano::AgregarFinal(Ficha* Ficha) {
	Mano* _Nuevo = new Mano(Ficha);
	if (this->Primero == NULL)
	{
		this->Primero = _Nuevo;
		this->Ultimo = _Nuevo;
	}
	else
	{
		this->Ultimo->setSiguiente(_Nuevo);
		_Nuevo->setAnterior(this->Ultimo);
		this->Ultimo = _Nuevo;
	}

	this->_Contador++;
}

void Mano::AgregarMano(){
	for (int i = 0; i < 5; i++)
	{
		this->AgregarFinal(Ficha::Lista->First);
		Ficha::Lista->Sacar();
	}
}

void Mano::VerMano() {
	Mano* _aux = this->Primero;
	while (_aux !=NULL)
	{
		cout << _aux->_Ficha->GetLetra() << " / " << _aux->_Ficha->GetValor()<< " ->";
		_aux = _aux->getSiguiente();
	}
	cout << endl;
}

void Mano::ReporteManoLD() {

	RepManoLD.open("RepManoLD.dot", ios::out);
	if (RepManoLD.fail()) {
		cout << "ERROR ARCHIVO NO ENCONTRADO" << endl;
	}
	else {

		RepManoLD << "digraph G {rankdir=LR; style = filled; bgcolor = white; color = lightgrey; node[shape=box3d, style = filled];" << endl;


		Mano* _aux = this->Primero;
		while (_aux != NULL)
		{

			RepManoLD << to_string((int)&*_aux) << "[label = \"" << _aux->getFicha()->GetLetra() << "\"] ;" << endl;

			if (_aux->getAnterior() != NULL)
			{
				RepManoLD << to_string((int)&*_aux) << "->" << to_string((int)&*_aux->getAnterior()) << ";" << endl;
			}
			if (_aux->getSiguiente() != NULL)
			{
				RepManoLD << to_string((int)&*_aux) << "->" << to_string((int)&*_aux->getSiguiente()) << ";" << endl;
			}

			_aux = _aux->getSiguiente();
		}
		cout << endl;

		RepManoLD << "}";
		RepManoLD.close();

		char  dotT[] = "dot -Tjpg RepManoLD.dot -o RepManoLD.jpg";
		system(dotT);
		char  dotI[] = "RepManoLD.jpg";
		system(dotI);
	}
}


void Mano::CambiarFicha(){
	int Nodo = 0;
	cout << "INGRESAR NUMERO DE FICHA:" << endl;

	cin >> Nodo;

	if (this->Primero!=NULL)
	{

		Mano* aux = this->Primero;
		for (int i = 0; i < this->_Contador; i++)
		{
			if (Nodo==i)
			{
				Ficha::Lista->GuardarFicha(aux->getFicha());
				aux->setFicha(Ficha::Lista->First);
				Ficha::Lista->Sacar();
			}

			aux = aux->getSiguiente();
		}

	}
}



Ficha* Mano::SeleccionarFicha(int Nodo) {
	Mano* aux = this->Primero;
	for (int i = 0; i < this->_Contador; i++)
	{
		if (Nodo == i)
		{
			return aux->_Ficha;
		}

		aux = aux->getSiguiente();
	}
	return NULL;
}

void Mano::QuitarFicha(int Nodo) {

	if (this->_Contador>1)
	{


		Mano* aux = this->Primero;
		for (int i = 0; i < this->_Contador; i++)
		{
			if (Nodo == i)
			{
				if (aux == this->Primero)
				{
					this->Primero = this->Primero->getSiguiente();
					this->Primero->setAnterior(NULL);
				}
				else if (aux == this->Ultimo)
				{
					this->Ultimo = this->Ultimo->getAnterior();
					this->Ultimo->setSiguiente(NULL);
				}
				else
				{
					aux->getAnterior()->setSiguiente(aux->getSiguiente());
					aux->getSiguiente()->setAnterior(aux->getAnterior());
				}

			}

			aux = aux->getSiguiente();
		}
		this->_Contador--;

	}
	else
	{
		cout << "FICHA ELIMINADA" << endl;
		this->Primero = NULL;
		this->Ultimo = NULL;
		this->_Contador = 0;;
	}
}