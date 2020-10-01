#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

struct ChoferPuntoC{
    char dni[10],nombre[50],apellido[50];
    float cantTotalKm;
};

void puntoA();
void puntoB();
void puntoC();
Chofer leerChoferDni();
void mostrarPuntoC(ChoferPuntoC);
float totalKMPuntoC(char *);
bool crearPuntoC(ChoferPuntoC);
void mostrarDias(float *,int );


#endif // REPORTES_H_INCLUDED
