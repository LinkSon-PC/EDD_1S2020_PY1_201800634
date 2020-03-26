#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include <ctime>
#include <iostream>
using namespace std;

class Ficha
{
	char Letra;
	int Valor;
	Ficha* Next;

public:
	static Ficha Lista;
	int Contador;

	Ficha* First;
	Ficha* Last;
	int Cantidad;

	Ficha();
	Ficha(char, int);

	Ficha(int);

	inline char GetLetra() { return this->Letra; }
	inline void SetLetra(char _Letra) { this->Letra=_Letra; }

	inline int GetValor() { return this->Valor; }
	inline void SetValor(int _Valor) { this->Valor = _Valor; }

	inline int GetCantidad() { return this->Cantidad; }
	inline void SetCantidad(int _Cantidad) { this->Cantidad = _Cantidad; }

	inline void IngresarInicio(char,int);
	inline void IngresarFinal(char, int);


	inline void Aleatorio();
	inline void IngresarCaso(char, int);

	inline void Sacar();


	inline void Imprimir();

};

Ficha Ficha::Lista = NULL;

Ficha::Ficha() {
	this->Contador =0;
	this->First = NULL;
	this->Last = NULL;

	SetLetra(' ');
	SetValor(0);
	SetCantidad(0);
}

Ficha::Ficha(int _Cantidad) {
	this->SetCantidad(_Cantidad);
	this->First = NULL;
	this->Last = NULL;
	this->Contador = 0;
}

Ficha::Ficha(char _Letra, int _Valor) {
	SetLetra(_Letra);
	SetValor(_Valor);
	this->Next = NULL;
}


void Ficha::IngresarInicio(char _Letra, int _Valor) {
	Ficha* _ficha = new Ficha(_Letra, _Valor);
	if (this->First == NULL)
	{
		this->First = _ficha;
		this->Last = _ficha;
	}
	else
	{
		_ficha->Next = this->First;
		this->First = _ficha;
	}

	this->Contador++;
}

//ESTRUCTURA FIFO (COLA)
void Ficha::IngresarFinal(char _Letra, int _Valor) {
	Ficha* _ficha = new Ficha(_Letra, _Valor);
	if (this->Last == NULL)
	{
		this->First = _ficha;
		this->Last = _ficha;
	}
	else
	{
		this->Last->Next =_ficha;
		this->Last = _ficha;
	}
	this->Contador++;
}

void Ficha::Sacar() {
	if (this->Contador > 0)
	{
		if (this->First->Next != NULL)
		{
			this->First = Ficha::Lista.First->Next;
		}
		else
		{
			this->First = NULL;
			this->Last = NULL;
		}
		Ficha::Lista.Contador--;
	}
}

void Ficha::Aleatorio() {
	Ficha::Lista = Ficha::Ficha();


	Ficha* doce = new Ficha(12);
	doce->IngresarCaso('A', 1);
	doce->IngresarCaso('E', 1);

	Ficha* nueve = new Ficha(9);
	nueve->IngresarCaso('O', 1);
	nueve->IngresarCaso('I', 1);

	Ficha* seis = new Ficha(6);
	seis->IngresarCaso('S', 1);

	Ficha* cinco = new Ficha(5);
	cinco->IngresarCaso('N', 1);
	cinco->IngresarCaso('R', 1);
	cinco->IngresarCaso('U', 1);
	cinco->IngresarCaso('D', 2);

	Ficha* cuatro = new Ficha(4);
	cuatro->IngresarCaso('L', 1);
	cuatro->IngresarCaso('T', 1);
	cuatro->IngresarCaso('C', 3);

	Ficha* dos = new Ficha(2);
	dos->IngresarCaso('G', 2);
	dos->IngresarCaso('B', 3);
	dos->IngresarCaso('M', 3);
	dos->IngresarCaso('P', 3);
	dos->IngresarCaso('H', 4);

	Ficha* uno = new Ficha(1);
	uno->IngresarCaso('F', 4);
	uno->IngresarCaso('V', 4);
	uno->IngresarCaso('Y', 2);
	uno->IngresarCaso('Q', 5);
	uno->IngresarCaso('J', 8);
	uno->IngresarCaso('Ñ', 8);
	uno->IngresarCaso('X', 8);
	uno->IngresarCaso('Z', 10);
}

void Ficha::IngresarCaso(char _Letra, int _Valor) {
	srand(time(0));

	for (int i = 0; i < GetCantidad(); i++)
	{
		int _nodo = (rand() % 10);

			Ficha * _aux = Ficha::Lista.First;
			
			if (_nodo == 0 || _nodo == 1)
			{
				Ficha::Lista.IngresarInicio(_Letra, _Valor);
			}
			else if (_nodo == 9)
			{
				Ficha::Lista.IngresarFinal(_Letra, _Valor);
			}
			else if (Ficha::Lista.Contador > (Ficha::Lista.Contador % _nodo))
			{
				Ficha* _nuevo = new Ficha(_Letra, _Valor);

				for (int i = 0; i < (Ficha::Lista.Contador % _nodo); i++)
				{
					_aux = _aux->Next;
				}

				_nuevo->Next = _aux->Next;
				_aux->Next = _nuevo;

				Ficha::Lista.Contador++;
			}
			else
			{
				Ficha::Lista.IngresarFinal(_Letra, _Valor);
			}
	}

}

void Ficha::Imprimir() {

	Ficha* _aux = Ficha::Lista.First;

	for (int i = 0; i < Ficha::Lista.Contador; i++)
	{
		if (_aux!=NULL)
		{
			cout << "Letra: "<< _aux->GetLetra() << " -> Valor:" + to_string(_aux->GetValor()) + " " + to_string(i) << endl;
			_aux = _aux->Next;
		}
	}

	cout << "EL contador es: " << Ficha::Lista.Contador << endl;
}
