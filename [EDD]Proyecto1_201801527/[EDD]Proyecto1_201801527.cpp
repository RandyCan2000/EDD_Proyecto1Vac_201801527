#include <iostream> 
#include "Globales.h"
#include "NodoMatriz.h"
#include "NodoAVL.h"
#include "NodoTransaccion.h"


using namespace std;
/*
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15
*/
int A = 0;

void FormularioRegistro() {
	system("cls");
	char U[100], C[100], D[100], E[100];
	char* Usuario = U, * Contrasena = C, * Departamento = D, * Empresa = E;
	gotoxy(50, 5); SetColor(6);
	cout << "FORMULARIO DE REGISTRO";
	gotoxy(30, 7); SetColor(9);
	cout << "USUARIO: "; SetColor(11); cin.getline(Usuario, 100);
	gotoxy(30, 9); SetColor(9);
	cout << "CONTRASENA: "; SetColor(11); cin.getline(Contrasena, 100);
	gotoxy(30, 11); SetColor(9);
	cout << "DEPARTAMENTO: "; SetColor(11); cin.getline(Departamento, 100);
	gotoxy(30, 13); SetColor(9);
	cout << "EMPRESA: "; SetColor(11); cin.getline(Empresa, 100);
	if (ToUpperCase(U) != "" && ToUpperCase(C) != "" && ToUpperCase(D) != "" && ToUpperCase(E) != "") {
		NM Registrar = new NodoMatriz();
		bool Agregado=Registrar->AgregarNodo(U,C,ToUpperCase(D),ToUpperCase(E));
		if (Agregado==true) {
			gotoxy(30, 15); SetColor(2);
			cout << "USUARIO AGREGADO CON EXITO";
			getchar();
		}else{
			gotoxy(30, 15); SetColor(4);
			cout << "EL USUARIO YA EXISTE";
			getchar();
		}
	}
	else {
		gotoxy(30, 15); SetColor(4);
		cout << "DEBE LLENAR TODOS LOS CAMPOS";
		getchar();
	}
}

void ReporteActDep() {
	char D[100];
	char* Departamento = D;
	system("cls");
	gotoxy(30, 5); SetColor(6); cout << "INGRESE EL NOMBRE DEL DEPARTAMENTO: ";
	SetColor(11); cin.getline(Departamento, 100);
	NM Arbol = new NodoMatriz();
	bool a=Arbol->ReporteActivosDepartamento(ToUpperCase(D));
	if (a==true){
		gotoxy(30, 7); SetColor(2); cout << "SE CREO EL REPORTE CON EXITO";
	}
	else {
		gotoxy(30, 7); SetColor(4); cout << "NO SE CREO EL REPORTE CON EXITO";
	}
	getchar(); delete Arbol;
}

void RepActEmpresa() {
	char E[100];
	char* Empresa = E;
	system("cls");
	gotoxy(30, 5); SetColor(6); cout << "INGRESE EL NOMBRE DE LA EMPRESA: ";
	SetColor(11); cin.getline(Empresa, 100);
	NM Arbol = new NodoMatriz();
	bool a=Arbol->ReporteActivosEmpresa(ToUpperCase(E));
	if (a == true) {
		gotoxy(30, 7); SetColor(2); cout << "SE CREO EL REPORTE CON EXITO";
	}
	else {
		gotoxy(30, 7); SetColor(4); cout << "NO SE CREO EL REPORTE CON EXITO";
	}
	getchar();
	delete Arbol;
}

void RepActUser() {
	system("cls");
	char U[100], D[100], E[100];
	char* Usuario = U, * Departamento = D, * Empresa = E;
	gotoxy(50, 5); SetColor(6);
	cout << "DATOS DEL USUARIO";
	gotoxy(30, 7); SetColor(9);
	cout << "USUARIO: "; SetColor(11); cin.getline(Usuario, 100);
	gotoxy(30, 9); SetColor(9);
	cout << "DEPARTAMENTO: "; SetColor(11); cin.getline(Departamento, 100);
	gotoxy(30, 11); SetColor(9);
	cout << "EMPRESA: "; SetColor(11); cin.getline(Empresa, 100);
	if (ToUpperCase(U) != ""  && ToUpperCase(D) != "" && ToUpperCase(E) != "") {
		NM Buscar = new NodoMatriz();
		NM USER = Buscar->BuscarUsuario(U,ToUpperCase(D), ToUpperCase(E));
		if (USER != NULL) {
			NAVL AVL = new NodoAVL();
			if (USER->Activos!=NULL) {
				AVL->ImagenArbol(*USER->Activos);
				gotoxy(30, 13); SetColor(2);
				cout << "SE CREO EL REPORTE CON EXITO";
				getchar();
			}
			else {
				gotoxy(30, 13); SetColor(4);
				cout << "EL USUARIO NO TIENE ACTIVOS";
				getchar();
			}
			delete AVL;
		}
		else {
			gotoxy(30, 13); SetColor(4);
			cout << "EL USUARIO NO EXISTE";
			getchar();
		}
		delete Buscar;
	}
	else {
		gotoxy(30, 13); SetColor(4);
		cout << "DEBE LLENAR TODOS LOS CAMPOS";
		getchar();
	}
}

