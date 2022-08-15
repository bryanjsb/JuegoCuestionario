#include <iostream>
#include<sstream>
#include<ctime>
#include <conio.h>
#include <iomanip>
#include <cctype>
#include <fstream>

using namespace std;

//Menu
void bienvenida();
void menuPrincipal();
void ingresarJugadores();
int obtenerCedula();
void reporteJugadores();
void listaMejoresJugadores();
void salirPrograma();

//Archivos - jugadores
void guardarJugadores(int noCedula, string nombre);
void cargarJugadores();
bool validarJugador(int noCedula);

//Archivos - preguntas

//Juego
void jugar();

//validaciones
bool validarCedula(int cedula);
int obtenerEntero(istream &linea);
double obtenerFlotante(istream &linea);
string obtenerHilera(istream &linea);

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
        system("cls");

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
    int noCedula;
    string nombre;
    cout<<"Registrarse"<<endl;

    noCedula = obtenerCedula();

    cout<<"Nombre jugador: ";
    cin>> nombre;
    cout<<endl;

    guardarJugadores(noCedula,nombre);

}

void guardarJugadores(int noCedula, string nombre) {
    if(!validarJugador(noCedula)){

    try {
        cout<<"-----Guardando informacion registro Jugadores-----"<<endl;
        //el ios::app  sirve para abrir un fichero de salida en modo añadir,
        //de manera que no borra el fichero actual y el cursor del fichero se pone después del último elemento.
        ofstream os("jugadoresPrueba.txt", ios::out | ios::app);// Creando y abriendo archivo
        if (!os) {
            throw exception();
        } else {
            os<<noCedula;
            os<<"-";
            os<<nombre;
            os<<"-0"<<endl;
            os.close();
        }
    } catch(...) {
        cout << "ERROR :Algo paso con la escritura..." << endl;
    }

    try {
        ofstream os("registroCedulaJugador.txt", ios::out | ios::app);
        if (!os) {
            throw exception();
        } else {
            os<<noCedula<<endl;
            os.close();
        }
    } catch(...) {
        cout << "ERROR :Algo paso con la escritura..." << endl;
    }
    }
}

bool validarJugador(int noCedula) {
    long double cedulas[100];

    try {
        //cout << "------Cargando Informacion Jugadores------" << endl;

        ifstream is("registroCedulaJugador.txt", ios::in);
        if (!is) {
            throw exception();
        } else {
            int i=0;
            int cedula;
            is >> cedula;
            while(!is.eof()) {
                cedulas[i] = cedula;
                i++;
                is >> cedula;
            }
            is.close();
        }
    } catch(...) {
        cout << "ERROR: Algo paso " << endl;
    }

    //comparando si existe la cedula en el registro
    for(int i = 0; i<100;i++){
        if(cedulas[i]==noCedula){
            return false;
        }
    }
    return true;

}

int obtenerCedula() {
    //https://ccia.ugr.es/~jfv/ed1/c/cdrom/cap2/cap24.htm
    // unsigned elimina numero negativos
    // long int tengo mayor rango
    long double noCedula;

    try {
        cout<<"Numero de cedula: ";
        cin>>noCedula;
        cout<<endl;

        if(!(noCedula>=100000000 && noCedula<=999999999)) {
            throw(1);
        }

    } catch(int x) {
        cerr<<"ERROR EL NUMERO DE CEDULA ES INCORRECTO,  TIPO DE ERROR: "<<x<<endl;
        obtenerCedula();
    }

    try{
        if(!validarJugador(noCedula)){
            throw(2);
        }
    }catch(int x){
        cerr<<"EL JUGADOR YA EXISTE, TIPO DE ERROR: "<<x<<endl;
        obtenerCedula();
    }

    return noCedula;
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























int obtenerEntero(istream &linea) {
    string s = obtenerHilera(linea);
    stringstream r(s);
    int n;
    if (!(r >> n)) {
        throw -1;
    }
    return n;
}

double obtenerFlotante(istream &linea) {
    string s = obtenerHilera(linea);
    stringstream r(s);
    double x;
    if (!(r >> x)) {
        throw -1;
    }
    return x;
}

string obtenerHilera(istream &linea) {
    string r;
    getline(linea, r, '\t');
    return r;
}

