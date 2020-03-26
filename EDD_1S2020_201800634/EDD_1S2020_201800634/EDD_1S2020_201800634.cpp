#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Ficha.h"
#include "Punteo.h"
#include "Usuario.h"
#include "Score.h"

using namespace std;

int main()
{
	cout << "==============  FICHA 1  ============" << endl;


	/*srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		cout << (rand() % 10);
	}*/

	/*Ficha::Lista.Aleatorio();
	Ficha::Lista.Imprimir();*/

	//Punteo lista;
	//lista.Agregar_Ordenar(10);
	//lista.Agregar_Ordenar(100);
	//lista.Agregar_Ordenar(3);
	//lista.Agregar_Ordenar(40);
	//lista.Agregar_Ordenar(57);
	//lista.Agregar_Ordenar(99);
	//lista.Agregar_Ordenar(20);
	//lista.Agregar_Ordenar(13);
	//lista.Imprimir();


	/*string n1 = "c";
	string n2 = "f";

	cout << strcmp(n1.c_str(), n2.c_str());*/
	//cout << strcmpi(n1.c_str, n2.c_str);

	Usuario user;
	user.AgregarUsurio("f");
	user.AgregarUsurio("c");
	user.AgregarUsurio("d");
	user.AgregarUsurio("f");
	user.AgregarUsurio("b");
	user.AgregarUsurio("g");
	user.AgregarUsurio("z");


	Score score;
	score.Agregar_Ordenar("f", 55);
	score.Agregar_Ordenar("c", 75);
	score.Agregar_Ordenar("d", 85);
	score.Agregar_Ordenar("b", 25);
	score.Agregar_Ordenar("g", 35);
	score.Agregar_Ordenar("z", 95);


	user.AgregarScore("f",10);
	user.AgregarScore("f", 90);
	user.AgregarScore("f", 15);

	user.AgregarScore("c", 10);
	user.AgregarScore("c", 93);
	user.AgregarScore("c", 17);

	user.AgregarScore("d", 50);
	user.AgregarScore("d", 40);
	user.AgregarScore("d", 32);

	user.AgregarScore("b", 54);
	user.AgregarScore("g", 30);
	user.AgregarScore("z", 45);
	user.Imprimir();

	score.Imprimir();


}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
