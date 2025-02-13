/*****************************
 Librer�as utilizadas
*****************************/
#include <iostream>					/*Flujo de entrada y salida de datos*/
#include <string.h>					/*Funciones de manejo de cadenas*/
#include <windows.h>				/*Permite usar comandos de Windows Console*/
#include <stdio.h>					/*se utiliza para proporcionar las funciones para la entrada y salida de archivos.*/
#include <algorithm>				/*se utiliza para proporcionar varias funciones de algoritmos para trabajar con contenedores.*/
#include <locale.h>					/* se utiliza para establecer la configuraci�n regional y de idioma para el programa*/
#define CANTIDAD 500 				/*Cantidad maxima de contactos: 500*/
#include <limits>					/* proporciona funciones para obtener las limitaciones y caracter�sticas del tipo de datos b�sicos de C++.*/
#include <fstream>					/*se utiliza para proporcionar las funciones para la entrada y salida de archivos.*/

using namespace std;

/*
	Variables globales que representan 
	contactos registrados, eliminados y
	una variable Regla que presentara una
	mejor vista en el programa.
*/
int ContactosRegistrados = 0;
int ContactosEliminados  = 0;
const int ANCHO_CONSOLA = 65;
string Regla = string(ANCHO_CONSOLA, '-');

/*****************************
Estructura de fecha y Agenda
*****************************/
/*Estructura de fecha de nacimiento*/
struct Cumple {
	string Nacimiento;
};

/*Estructura de Agenda, contiene todos los atributos*/
struct Agenda {
	string Nombre;
	string Telefono;
	string Celular;
	string Email;
	Cumple Fecha;					/*Referencia a la estructura Cumple*/
	Agenda();  						/*Declaraci�n del constructor*/
};

/*****************************
	FUNCIONES PRINCIPALES 
*****************************/

int MenuPrimario();					/*Se muestra cuando no hay contactos*/
int MenuSecundario();				/*Se muestra cuando hay contactos que gestionar*/

/*Relevante e importante*/
void Insertar(struct Agenda Contactos[]);			/*Inserta contactos en la agenda*/

/*Relevante e importante*/
void Buscar(struct Agenda Contactos[]);				/*Busca contactos en la agenda*/
int BuscarMenuCategoria();							/*Se muestra un mensaje para buscar por categorias*/
void BuscarPorNombre(struct Agenda Contactos[]);	/*Aplica una busqueda por nombre de contacto*/
void BuscarPorTelefono(struct Agenda Contactos[]);	/*Aplica una busqueda por telefono de contacto*/
void BuscarPorCelular(struct Agenda Contactos[]);	/*Aplica una busqueda por celular de contacto*/
void BuscarPorEmail(struct Agenda Contactos[]);		/*Aplica una busqueda por email de contacto*/

/*Relevante e importante*/
void Listar(struct Agenda Contactos[]);				/*Lista todos los contactos existentes*/
void Imprimir(struct Agenda Contactos[], int);		/*Mostrar un contacto seleccionado*/

/*Relevante e importante*/
void Actualizar(struct Agenda Contactos[], int);	/*Actualiza un contacto seleccionado en la agenda*/
/*Relevante e importante*/
void Eliminar(struct Agenda Contactos[], int);		/*Elimina un contacto seleccionado en la agenda*/

int VerificarContacto(struct Agenda Contactos[], string);	/*Verifica si el contacto especificado existe*/

/*
Esta funci�n es interesante, tiene como objetivo
cargar datos (contactos) en la agenda para pruebas
r?pidas en la ejcuci�n del programa.
*/
void CargarContactos(struct Agenda Contactos[]);
bool HayContactos(struct Agenda Contactos[]);		/*Verifica si hay contactos en la agenda*/

/*****************************
	FUNCIONES SECUNDARIAS
*****************************/
void Detenerse();									/*Detiene la ejecuci?n, hasta que se presione una tecla*/
void LimpiarPantalla();								/*Limpia la pantalla para mostrar un nuevo Men�*/
void Dormir(int);									/*Aplica un retraso temporal*/
int Salir();										/*Centinela que pregunta por la salida de los Men�es*/

