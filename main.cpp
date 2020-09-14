#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

#include "utilidades.h"
#include "chofer.h"

int main()
{
    int opt;
    do{
        system("cls");
        cout << "MENU PRINCIPAL" <<endl;
        cout << "----------------------"<<endl<<endl;
        cout << "1) CHOFERES"<<endl;
        cout << "2) VIAJES"<<endl;
        cout << "3) REPORTES"<<endl;
        cout << "4) CONFIGURACION"<<endl;
        cout << "----------------------"<<endl<<endl;
        cout << "0) SALIR DEL PROGRAMA"<<endl;

        cout << "OPCION: ";
        cin >> opt;

        switch(opt){
            case 1:
                menuChoferes();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }while(opt != 0);

    return 0;
}
