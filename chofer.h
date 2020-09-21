#include  "utilidades.h"

struct Chofer {
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
void altaChofer();
void modificacionChofer();
void bajaChofer();
void listarUnchofer();
void listarChoferes();
Fecha cargarFecha();
void menuChoferes();
Chofer agregarChofer();
Chofer leerChofer(int);
int pedirDni();
void mostrarChofer(struct Chofer);
bool crearChofer(struct Chofer);
bool crearChofer(struct Chofer, int);
int cantidadDeChoferes(Chofer);
int siExiste(char*);
int siExiste(char*, char*);
void verificarCadena(const char* , char*, int);