/*****************************
 DEFINICI�N DEL CONSTRUCTOR
-----------------------------
Inicializando la estructura.
*****************************/
Agenda::Agenda() {
	Nombre 		= " ";								/*Para nombre, dejar un espacio en blanco*/
	Telefono 	= "0";								/*Para telefono, dejar 0 como contenido*/
	Celular 	= "0";								/*Para celular, dejar 0 como contenido*/
	Email 		= " ";								/*Para email, dejar un espacio en blanco*/
	Fecha.Nacimiento = " ";							/*Para fecha, dejar un espacio en blanco*/
}

/*****************************
	  FUNCION PRINCIPAL
*****************************/
int main(int argc, char *argv[]) {
	
	//Tama�o de la consola
	system("mode con: cols=80 lines=30");

	setlocale(LC_CTYPE, "spanish");
	int x;											/*Almacena las opciones seleccionadas*/
	int salir = 0;                                  /*bandera para salir*/
	Agenda Contactos[CANTIDAD]; 					/*Definici�n de la variable Contactos con la cantidad*/
	CargarContactos(Contactos);						/*menasaje para cargar datos o iniciar una nueva agenda*/
	
	
	do{											/*Etiqueta para retornar al Menu recursivamente*/
		if (HayContactos(Contactos)){				/*Verifica si no hay contactos*/
			ContactosRegistrados = 0;
			ContactosEliminados  = 0;
			/*No hay contactos*/
			do {
				x = MenuPrimario();					/*Primer Menu donde la agenda est? vac?a*/
			} while(x < 1 || x > 2);
			
			switch (x){								/*En este Menu se validan 2 opciones (Insertar, Salir)*/
				case 1: 
					Insertar(Contactos);			/*Men� para insertar datos*/
					break;
				case 2:
					salir = Salir();				/*Centinela para Salir*/
					break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					system("PAUSE>NUL");
					break;
			}
			
		} else {
			/*Si hay contactos*/
			do {
				x = MenuSecundario();				/*Segundo Men� donde la agenda contiene contactos*/
			} while(x < 1 || x > 4);
			
			switch (x){								/*Este Men� contiene m�s opciones (Insertar, buscar, listar)*/
				case 1: 
					Insertar(Contactos);
					break;
				case 2:
					Buscar(Contactos);				/*Men� para realizar una b�squeda de contactos por categor?as*/
					break;
				case 3: 
					Listar(Contactos);				/*Listar todos los contactos existentes de manera interactiva*/
					break;
				case 4:
					salir = Salir();				/*Centinela para Salir*/
					break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					system("PAUSE>NUL");
					break;
			}
		}
	}
	while (salir == 0);						/*Se retorna al Men� principal en caso de que no haya seleccionado Salir*/
	
	ofstream Archivo("Contactos.txt");
	for (int i= 0 ; i<ContactosRegistrados;i++) {
		
		Archivo<<"Contactos  "<<i+1<<":"<<endl;
		Archivo<<"Nombre: "<<Contactos[i].Nombre<<endl;
		Archivo<<"Tel�fono: "<<Contactos[i].Telefono<<endl;
		Archivo<<"Celular: "<<Contactos[i].Celular<<endl;
		Archivo<<"Email: "<<Contactos[i].Email<<endl;
		Archivo<<"Fecha de Nacimiento:  "<<Contactos[i].Fecha.Nacimiento<<endl;
		
		Archivo<<endl;
	}
	Archivo.close();
	cout<<"Datos de contacto exportado correctamente al archivo Contacto.txt"<<endl;	
	return 0;
}

