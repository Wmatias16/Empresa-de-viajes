#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "utilidades.h"
#include "Chofer.h"
#include "viaje.h"
#include "backup.h"

using namespace std;

void backup() {
	system("cls");
	int opt;
	cout << "DESEA HACER UN BACKUP DE LOS ARCHIVOS?"<<endl;
	cout << "1.PARA CONFIRMAR \t 2.PARA CANCELAR"<<endl;
	cout << "---------------------------"<<endl;
	cout << "OPCION: ";
	cin >> opt;
    if(opt == 1){
        backupChofer();system("pause");
        backupViaje();system("pause");
	}
}
void restaurar() {
    system("cls");
	int opt;
	cout << "DESEA RESTAURAR BACKUP DE LOS ARCHIVOS?"<<endl;
	cout << "1.PARA CONFIRMAR \t 2.PARA CANCELAR"<<endl;
	cout << "---------------------------"<<endl;
	cout << "OPCION: ";
	cin >> opt;
	if(opt == 1){
        restaurarChofer();system("pause");
        restaurarViaje();system("pause");
	}
}

void backupChofer() {
	Chofer reg;
	FILE* pchoferBackup = fopen("choferes.bkp", "wb");
	int cantChoferes = cantidadDeChoferes();

	if (pchoferBackup == NULL) return;

	for (int i = 0; i < cantChoferes; i++) {
		leerChofer(i, &reg);
		fwrite(&reg, sizeof(Chofer), 1, pchoferBackup);
	}
	fclose(pchoferBackup);

	if (cantChoferes == cantidadDeChoferes()) cout << "ARCHIVO CHOFERES GUARDADO CORRECTAMENTE" << endl;
	else cout << "ERROR EN REALIZAR BACKUP DEL ARCHIVO CHOFERES" << endl;

}
void backupViaje() {
	Viaje reg;
	FILE* pviajeBackup = fopen("viajes.bkp", "wb");
	int cantViajes = cantidadDeViajes();

	if (pviajeBackup == NULL) return;

	for (int i = 0; i < cantViajes; i++) {
		leerViaje(i, &reg);
		fwrite(&reg, sizeof(Viaje), 1, pviajeBackup);
	}
	fclose(pviajeBackup);

	if (cantViajes == cantidadDeViajesBkp()) cout << "ARCHIVO VIAJES GUARDADO CORRECTAMENTE" << endl;
	else cout << "ERROR EN REALIZAR BACKUP DEL ARCHIVO VIAJES"<<endl;
}

void restaurarChofer() {
	Chofer reg;
	FILE* pchofer = fopen("choferes.dat", "wb");
	int cantChoferes = cantidadDeChoferesBkp();

	if (pchofer == NULL) return;

	for (int i = 0; i < cantChoferes; i++) {
		if (leerChoferBKP(i, &reg)){
			fwrite(&reg, sizeof(Chofer), 1, pchofer);
		}

	}
	cout << "CHOFER RESTUARADO CORRECTAMENTE"<<endl;

	fclose(pchofer);
}
void restaurarViaje() {
	Viaje reg;
	FILE* pviaje = fopen("viajes.dat", "wb");
	int cantViajes = cantidadDeViajesBkp();

	if (pviaje == NULL) return;

	for (int i = 0; i < cantViajes; i++) {
		leerViajeBKP(i, &reg);
		fwrite(&reg, sizeof(Viaje), 1, pviaje);
	}
    cout << "VIAJE RESTUARADO CORRECTAMENTE"<<endl;
	fclose(pviaje);
}

int cantidadDeViajesBkp() {
	FILE* fviaje = fopen("viajes.bkp", "rb");

	if (fviaje == NULL) {
		return 0;
	}

	fseek(fviaje, 0, SEEK_END);

	int cantReg = ftell(fviaje) / sizeof(Viaje);

	fclose(fviaje);
	return cantReg;
}
int cantidadDeChoferesBkp() {
	FILE* fchofer = fopen("choferes.bkp", "rb");

	if (fchofer == NULL) {
		return 0;
	}

	fseek(fchofer, 0, SEEK_END);

	int cantReg = ftell(fchofer) / sizeof(Viaje);

	fclose(fchofer);

	return cantReg;
}