void MenuRepRentaUnUsuario() {
	system("cls");
	char U[100], D[100], E[100];
	char* Usuario = U, * Departamento = D, * Empresa = E;
	gotoxy(50, 5); SetColor(6);
	cout << "DATOS DEL USUARIO";
	gotoxy(30, 7); SetColor(9);
	cout << "USUARIO: "; SetColor(11); cin.getline(Usuario, 100);
	gotoxy(30, 9); SetColor(9);
	cout << "DEPARTAMENTO: "; SetColor(11); cin.getline(Departamento, 100);
	gotoxy(30, 11); SetColor(9);
	cout << "EMPRESA: "; SetColor(11); cin.getline(Empresa, 100);
	if (ToUpperCase(U) != "" && ToUpperCase(D) != "" && ToUpperCase(E) != "") {
		NM Buscar = new NodoMatriz();
		NM USER = Buscar->BuscarUsuario(U, ToUpperCase(D), ToUpperCase(E));
		if (USER != NULL) {
			gotoxy(30, 13); SetColor(2);
			NT Rep = new NodoTransaccion();
			Rep->ReporteTransaccionesUnUsuario(*USER);
			cout << "SE CREO EL REPORTE CON EXITO";
			getchar();
		}
		else {
			gotoxy(30, 13); SetColor(4);
			cout << "EL USUARIO NO EXISTE";
			getchar();
		}
		delete Buscar;
	}
	else {
		gotoxy(30, 13); SetColor(4);
		cout << "DEBE LLENAR TODOS LOS CAMPOS";
		getchar();
	}
}
void MenuAdmin() {
	do{
		system("cls");
		char O[100];
		char* Opcion = O;
		gotoxy(50, 5); SetColor(6);
		cout << "MENU ADMINISTRADOR";
		gotoxy(30, 7); SetColor(9);
		cout << "1. REGISTRAR USUARIO";
		gotoxy(30, 9);
		cout << "2. REPORTE MATRIZ DISPERSA";
		gotoxy(30, 11);
		cout << "3. REPORTE ACTIVOS DISPONIBLES DE UN DEPARTAMENTO";
		gotoxy(30, 13);
		cout << "4. REPORTE ACTIVOS DISPONIBLES DE UNA EMPRESA";
		gotoxy(30, 15);
		cout << "5. REPORTE TRANSACCIONES";
		gotoxy(30, 17);
		cout << "6. REPORTE ACTIVOS DE UN USUARIO";
		gotoxy(30, 19);
		cout << "7. REPORTE ACTIVOS RENTADOS DE UN USUARIO";
		gotoxy(30, 21);
		cout << "8. ORDENAR TRANSACCIONES";
		gotoxy(30, 23);
		cout << "9. CERRAR SESION";
		gotoxy(30, 25); SetColor(6);
		cout << "SELECCIONE UNA OPCION: ";
		SetColor(11);
		cin.getline(Opcion, 100);
		gotoxy(30, 27);
		if (EsUnNumero(Opcion) == true) {
			string val = Opcion;
			if (val == "1") { FormularioRegistro();}
			else if (val == "2") { NM MAT = new NodoMatriz(); MAT->RepMatriz(); delete MAT; }
			else if (val == "3") { ReporteActDep(); }
			else if (val == "4") { RepActEmpresa(); }
			else if (val == "5") { NT REP = new NodoTransaccion(); REP->ReporteTransacciones(); SetColor(2); cout << "REPORTE CREADO CON EXITO"; getchar(); delete REP; }
			else if (val == "6") { RepActUser(); }
			else if (val == "7") { MenuRepRentaUnUsuario(); }
			else if (val == "8") {
				char N[100];
				char* Numero = N;
				system("cls");
				gotoxy(50, 5); SetColor(6);
				cout << "ORDENAR LISTA DE TRANSACCIONES";
				gotoxy(30, 7); SetColor(9);
				cout << "1. ORDEN ASCENDETE";
				gotoxy(30, 9); 
				cout << "2. ORDEN DESCENDETE";
				gotoxy(30, 11); SetColor(6);
				cout << "SELECCION EL TIPO DE ORDEN: ";
				SetColor(11); cin.getline(Numero,100);
				if (EsUnNumero(N)==true) {
					gotoxy(30, 13); SetColor(2);
					string val1 = Numero;
					NT Ordenamiento = new NodoTransaccion();
					if (val1=="1") { 
						Ordenamiento->BubbleSort(true);
						cout << "ORDENADO DE FORMA ASCENDENTE"; 
						getchar();
					}
					else if (val1 == "2") { 
						Ordenamiento->BubbleSort(false);
						cout << "ORDENADO DE FORMA DESCENDENTE"; 
						getchar();
					}
					else {
						SetColor(4); cout << "OPCION NO ENCONTRADA"; getchar();
					}
					NT REP = new NodoTransaccion(); 
					REP->ReporteTransacciones(); 
					SetColor(2); gotoxy(30, 15);
					cout << "REPORTE CREADO CON EXITO"; 
					getchar(); 
					delete REP;
					delete Ordenamiento;
				}
				else {
					gotoxy(30, 13); SetColor(4);
					cout << "INGRESE UNICAMENTE NUMEROS";
					getchar();
				}
			}
			else if (val == "9") { break; }
			else {
				SetColor(4);
				cout << "OPCION NO ENCONTRADA";
				getchar();
			}
		}
		else {
			SetColor(4);
			cout << "INGRESE SOLO NUMEROS";
			getchar();
		}
	} while (true);
}

