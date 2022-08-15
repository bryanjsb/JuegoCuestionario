#include <iostream>
#include <sstream>
#include <ctime>
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
void guardarJugadores(int noCedula,string nombre);
void cargarJugadores();
bool validarJugador(int noCedula);

//Archivos - preguntas

//Juego
void jugador(string *nombre, int *cedula, int numero);
void jugar();
string preguntas[25][3];
void cargarPreguntas();
//int listaNumeroAleatorios[25];
int preguntaAleatoria();
string obtenerPregunta(int item);
bool evaluaRespuesta(int item, string respuesta);
void mostrarResultados(string *nombre1, string *nombre2,int resultado1,int resultado2);



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
        cerr << "ERROR: Algo paso con la lectura... " << endl;
    }
    system("pause");
}

void listaMejoresJugadores() {
    system("cls");
    cout<<"Mostrando los 10 mejores jugadores"<<endl<<endl;
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
        //cout<<"cantidad de lineas: "<<cantidadLinea-1<<endl;
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

            /*Una ves cargado el archivo debemos calcular los 10 mejores resultados */
            string mejores10[10][3];
            int posicion = 0;
            int aux = 0;
            int numero =0;
            for(int i=0; i<10; i++) {

                for(int j=0; j<cantidadLinea-1; j++) {
                    numero = stoi(matriz[j][2]);
                    if(numero>aux) {
                        aux = numero;
                        posicion=j;
                    }

                }

                for(int j=0; j<3; j++) {
                    mejores10[i][j]=matriz[posicion][j];
                }

                matriz[posicion][2]="0";
                aux = 0;
            }


            cout<<"Cedula       "<<"Nombre    "<<"Puntaje"<<endl;
            for(int i=0; i<10; i++) {
                for(int j=0; j<3; j++) {
                    cout<<setw(10)<<mejores10[i][j] + "  ";
                }
                cout<<endl;
            }
            system("pause");
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
    system("cls");


    cout<<"Jugar"<<endl;
    //jugador 1
    string nombreJugador1="";
    int cedulaJugador1=0;
    int asiertosJugador1=0;

    //jugador 2
    string nombreJugador2="";
    int cedulaJugador2=0;
    int asiertosJugador2=0;

    //Reglas del juego
    int turno = 1;
    int item=0;
    string respuesta="";
    string continuarJuego="";
    //obtener informacion jugadores
    jugador(&nombreJugador1,&cedulaJugador1,1);
    jugador(&nombreJugador2,&cedulaJugador2,2);

    cargarPreguntas();

    do {
        system("cls");
        item = preguntaAleatoria();
        cout<<"Turno: "<<turno<<" de  10"<<endl;
        cout<<setw(10)<<"Jugador#1----------> Asiertos: "<<asiertosJugador1<<endl<<endl;

        cout<<obtenerPregunta(item)<<endl;
        cin>>respuesta;

        if(evaluaRespuesta(item, respuesta)) {
            asiertosJugador1+=100;
            item = preguntaAleatoria();
            cout<<"Respuesta Correcta"<<endl;
        } else {
            cout<<"Respuesta Inorrecta"<<endl;
        }

        cout<<setw(10)<<"Jugador#2----------> Asiertos: "<<asiertosJugador2<<endl<<endl;
        cout<<obtenerPregunta(item)<<endl;
        cin>>respuesta;
        if(evaluaRespuesta(item, respuesta)) {
            asiertosJugador2+=100;
            cout<<"Respuesta Correcta"<<endl;
        } else {
            cout<<"Respuesta Inorrecta"<<endl;
        }

        cout<<"Desean salir del juego?S/N"<<endl;
        cin>>continuarJuego;

        if(continuarJuego =="s"||continuarJuego=="S") {
            mostrarResultados(&nombreJugador1, &nombreJugador2, asiertosJugador1, asiertosJugador2);
            break;
        }

        turno++;

    } while(turno <=10);

    if(turno==10) {
        mostrarResultados(&nombreJugador1, &nombreJugador2, asiertosJugador1, asiertosJugador2);
    }
}


