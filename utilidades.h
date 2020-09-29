#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

struct Fecha{
	int dia;
	int mes;
	int anio;
};

void verificarCadena(const char*, char*, int);
struct Fecha cargarFecha();
void cargarCadena(char*, int);
bool verificarFecha(struct Fecha);
void cargarFechas(const char*, Fecha *,bool);
void cargarEnteros(const char*,int*, int, int );
void cargarFlotantes(const char* msj, float*, int);

int pedirDni();



#endif // UTILIDADES_H_INCLUDED
