#ifndef VIAJE_H_INCLUDED
#define VIAJE_H_INCLUDED

struct Viaje {
	int idViaje;
	char dniChofer[10];
	int idCliente;
	Fecha fechaDeViaje;
	int horaDeSalida;
	float kilometraje;
	float importe;
	char patente[10];
	int calificacion;
	bool estado;
};
void nuevoViaje();
void bajaViaje();
void listarUnViaje();
void listarViajes();

int cantidadDeViajes();
bool crearViaje(Viaje);
bool modificarViaje(Viaje, int);
Viaje cargarViaje();
bool leerViaje(int,Viaje*);
int siExisteID(int);
int pedirID();
void mostrarViaje(Viaje);


#endif // VIAJE_H_INCLUDED
