#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

#include "utilidades.h"
#include "chofer.h"


int pedirDni() {
	char dni[10];
	system("cls");
	cout << "INGRESE EL D.N.I DEL CHOFER: ";
	cin >> dni;
	return siExiste(dni);
}



int siExiste(char* dni) {
	FILE* fchofer;
	Chofer reg;
	int pos = 0;

	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		return -2;
	}

	while (fread(&reg, sizeof(Chofer), 1, fchofer) == 1) {
		if (strcmp(reg.dni, dni) == 0) {
			fclose(fchofer);
			return pos;
		}
		pos++;
	}
	fclose(fchofer);

	return -1;
}

int siExiste(char* dni, char* cuit) {
	FILE* fchofer;
	Chofer reg;
	int pos = 0;

	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		return -2;
	}

	while (fread(&reg, sizeof(Chofer), 1, fchofer) == 1) {
		if (strcmp(reg.dni, dni) == 0 || strcmp(reg.cuit, cuit) == 0) {
			fclose(fchofer);
			return pos;
		}
		pos++;
	}
	fclose(fchofer);

	return -1;
}
struct Fecha cargarFecha() {
	struct Fecha fecha;

	cout << "INGRESE EL DIA: ";
	cin >> fecha.dia;
	cout << "INGRESE EL MES: ";
	cin >> fecha.mes;
	cout << "INGRESE EL ANIO: ";
	cin >> fecha.anio;

	return fecha;
}


int cargarEnteros(const char* msj) {
	int dato;
	cout << msj;
	cin >> dato;
	system("cls");
	return dato;
}


void cargarCadena(char* pal, int tam) {
	int i;
	fflush(stdin);
	for (i = 0; i < tam; i++) {
		pal[i] = cin.get();
		if (pal[i] == '\n') break;
	}
	pal[i] = '\0';
	fflush(stdin);
}

bool verificarFecha(struct Fecha reg) {
	int anio, mes, dia, diasFechaSistema, diasFechaIngresado, diferencia;
	bool state;
	time_t t = time(0);
	tm* now = localtime(&t);

	anio = now->tm_year + 1900;
	mes = now->tm_mon + 1;
	dia = now->tm_mday;

	diasFechaSistema = (anio * 365) + (mes - 1) * 30 + dia;
	diasFechaIngresado = (reg.anio * 365) + (reg.mes - 1) * 30 + reg.dia;

	diferencia = diasFechaSistema - diasFechaIngresado;

	state = (diferencia >= 0) ? true : false;

	return state;
}
struct Fecha cargarFechas(const char* titulo, bool opc) {
	struct Fecha reg;

	bool state = !(opc);
	do {
		system("cls");

		cout << titulo << endl;
		reg = cargarFecha();

		if (opc) {
			if (verificarFecha(reg) != true) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
				cout << "ERROR AL INGRESAR DATOS DE LA FECHA" << endl << endl;
				cout << "DEBE INGRESAR UNA FECHA MENOR A LA FECHA ACTUAL!!" << endl;
				system("pause");
			}
			else {
				state = true;
			}
		}
		else {
			if (verificarFecha(reg) != false) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
				cout << "ERROR AL INGRESAR DATOS DE LA FECHA" << endl << endl;
				cout << "DEBE INGRESAR UNA FECHA MAYOR A LA FECHA ACTUAL!!" << endl;
				system("pause");
			}
			else {
				state = false;
			}
		}

	} while (state == !(opc));
	system("cls");
	return reg;
}

void verificarCadena(const char* reg, char* v, int tam) {
	bool state = false;

	while (state == false) {
		cout << reg;

		cargarCadena(v, tam);

		if (strlen(v) < tam && strlen(v) > 2) {
			system("cls");
			state = true;
		}
		else {
			system("cls");      //USAR RLUTIL
			cout << "CAMPO INCOMPLETO!!" << endl;
			state = false;
		}
	}
}
