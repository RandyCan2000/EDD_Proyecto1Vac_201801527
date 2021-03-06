#include "NodoAVL.h"
#include "NodoMatriz.h"
#include "Globales.h"
#include <iostream>
#include <string>
#include <fstream>

std::string LSTUser="";
std::string EstructuraUserGrafica = "";
int ContadorNodoUsuario = 0;

NodoMatriz::NodoMatriz(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	this->Index = IndexUsuarios;
	this->Usuario = Usuario;
	this->Contrasena = Contrasena;
	this->Departamento = Departamento;
	this->Empresa = Empresa;
	this->Abajo = NULL;
	this->Arriba = NULL;
	this->Derecha = NULL;
	this->Izquierda = NULL;
	this->Adelante = NULL;
	this->Atras = NULL;
	this->Cabecera = false;
	this->ID = "algo";
	//activos
	this->Activos = NULL;
	IndexUsuarios++;
}
NodoMatriz::NodoMatriz(std::string Nombre, bool D_E) {
	if (D_E==true){//con true Cabecera Departamento
		this->Departamento = Nombre;
		this->Empresa = "";
	}
	else {//con false Cabecera Empresa
		this->Empresa = Nombre;
		this->Departamento = "";
	}
	//activo
	this->Activos = NULL;
	//fin activo
	this->Cabecera = true;
	this->Abajo = NULL;
	this->Arriba = NULL;
	this->Derecha = NULL;
	this->Izquierda = NULL;
	this->Adelante = NULL;
	this->Atras = NULL;
}
NodoMatriz::NodoMatriz(){
}

void NodoMatriz::BuscarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	NM Aux = InicioMatriz;
	if (Aux->Usuario==Usuario && Aux->Contrasena==Contrasena && Aux->Departamento==Departamento && Aux->Empresa==Empresa) {
		UserLog = Aux;
		Admin = true;
	}
	else {
		while(Aux!=NULL){
			if (Departamento == Aux->Departamento) {
				while (Aux != NULL) {
					if (Empresa==Aux->Empresa) {
						while(Aux!=NULL) {
							if (Usuario == Aux->Usuario && Contrasena ==Aux->Contrasena) {
								UserLog = Aux;
								break;
							}
							Aux = Aux->Atras;
						} 
						break;
					}
					Aux = Aux->Abajo;
				} 
				break;
			}
			Aux = Aux->Derecha;
		}
	}
}

NM NodoMatriz::BuscarUsuario(std::string Usuario, std::string Departamento, std::string Empresa) {
	NM Aux = InicioMatriz;
	if (Aux->Usuario == Usuario && Aux->Departamento == Departamento && Aux->Empresa == Empresa) {
		return Aux;
	}
	else {
		Aux = Aux->Derecha;
		while (Aux != NULL) {
			if (Departamento == Aux->Departamento) {
				Aux = Aux->Abajo;
				while (Aux != NULL) {
					if (Empresa == Aux->Empresa) {
						while (Aux != NULL) {
							if (Usuario == Aux->Usuario) {
								return Aux;
							}
							if (Aux == NULL) { return NULL; }
							Aux = Aux->Atras;
							if (Aux == NULL) { return NULL; }
						}
					}
					if (Aux == NULL) { return NULL; }
					Aux = Aux->Abajo;
					if (Aux == NULL) { return NULL; }
				}
			}
			if (Aux == NULL) { return NULL; }
			Aux = Aux->Derecha;
			if (Aux == NULL) { return NULL; }
		}
	}
	return NULL;
}

