#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#include "utilidades.h"
#include "viaje.h"
#include "Chofer.h"
#include "backup.h"
#include "reportes.h"
#include "menu.h"


void menuPrincipal() {
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
		case 1:menuChoferes();
			break;
		case 2:menuViajes();
			break;
		case 3:menuReportes();
			break;
		case 4:menuBackup();
			break;
		case 0:cout << "SALIENDO.."<< endl; system("pause");
			break;
		default: cout << "ERROR! \t NO EXISTE LA OPCION INGRESADA" << endl; system("pause");
			break;
		}
	} while (opt != 0);
}
void menuChoferes() {
	int opt;
	do {
		system("cls");
		cout << "MENU CHOFERES" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) NUEVO CHOFER" << endl;
		cout << "2) MODIFICAR CHOFER" << endl;
		cout << "3) LISTAR CHOFER POR DNI" << endl;
		cout << "4) LISTAR TODOS LOS CHOFERES" << endl;
		cout << "5) ELIMINAR CHOFER" << endl;
		cout << "----------------------" << endl << endl;
		cout << "0) VOLVER AL MENU PRINCIPAL" << endl;

		cout << "OPCION: ";
		cin >> opt;

		switch (opt) {
			case 1: nuevoChofer();
				break;
			case 2:modificarFechaChofer();
				break;
			case 3:listarUnchofer();
				break;
			case 4:listarChoferes();
				break;
			case 5:eliminarChofer();
				break;
			case 0:cout << "SALIENDO.." << endl; system("pause");
				break;
			default: cout << "ERROR! \t NO EXISTE LA OPCION INGRESADA" << endl; system("pause");
				break;
		}
	} while (opt != 0);
}
void menuViajes() {
	int opt;
	do {
		system("cls");
		cout << "MENU VIAJES" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) NUEVO VIAJE" << endl;
		cout << "2) LISTAR VIAJE POR ID" << endl;
		cout << "3) LISTAR TODOS LOS VIAJES" << endl;
		cout << "4) ELIMINAR VIAJE" << endl;
		cout << "----------------------" << endl << endl;
		cout << "0) VOLVER AL MENU PRINCIPAL" << endl;

		cout << "OPCION: ";
		cin >> opt;

		switch (opt) {
		case 1:nuevoViaje();
			break;
		case 2:listarUnViaje();
			break;
		case 3:listarViajes();
			break;
		case 4:bajaViaje();
			break;
		case 0:cout << "SALIENDO.." << endl; system("pause");
			break;
		default: cout << "ERROR! \t NO EXISTE LA OPCION INGRESADA" << endl; system("pause");
			break;
		}
	} while (opt != 0);
}
void menuBackup() {
	int opt;
	do {
		system("cls");
		cout << "MENU BACKUP" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) REALIZAR BACKUP" << endl;
		cout << "2) RESTUARAR BACKUP" << endl;
		cout << "3) CARGAR DATOS DE INICIO" << endl;
		cout << "----------------------" << endl << endl;
		cout << "0) VOLVER AL MENU PRINCIPAL" << endl;

		cout << "OPCION: ";
		cin >> opt;

		switch (opt) {
		case 1:backup();
			break;
		case 2:restaurar();
			break;
		case 3:cargarDatosInicio();
			break;
		case 0:cout << "SALIENDO.." << endl; system("pause");
			break;
		default: cout << "ERROR! \t NO EXISTE LA OPCION INGRESADA" << endl; system("pause");
			break;
		}
	} while (opt != 0);
}
void menuReportes() {
	int opt;
	do {
		system("cls");
		cout << "MENU REPORTES" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) PUNTO A" << endl;
		cout << "2) PUNTO B" << endl;
		cout << "3) PUNTO C" << endl;
		cout << "----------------------" << endl << endl;
		cout << "0) VOLVER AL MENU PRINCIPAL" << endl;

		cout << "OPCION: ";
		cin >> opt;

		switch (opt) {
		case 1:puntoA();
			break;
		case 2:puntoB();
			break;
		case 3:puntoC();
			break;
		case 0:cout << "SALIENDO.." << endl; system("pause");
			break;
		default: cout << "ERROR! \t NO EXISTE LA OPCION INGRESADA" << endl; system("pause");
			break;
		}
	} while (opt != 0);
}
