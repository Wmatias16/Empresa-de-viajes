#include <iostream>
#include <cstdlib>

#include "chofer.h"
using namespace std;

void menuChoferes(){
    int opt;
    while(true){
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
                agregarChofer();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 0:
                break;
        }
    }
}

Chofer agregarChofer(){
    struct Chofer reg;
    cout << "------- AGREGAR CHOFER ------- " << endl;
    cout << " INGRESE NRO DE D.N.I:  ";
    cin >> reg.dni;

    return reg;
}