bool AgregarNodoEmpresa(std::string Empresa, NodoMatriz& User, NodoMatriz& Empre) {
	NM NuevoUser = &User;
	NM NuevoEmp = &Empre;
	NM Emp = InicioMatriz;
	while (Emp != NULL) {
		if (strcmp(Empresa.c_str(), Emp->Empresa.c_str()) == 1) {
			if (Emp->Abajo != NULL) {
				if (strcmp(Empresa.c_str(), Emp->Abajo->Empresa.c_str()) == -1) {
					NM Aux1 = Emp->Abajo;
					Emp->Abajo = NuevoEmp;
					Aux1->Arriba = NuevoEmp;
					NuevoEmp->Arriba = Emp;
					NuevoEmp->Abajo = Aux1;
					NuevoEmp->Derecha = NuevoUser;
					NuevoUser->Izquierda = NuevoEmp;
					return true;
				}
			}
			else {
				Emp->Abajo = NuevoEmp;
				NuevoEmp->Arriba = Emp;
				NuevoEmp->Derecha = NuevoUser;
				NuevoUser->Izquierda = NuevoEmp;
				return true;
			}
		}
		Emp = Emp->Abajo;
	}
	return false;
}
bool AgregarNodoDepartamento(std::string Departamento, NodoMatriz& User, NodoMatriz& Depa) {
	NM NuevoUser = &User;
	NM NuevoDep = &Depa;
	NM Dep = InicioMatriz;
	while (Dep != NULL) {
		if (strcmp(Departamento.c_str(), Dep->Departamento.c_str()) == 1) {
			if (Dep->Derecha != NULL) {
				if (strcmp(Departamento.c_str(), Dep->Derecha->Departamento.c_str()) == -1) {
					NM Aux = Dep->Derecha;
					Dep->Derecha = NuevoDep;
					Aux->Izquierda = NuevoDep;
					NuevoDep->Izquierda = Dep;
					NuevoDep->Derecha = Aux;
					NuevoDep->Abajo = NuevoUser;
					NuevoUser->Arriba = NuevoDep;
					return true;
				}
			}
			else {
				Dep->Derecha = NuevoDep;
				NuevoDep->Izquierda = Dep;
				NuevoDep->Abajo = NuevoUser;
				NuevoUser->Arriba = NuevoDep;
				return true;
			}
		}
		Dep = Dep->Derecha;
	}
	return false;
}

void AgregarNodoEntreNodos(NodoMatriz& CabeceraDep, NodoMatriz& CabeceraEmp, NodoMatriz& Usuario) {
	NM AuxDep = &CabeceraDep, AuxEmp = &CabeceraEmp, AuxUser = &Usuario;
	while (AuxEmp!=NULL){
		if (strcmp(AuxUser->Departamento.c_str(), AuxEmp->Departamento.c_str()) == 1) {
			if (AuxEmp->Derecha!=NULL) {
				if (strcmp(AuxUser->Departamento.c_str(), AuxEmp->Derecha->Departamento.c_str()) == -1) {
					NM Sig = AuxEmp->Derecha;
					AuxEmp->Derecha = AuxUser;
					AuxUser->Izquierda = AuxEmp;
					Sig->Izquierda = AuxUser;
					AuxUser->Derecha = Sig;
					break;
				}
			}
			else {
				AuxEmp->Derecha = AuxUser;
				AuxUser->Izquierda = AuxEmp;
				break;
			}
		}
		AuxEmp = AuxEmp->Derecha;
	}
	while (AuxDep!=NULL){
		if (strcmp(AuxUser->Empresa.c_str(), AuxDep->Empresa.c_str()) == 1) {
			if (AuxDep->Abajo!=NULL) {
				if (strcmp(AuxUser->Empresa.c_str(), AuxDep->Abajo->Empresa.c_str()) == -1) {
					NM Sig = AuxDep->Abajo;
					AuxDep->Abajo = AuxUser;
					AuxUser->Arriba = AuxDep;
					Sig->Arriba = AuxUser;
					AuxUser->Abajo = Sig;
					break;
				}
			}
			else {
					AuxDep->Abajo = AuxUser;
					AuxUser->Arriba = AuxDep;
					break;
			}
		}
		AuxDep = AuxDep->Abajo;
	}
}

