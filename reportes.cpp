#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilidades.h"
#include "chofer.h"
#include "viaje.h"
#include "reportes.h"

using namespace std;

void mostrarDias(float *dias,int tam){
    cout << "DIAS \t TOTALT KM"<<endl;
    cout << "--------------------"<<endl;
    for(int i=0;i<tam;i++){
        cout <<i+1<<"\t"<<dias[i]<<endl;
    }
    system("pause");
}

void puntoA(){
    char dni[] = {"11113333"};

    Viaje reg;
    float dias[30] = {0};

    int cantViajes = cantidadDeViajes();

    for(int i=0;i<cantViajes;i++){
        leerViaje(i,&reg);
        if(strcmp(dni,reg.dniChofer)==0 && reg.fechaDeViaje.anio == 2020 && reg.fechaDeViaje.mes == 9){
            dias[reg.fechaDeViaje.dia - 1] += reg.kilometraje;
        }
    }

    mostrarDias(dias,30);
}

void puntoB(){
    system("cls");
    char dni[10], patente[10];
    cout << "INGRESE DNI: ";
    cin.ignore();
    cin.getline(dni,10);
    cout << "INGRESE NRO DE PATENTE: ";
    cin.ignore();
    cin.getline(patente,10);

    Viaje reg;

    int cantViajes = cantidadDeViajes();
    float totalKM = 0;

    for(int i=0;i<cantViajes;i++){
        leerViaje(i,&reg);
        if(strcmp(dni,reg.dniChofer)==0 && reg.fechaDeViaje.anio == 2020 && strcmp(patente,reg.patente)==0 ){
            totalKM += reg.kilometraje;
        }
    }
    system("cls");
    cout <<"CANTIDAD DE KM ENTRE TODOS LOS VIAJES ES: "<<totalKM<<endl;
    system("pause");
}

bool crearPuntoC(ChoferPuntoC reg){

    bool escribio = false;
    FILE *pchofer = fopen("choferPuntoC","ab");
    if(pchofer == NULL) return escribio;

    escribio = fwrite(&reg,sizeof(ChoferPuntoC),1,pchofer);

    return escribio;
}

float totalKMPuntoC(char *dni){
    Viaje reg;
    float totalKM = 0;
    int cantViajes = cantidadDeViajes();
    for(int i=0;i<cantViajes;i++){
        leerViaje(i,&reg);
        if(strcmp(dni,reg.dniChofer)==0 && reg.fechaDeViaje.anio == 2020){
            totalKM += reg.kilometraje;
        }
    }
    return totalKM;
}

void mostrarPuntoC(ChoferPuntoC reg){
    cout << "DNI: "<<reg.dni<<endl;
    cout << "NOMBRE: "<<reg.nombre<<endl;
    cout << "APELLIDO: "<<reg.apellido<<endl;
    cout << "CANTIDAD KM: "<<reg.cantTotalKm<<endl;
    cout << "--------------------------"<<endl;
}

void puntoC(){
    system("cls");
    Chofer reg;
    ChoferPuntoC regPuntoC;
    int cantChofer = cantidadDeChoferes();

    for(int i=0;i<cantChofer;i++){
        leerChofer(i,&reg);
        if(reg.tipoDeRegistro != 1){
            strcpy(regPuntoC.dni,reg.dni);
            strcpy(regPuntoC.nombre,reg.nombre);
            strcpy(regPuntoC.apellido,reg.apellido);
            regPuntoC.cantTotalKm = totalKMPuntoC(reg.dni);

            if(crearPuntoC(regPuntoC)){
                mostrarPuntoC(regPuntoC);
            }
        }
    }
    system("pause");
}