int MenuPrimario() {
    char input;
    int option;

    LimpiarPantalla();
    // Obtener el ancho de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;

    // titulo a centrar
    string titulo = "\x1B[1mBienvenido a tu Agenda Electr�nica (Contactos)\x1B[0m";
    string subtitulo = "\x1B[1mNo hay contactos\x1B[0m";

    // Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
    int espaciosEnBlancoTitulo = (consoleWidth - titulo.length()) / 2;
    int espaciosEnBlancoSubtitulo = (consoleWidth - subtitulo.length()) / 2;

    cout << Regla << endl;
    // Imprimir los espacios en blanco seguidos de la palabra centrada
    for (int i = 0; i < espaciosEnBlancoTitulo; i++) {
        cout << " ";
    }
    cout << titulo << endl;
    cout << Regla << endl << endl;

    // Imprimir los espacios en blanco seguidos de la palabra centrada
    for (int i = 0; i < espaciosEnBlancoSubtitulo; i++) {
        cout << " ";
    }
    cout << subtitulo << endl << endl;

    cout << Regla << endl;
    cout << "\x1B[1m\t\t1.Nuevo contacto\x1B[0m\n\n\x1B[1m\t\t2.Salir\x1B[0m" << endl;
    cout << Regla << endl;

    do {
        cout << "\x1B[1m\t Esperando respuesta: \x1B[0m";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del cin
        if (isdigit(input)) {
            option = input - '0'; // Convertir de char a int
            if (option < 1 || option > 2) {
                cout << "\n\x1B[31mError: La opci�n debe ser 1 o 2.\x1B[0m\n" << endl;
            }
        } else {
            cout << "\n\x1B[31mError: La entrada debe ser num�rica.\x1B[0m\n" << endl;
        }
    } while (option < 1 || option > 2);

    return option;
}


int MenuSecundario(){
	int x;
	
	LimpiarPantalla();
	
	// Obtener el ancho de la consola

	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.dwSize.X;
    	
    // titulo a centrar
    string titulo = "\x1B[1mBienvenido a tu Agenda Electronica (Contactos)\x1B[0m";
    string subtitulo = "\x1B[1mSi hay contactos\x1B[0m";
	// Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
	int espaciosEnBlanco = (consoleWidth - titulo.length()) / 2;
	int espaciosEnBlancoSubtitulo = (consoleWidth - subtitulo.length()) / 2;	
	cout << Regla << endl;
		
	// Imprimir los espacios en blanco seguidos de la palabra centrada
	for (int i = 0; i < espaciosEnBlanco; i++) {
	    cout << " ";
    }
	cout << titulo << endl;
	cout << Regla << endl;
	
	cout << "\n";
	
		
	// Imprimir los espacios en blanco seguidos de la palabra centrada
	for (int i = 0; i < espaciosEnBlancoSubtitulo; i++) {
	        cout << " ";
	}
	
	cout << subtitulo << " (" << (ContactosRegistrados - ContactosEliminados)<<")"<< endl;
	cout << "\n";
		
	cout << Regla << endl;
	
	cout << "\x1B[1m\t1. Nuevo \x1B[0m\n\t\x1B[1m2. Buscar\x1B[0m\n\t\x1B[1m3. Listar \x1B[0m\n\t\x1B[1m4. Salir\x1B[0m" << endl;
	cout << Regla << endl;
	
	cout << "\x1B[1m\tEsperando respuesta: \x1B[0m";
	cin >> x;
	
	return x;
}