bool leerViajeBKP(int pos, Viaje* reg) {
	bool leyo = false;
	FILE* fviaje = fopen("viajes.bkp", "rb");

	if (fviaje == NULL)return leyo;

	fseek(fviaje, pos * sizeof(Viaje), SEEK_SET);

	leyo = fread(reg, sizeof(Viaje), 1, fviaje);

	fclose(fviaje);
	return leyo;
}
bool leerChoferBKP(int pos, Chofer* reg) {
	FILE* fchoferbkp = fopen("choferes.bkp", "rb");
	bool leyo = false;
	if (fchoferbkp == NULL)return leyo;

	fseek(fchoferbkp, pos * sizeof(Chofer), SEEK_SET);

	leyo = fread(reg, sizeof(Chofer), 1, fchoferbkp);

	fclose(fchoferbkp);
	return leyo;
}


void cargarDatosInicio() {
	int opt;
	do {
		system("cls");

		cout << "---MENU CARGAR DATOS INICIO---" << endl;
		cout << "1.CARGAR DATOS CHOFER" << endl;
		cout << "2.CARGAR DATOS VIAJES" << endl;
		cout << "3.RECUPERAR DATOS" << endl;
		cout << "0.SALIR" << endl;
		cout << "-----------------------" << endl;
		cout << "OPCION: ";
		cin >> opt;

		switch (opt){
		case 1:cargarDatosInicioChofer();
			break;
		case 2:cargarDatosInicioViaje();
			break;
		case 3:
		    system("cls");
            int aux;
            cout << "DESEA CARGAR LOS DATOS DE INICIO?"<<endl;
            cout << "1.PARA CONFIRMAR \t 2.PARA CANCELAR"<<endl;
            cout << "---------------------------"<<endl;
            cout << "OPCION: ";
            cin >> aux;
		    if(aux == 1){
                restuararDatosViaje();
                restuararDatosChofer();
		    }
		default:
			break;
		}
	} while (opt != 0);
}

void cargarDatosInicioViaje() {
    system("cls");
	FILE* pviaje = fopen("viajes.ini", "a");
	if (pviaje == NULL) return;
    Viaje reg;
	reg = cargarViaje();

	if (fwrite(&reg, sizeof(reg), 1, pviaje)) {
		cout << "REGISTRO GUARDADO!!" << endl;
		system("pause");
	}

	fclose(pviaje);
}

void restuararDatosViaje() {
	Viaje reg;
	FILE* pviajeIni = fopen("viajes.ini", "rb");
	FILE* pviaje = fopen("viajes.dat", "wb");
	if (pviajeIni == NULL || pviaje == NULL) return;

	while (fread(&reg, sizeof(Viaje), 1, pviajeIni) == 1) {
		fwrite(&reg, sizeof(Viaje), 1, pviaje);
	}
	fclose(pviajeIni);
    fclose(pviaje);

	cout << "REGISTROS GUARDADOS!" << endl;
	system("pause");


}
void cargarDatosInicioChofer() {
    system("cls");
	Chofer reg = agregarChofer();
	FILE* pchofer = fopen("choferes.ini", "a");
	if (pchofer == NULL) return;

	if (fwrite(&reg, sizeof(reg), 1, pchofer)) {
		cout << "REGISTRO GUARDADO!!"<<endl;
		system("pause");
	}

	fclose(pchofer);
}

void restuararDatosChofer() {
	Chofer reg;
	FILE* pchoferIni = fopen("choferes.ini", "r");
	FILE* pchofer = fopen("choferes.dat", "wb");
	if (pchofer == NULL || pchoferIni == NULL) return;

	while (fread(&reg, sizeof(Chofer), 1, pchoferIni)) {
		fwrite(&reg, sizeof(Chofer), 1, pchofer);
	}
	cout << "REGISTROS GUARDADOS!"<<endl;
	system("pause");

	fclose(pchofer);
	fclose(pchoferIni);
}