void FormularioAgregarActivo() {
	system("cls");
	char N[100],D[100];
	char* Nombre=N,*Descripcion=D;
	gotoxy(50,5); SetColor(6);
	cout << "FORMULARIO PARA AGREGAR ACTIVO";
	gotoxy(30, 7); SetColor(9);
	cout << "NOMBRE DEL ACTIVO: "; SetColor(11); cin.getline(Nombre,100);
	gotoxy(30, 9); SetColor(9);
	cout << "DESCRIPCION DEL ACTIVO: "; SetColor(11); cin.getline(Descripcion, 100);
	if (ToUpperCase(N) != "" && ToUpperCase(D) != "") {
		NAVL AVL = new NodoAVL(); 
		bool Agregado=AVL->NuevoNodoAVL(ToUpperCase(Nombre), ToUpperCase(Descripcion));
		AVL->CalcularAlturas(*UserLog->Activos);
		if (Agregado == true) {
			gotoxy(30, 15); SetColor(2);
			cout << "ACTIVO AGREGADO CON EXITO";
			getchar();
		}
		else {
			gotoxy(30, 15); SetColor(4);
			cout << "EL ACTIVO YA EXISTE";
			getchar();
		}
	}
	else {
		gotoxy(30, 15); SetColor(4);
		cout << "DEBE LLENAR TODOS LOS CAMPOS";
		getchar();
	}
}

void FormularioEliminarActivo () {
	char A[100];
	char* Activo=A;
	system("cls");
	gotoxy(50, 5); SetColor(6);
	cout << "LISTADO DE ACTIVOS";
	gotoxy(30, 7); SetColor(9);
	NAVL ELIMINAR = new NodoAVL(); string listado = ELIMINAR->ListaActivo(*UserLog->Activos,true);
	std::string s = listado;
	std::string delimiter = "\n";
	size_t pos = 0;
	std::string token;
	int ypos = 9;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		gotoxy(30, ypos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
		ypos += 2;
	}
	gotoxy(30, ypos); SetColor(6);
	cout << "INGRESE EL NOMBRE DEL ACTIVO A ELIMINAR: ";
	SetColor(11);cin.getline(Activo,100);
	//Metodo que elimina Nodo
	bool ACTELIM=ELIMINAR->EliminarActivo(*UserLog->Activos, ToUpperCase(A), ypos);
	if (ACTELIM == true) {
		gotoxy(30, ypos + 10); SetColor(2);
		cout << "SE ELIMINO EL ACTIVO CORRECTAMENTE";
	}
	else {
		gotoxy(30, ypos + 10); SetColor(4);
		cout << "NO SE ELIMINO EL ACTIVO CORRECTAMENTE";
		gotoxy(30, ypos + 12);
		cout << "NOTA: SI EL ACTIVO SE ENCUENTRA RENTADO NO SE PUEDE ELIMINAR";
	}
	getchar();
	delete ELIMINAR;
}