void Insertar(struct Agenda Contactos[]){
	int x;
	int salir =0;						/*bandera para salir*/
	
	do{ 									/*Etiqueta de Men� para insertar contactos*/
		
		/*Se verifica si hay espacio en la agenda*/
		if (ContactosRegistrados < CANTIDAD){
			cout << "\x1B[1m\n\tNumero de contacto: \x1B[0m" << (ContactosRegistrados + 1) << endl;
			cout << "\x1B[1m\tNombre:   \x1B[0m";
			cin >>  Contactos[ContactosRegistrados].Nombre;
			
			/*Se verifica si el contacto que est? intentando insertar, existe en la agenda*/
			if (VerificarContacto(Contactos, Contactos[ContactosRegistrados].Nombre)){
				cout << "\n\tEl contacto \"" << Contactos[ContactosRegistrados].Nombre << "\" ya existe!" << endl;
				
				Contactos[ContactosRegistrados].Nombre = " ";
				
				/*Si existe se intenta ingresar otro*/
				do {
					cout << "\n\t\x1B[1m�Desea agregar otro contacto?\x1B[0m" << endl;
					cout << "\t\x1B[1m1. Si\x1B[0m\n\t\x1B[1m2. No\x1B[0m";
					cout << "\x1B[1m\n\tEsperando respuesta: \x1B[0m";
					cin >> x;
					
				} while(x < 1 || x > 2);
				
				switch (x){
					case 1: 
						// volvemos a InsertarMenu
						cout<<"\n"<<endl;
						Insertar(Contactos);
						break;
					case 2:
						salir = 1;
						Detenerse();
						MenuSecundario();
						break;
					default:
						cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
						Detenerse();
						break;
				}
			}
			
			cout << "\x1B[1m\tTelefono: \x1B[0m";									
			cin >>  Contactos[ContactosRegistrados].Telefono;	/*Agregando valor a atributo Telefono*/
			
			cout << "\x1B[1m\tCelular:  \x1B[0m";
			cin >>  Contactos[ContactosRegistrados].Celular;	/*Agregando valor a atributo Celular*/
			
			cout << "\x1B[1m\tEmail:    \x1B[0m";
			cin >>  Contactos[ContactosRegistrados].Email;	/*Agregando valor a atributo Email*/
			
			cout << "\x1B[1m\tFecha de Nacimiento (DD/MM/AAAA): \x1B[0m";
			cin >>  Contactos[ContactosRegistrados].Fecha.Nacimiento;	/*Agregando valor a atributo de Fecha*/
			
			ContactosRegistrados++;									/*Se incrementa la variable, indicando nuevo contacto*/
			
			cout << "\x1B[1m\n\t�Agregado con exito!\x1B[0m" << endl << endl;
			
		
			do {
				cout << "\n\t\x1B[1m�Desea agregar otro contacto?\x1B[0m" << endl;
				cout << "\t\x1B[1m1. Si\x1B[0m\n\t\x1B[1m2. No\x1B[0m";
				cout << "\x1B[1m\n\tEsperando respuesta: \x1B[0m";
				cin >> x;
				
			} while(x < 1 || x > 2);
			
			switch (x){
				case 1: 
					// volvemos a InsertarMenu
					break;
				case 2:
					salir = 1;
					Detenerse();
					break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					Detenerse();
					break;
			}
			
		} else {
			cout << "Llego al limite de contactos permitidos en la agenda." << endl << endl;
		}
	}
	while(salir == 0);
	return;
}

void Buscar(struct Agenda Contactos[]){
	int x;
	int salir = 0;                                      /*bandera para salir*/
	
	do{ 
		LimpiarPantalla();
	
		do {
			x = BuscarMenuCategoria();				/*Men� para buscar contactos por categor?as*/
		} while(x < 1 || x > 5);
		
		switch (x){
			case 1: 
				BuscarPorNombre(Contactos);			/*Buscar por nombre*/
				break;
			case 2:
				BuscarPorTelefono(Contactos);		/*Buscar por tel?fono*/
				break;
			case 3: 
				BuscarPorCelular(Contactos);		/*Buscar por celular*/
				break;
			case 4: 
				BuscarPorEmail(Contactos);			/*Buscar por email*/
				break;
			case 5:
				salir = Salir();
				break;
			default:
				cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				system("PAUSE>NUL");
				break;
		}
	
	}
	while(salir == 0);

	Detenerse();
	return;
}

int BuscarMenuCategoria(){
	int x; 
	// Obtener el ancho de la consola

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;
    	
    // titulo a centrar
    string titulo = "\x1B[1mRealizar busqueda por:\x1B[0m";
    
	// Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
	int espaciosEnBlanco = (consoleWidth - titulo.length()) / 2;
		
	cout << Regla << endl;
		
	// Imprimir los espacios en blanco seguidos de la palabra centrada
	for (int i = 0; i < espaciosEnBlanco; i++) {
	    cout << " ";
	}
					
	cout <<titulo<< endl;
	
	cout << Regla << endl;
	cout << "\x1B[1m\t1. Nombre\x1B[0m\n\t\x1B[1m2. Telefono\x1B[0m\n\t\x1B[1m3. Celular\x1B[0m\n\t\x1B[1m4. Email\x1B[0m\n\t\x1B[1m5. Volver\x1B[0m" << endl;
	cout << Regla << endl;
	
	cout << "\x1B[1m\n\tEsperando respuesta: \x1B[0m";
	cin >> x;
	
	
	return x;
}

