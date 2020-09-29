#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const char* ARCHIVO_VIAJES = "viajes.dat";

#include "utilidades.h"
#include "Chofer.h"
#include "viaje.h"

using namespace std;

void nuevoViaje() {
	Viaje reg = cargarViaje();

	int pos = siExiste(reg.dniChofer);

	if (pos >= 0) {
		reg.idViaje = cantidadDeViajes() + 1;

		if (crearViaje(reg)) {
			cout << "VIAJE CREADO CORRECTAMENTE!!" << endl;
			system("pause");
		}
	}
	else {
		cout << "ERROR: EL DNI DEL CHOFER NO EXISTE!!" << endl;
		system("pause");
	}
}

void listarUnViaje() {

	int pos = pedirID();

	if (pos >= 0) {
		Viaje reg;
		leerViaje(pos, &reg);
		mostrarViaje(reg);
	}
	else {
		cout << "NO EXISTE EL ID INGRESADO" << endl;
		system("pause");
		return;
	}
	system("pause");
}

void listarViajes() {
	system("cls");

	int cantViajes = cantidadDeViajes();

	if (cantViajes != -1) {
		Viaje reg;

		for (int i = 0; i < cantViajes; i++) {
			leerViaje(i, &reg);
			mostrarViaje(reg);
			cout << endl;
		}
		system("pause");
	}
	else {
		cout << "ERROR: NO EXISTE NINGUN VIAJE EN EL SISTEMA" << endl;
		system("pause");

	}
}

void bajaViaje() {
	int pos = pedirID();

	if (pos >= 0) {
		Viaje reg;
		leerViaje(pos,&reg);

		reg.estado = false;

		if (modificarViaje(reg, pos)) {
			cout << "BAJA LOGICA HECHO CORRECTAMENTE!!!" << endl;
			system("pause");
		}
		else {
			cout << "ERROR EN HACER LA BAJA LOGICA!!!" << endl;
			system("pause");
		}
	}
	else {
		cout << "NO EXISTE EL ID INGRESADO" << endl;
		system("pause");
	}
}

int pedirID() {
	int id;
	system("cls");
	cout << "INGRESE EL ID DEL VIAJE: ";
	cin >> id;
	return siExisteID(id);
}

int siExisteID(int id) {
	FILE* fviaje = fopen(ARCHIVO_VIAJES, "rb");
	Viaje reg;
	int pos = 0;

	if (fviaje == NULL) {
		return -2;
	}

	while (fread(&reg, sizeof(Viaje), 1, fviaje) == 1) {
		if (id == reg.idViaje) {
			fclose(fviaje);
			return pos;
		}
		pos++;
	}
	fclose(fviaje);
	return -1;
}

bool leerViaje(int pos,Viaje *reg) {
	bool leyo = false;
	FILE* fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL)return leyo;

	fseek(fviaje, pos * sizeof(Viaje), SEEK_SET);

	leyo = fread(reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);
	return leyo;
}

bool crearViaje(Viaje reg) {
	FILE* fviaje = fopen(ARCHIVO_VIAJES, "ab");
	bool guardo = false;

	if (fviaje == NULL) {
		cout << "ERROR AL ABRIR REGISTRO" << endl;
		system("pause");
		return guardo;
	}
	guardo = fwrite(&reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);
	return guardo;
}

bool modificarViaje(Viaje reg, int pos) {
	bool guardo = false;
	FILE* fviaje = fopen(ARCHIVO_VIAJES, "rb+");

	if (fviaje == NULL) {
		return guardo;
	}
	fseek(fviaje, pos * sizeof(Viaje), SEEK_SET);

	guardo = fwrite(&reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);
	return guardo;
}

int cantidadDeViajes() {
	FILE* fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		return 0;
	}

	fseek(fviaje, 0, SEEK_END);

	int cantReg = ftell(fviaje) / sizeof(Viaje);

	fclose(fviaje);
	return cantReg;
}

void mostrarViaje(Viaje reg) {
	if (reg.estado == true) {
		cout << "ID VIAJE: "<< reg.idViaje << endl;
		cout << "D.N.I DEL CHOFER: " << reg.dniChofer << endl;
		cout << "ID CLIENTE: "<< reg.idCliente << endl;
		cout << "FECHA DEL VIAJE: "<<endl;
		cout << reg.fechaDeViaje.dia << " / " << reg.fechaDeViaje.mes << " / " << reg.fechaDeViaje.anio << endl;
		cout << "HORA DE SALIDA: "<<reg.horaDeSalida << endl;
		cout << "KILOMETRAJE: "<<reg.kilometraje << endl;
		cout << "IMPORTE: " << reg.importe << endl;
		cout << "PATENTE: " << reg.patente << endl;
		cout << "CALIFICACION: "<< reg.calificacion << endl;
	}
}
Viaje cargarViaje() {
	Viaje reg;

	verificarCadena("INGRESE DNI DEL CHOFER: ", reg.dniChofer, 10);
	cargarEnteros("INGRESE ID CLIENTE: ",&reg.idCliente,0,-1);
	cargarFechas("INGRESE FECHA DEL VIAJE: ", &reg.fechaDeViaje , true);
	cargarEnteros("INGRESE LA HORA DE SALIDA: ",&reg.horaDeSalida,0,23);
	cargarFlotantes("INGRESE EL KILOMETRAJE: ",&reg.kilometraje,0);
	cargarFlotantes("INGRESE EL IMPORTE: ",&reg.importe,0);
	verificarCadena("INGRESE NRO DE PATENTE: ", reg.patente, 10);
	cargarEnteros("INGRESE LA CALIFICACION: ",&reg.calificacion,1,5);
	reg.estado = true;

	return reg;
}
