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

void menuViajes();
void nuevoViaje();
void bajaViaje();
void listarUnViaje();
void listarViajes();



int cantidadDeViajes(Viaje);
bool crearViaje(Viaje);
bool crearViaje(Viaje, int);
Viaje cargarViaje();
Viaje leerViaje(int);
int siExisteID(int);
int pedirID();
void mostrarViaje(Viaje);


#endif // VIAJE_H_INCLUDED