void BuscarPorNombre(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador en el ciclo*/
	int c = 0;					/*Coincidencias*/
	
	string PorNombre;
	
	cout << "\n\t\x1B[1mDigite el nombre: \x1B[0m";
	cin >>  PorNombre;
	cout << endl;
	
	/*Recorrer la cantidad de contactos registrados en la agenda*/
	for (i=0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Nombre == PorNombre) ==0){				/*Si lo encuentra*/
			Imprimir(Contactos, i);							/*Muestra la informaci?n del contacto*/
			c++;
			break;
		}
	}
	
	if (c == 0)
		cout << "\n\tEl contacto \"" << PorNombre << "\" no se ha encontrado." << endl << endl;
	
	Detenerse();
	return;
}

void BuscarPorTelefono(Agenda Contactos[]) {
    int i = 0; 
    int c = 0;
    
    string PorTelefono;
    
    cout << "\n\t\x1B[1mDigite el numero de telefono: \x1B[0m";
    cin >> PorTelefono;
    cout << endl;

    // Eliminar los espacios en blanco del n�mero de tel�fono ingresado
    PorTelefono.erase(remove(PorTelefono.begin(), PorTelefono.end(), ' '), PorTelefono.end());

    for (i = 0; i < ContactosRegistrados; i++) {
        // Eliminar los espacios en blanco del n�mero de tel�fono en la agenda antes de comparar
        string TelefonoAgenda = Contactos[i].Telefono;
        TelefonoAgenda.erase(remove(TelefonoAgenda.begin(), TelefonoAgenda.end(), ' '), TelefonoAgenda.end());

        if (TelefonoAgenda == PorTelefono) {
            Imprimir(Contactos, i);
            c++;
            break;
        }
    }
    
    if (c == 0) {
        // Mostrar mensaje de error con el n�mero de tel�fono ingresado
        cout << "\n\t\x1B[1mEl contacto \"" << PorTelefono << "\" no se ha encontrado.\x1B[0m" << endl << endl;       
    }
    
    Detenerse();
    return;
}





void BuscarPorCelular(struct Agenda Contactos[]){
    int i = 0; 
    int c = 0;  /*Coincidencias*/
    
    string PorCelular;
    
    cout << "\n\t\x1B[1mDigite el numero de celular: \x1B[0m";
    cin >> PorCelular;
    cout << endl;
    
    // Eliminar los espacios en blanco del n�mero de celular ingresado
    PorCelular.erase(remove(PorCelular.begin(), PorCelular.end(), ' '), PorCelular.end());

    for (i = 0; i < ContactosRegistrados; i++){
        // Eliminar los espacios en blanco del n�mero de celular en la agenda antes de comparar
        string CelularAgenda = Contactos[i].Celular;
        CelularAgenda.erase(remove(CelularAgenda.begin(), CelularAgenda.end(), ' '), CelularAgenda.end());

        if (CelularAgenda == PorCelular){
            Imprimir(Contactos, i);
            c++;
            break;
        }
    }
    
    if (c == 0){
        cout << "\n\t\x1B[1mEl contacto \"" << PorCelular << "\" no se ha encontrado.\x1B[0m" << endl << endl;       
    }
    
    Detenerse();
    return;
}


void BuscarPorEmail(struct Agenda Contactos[]){
    int i = 0; 
    int c = 0;  /*Coincidencias*/
    /*Tienen que concidir al menos 7 caracetres consiguientes*/
    string PorEmail;
    
    cout << "\n\t\x1B[1mDigite el Email: \x1B[0m";
    cin >>  PorEmail;
    cout << endl;
    
    for (i = 0; i < ContactosRegistrados; i++){
        if (Contactos[i].Email.find(PorEmail) != string::npos && PorEmail.size() >= 7) {
            Imprimir(Contactos, i);
            c++;
        }
    }
    
    if (c == 0){
        cout << "\n\t\x1B[1mNo se ha encontrado ning�n contacto con \"" << PorEmail << "\" en su email con al menos 7 caracteres coincidentes.\x1B[0m" << endl << endl;       
    }
    
    Detenerse();
    return;
}




