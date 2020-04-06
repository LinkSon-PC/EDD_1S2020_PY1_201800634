
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
	
	inline int getPunteo() { return this->Puntos; }
	inline void setPunteo(int _Punteo) { this->Puntos = _Punteo; }

	inline Punteo* getSiguiente() { return this->Next; };
	inline void setSiguiente(Punteo* Siguiente) { this->Next = Siguiente; };

	 Punteo();
	 Punteo(int);


	 void IngresarInicio(int);
	 void IngresarFinal(int);

	 void Agregar_Ordenar(int);

	 void Imprimir();
};
