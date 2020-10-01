#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED
void backup();
void backupChofer();
void backupViaje();

void restaurar();
void restaurarChofer();
void restaurarViaje();

int cantidadDeViajesBkp();
int cantidadDeChoferesBkp();

bool leerChoferBKP(int, Chofer*);
bool leerViajeBKP(int, Viaje*);

void cargarDatosInicio();
void cargarDatosInicioViaje();
void cargarDatosInicioChofer();
void restuararDatosChofer();
void restuararDatosViaje();


#endif // BACKUP_H_INCLUDED