void Listar(struct Agenda Contactos[]){
	int i = 0;									/*Iterador del ciclo*/
	int x = 0; 									/*N?mero de contacto*/
	int contactos_restantes = 0;				/*Contactos restantes*/
	
	/*Se recorren todos los contactos registrados*/
	for (; i < ContactosRegistrados; i++){
		
		/*Si se encuentran contactos registrados*/
		if (Contactos[i].Nombre != " "){
			if (i > 1){
				contactos_restantes = (ContactosRegistrados - x) - ContactosEliminados;
				Dormir(1);						/*Aplicar retraso de 1 segundo*/
				
				if (contactos_restantes > 1)
					cout << "\t-- A?n quedan " << contactos_restantes << " por visualizar --" << endl;
				else if (contactos_restantes == 1)
					cout << "\t-- S?lo queda " << contactos_restantes << " por visualizar --" << endl;
				
				Detenerse();
				cout << endl;
			}
			
			/*Impresi?n de todos los datos de los contactos resultates*/
			cout << "\n\t\x1B[1mNumero de contacto: \x1B[0m" << (x+1) << endl;
			cout << "\t\x1B[1mNombre:   \x1B[0m" << Contactos[i].Nombre << endl;
			cout << "\t\x1B[1mTelefono: \x1B[0m" << Contactos[i].Telefono << endl;
			cout << "\t\x1B[1mCelular:  \x1B[0m" << Contactos[i].Celular << endl;
			cout << "\t\x1B[1mEmail:    \x1B[0m" << Contactos[i].Email << endl;
			cout << "\t\x1B[1mFecha N.: \x1B[0m" << Contactos[i].Fecha.Nacimiento << endl << endl;
			
			x++;			/*Incremento de la variable de n?mero de contacto*/
		}
	}
	
	cout << "\t <-- Regresar" << endl;
	Detenerse();
	return;
}
void Imprimir(struct Agenda Contactos[], int posicion){
	int x;
	
	/*Imprime el contacto que est? en una posici?n espec?fica de la agenda*/
	cout << "\n\t\x1B[1mNombre:  \x1B[0m" << Contactos[posicion].Nombre << endl;
	cout << "\t\x1B[1mTelefono:  \x1B[0m" << Contactos[posicion].Telefono << endl;
	cout << "\t\x1B[1mCelular:   \x1B[0m" << Contactos[posicion].Celular << endl;
	cout << "\t\x1B[1mEmail:     \x1B[0m" << Contactos[posicion].Email << endl;
	cout << "\t\x1B[1mFecha N.:  \x1B[0m" << Contactos[posicion].Fecha.Nacimiento << endl << endl;
	
	/*CENTINELA: Opciones Actualizar y Elmiminar contacto*/
	do {
		cout << Regla<<endl;
		
		cout << "\t\x1B[1mOpciones del contacto \x1B[0m\"\x1B[1m" << Contactos[posicion].Nombre << "\" \x1B[0m" << endl;
		cout << "\t\x1B[1m1. Actualizar\x1B[0m\n\t\x1B[1m2. Eliminar\x1B[0m\n\t\x1B[1m3. Volver\x1B[0m" << endl;
		cout << Regla << endl;
		
		cout << "\x1B[1m\n\tEsperando respuesta: \x1B[0m";
		cin >> x;
		
		cout << endl;
		
	} while(x < 1 || x > 3);
	
	switch (x){
	case 1: 
		Actualizar(Contactos, posicion);				/*Actualiza el contacto seleccionado*/
		break;
	case 2:
		Eliminar(Contactos, posicion);					/*Elimina el contacto seleccionado*/
		break;
	case 3: 
		if (Salir() == 1)
			return;
	default:
		cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
		Detenerse();
		break;
	}
	
	return;
}