bool NodoMatriz::AgregarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	NM Dep = InicioMatriz;
	NM Emp = InicioMatriz;
	NM BUSCADO=BuscarUsuario(Usuario,Departamento,Empresa);
	if (BUSCADO==NULL) {
		while (Dep != NULL) {
			if (Departamento == Dep->Departamento) { break; }
			Dep = Dep->Derecha;
		}
		while (Emp != NULL) {
			if (Empresa == Emp->Empresa) { break; }
			Emp = Emp->Abajo;
		}
		if (Dep != NULL && Emp != NULL) {
			NM CabeceraDep = Dep, CabeceraEmp = Emp;
			while (Dep != NULL) {
				if (Dep->Departamento == Departamento && Dep->Empresa == Empresa) {
					while (Dep != NULL) {
						if (Dep->Atras == NULL) {
							NM Nuevo = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
							Dep->Atras = Nuevo;
							Nuevo->Adelante = Dep;
							return true;
						}
						Dep = Dep->Atras;
					}
				}
				Dep = Dep->Abajo;
			}
			//Casos
			NM Nuevo = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
			AgregarNodoEntreNodos(*CabeceraDep, *CabeceraEmp, *Nuevo);
			return true;
		}
		else if (Dep == NULL && Emp == NULL) {
			NM NuevoDep = new NodoMatriz(Departamento, true);
			NM NuevoEmp = new NodoMatriz(Empresa, false);
			NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
			if (AgregarNodoDepartamento(Departamento, *NuevoUser, *NuevoDep) == true) {
				if (AgregarNodoEmpresa(Empresa, *NuevoUser, *NuevoEmp) == true) { return true; }
			}
		}
		else if (Dep != NULL && Emp == NULL) {
			NM NuevoEmp = new NodoMatriz(Empresa, false);
			NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
			AgregarNodoEmpresa(Empresa, *NuevoUser, *NuevoEmp);
			AgregarNodoEntreNodos(*Dep, *NuevoEmp, *NuevoUser);
			return true;
		}
		else if (Dep == NULL && Emp != NULL) {
			NM NuevoDep = new NodoMatriz(Departamento, true);
			NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
			AgregarNodoDepartamento(Departamento, *NuevoUser, *NuevoDep);
			AgregarNodoEntreNodos(*NuevoDep, *Emp, *NuevoUser); 
			return true;
		}
	}
	else {
		return false;
	}
}


std::string NodoMatriz::ImprimirMatriz() {
	std::string Texto="";
	NM Aux = InicioMatriz->Derecha;
	while (Aux != NULL) {
		Texto += Aux->Departamento + "->";
		Aux = Aux->Derecha;
	}
	Texto += "NULL";
	NM Aux1 = InicioMatriz->Abajo;
	while (Aux1 != NULL) {
		Texto += Aux1->Empresa + "->";
		Aux1 = Aux1->Abajo;
	}
	Texto += "NULL";
	return Texto;
}

