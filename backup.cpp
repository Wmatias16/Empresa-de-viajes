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
	backupChofer();
	backupViaje();
	system("pause");
}
void restaurar() {
	restaurarChofer();
	restaurarViaje();
	system("pause");
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
	cout << "RESTUARADO CORRECTAMENTE"<<endl;

	fclose(pchofer);
}
void restaurarViaje() {
	Viaje reg;
	FILE* pviaje = fopen("viajes.dat", "wb");
	int cantViajes = cantidadDeViajesBkp();

	if (pviaje == NULL) return;

	for (int i = 0; i < cantViajes; i++) {
		leerViaje(i, &reg);
		fwrite(&reg, sizeof(Viaje), 1, pviaje);
	}

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
