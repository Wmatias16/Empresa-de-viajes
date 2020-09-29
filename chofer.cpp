#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* ARCHIVO_CHOFER = "choferes.dat";

#include "utilidades.h"
#include "Chofer.h"

using namespace std;

void nuevoChofer() {
	system("cls");

	Chofer reg = agregarChofer();
	int pos = siExiste(reg.dni, reg.cuit);

	if (pos < 0) {
		if (crearChofer(reg)) {
			cout << "CHOFER CREADO CORRECTAMENTE!!" << endl;
			system("pause");
		}
	}
	else {
		cout << "EL CHOFER QUE DESEA CREAR YA SE EXISTE!!" << endl;
		system("pause");
	}

}

void eliminarChofer() {
	int pos = pedirDni();

	if (pos >= 0) {
		Chofer reg;

		leerChofer(pos,&reg);
		reg.estado = false;

		if (modificarChofer(reg, pos)) {
			cout << "BAJA LOGICA HECHO CORRECTAMENTE!!!";
			system("pause");
		}else {
			cout << "ERROR EN HACER LA BAJA LOGICA!!!";
			system("pause");
		}

	}else {
		cout << "NO EXISTE EL D.N.I INGRESADO" << endl;
		system("pause");
	}
}

void modificarFechaChofer() {

	int pos = pedirDni();

	if (pos >= 0) {
		Chofer reg;
		leerChofer(pos,&reg);

		cargarFechas("INGRESE NUEVA FECHA DE VENCIMIENTO", &reg.fechaDeVencimiento, false);

		if (modificarChofer(reg, pos)) {
			cout << "FECHA MODIFICADA CORRECTAMENTE!!!" << endl;
			system("pause");
		}
		else {
			cout << "ERROR EN MODIFICAR LA FECHA!!!";
			system("pause");
		}
	}
	else {
		cout << "NO EXISTE EL D.N.I INGRESADO" << endl;
		system("pause");
	}
}

void listarUnchofer() {
	int pos = pedirDni();

	if (pos >= 0) {
		Chofer reg;
		leerChofer(pos, &reg);
		mostrarChofer(reg);
	}
	else {
		cout << "NO EXISTE EL D.N.I INGRESADO" << endl;
		system("pause");
		return;
	}
	system("pause");
}

void listarChoferes() {
	system("cls");

	int cantChofer = cantidadDeChoferes();
	if (cantChofer != -1) {
		Chofer reg;

		for (int i = 0; i < cantChofer; i++) {
			leerChofer(i, &reg);
			mostrarChofer(reg);
		}
		system("pause");
	}
	else {
		cout << "ERROR: NO EXISTE NINGUN CHOFER EN EL SISTEMA"<< endl;
	}
}

bool crearChofer(Chofer reg) {
	bool guardo = false;
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "ab");

	if (fchofer == NULL)return guardo;

	guardo = fwrite(&reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return guardo;
}

bool modificarChofer(Chofer reg, int pos) {
	bool guardo;
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "rb+");

	if (fchofer == NULL) return false;

	fseek(fchofer, pos * sizeof(Chofer), SEEK_SET);

	guardo = fwrite(&reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return guardo;
}

bool leerChofer(int pos,Chofer *reg) {
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "rb");
	bool leyo = false;
	if (fchofer == NULL)return leyo;

	fseek(fchofer, pos * sizeof(Chofer), SEEK_SET);

	leyo = fread(reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return leyo;
}

int siExiste(char* dni) {
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "rb");
	Chofer reg;
	int pos = 0;

	if (fchofer == NULL) return -1;

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

int pedirDni() {
	system("cls");
	char dni[10];
	cout << "INGRESE EL D.N.I DEL CHOFER: ";
	cin >> dni;
	return siExiste(dni);
}

int cantidadDeChoferes() {
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "rb");

	if (fchofer == NULL) {
		return -1;
	}
	fseek(fchofer, 0, SEEK_END);

	int cantReg = ftell(fchofer) / sizeof(Chofer);

	fclose(fchofer);
	return cantReg;
}

int siExiste(char* dni, char* cuit) {
	FILE* fchofer = fopen(ARCHIVO_CHOFER, "rb");
	Chofer reg;
	int pos = 0;

	if (fchofer == NULL)return -1;

	while (fread(&reg, sizeof(Chofer), 1, fchofer) == 1) {
		if (strcmp(reg.dni, dni) == 0 || strcmp(reg.cuit, cuit) == 0) {
			fclose(fchofer);
			return pos;
		}pos++;
	}
	fclose(fchofer);

	return -1;
}

Chofer agregarChofer() {
	Chofer reg;
	int opt;
	verificarCadena("INGRESE NRO DE D.N.I:", reg.dni, 10);
	verificarCadena("INGRESE APELLIDO:", reg.apellido, 50);
	verificarCadena("INGRESE NOMBRE:", reg.nombre, 50);
	cargarFechas("------ - INGRESE FECHA DE INGRESO-------- ", &reg.fechaIngreso, true);
	verificarCadena("INGRESE C.U.I.T: ", reg.cuit, 20);
	cargarEnteros("TIPO DE REGISTRO: ", &reg.tipoDeRegistro, 1, 3);
	cargarFechas(" -------INGRESE FECHA DE VENCIMIENTO DEL REGISTRO--------", &reg.fechaDeVencimiento, false);
	verificarCadena("INGRESE NRO DE TELEFONO:", reg.telefono, 15);
	cargarEnteros("0.SOY PROPIETARIO\t 1. NO SOY PROPIETARIO\n PROPIETARIO: ", &opt, 0, 1);
	reg.propietarioDelAuto = opt;
	reg.estado = true;
	return reg;
}

void mostrarChofer(Chofer reg) {

	if (reg.estado == true) {
		cout << "NRO DE D.N.I:  " << reg.dni << endl;
		cout << "APELLIDO: " << reg.apellido << endl;
		cout << "NOMBRE: " << reg.nombre << endl;
		cout << "FECHA DE INGRESO-------- " << endl;
		cout << reg.fechaIngreso.dia << " / " << reg.fechaIngreso.mes << " / " << reg.fechaIngreso.anio << endl;
		cout << "C.U.I.T: " << reg.cuit << endl;
		cout << "TIPO DE REGISTRO: " << reg.tipoDeRegistro << endl;
		cout << "FECHA DE VENCIMIENTO DEL REGISTRO--------  " << endl;
		cout << reg.fechaDeVencimiento.dia << " / " << reg.fechaDeVencimiento.mes << " / " << reg.fechaDeVencimiento.anio << endl;
		cout << "INGRESE NRO DE TELEFONO: " << reg.telefono << endl;
		cout << "PROPIETARIO: " << reg.propietarioDelAuto << endl;
		cout << endl;
	}

}
