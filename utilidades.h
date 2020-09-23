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
struct Fecha cargarFechas(const char*, bool);
int cargarEnteros(const char*);
int pedirDni();
int siExiste(char*);
int siExiste(char*, char*);



#endif // UTILIDADES_H_INCLUDED
