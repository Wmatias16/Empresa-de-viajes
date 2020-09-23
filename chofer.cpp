#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "utilidades.h"
#include "Chofer.h"
using namespace std;

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
		case 1:
			altaChofer();
			break;
		case 2:modificacionChofer();
			break;
		case 3:listarUnchofer();
			break;
		case 4:listarChoferes();
			break;
		case 5:bajaChofer();
			break;
		}
	} while (opt != 0);
}

/// ABML

//////////////////////// ALTA /////////////////////////////////////
void altaChofer() {
	Chofer reg;
	int pos;
	system("cls");

	reg = agregarChofer();


	pos = siExiste(reg.dni, reg.cuit);

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

//////////////////////// BAJA /////////////////////////////////////

void bajaChofer() {
	Chofer reg;
	int pos;
	pos = pedirDni();

	if (pos >= 0) {

		reg = leerChofer(pos);

		reg.estado = false;

		if (crearChofer(reg, pos)) {
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
//////////////////////// MODIFICACION /////////////////////////////////////

void modificacionChofer() {
	Chofer reg;
	int pos;
	pos = pedirDni();

	if (pos >= 0) {

		reg = leerChofer(pos);
		reg.fechaDeVencimiento = cargarFechas("INGRESE NUEVA FECHA DE VENCIMIENTO", false);

		if (crearChofer(reg, pos)) {
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
		return;
	}
}

//////////////////////// LISTADO / S /////////////////////////////////////

void listarUnchofer() {
	FILE* fchofer;
	Chofer reg;

	int pos = pedirDni();

	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
		system("pause");
		return;
	}

	if (pos >= 0) {

		fseek(fchofer, pos * sizeof(Chofer), 0);
		fread(&reg, sizeof(reg), 1, fchofer);
		mostrarChofer(reg);

		fclose(fchofer);
	}
	else {
		cout << "NO EXISTE EL D.N.I INGRESADO" << endl;
		system("pause");
		return;
	}

	fclose(fchofer);
	system("pause");
}

void listarChoferes() {
	FILE* fchofer;
	Chofer reg;
	system("cls");
	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
		system("pause");
		return;
	}

	while (fread(&reg, sizeof(Chofer), 1, fchofer) == 1) {
		mostrarChofer(reg);
		cout << endl;
	}

	system("pause");
	fclose(fchofer);
}


/// END ABML



bool crearChofer(Chofer reg) {
	FILE* fchofer;
	bool guardo;
	fchofer = fopen("choferes.dat", "ab");

	if (fchofer == NULL) {
		cout << "ERROR AL ABRIR REGISTRO" << endl;
		system("pause");
		return false;
	}
	guardo = fwrite(&reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return guardo;
}

bool crearChofer(Chofer reg, int pos) {
	FILE* fchofer;
	bool guardo;
	fchofer = fopen("choferes.dat", "rb+");

	if (fchofer == NULL) {
		return false;
	}
	fseek(fchofer, pos * sizeof(Chofer), SEEK_SET);

	guardo = fwrite(&reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return guardo;
}

Chofer leerChofer(int pos) {
	FILE* fchofer;
	Chofer reg;
	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		cout << "ERROR AL GUARDAR REGISTRO" << endl;
	}

	fseek(fchofer, pos * sizeof(Chofer), SEEK_SET);

	fread(&reg, sizeof(Chofer), 1, fchofer);

	fclose(fchofer);

	return reg;
}




Chofer agregarChofer() {
	Chofer reg;

	verificarCadena("INGRESE NRO DE D.N.I:", reg.dni, 10);

	verificarCadena("INGRESE APELLIDO:", reg.apellido, 50);

	verificarCadena("INGRESE NOMBRE:", reg.nombre, 50);

	reg.fechaIngreso = cargarFechas("------ - INGRESE FECHA DE INGRESO-------- ", true);

	verificarCadena("INGRESE C.U.I.T: ", reg.cuit, 20);

	cout << " TIPO DE REGISTRO: ";
	cin >> reg.tipoDeRegistro;

	reg.fechaDeVencimiento = cargarFechas(" -------INGRESE FECHA DE VENCIMIENTO DEL REGISTRO--------", false);

	verificarCadena("INGRESE NRO DE TELEFONO:", reg.telefono, 15);
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
		cout << "ESTADOOO: " << reg.estado << endl;
		cout << endl;
	}

}

