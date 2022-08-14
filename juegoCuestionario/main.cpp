#include <iostream>
#include<sstream>
#include<ctime>
#include <conio.h>
#include <iomanip>

using namespace std;


//Menu
void bienvenida();
void menuPrincipal();
void ingresarJugadores();
void reporteJugadores();
void listaMejoresJugadores();
void salirPrograma();

//Archivos

//Juego
void jugar();

//

int main() {
    srand(time(NULL));
    menuPrincipal();

    return 0;
}

void bienvenida() {
    cout<<"Bienvenido al juego: Que tanto sabes de las partes del cuerpo?"<<endl;
    cout<<"Estudiante: Luiz Mendez"<<endl<<endl<<endl;
}

void menuPrincipal() {
    bienvenida();

    int opcion = 0;

    do {

        cout<<"Seleccionar(Ingrese el numero de la opcion a elegir) "<<endl;
        cout<<"1. Ingresar jugadores"<<endl;
        cout<<"2. Jugar ---> Que tanto sabes de las partes del cuerpo?"<<endl;
        cout<<"3. Reporte de jugadores"<<endl;
        cout<<"4. Los 10 mejores jugadores"<<endl;
        cout<<"5. Salir del programa"<<endl;
        cin>>opcion;

        switch(opcion) {
        default: {
            cout<<"Valor incorrecto, vuelva a intertarlo"<<endl;
            menuPrincipal();
        }
        break;

        case 1: {
            ingresarJugadores();
        }
        break;
        case 2: {
            jugar();
        }
        break;
        case 3: {
            reporteJugadores();
        }
        break;
        case 4: {
            listaMejoresJugadores();
        }
        break;
        case 5: {
            salirPrograma();
        }
        break;


        }

    } while(opcion != 5);
}

void ingresarJugadores() {
    cout<<"Ingresando a Ingresar  Jugadores"<<endl;
}
void reporteJugadores() {
    cout<<"Ingresando a reporte jugadores"<<endl;
}
void listaMejoresJugadores() {
    cout<<"Mostrando los 10 mejores jugadores"<<endl;
}
void salirPrograma() {
    string opcion;
    cout<<"Saliendo el programa ---> Que tanto sabes de las partes del cuerpo?"<<endl;
    cout<<"Desea guardar? S/N"<<endl;
    cin>>opcion;

    //opcion = toupper(opcion);
    if(opcion == "s" || opcion == "S") {
        cout<<"Guardando Juego"<<endl;
    }
}
void jugar() {
    cout<<"Jugar"<<endl;
}