void Actualizar(struct Agenda Contactos[], int posicion){
	int x; 
	string Nombre, Telefono, Celular, Email;			/*Declaraci?n de variables que almacenar?n una copia*/
	int salir = 0;                                      /*bandera para salir*/
	
	do { 												//ActualizarOtroContacto: 
		
		Nombre 	= Contactos[posicion].Nombre;
		Telefono= Contactos[posicion].Telefono;
		Celular = Contactos[posicion].Celular;
		Email 	= Contactos[posicion].Email;
		// Obtener el ancho de la consola

		CONSOLE_SCREEN_BUFFER_INFO csbi;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    	int consoleWidth = csbi.dwSize.X;
    	
    	// titulo a centrar
    	string titulo = "\x1B[1mQu� dato le gustar�a actualizar de este contacto?\x1B[0m";
    
		// Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
		int espaciosEnBlanco = (consoleWidth - titulo.length()) / 2;
		

		


		/*Men� para seleccionar qu? atributos desean actualizar*/
		do {
			cout << Regla << endl;
			// Imprimir los espacios en blanco seguidos de la palabra centrada
	    	for (int i = 0; i < espaciosEnBlanco; i++) {
	        	cout << " ";
	    	}
			cout <<titulo<< endl;
			
			cout << Regla << endl;
			cout << "\x1B[1m\t1. Nombre\x1B[0m\n\t\x1B[1m2. Telefono\x1B[0m\n\t\x1B[1m3. Celular\x1B[0m\n\t\x1B[1m4. Email\x1B[0m\n\t\x1B[1m5. Ninguno\x1B[0m" << endl;			
			cout << Regla << endl;			
			cout << "\x1B[1m\n\tEsperando respuesta: \x1B[0m";
			cin >> x;
			
			cout << endl;
			
		} while(x < 1 || x > 5);
		
		/*Modificaci?n para los correspondientes atributos seleccionados*/
		switch (x){
			case 1: 
				cout << "\t\x1B[1mDigite el nuevo nombre: \x1B[0m";
				cin >>  Contactos[posicion].Nombre;
				cout << "   Se ha actualizado de \"" << Nombre << "\" a " << "\"" << Contactos[posicion].Nombre << "\"" << endl; 
				break;
			case 2:
				cout << "\t\x1B[1mDigite el nuevo telefono: \x1B[0m";
				cin >>  Contactos[posicion].Telefono;
				cout << "   Se ha actualizado de \"" << Telefono << "\" a " << "\"" << Contactos[posicion].Telefono << "\"" << endl; 
				break;
			case 3: 
				cout << "\t\x1B[1mDigite el nuevo celular: \x1B[0m";
				cin >>  Contactos[posicion].Celular;
				cout << "   Se ha actualizado de \"" << Celular << "\" a " << "\"" << Contactos[posicion].Celular << "\"" << endl; 
				break;
			case 4: 
				cout << "\t\x1B[1mDigite el nuevo email: \x1B[0m";
				cin >>  Contactos[posicion].Email;
				cout << "\x1B[1m   Se ha actualizado de \x1B[0m\"\x1B[1m" << Email << "\\x1B[0m\" a \"\x1B[1m" << Contactos[posicion].Email << "\"\x1B[0m" << endl;

				break;
			case 5: 
				salir = Salir();
			default:
				cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				Detenerse();
				break;
		}
	}
	while(salir == 0);
	
	return;
}

void Eliminar(struct Agenda Contactos[], int posicion){
	string Nombre;
	
	Nombre = Contactos[posicion].Nombre;
	
	/*Despu?s de ejecutar la centinela, se resetean los valores de esa posici?n
	  y no se vuelven a tomar en cuenta. Este algoritmo est? trabajado para que 
	  no perjudique en ning?n momento en la ejecuci?n del programa.
	*/
	if (Salir() == 1){
		Contactos[posicion].Nombre 	= " ";
		Contactos[posicion].Telefono= "0";
		Contactos[posicion].Celular	= "0";
		Contactos[posicion].Email	= " ";
		ContactosEliminados++;
		
		cout << "\n\x1B[1m�El ex-contacto \"" << Nombre <<  "\" ha sido eliminado con exito!\x1B[0m\n\n";
	}
	
	return;
}

int VerificarContacto(struct Agenda Contactos[], string Nombre){
	int i = 0; 
	int c = 0;
	
	/*Verifica si existe un contacto en espec?fico*/
	for (; i < ContactosRegistrados; i++){
		if (Contactos[i].Nombre == Nombre){
			c++;
			break;
		}
	}
	
	if (c == 0)
		return false;
	
	return true;
}