bool NodoMatriz::ReporteActivosEmpresa(std::string NombreEmpresa) {
	std::ofstream fs("C:\\GraficasE\\ActivosEmpresa.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=circle, style=filled];" << std::endl;
	NAVL Arbol = new NodoAVL();
	EstrucArbol = ""; 
	NNodoARBOl = 0;
	NM Empresa = InicioMatriz;
	while (Empresa!=NULL){//Busca Empresa
		if (Empresa->Empresa==NombreEmpresa) {
			Empresa = Empresa->Derecha;
			while (Empresa!=NULL){//Recorre A los primeros Usuario
				NM Primero = Empresa;
				if (Empresa->Activos!=NULL) {
					NNodoARBOl++;
					EstrucArbol += "N" + std::to_string(NNodoARBOl);
					std::string NP = "N" + std::to_string(NNodoARBOl);
					if (Empresa->Activos->Rentado == true) {
						EstrucArbol += "[fillcolor=red ";
					}
					else {
						EstrucArbol += "[fillcolor=green ";
					}
					EstrucArbol += "label=\"" + Empresa->Activos->Nombre +"\",xlabel=\"" + std::to_string(Empresa->Activos->Altura) + "\"];\n";
					NNodoARBOl++;
					Arbol->EstructuraArbol(*Empresa->Activos, NP);
				}
				if (Empresa->Atras!=NULL) {
					Empresa = Empresa->Atras;
					while (Empresa!=NULL){
						if (Empresa->Activos!=NULL) {
							NNodoARBOl++;
							EstrucArbol += "N" + std::to_string(NNodoARBOl);
							std::string NP = "N" + std::to_string(NNodoARBOl);
							if (Empresa->Activos->Rentado == true) {
								EstrucArbol += "[fillcolor=red ";
							}
							else {
								EstrucArbol += "[fillcolor=green ";
							}
							EstrucArbol += "label=\"" + Empresa->Activos->Nombre +"\",xlabel=\"" + std::to_string(Empresa->Activos->Altura) + "\"];\n";
							NNodoARBOl++;
							Arbol->EstructuraArbol(*Empresa->Activos, NP);
						}
						Empresa = Empresa->Atras;
					}
				}
				Empresa = Primero->Derecha;
			}
			break;
		}
		Empresa = Empresa->Abajo;
	}
	fs << EstrucArbol;
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\ActivosEmpresa.dot -o C:\\GraficasE\\ActivosEmpresa.png");
	system("C:\\GraficasE\\ActivosEmpresa.png &");
	return true;
}
bool NodoMatriz::ReporteActivosDepartamento(std::string NombreDepartamento) {
	std::ofstream fs("C:\\GraficasE\\ActivosDepartamento.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=circle, style=filled];" << std::endl;
	NAVL Arbol = new NodoAVL();
	EstrucArbol = "";
	NNodoARBOl = 0;
	NM Departamento = InicioMatriz;
	while (Departamento != NULL) {//Busca departamento
		if (Departamento->Departamento == NombreDepartamento) {
			Departamento = Departamento->Abajo;
			while (Departamento != NULL) { //Recorre A los primeros Usuario
				NM Primero = Departamento;
				if (Departamento->Activos != NULL) {
					NNodoARBOl++;
					EstrucArbol += "N" + std::to_string(NNodoARBOl);
					std::string NP = "N" + std::to_string(NNodoARBOl);
					if (Departamento->Activos->Rentado == true) {
						EstrucArbol += "[fillcolor=red ";
					}
					else {
						EstrucArbol += "[fillcolor=green ";
					}
					EstrucArbol += "label=\"" + Departamento->Activos->Nombre +"\",xlabel=\"" + std::to_string(Departamento->Activos->Altura) + "\"];\n";
					NNodoARBOl++;
					Arbol->EstructuraArbol(*Departamento->Activos, NP);
				}
				if (Departamento->Atras != NULL) {
					Departamento = Departamento->Atras;
					while (Departamento != NULL) {
						if (Departamento->Activos != NULL) {
							NNodoARBOl++;
							EstrucArbol += "N" + std::to_string(NNodoARBOl);
							std::string NP = "N" + std::to_string(NNodoARBOl);
							if (Departamento->Activos->Rentado == true) {
								EstrucArbol += "[fillcolor=red ";
							}
							else {
								EstrucArbol += "[fillcolor=green ";
							}
							EstrucArbol += "label=\"" + Departamento->Activos->Nombre +"\",xlabel=\"" + std::to_string(Departamento->Activos->Altura) + "\"];\n";
							NNodoARBOl++;
							Arbol->EstructuraArbol(*Departamento->Activos, NP);
						}
						Departamento = Departamento->Atras;
					}
				}
				Departamento = Primero->Abajo;
			}
			break;
		}
		Departamento = Departamento->Derecha;
	}
	fs << EstrucArbol;
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\ActivosDepartamento.dot -o C:\\GraficasE\\ActivosDepartamento.png");
	system("C:\\GraficasE\\ActivosDepartamento.png &");
	return true;
}

void EstructuraUsuariosEjeZ(NodoMatriz &Nodo) {
	NM Aux = &Nodo;
	int NumInicial = ContadorNodoUsuario;
	EstructuraUserGrafica += "N"+std::to_string(ContadorNodoUsuario)+" [label=\""+Aux->Departamento+"\l"+Aux->Empresa+"\",fillcolor = slategrey];\n";
	ContadorNodoUsuario++;
	while (Aux!=NULL){
		EstructuraUserGrafica += "N" + std::to_string(ContadorNodoUsuario) + " [label=\"" +Aux->Usuario+ "\",fillcolor=\"#967373\"];\n";
		ContadorNodoUsuario++;
		Aux = Aux->Atras;
	}
	for (int i = NumInicial; i < ContadorNodoUsuario; i++){
		if (i==ContadorNodoUsuario-1) {
			EstructuraUserGrafica += "N"+std::to_string(i)+" [dir=\"both\"];\n";
		}
		else {
			EstructuraUserGrafica += "N" + std::to_string(i) + " -> ";
		}
	}
}

void GenerarReporte() {
	std::ofstream fs("C:\\GraficasE\\UsuarioEjeZ.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=box, style=filled];" << std::endl;
	fs << EstructuraUserGrafica;
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\UsuarioEjeZ.dot -o C:\\GraficasE\\UsuarioEjeZ.png");
	system("C:\\GraficasE\\UsuarioEjeZ.png &");
}

void NodoMatriz::RepMatriz() {
	EstructuraUserGrafica = ""; ContadorNodoUsuario = 0;
	NM Aux = InicioMatriz;
	std::ofstream fs("C:\\GraficasE\\MatrizUsuarios.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=box, style=filled];" << std::endl;
	fs << "MATRIZ [ label =\"USUARIOS\",width = 1.5, group=1];\n";
	Aux = Aux->Abajo;
	while (Aux!=NULL) {
		fs << "E" << Aux->Empresa << " [ label=\""<<Aux->Empresa << "\",width = 1.5,fillcolor = slategrey, group=1];\n";
		Aux = Aux->Abajo;
	}
	int Contador = 2;
	Aux = InicioMatriz->Derecha;
	while (Aux != NULL) {
		fs << "D" << Aux->Departamento << " [ label=\"" << Aux->Departamento << "\",width = 1.5,fillcolor=seagreen, group="<< std::to_string(Contador) <<"];\n";
		Contador++;
		Aux = Aux->Derecha;
	}
	Aux = InicioMatriz->Abajo;
	while (Aux!=NULL) {
		if (Aux->Abajo!=NULL) {
			fs << "E" << Aux->Empresa << " -> " << "E" << Aux->Abajo->Empresa<<" [dir=\"both\"];\n";
		}
		Aux = Aux->Abajo;
	}
	Aux = InicioMatriz->Derecha;
	while (Aux != NULL) {
		if (Aux->Derecha != NULL) {
			fs << "D" << Aux->Departamento << " -> " << "D" << Aux->Derecha->Departamento << " [dir=\"both\"];\n";
		}
		Aux = Aux->Derecha;
	}
	if (InicioMatriz->Abajo != NULL) { fs << "MATRIZ -> E" << InicioMatriz->Abajo->Empresa<<" [dir=\"both\"];\n"; }
	if (InicioMatriz->Derecha != NULL) { fs << "MATRIZ -> D" << InicioMatriz->Derecha->Departamento << " [dir=\"both\"];\n"; }
	
	fs << "{ rank=same;MATRIZ;";
	Aux = InicioMatriz->Derecha;
	while (Aux!=NULL) {
		fs <<"D"<< Aux->Departamento<<";";
		Aux = Aux->Derecha;
	}
	fs << "}\n";

	//Creacion de Nodo Usuario
	Aux = InicioMatriz->Derecha; Contador = 2;

	while (Aux != NULL) {
		NM Cabecera = Aux;
		Aux = Aux->Abajo;
		while (Aux != NULL) {
			fs << "USER" << Aux->Departamento << Aux->Empresa << " [label=\"" + Aux->Usuario + "\", width = 1.5,fillcolor=\"#967373\", group=" + std::to_string(Contador) + "];\n";
			//Aqui Se crea el reporte si existen mas usuarios atras del principal
			if (Aux->Atras != NULL) { EstructuraUsuariosEjeZ(*Aux); }
			Aux = Aux->Abajo;
		}
		Aux = Cabecera->Derecha; Contador++;
	}
	Aux = InicioMatriz->Abajo;
	std::string Rank = "";
	while (Aux!=NULL) {
		NM Cabecera = Aux;
		Rank = "";
		fs << "E"<<Aux->Empresa<<" -> USER"<<Aux->Derecha->Departamento<<Aux->Derecha->Empresa<<" [dir=\"both\"];\n";
		Aux = Aux->Derecha;
		while (Aux!=NULL){
			Rank += "USER" + Aux->Departamento + Aux->Empresa+";";
			if (Aux->Derecha!=NULL) {
				fs << "USER" << Aux->Departamento<<Aux->Empresa << " -> USER" << Aux->Derecha->Departamento << Aux->Derecha->Empresa << " [dir=\"both\"];\n";
			}
			Aux = Aux->Derecha;
		}
		fs << "{ rank=same ; E"<<Cabecera->Empresa<<";"<<Rank;
		fs << "}\n";
		Aux = Cabecera->Abajo;
	}
	Aux = InicioMatriz->Derecha;
	while (Aux!=NULL){
		NM Cabecera = Aux;
		fs << "D"<<Aux->Departamento<<" -> USER"<<Aux->Abajo->Departamento<<Aux->Abajo->Empresa<<" [dir=\"both\"];\n";
		Aux = Aux->Abajo;
		while (Aux!=NULL){
			if (Aux->Abajo!=NULL) {
				fs << "USER" << Aux->Departamento<<Aux->Empresa << " -> USER" << Aux->Abajo->Departamento << Aux->Abajo->Empresa << " [dir=\"both\"];\n";
			}
			Aux = Aux->Abajo;
		}
		Aux = Cabecera->Derecha;
	}

	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\MatrizUsuarios.dot -o C:\\GraficasE\\MatrizUsuarios.png");
	system("C:\\GraficasE\\MatrizUsuarios.png &");
	if (EstructuraUserGrafica != "") { GenerarReporte(); }
}
std::string NodoMatriz::ListarTodosLosActivos() {
	std::string TodosLosActivos = "";
	NAVL Activos = new NodoAVL();
	NM Aux = InicioMatriz->Abajo;
	while (Aux!=NULL){//while que recorre las empresa
		NM CabEmpresa = Aux;//Guarda la cabecera de la empresa
		Aux = Aux->Derecha;//Toma El primero usuario de la empresa en el departamento que este (el Departamento es indiferente)
		while (Aux!=NULL) {//while que recorre los primeros usuarios en la empresa no importa el departamento
			NM PrimerUser = Aux;//Guarda al primero usuario
			if (Aux!=UserLog) {//Mira si es distinto al usuario logueado
				TodosLosActivos += "-----USUARIO: " + Aux->Usuario + " DEPARTAMENTO: " + Aux->Departamento + " EMPRESA: " + Aux->Empresa + "-----\n";
				TodosLosActivos += Activos->ListaActivo(*Aux->Activos,false);
			}
			if (Aux->Atras!=NULL) {//Verifica si hay mas usuario aparte del inicial
				Aux = Aux->Atras;//toma al usuario de atras del primero
				while (Aux!=NULL){//recorre los usuarios en el eje Z de la matriz
					if (Aux!=UserLog) {//Mira si es distinto al usuario logueado
						TodosLosActivos += Activos->ListaActivo(*Aux->Activos,false);
					}
					Aux = Aux->Atras;//toma al usuario de atras
				}
			}//fin IF
			Aux = PrimerUser->Derecha;//toma el valor a la derecha del primer usuario
		}
		Aux = CabEmpresa->Abajo;//Toma la empresa de abajo
	}//fin del whiile que recorre las empresa
	delete Activos;
	return TodosLosActivos;
}