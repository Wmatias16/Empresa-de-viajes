#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "chofer.h"
using namespace std;

void menuChoferes(){
    int opt;
    do{
        system("cls");
        cout << "MENU CHOFERES" <<endl;
        cout << "----------------------"<<endl<<endl;
        cout << "1) NUEVO CHOFER"<<endl;
        cout << "2) MODIFICAR CHOFER"<<endl;
        cout << "3) LISTAR CHOFER POR DNI"<<endl;
        cout << "4) LISTAR TODOS LOS CHOFERES"<<endl;
        cout << "5) ELIMINAR CHOFER"<<endl;
        cout << "----------------------"<<endl<<endl;
        cout << "0) VOLVER AL MENU PRINCIPAL"<<endl;

        cout << "OPCION: ";
        cin >> opt;

        switch(opt){
            case 1:
                altaChofer();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }while(opt != 0);
}
/// ABML
void altaChofer(){
    Chofer reg;
    reg = agregarChofer();

    if(crearChofer(reg)){
        cout << " GUARDADO CORRECTAMENTE!!"<<endl;
        system("pause");
    }
}

bool crearChofer(Chofer reg){
    FILE *fchofer;
    bool guardo;
    fchofer = fopen("choferes.dat","ab");

    if(fchofer == NULL){
        cout << "ERROR AL GUARDAR REGISTRO" <<endl;
        system("pause");
        return false;
    }
    guardo = fwrite(&reg,sizeof(Chofer),1,fchofer);

    if(guardo == false){
        cout << "NO SE PUDO GUARDAR EL REGISTRO!!"<<endl;
        return guardo;
    }

    fclose(fchofer);

    return guardo;
}




/// END ABML

Chofer agregarChofer(){
    Chofer reg;
    system("pause");
    cout << "------- AGREGAR CHOFER ------- " << endl;
    cout << " INGRESE NRO DE D.N.I:  ";
    cin >> reg.dni;
    cout << " INGRESE APELLIDO: ";
    cin >> reg.apellido;
    cout << " INGRESE NOMBRE: ";
    cin >> reg.nombre;
    cout << "-------INGRESE FECHA DE INGRESO-------- " << endl;
    cout << "DIA: ";
    cin >> reg.fechaIngreso.dia;
    cout << "MES: ";
    cin >> reg.fechaIngreso.mes;
    cout << "ANIO: ";
    cin >> reg.fechaIngreso.anio;
    cout << "INGRESE C.U.I.T: ";
    cin >> reg.cuit;
    cout << " TIPO DE REGISTRO: ";
    cin >> reg.tipoDeRegistro;
    cout << " -------INGRESE FECHA DE VENCIMIENTO DEL REGISTRO--------  " <<endl;
    cout << "DIA: ";
    cin >> reg.fechaDeVencimiento.dia;
    cout << "MES: ";
    cin >> reg.fechaDeVencimiento.mes;
    cout << "ANIO: ";
    cin >> reg.fechaDeVencimiento.anio;
    cout << "INGRESE NRO DE TELEFONO: ";
    cin >> reg.telefono;

    return reg;
}
void mostrarChofer(Chofer reg){
    cout << " NRO DE D.N.I:  " << reg.dni << endl;
    cout << " APELLIDO: "<< reg.apellido << endl;
    cout << " NOMBRE: "<< reg.nombre << endl;
    cout << "------- FECHA DE INGRESO-------- " << endl;
    cout << reg.fechaIngreso.dia << " / " << reg.fechaIngreso.mes << " / " << reg.fechaIngreso.anio <<endl;
    cout << " C.U.I.T: " << reg.cuit <<endl;
    cout << " TIPO DE REGISTRO: " << reg.tipoDeRegistro << endl;
    cout << " ------- FECHA DE VENCIMIENTO DEL REGISTRO--------  " << endl;
    cout << reg.fechaDeVencimiento.dia << " / " << reg.fechaDeVencimiento.mes << " / " << reg.fechaDeVencimiento.anio <<endl;
    cout << "INGRESE NRO DE TELEFONO: ";
    cin >> reg.telefono;
}



