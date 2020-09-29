
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
void nuevoChofer();
void modificarFechaChofer();
void eliminarChofer();
void listarUnchofer();
void listarChoferes();

Chofer agregarChofer();
bool modificarChofer(Chofer, int);
bool leerChofer(int,Chofer *);
void mostrarChofer(Chofer);
bool crearChofer(Chofer);
int cantidadDeChoferes();
int siExiste(char*);
int siExiste(char*, char*);
int pedirDni();
