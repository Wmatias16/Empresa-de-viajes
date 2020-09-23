#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;
#include "utilidades.h"
#include "chofer.h"
#include "viaje.h"

int main()
{
	int opt;
	do {
		system("cls");
		cout << "MENU PRINCIPAL" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) CHOFERES" << endl;
		cout << "2) VIAJES" << endl;
		cout << "3) REPORTES" << endl;
		cout << "4) CONFIGURACION" << endl;
		cout << "----------------------" << endl << endl;
		cout << "0) SALIR DEL PROGRAMA" << endl;

		cout << "OPCION: ";
		cin >> opt;

		switch (opt) {
		case 1:
			menuChoferes();
			break;
		case 2:menuViajes();
			break;
		case 3:
			break;
		case 4:
			break;
		}
	} while (opt != 0);

	return 0;
}