void CargarContactos(struct Agenda Contactos[]){
	int x;
	
	/*Cargar datos por omisi?n para realizar pruebas r?pidas de las opciones
	  que presenta este programa sobre la gesti?n de contactos de la Agenda.
	*/
	do {
		LimpiarPantalla();
		
	    // Obtener el ancho de la consola

		CONSOLE_SCREEN_BUFFER_INFO csbi;
	    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    	int consoleWidth = csbi.dwSize.X;
    	
    	// titulo a centrar
    	string titulo = "\x1B[1mBienvenido a tu Agenda Electronica (Contactos)\x1B[0m";
    
		// Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
		int espaciosEnBlanco = (consoleWidth - titulo.length()) / 2;
		
		cout << Regla << endl;
		
		// Imprimir los espacios en blanco seguidos de la palabra centrada
	    for (int i = 0; i < espaciosEnBlanco; i++) {
	        cout << " ";
	    }
				
		cout <<titulo<< endl;
		cout << Regla << endl;
			
		cout << "\t\x1B[1m 1.Cargar contactos previos\x1B[0m \n\t \x1B[1m2.Nueva agenda\x1B[0m\n\t\x1B[1m 3.Salir\x1B[0m" << endl;
		cout << Regla << endl;
			
		cout << "\x1B[1m\t Esperando respuesta: \x1B[0m";
		cin >> x;
		
			
	} while(x < 1 || x > 3);
		
	switch (x){
		case 1: 
			/*Primer contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Daniel Estrada";
			Contactos[ContactosRegistrados].Telefono 		= "+51 222111";
			Contactos[ContactosRegistrados].Celular 		= "+51 963852741";
			Contactos[ContactosRegistrados].Email 			= "danielestrada@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "16/12/1999";
			ContactosRegistrados++;
			
			/*Segundo contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Jose Manuel";
			Contactos[ContactosRegistrados].Telefono 		= "+51 221133";
			Contactos[ContactosRegistrados].Celular 		= "+51 987654321";
			Contactos[ContactosRegistrados].Email 			= "josemanuel@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "22/08/2000";
			ContactosRegistrados++;
			
			/*Tercer contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Pamela Grava";
			Contactos[ContactosRegistrados].Telefono 		= "+51 223311";
			Contactos[ContactosRegistrados].Celular 		= "+51 951874236";
			Contactos[ContactosRegistrados].Email 			= "pamelagrava@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "06/04/2002";
			ContactosRegistrados++;
			
			/*Cuarto contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Claudia Caliza";
			Contactos[ContactosRegistrados].Telefono 		= "+51 224433";
			Contactos[ContactosRegistrados].Celular 		= "+51 951632478";
			Contactos[ContactosRegistrados].Email 			= "claudiacaliza@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "10/07/2003";
			ContactosRegistrados++;
			break;
		case 2:
			return;
		case 3: 
			if (Salir() == 1)
				return;
		default:
			cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
			Detenerse();
			break;
	}
	
	return;
}

bool HayContactos(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador*/
	int c = 0;					/*Coincidencias*/
	
	/*Verifica si hay contactos disponibles*/
	for (; i < CANTIDAD; i++)
		if (Contactos[i].Nombre != " ")
			c++;
	
	if (c > 0)
		return false; //Est� vaci�
	
	return true;
}

void Detenerse(){
	cout << "\t�Presione una tecla para continuar!";
	system("PAUSE");								/*Pausar la aplicaci�n sin mensaje de salida*/
}

void LimpiarPantalla(){
	system("CLS");									/*Limpiar pantalla*/
}

void Dormir(int x){
	Sleep(x * 1000);							/*Dormir el programa*/
}

int Salir(){
	LimpiarPantalla();
	
	int x;
	
	// Obtener el ancho de la consola

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;
    	
    // titulo a centrar
    string titulo = "\x1B[1m�Est� seguro(a) de querer hacerlo?\x1B[0m";
    
	// Calcular el n�mero de espacios en blanco necesarios para centrar la palabra
	int espaciosEnBlanco = (consoleWidth - titulo.length()) / 2;
		
		
			
	/*Centinela general*/
	do {
		cout << Regla << endl;
		
		// Imprimir los espacios en blanco seguidos de la palabra centrada
	    for (int i = 0; i < espaciosEnBlanco; i++) {
	        cout << " ";
	    }		
		cout << titulo<< endl;
		cout << "\x1B[1m\t1. S�\x1B[0m\n\x1B[1m\t2. No \x1B[0m\n";
		cout << Regla << endl;
		cout << "\x1B[1m\tEsperando respuesta: \x1B[0m";
		cin >> x;
	} while(x < 1 || x > 2);
	
	cout << endl;
	
	return x;
}

