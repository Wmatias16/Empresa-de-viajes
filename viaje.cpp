#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "utilidades.h"
#include "viaje.h"

using namespace std;


const char* ARCHIVO_VIAJES = "viajes.dat";

void menuViajes() {
	int opt;
	do {
		system("cls");
		cout << "MENU VIAJES" << endl;
		cout << "----------------------" << endl << endl;
		cout << "1) NUEVO VIAJE" << endl;
		cout << "2) LISTAR VIJAE POR ID VIAJE" << endl;
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
		}
	} while (opt != 0);
}




////////////////////////ABML///////////////////////////////////
void nuevoViaje() {
	int pos;
	Viaje reg = cargarViaje();
	int cant = cantidadDeViajes(reg);
	cant++;

	reg.idViaje = cant;

	pos = siExiste(reg.dniChofer);

	if (pos > 0) {
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
	FILE* fviaje;
	Viaje reg;

	int pos = pedirID();

	fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
		system("pause");
		return;
	}

	if (pos >= 0) {

		fseek(fviaje, pos * sizeof(Viaje), 0);
		fread(&reg, sizeof(reg), 1, fviaje);
		mostrarViaje(reg);

		fclose(fviaje);
	}
	else {
		cout << "NO EXISTE EL ID INGRESADO" << endl;
		system("pause");
		return;
	}

	fclose(fviaje);
	system("pause");
}

void listarViajes() {
	FILE* fviaje;
	Viaje reg;
	system("cls");
	fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
		system("pause");
		return;
	}

	while (fread(&reg, sizeof(Viaje), 1, fviaje) == 1) {
		mostrarViaje(reg);
		cout << endl;
	}

	system("pause");
	fclose(fviaje);
}




void bajaViaje() {
	Viaje reg;
	int pos;
	pos = pedirID();

	if (pos >= 0) {

		reg = leerViaje(pos);

		reg.estado = false;

		if (crearViaje(reg, pos)) {
			cout << "BAJA LOGICA HECHO CORRECTAMENTE!!!";
			system("pause");
		}
		else {
			cout << "ERROR EN HACER LA BAJA LOGICA!!!";
			system("pause");
		}
	}
	else {
		cout << "NO EXISTE EL D.N.I INGRESADO" << endl;
		system("pause");
		return;
	}
}






////////////////////////ABML///////////////////////////////////



int pedirID() {
	int id;
	system("cls");
	cout << "INGRESE EL ID DEL VIAJE: ";
	cin >> id;
	return siExisteID(id);
}


int siExisteID(int id) {
	FILE* fviaje;
	Viaje reg;
	int pos = 0;

	fviaje = fopen(ARCHIVO_VIAJES, "rb");

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


Viaje leerViaje(int pos) {
	FILE* fviaje;
	Viaje reg;

	fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		cout << "ERROR AL GUARDAR REGISTRO" << endl;
	}

	fseek(fviaje, pos * sizeof(Viaje), SEEK_SET);

	fread(&reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);

	return reg;
}

bool crearViaje(Viaje reg) {
	FILE* fviaje;
	bool guardo;
	fviaje = fopen(ARCHIVO_VIAJES, "ab");

	if (fviaje == NULL) {
		cout << "ERROR AL ABRIR REGISTRO" << endl;
		system("pause");
		return false;
	}
	guardo = fwrite(&reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);

	return guardo;
}

bool crearViaje(Viaje reg, int pos) {
	FILE* fviaje;
	bool guardo;
	fviaje = fopen(ARCHIVO_VIAJES, "rb+");

	if (fviaje == NULL) {
		return false;
	}

	fseek(fviaje, pos * sizeof(Viaje), SEEK_SET);

	guardo = fwrite(&reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);

	return guardo;
}


int cantidadDeViajes(Viaje reg) {
	FILE* fviaje;

	fviaje = fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		return 0;
	}
	fseek(fviaje, 0, SEEK_END);

	int cantReg = ftell(fviaje) / sizeof(Viaje);

	fclose(fviaje);
	return cantReg;
}



void  mostrarUnviaje() {
	FILE* fviaje;
	Viaje reg;

	int pos = pedirID();

	fviaje= fopen(ARCHIVO_VIAJES, "rb");

	if (fviaje == NULL) {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
		system("pause");
		return;
	}

	if (pos >= 0) {

		fseek(fviaje, pos * sizeof(Viaje), 0);
		fread(&reg, sizeof(reg), 1, fviaje);
		mostrarViaje(reg);

		fclose(fviaje);
	}
	else {
		cout << "NO EXISTE EL ID INGRESADO" << endl;
		system("pause");
		return;
	}

	fclose(fviaje);
	system("pause");
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
		cout << "ESTADO: " << reg.estado << endl;

	}
}


Viaje cargarViaje() {
	Viaje reg;

	verificarCadena("INGRESE DNI DEL CHOFER: ", reg.dniChofer, 10);
	reg.idCliente = cargarEnteros("INGRESE ID CLIENTE: ");
	reg.fechaDeViaje = cargarFechas("INGRESE FECHA DEL VIAJE: ", true);
	reg.horaDeSalida = cargarEnteros("INGRESE LA HORA DE SALIDA: ");
	reg.kilometraje = cargarEnteros("INGRESE EL KILOMETRAJE: ");
	reg.importe = cargarEnteros("INGRESE EL IMPORTE: ");
	reg.calificacion = cargarEnteros("INGRESE LA CALIFICACION: ");
	verificarCadena("INGRESE NRO DE PATENTE: ", reg.patente, 10);
	reg.estado = true;

	return reg;
}
