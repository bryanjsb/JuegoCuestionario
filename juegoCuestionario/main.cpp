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

//mostrar

int main() {
    srand(time(NULL));
    menuPrincipal();
    return 0;
}

void bienvenida() {
    cout<<"Bienvenido al juego: Que tanto sabes de las partes del cuerpo?"<<endl;
    cout<<"Estudiante: Luiz Mendez"<<endl<<endl<<endl;
    system("pause");
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


    string opcion;
    cout<<"Desea ingresar otro jugador? S/N"<<endl;
    cin>>opcion;

    if(opcion == "s" || opcion == "S") {
        ingresarJugadores();
    }
}

void guardarJugadores(int noCedula, string nombre) {
    if(!validarJugador(noCedula)) {

        try {
            cout<<"-----Guardando informacion registro Jugadores-----"<<endl;
            //el ios::app  sirve para abrir un fichero de salida en modo añadir,
            //de manera que no borra el fichero actual y el cursor del fichero se pone después del último elemento.
            ofstream os("jugadores.txt", ios::out | ios::app);// Creando y abriendo archivo
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
            cerr << "ERROR :Algo paso con la escritura..." << endl;
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
            cerr << "ERROR :Algo paso con la escritura..." << endl;
        }
    }
}

bool validarJugador(int noCedula) {
    long double cedulas[100];

    try {
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
        cerr << "ERROR: Algo paso con la lectura..." << endl;
    }

    //comparando si existe la cedula en el registro
    for(int i = 0; i<100; i++) {
        if(cedulas[i]==noCedula) {
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

    try {
        if(!validarJugador(noCedula)) {
            throw(2);
        }
    } catch(int x) {
        cerr<<"EL JUGADOR YA EXISTE, TIPO DE ERROR: "<<x<<endl;
        obtenerCedula();
    }

    return noCedula;
}

void reporteJugadores() {
    system("cls");
    cout<<"Ingresando a reporte jugadores"<<endl;
    char linea[125];

    try {
        //cout << "------Cargando Informacion Jugadores------" << endl;
        ifstream is("jugadores.txt", ios::in);
        if (!is) {
            throw exception();
        } else {

            cout<<"Cedula-Nombre-Puntaje"<<endl;
            while(!is.eof()) {
                is.getline(linea, sizeof(linea));
                cout << linea << endl;

            }
            is.close();
        }
    } catch(...) {
        cout << "ERROR: Algo paso con la lectura... " << endl;
    }
    system("pause");
}

void listaMejoresJugadores() {
    system("cls");
    cout<<"Mostrando los 10 mejores jugadores"<<endl;
    char linea[125];
    char delimitador='-';
    string lectura;
    int cantidadLinea =0;
    try {
        //cout << "------Cargando Informacion Jugadores------" << endl;

        //conocer la cantidad de lineas
        ifstream s("jugadores.txt", ios::in);
        while(!s.eof()) {
            s.getline(linea, sizeof(linea));
            cantidadLinea++;
        }
        cout<<"cantidad de lineas: "<<cantidadLinea-1<<endl;
        s.close();

        ifstream is("jugadores.txt", ios::in);
        if (!is) {
            throw exception();
        } else {

            /*
                https://parzibyte.me/blog/2021/04/15/cpp-separar-cadena-delimitador/
                el primer while lee la linea, el segundo while separa la informacion
                segun el delimitador.
                usamos stringstream para convert un string a stream
                el getline leera la linea y separara los valores cuando aparezca el delimitador
            */


            string matriz[cantidadLinea-1][3];
            int contI=0;
            int contJ=0;

            //este ciclo lee linea por linea
            while(!is.eof()) {
                is.getline(linea, sizeof(linea));

                stringstream input_stringstream(linea);

                while(getline(input_stringstream, lectura, delimitador)) {
                    matriz[contI][contJ]=lectura;
                    contJ++;
                }
                contI++;
                contJ =0;
            }
            is.close();

            cout<<"Cedula       "<<"Nombre    "<<"Puntaje"<<endl;
            for(int i=0; i<cantidadLinea-1; i++) {
                for(int j=0; j<3; j++) {
                    cout<<setw(10)<<matriz[i][j] + "  ";
                }
                cout<<endl;
            }
            system("pause");

            //Una ves cargado el archivo debemos calcular los 10 mejores resultados


        }

    } catch(...) {
        cerr << "ERROR: Algo paso" << endl;
        system("pause");
    }




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







//borrar si no se usa
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