void FormularioEditarActivo() {
	char N[100],D[100];
	char* Nombre = N,*Descripcion=D;
	system("cls");
	gotoxy(50, 5); SetColor(6);
	cout << "LISTADO DE ACTIVOS";
	gotoxy(30, 7); SetColor(9);
	NAVL EDITAR = new NodoAVL(); string listado = EDITAR->ListaActivo(*UserLog->Activos,true);
	std::string s = listado;
	std::string delimiter = "\n";
	size_t pos = 0;
	std::string token;
	int ypos = 9;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		gotoxy(30, ypos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
		ypos += 2;
	}
	gotoxy(30, ypos); SetColor(6);
	cout << "INGRESE EL NOMBRE DEL ACTIVO A MODIFICAR: ";
	SetColor(11); cin.getline(Nombre, 100);
	gotoxy(30, ypos+2); SetColor(6);
	cout << "INGRESE LA NUEVA DESCRIPCION: ";
	SetColor(11); cin.getline(Descripcion, 100);
	bool Editado = EDITAR->EditarActivo(*UserLog->Activos, ToUpperCase(D), ToUpperCase(N));
	if (UserLog->Activos!=NULL) {
		if (Editado == true) {
			gotoxy(30, ypos + 4); SetColor(2);
			cout << "SE EDITO EL ACTIVO CORRECTAMENTE";
		}
		else {
			gotoxy(30, ypos + 4); SetColor(4);
			cout << "NO SE EDITO EL ACTIVO CORRECTAMENTE";
		}
	}
	else {
		gotoxy(30, ypos + 4); SetColor(4);
		cout << "NO EXISTEN ACTIVOS";
	}
	getchar();
	delete EDITAR;
}

void PedirDatosActivoARentar(int PosY) {
	char U[100], D[100], E[100], N[100],DR[100];
	char* Usuario = U, * Departamento = D, * Empresa = E, * NombreActivo = N,*DiasRenta=DR;
	gotoxy(30, PosY); SetColor(6); cout << "USUARIO: "; SetColor(11); cin.getline(Usuario, 100); PosY = PosY + 2;
	gotoxy(30, PosY); SetColor(6); cout << "DEPARTAMENTO: "; SetColor(11); cin.getline(Departamento, 100); PosY = PosY + 2;
	gotoxy(30, PosY); SetColor(6); cout << "EMPRESA: "; SetColor(11); cin.getline(Empresa, 100); PosY = PosY + 2;
	gotoxy(30, PosY); SetColor(6); cout << "NOMBRE DEL ACTIVO A RENTAR: "; SetColor(11); cin.getline(NombreActivo, 100); PosY = PosY + 2;
	gotoxy(30, PosY); SetColor(6); cout << "DIAS A RENTAR EL ACTIVO: "; SetColor(11); cin.getline(DiasRenta, 100); PosY = PosY + 2;
	if (ToUpperCase(U)!="" && ToUpperCase(D) != "" && ToUpperCase(E) != "" && ToUpperCase(N) != "" && ToUpperCase(DR) != "") {
		if (EsUnNumero(DR)==true) {
			//aqui agrega el activo a la lista doble circular
			NM Buscar = new NodoMatriz();
			NM UserRenta = Buscar->BuscarUsuario(U, ToUpperCase(D), ToUpperCase(E));
			if (UserRenta != NULL) {
				NAVL BuscarActivo = new NodoAVL();
				NAVL Activo = BuscarActivo->BuscarActivo(*UserRenta->Activos, ToUpperCase(N));
				if (Activo != NULL) {
					NT AGG = new NodoTransaccion();
					Activo->Rentado = true;
					bool agregado=AGG->AgregarRenta(*UserRenta, *Activo,atoi(DR));
					if (agregado==true) {
						gotoxy(30, PosY); SetColor(2); cout << "RENTA REALIZADA CON EXITO"; getchar();
					}
					else {
						gotoxy(30, PosY); SetColor(4); cout << "LA RENTA NO SE REALIZO CON EXITO"; getchar();
					}
				}
				else {
					gotoxy(30, PosY); SetColor(4); cout << "ACTIVO NO ENCONTRADO"; getchar();
				}
				delete BuscarActivo;
			}
			else {
				gotoxy(30, PosY); SetColor(4); cout << "USUARIO NO ENCONTRADO"; getchar();
			}
			delete Buscar;
		}
		else {
			gotoxy(30, PosY); SetColor(4); cout << "LOS DIAS DEBEN SER NUMEROS"; getchar();
		}
	}
	else {
		gotoxy(30, PosY); SetColor(4);
		cout << "HACEN FALTA PARAMETROS";
		getchar();
	}
}

