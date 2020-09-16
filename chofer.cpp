#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

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
            case 3:listarUnchofer();
                break;
            case 4:listarChoferes();
                break;
            case 5:bajaChofer();
                break;
        }
    }while(opt != 0);
}

/// ABML
void altaChofer(){
    system("cls");
    Chofer reg;
    reg = agregarChofer();

    int pos = siExiste(reg.dni);


    if(crearChofer(reg,pos)){
        cout << " GUARDADO CORRECTAMENTE!!"<<endl;
        system("pause");
    }
}

void bajaChofer(){
    FILE *fchofer;
    char dni[10];
    Chofer reg;

    cout << "INGRESE EL D.N.I DEL CHOFER QUE DESEA DAR DE BAJA: ";
    cin >> dni;

    fchofer = fopen("choferes.dat","rb+");
    if(fchofer == NULL){
        cout << "ERROR AL ABRIR ARCHIVO"<<endl;
        system("pause");
        return;
    }
    int pos = siExiste(dni);

    reg = leerChofer(pos);
    if(pos != -1){
        reg.estado = false;
        crearChofer(reg,pos);
    }else{
        cout << "NO EXISTE EL D.N.I INGRESADO" <<endl;
        system("pause");
        return;
    }
}

void listarUnchofer(){
    system("cls");
    FILE *fchofer;
    Chofer reg;
    char dni[10];
    cout << "INGRESE EL D.N.I DEL CHOFER QUE DESEA DAR DE BAJA: ";
    cin >> dni;

    fchofer = fopen("choferes.dat","rb");

    if(fchofer == NULL){
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
        system("pause");
        return;
    }
    int pos  = siExiste(dni);
    if(pos == -1){
        cout << "NO EXISTE EL D.N.I INGRESADO" <<endl;
        system("pause");
       return;
    }

    fseek(fchofer, pos * sizeof(Chofer),0);
    fread(&reg,sizeof(reg),1,fchofer);
    mostrarChofer(reg);

    system("pause");
    fclose(fchofer);

}

void listarChoferes(){
    system("cls");
    FILE *fchofer;
    Chofer reg;

    fchofer = fopen("choferes.dat","rb");

    if(fchofer == NULL){
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
        system("pause");
        return;
    }

    while(fread(&reg,sizeof(reg),1,fchofer)==1){
        mostrarChofer(reg);
    }
    system("pause");
    fclose(fchofer);
}

Chofer leerChofer(int pos){
    FILE *fchofer;
    Chofer reg;
    fchofer = fopen("choferes.dat","rb");

    if(fchofer == NULL){
        cout << "ERROR AL GUARDAR REGISTRO" <<endl;
    }

    fseek(fchofer, pos * sizeof(Chofer),0);

    fread(&reg,sizeof(reg),1,fchofer);

    fclose(fchofer);
    return reg;
}

bool crearChofer(Chofer reg,int pos){
    FILE *fchofer;
    bool guardo;
    fchofer = fopen("choferes.dat","rb+");

    if(fchofer == NULL){
        cout << "ERROR AL GUARDAR REGISTRO" <<endl;
        system("pause");
        return false;
    }
    if(pos == -1){
        guardo = fwrite(&reg,sizeof(Chofer),1,fchofer);
        return true;
    }else{
        fseek(fchofer, pos * sizeof(Chofer),0);
        guardo = fwrite(&reg,sizeof(Chofer),1,fchofer);
        if(guardo){
            cout << "BIENNN"<<endl;
            system("pause");
        }
    }

    if(guardo == false){
        cout << "NO SE PUDO GUARDAR EL REGISTRO!!"<<endl;
        return guardo;
    }

    fclose(fchofer);

    return guardo;
}

int siExiste(char *v){
    FILE *fchofer;
    Chofer reg;
    int pos = 0;

    fchofer = fopen("choferes.dat","rb");

    if(fchofer == NULL){
        cout << "ERROR AL ABRIR EL ARCHIVO"<<endl;
        system("pause");
        return -1;
    }

    while(fread(&reg,sizeof(reg),1,fchofer)== 1){
        if(strcmp(reg.dni,v)==0){
            fclose(fchofer);
            return pos;
        }
        pos++;
    }

    fclose(fchofer);


    return -1;
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
    reg.estado = true;
    return reg;
}
void mostrarChofer(Chofer reg){
    if(reg.estado == true){
        cout <<" NRO DE D.N.I:  " << reg.dni << endl;
        cout <<" APELLIDO: "<< reg.apellido << endl;
        cout <<" NOMBRE: "<< reg.nombre << endl;
        cout <<"FECHA DE INGRESO-------- " << endl;
        cout <<reg.fechaIngreso.dia << " / " << reg.fechaIngreso.mes << " / " << reg.fechaIngreso.anio <<endl;
        cout <<" C.U.I.T: " << reg.cuit <<endl;
        cout <<" TIPO DE REGISTRO: " << reg.tipoDeRegistro << endl;
        cout <<"FECHA DE VENCIMIENTO DEL REGISTRO--------  " << endl;
        cout <<reg.fechaDeVencimiento.dia << " / " << reg.fechaDeVencimiento.mes << " / " << reg.fechaDeVencimiento.anio <<endl;
        cout <<"INGRESE NRO DE TELEFONO: "<< reg.telefono <<endl;
        cout <<"ESTADOOO: "<<reg.estado<<endl;

        cout <<endl;
    }
}