void jugador(string *nombre,int *cedula, int numero) {
    int opcion=0;

    try {
        cout<<"Ingrese el numero de cedula del jugador "<<numero<<endl;
        cin>>*cedula;

        if(!(*cedula>=100000000 && *cedula<=999999999)) {
            throw(1);
        }

        if(validarJugador(*cedula)) {
            throw('3');
        }

    } catch(int x) {
        cerr<<"ERROR EL NUMERO DE CEDULA ES INCORRECTO,  TIPO DE ERROR: "<<x<<endl;
        jugador(nombre,cedula,numero);
    } catch(char x) {
        cerr<<"ERROR EL JUGADOR NO SE ENCUENTRA REGISTRADO, TIPO DE ERROR: "<<x<<endl;
        cout<<"1. Ir a menu principal?"<<endl;
        cout<<"2. Intentar de nuevo"<<endl;

        cin>>opcion;
        if(opcion == 1) {
            menuPrincipal();
        } else if(opcion ==2) {
            jugador(nombre,cedula,numero);
        }
    }



}

void cargarPreguntas() {

    system("cls");

    char linea[255];
    char delimitador='-';
    string lectura;

    try {

        ifstream is("preguntas.txt", ios::in);
        if (!is) {
            throw exception();
        } else {
            int contI=0;
            int contJ=0;

            while(!is.eof()) {
                is.getline(linea, sizeof(linea));

                stringstream input_stringstream(linea);

                while(getline(input_stringstream, lectura, delimitador)) {
                    preguntas[contI][contJ]=lectura;
                    contJ++;
                }
                contI++;
                contJ =0;
            }
            is.close();

            /*
            cout<<"Mostrando preguntas"<<endl;
            cout<<"Item       "<<"Respuesta    "<<"Definicion"<<endl;
            for(int i=0; i<25; i++) {
                for(int j=0; j<3; j++) {
                    cout<<setw(10)<<preguntas[i][j] + "  ";
                }
                cout<<endl;
            }
            */
            system("pause");

            //Una ves cargado el archivo debemos calcular los 10 mejores resultados


        }

    } catch(...) {
        cerr << "ERROR: Algo paso" << endl;
        system("pause");
    }

}

int preguntaAleatoria() {

    int numero=0;
    numero = 1 + rand()%25;

    /*
    creamos un vector para que guarde los numeros que ya sean utiizado, esto para que
    no se repitan las preguntas.

    for(int i=0; i<25;i++){
        if(listaNumeroAleatorios[i]==numero){
            return preguntaAleatoria();
        }else{
            listaNumeroAleatorios[i]=numero;
        }
    }
     */

    return numero;
}

string obtenerPregunta(int item) {
    return preguntas[item-1][2];
}

bool evaluaRespuesta(int item, string respuesta) {
    return preguntas[item-1][1] == respuesta;
}

void mostrarResultados(string *nombre1, string *nombre2,int resultado1,int resultado2) {
    cout<<"Mostrado resultados"<<endl;
    if(resultado1 == resultado2) {
        cout<<"El jugador 1:"<<*nombre1<<" y el jugador 2: "<<*nombre2<<" empatados"<<endl;
        cout<<"Total de asiertos jugador 1: "<<resultado1<<endl;
        cout<<"Total de asiertos jugador 2: "<<resultado2<<endl;
    } else if(resultado1>resultado2) {
        cout<<"El jugador 1:"<<*nombre1<<" es el ganador"<<endl;
        cout<<"Total de asiertos jugador 1: "<<resultado1<<endl;
        cout<<"Total de asiertos jugador 2: "<<resultado2<<endl;
    } else {
        cout<<"El jugador 2:"<<*nombre2<<" es el ganador"<<endl;
        cout<<"Total de asiertos jugador 1: "<<resultado1<<endl;
        cout<<"Total de asiertos jugador 2: "<<resultado2<<endl;
    }
    system("pause");
}