void MenuQuitarRentaActivo() {
	char I[100];
	char* ID = I;
	system("cls");
	gotoxy(50, 5); SetColor(6);
	cout << "DEVOLVER ACTIVO";
	gotoxy(30, 7); SetColor(9);
	NT Nuevo = new NodoTransaccion();
	string listado=Nuevo->ListadoActivosRentados();
	std::string s = listado;
	std::string delimiter = "\n";
	size_t pos = 0;
	std::string token;
	int ypos = 9;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		gotoxy(15, ypos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
		ypos += 2;
	}
	gotoxy(30, ypos); SetColor(6); ypos += 2;
	cout << "INGRESE EL ID DE LA RENTA A DEVOLVER: "; SetColor(11);
	cin.getline(ID,100);
	if (ToUpperCase(I)!="") {
		NT Eliminar = new NodoTransaccion();
		bool Eliminado = Eliminar->QuitarRenta(ToUpperCase(I));
		if (Eliminado == true) {
			gotoxy(30, ypos); SetColor(2);
			cout << "SE ELIMINO LA RENTA CORRECTAMENTE"; SetColor(11); getchar();
		}
		else {
			gotoxy(30, ypos); SetColor(4);
			cout << "NO SE ELIMINO LA RENTA CORRECTAMENTE"; SetColor(11); getchar();
		}
		delete Eliminar;
	}
	else {
		gotoxy(30, ypos); SetColor(4);
		cout << "NO INGRESO NINGUN ID"; getchar();
	}
}

void MenuRentaActivos() {
	system("cls");
	gotoxy(50, 5); SetColor(6);
	cout << "RENTA DE ACTIVOS";
	NM ListadoActivos = new NodoMatriz();
	char O[100]; char* Opcion = O;
	gotoxy(30, 7); SetColor(9);
	cout << "1. RENTAR ACTIVO";
	gotoxy(30, 9);
	cout << "2. DEVOLVER ACTIVO RENTADO";
	gotoxy(30, 11); SetColor(6);
	cout << "SELECCIONE UNA OPCION: ";
	SetColor(11); cin.getline(Opcion, 100);
	if (EsUnNumero(Opcion) == true) {
		string val = Opcion;
		if (val == "1") {
			system("cls");
			gotoxy(50, 5); SetColor(6);
			cout << "LISTA DE ACTIVOS RENTADOS";
			std::string listado = ListadoActivos->ListarTodosLosActivos();
			std::string s = listado;
			std::string delimiter = "\n";
			size_t pos = 0;
			std::string token;
			int ypos = 7;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				if (token[0]=='-') { SetColor(2);}
				else { SetColor(9); }
				gotoxy(30, ypos);
				std::cout << token << std::endl;
				s.erase(0, pos + delimiter.length());
				ypos += 2;
			}
			PedirDatosActivoARentar(ypos);
		}
		else if (val == "2") { MenuQuitarRentaActivo(); }
		else {
			SetColor(4);
			cout << "OPCION NO ENCONTRADA";
			getchar();
		}
	}
	else {
		SetColor(4);
		cout << "INGRESE SOLO NUMEROS";
		getchar();
	}
}

