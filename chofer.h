#ifndef CHOFER_H_INCLUDED
#define CHOFER_H_INCLUDED

#include "utilidades.h"

struct Chofer{
    char dni[10];
    char apellido[50];
    char nombre[50];
    Fecha fechaIngreso;
    char cuit[20];
    int tipoDeRegistro;
    Fecha fechaDeVencimiento;
    char telefono[15];
    bool propietarioDelAuto;
    bool estado;
};

/// PROTOTYPE
void menuChoferes();
Chofer agregarChofer();
Chofer leerChofer(int);
void mostrarChofer(struct Chofer);
void listarChoferes();
void altaChofer();
void bajaChofer();
void listarUnchofer();
int siExiste(char *);
bool crearChofer(struct Chofer,int);
/// END PROTOTYPE


#endif // CHOFER_H_INCLUDED
