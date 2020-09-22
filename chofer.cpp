#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Chofer.h"
using namespace std;


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

bool verificarFecha(Fecha reg) {
	int anio, mes, dia, diasFechaSistema, diasFechaIngresado,diferencia;
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
Fecha cargarFechas(const char *titulo, bool opc) {
	Fecha reg;

	bool state = !(opc);
	do {
		system("cls");

		cout << titulo << endl;
		reg = cargarFecha();

		if (opc) {
			if (verificarFecha(reg)!=true) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
				cout << "ERROR AL INGRESAR DATOS DE LA FECHA" << endl<<endl;
				cout << "DEBE INGRESAR UNA FECHA MENOR A LA FECHA ACTUAL!!" << endl;
				system("pause");
			}
			else {
				state = true;
			}
		}
		else {
			if (verificarFecha(reg)!=false) {//SI ES TRUE DIO MENOR SI ES FALSE ES MAYOR
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
		reg.fechaDeVencimiento = cargarFechas("INGRESE NUEVA FECHA DE VENCIMIENTO",false);

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


Fecha cargarFecha() {
	Fecha fecha;

	cout << "INGRESE EL DIA: ";
	cin >> fecha.dia;
	cout << "INGRESE EL MES: ";
	cin >> fecha.mes;
	cout << "INGRESE EL DIA: ";
	cin >> fecha.anio;

	return fecha;
}

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

int pedirDni() {
	char dni[10];
	system("cls");
	cout << "INGRESE EL D.N.I DEL CHOFER: ";
	cin >> dni;
	return siExiste(dni);
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




int cantidadDeChoferes(Chofer reg) {
	FILE* fchofer;

	fchofer = fopen("choferes.dat", "rb");

	if (fchofer == NULL) {
		return 0;
	}
	fseek(fchofer, 0, SEEK_END);

	int cantReg = ftell(fchofer) / sizeof(Chofer);

	fclose(fchofer);
	return cantReg;
}

void verificarCadena(const char* reg, char* v, int tam) {

	bool state = false;


	while (state == false) {
		cout << "------- AGREGAR CHOFER ------- " << endl << endl;
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

