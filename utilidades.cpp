#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

using namespace std;

#include "utilidades.h"

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

void cargarEnteros(const char* msj, int *dato,int inicio,int fin) {
	bool estado = true;
	do {
		system("cls");
		cout << msj;
		cin >> *dato;
		if (fin == -1 && *dato >= inicio) {
			estado = false;
		}else if (*dato >= inicio && *dato <= fin) {
			estado = false;
		}else {
			cout << "ERROR: INGRESE CORRECTAMENTE LOS DATOS" << endl;
			system("pause");
		}
		system("cls");
	} while (estado != false);
}
void cargarFlotantes(const char* msj, float* dato, int inicio) {
	bool estado = true;
	do {
		system("cls");
		cout << msj;
		cin >> *dato;
		if (*dato >= inicio) {
			estado = false;
		}else {
			cout << "ERROR" << endl;
			system("pause");
		}
		system("cls");
	} while (estado != false);
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
 void cargarFechas(const char* titulo,Fecha *reg, bool opc) {

	bool state = !(opc);
	do {
		system("cls");

		cout << titulo << endl;
		*reg = cargarFecha();

		if (opc) {
			if (verificarFecha(*reg) != true) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
				cout << "ERROR AL INGRESAR DATOS DE LA FECHA" << endl << endl;
				cout << "DEBE INGRESAR UNA FECHA MENOR A LA FECHA ACTUAL!!" << endl;
				system("pause");
			}
			else {
				state = true;
			}
		}
		else {
			if (verificarFecha(*reg) != false) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
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
			system("cls");
			cout << "ERROR:CAMPO INCOMPLETO!! \t NO DEBE DEJAR LOS CAMPOS VACIOS " << endl;
			system("pause");
			system("cls");
			state = false;
		}
	}
}