void MenuUser() {
	while (true){
		system("cls");
		char O[100];
		char* Opcion = O;
		gotoxy(50, 5); SetColor(6);
		cout << "MENU USUARIO";
		gotoxy(30, 7); SetColor(9);
		cout << "1. AGREGAR ACTIVO";
		gotoxy(30, 9);
		cout << "2. ELIMINAR ACTIVO";
		gotoxy(30, 11);
		cout << "3. MODIFICAR ACTIVO";
		gotoxy(30, 13);
		cout << "4. RENTAR ACTIVO";
		gotoxy(30, 15);
		cout << "5. MIS ACTIVOS";
		gotoxy(30, 17);
		cout << "6. CERRAR SESION";
		gotoxy(30, 19);
		SetColor(6);
		cout << "SELECCIONE UNA OPCION: ";
		SetColor(11); cin.getline(Opcion, 100);
		gotoxy(30, 21);
		if (EsUnNumero(Opcion) == true) {
			string val = Opcion;
			if (val == "1") { FormularioAgregarActivo(); }
			else if (val == "2") { FormularioEliminarActivo(); }
			else if (val == "3") { FormularioEditarActivo(); }
			else if (val == "4") { MenuRentaActivos(); }
			else if (val == "5") {
				if (UserLog->Activos!=NULL) {
					NAVL AVL = new NodoAVL();
					AVL->ImagenArbol(*UserLog->Activos);
					SetColor(2);
					cout << "SE CREO EL REPORTE CON EXITO";
					getchar();
				}
				else {
					SetColor(4);
					cout << "SIN ACTIVOS";
					getchar();
				}
			}
			else if (val == "6") { break; }
			else {
				SetColor(4);
				cout << "OPCION NO ENCONTRADA";
				getchar();
			}
		}
		else {
			SetColor(4);
			cout << "INGRESE SOLO NUMEROS";
			getchar();
		}
	}
}

void Login() {
	system("cls");
	char U[100],C[100],D[100],E[100];
	char* Usuario=U,*Contrasena =C,*Departamento = D,*Empresa = E;
	gotoxy(50, 5);SetColor(6);
	cout << "LOGIN";
	gotoxy(30, 7); SetColor(9);
	cout << "USUARIO: "; SetColor(11); cin.getline(Usuario,100);
	gotoxy(30, 9); SetColor(9);
	cout << "CONTRASENA: "; SetColor(11); cin.getline(Contrasena,100);
	gotoxy(30, 11); SetColor(9);
	cout << "DEPARTAMENTO: "; SetColor(11); cin.getline(Departamento,100);
	gotoxy(30, 13); SetColor(9);
	cout << "EMPRESA: "; SetColor(11); cin.getline(Empresa,100);
	NM Log = new NodoMatriz();
	Log->BuscarNodo(U,C,ToUpperCase(D), ToUpperCase(E));
	if (UserLog!=NULL) {
		gotoxy(30, 15);
		SetColor(6);
		cout << "BIENVENIDO ";
		SetColor(2);
		cout<<UserLog->Usuario;
		getchar();
		SetColor(15);
		if (Admin == true) {
			MenuAdmin();
		}
		else {
			MenuUser();
		}
	}
	else {
		gotoxy(30, 15);
		SetColor(4);
		cout << "USUARIO NO ENCONTRADO";
		getchar();
		SetColor(15);
	}
	//delete Log;
}

int main(){
	InicioMatriz = new NodoMatriz("admin", "admin", "", "");
	do
	{
		char N[10];
		char* Opcion=N;
		system("cls");
		gotoxy(50, 5);
		SetColor(6);
		cout << "BIENVENIDO";
		gotoxy(20, 7);
		SetColor(10);
		cout << "OPCIONES";
		gotoxy(30, 9);
		SetColor(9);
		cout << "1. LOGIN";
		gotoxy(30, 11);
		cout << "2. SALIR";
		gotoxy(30, 13);
		SetColor(6);
		cout << "SELECCIONAR OPCION: ";
		SetColor(11);
		cin.getline(Opcion,10);
		if (EsUnNumero(N)==true) {
			string val = N;
			if (val=="1") {
				Login();
				UserLog = NULL;
				Admin = false;
			}
			else if(val=="2"){
				break;
			}
			else if (val == "3") {
				MenuUser();
			}
			else {
				gotoxy(30, 15);
				SetColor(4);
				cout << "OPCION NO ENCONTRADA";
				getchar();
			}
		}
		else {
			gotoxy(30, 15);
			SetColor(4);
			cout << "SOLO INGRESE NUMEROS";
			getchar();
		}
	} while (true);
	return 0;
}