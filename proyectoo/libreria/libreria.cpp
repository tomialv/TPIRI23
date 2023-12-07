#include "libreria.h"
#include <sstream>

int contarClientes(const string& archivocliente) {
    ifstream archiCliente(archivocliente);
    string linea;
    int acum = 0;

    if (archiCliente.is_open()) {
        getline(archiCliente, linea); // Ignorar encabezado

        while (getline(archiCliente, linea)) {
            acum++;
        }
        return acum;
    } else {
        cout << "Error al abrir el archivo de clientes" << endl;
        return 0;
    }
    archiCliente.close();
}

int contarClases(const string& archivoclases) {
    ifstream archiClases(archivoclases);
    string linea;
    int acum=0;

    if(archiClases.is_open()) {
        getline(archiClases, linea); // ignoro encabezado

        while (getline(archiClases, linea)) {
            acum++;
        }
        return acum;
    } else {
            cout << "Error al abrir archivo de clases" << endl;
    }

}


//------------------------------LEER Y GUARDAR----------------------------------------------------

int LeerClientes(const string& archivocliente, Persona* clientes) {
    ifstream archiCliente(archivocliente);
    string linea;
    char delimitador= ',';

    if (archiCliente.is_open()) {
        getline(archiCliente, linea); // Ignorar encabezado
        int i=0;
        while (getline(archiCliente, linea)) {
            stringstream ss(linea);
            string campo;


            getline(ss,campo, delimitador);
            clientes[i].idCliente = stoi(campo); // uso stoi para transformar id de string a int


            // Leo los datos que son tipo string
            getline(ss, clientes[i].nombre, delimitador);
            getline(ss, clientes[i].apellido, delimitador);
            getline(ss, clientes[i].email, delimitador);
            getline(ss, clientes[i].telefono, delimitador);
            getline(ss, clientes[i].fechaNac, delimitador);

            getline(ss, campo, delimitador);
            clientes[i].estado = stof(campo); // uso stof para convertir a flotante el campo estado
            i++;

        }

        archiCliente.close();
        return 0;
    } else {
        cout << "Error al abrir el archivo clientes." << endl;
        return 1;
    }
}

int LeerClases(const string& archivoclase, Clases* clas){
    ifstream archiCla(archivoclase);
    string linea;
    char delimitador= ',';
    if (archiCla.is_open()) {
        getline(archiCla, linea); //ignoro encabezado
        int i=0;
        while (getline(archiCla, linea)){

            stringstream ss(linea);
            string campo;

            getline(ss,campo, delimitador);
            clas[i].idClase = stoi(campo); // uso stoi para transformar id de string a int

            getline(ss, campo, delimitador);
            clas[i].nombre = campo;

            getline(ss, campo, delimitador); // convierto horario a float.
            clas[i].horario = stof(campo);

            i++;
        }
        return 0;
    } else {
        cout << "error al abrir archivo";
        return 1;
    }
}

int leerAsistencia(const string&archivobinario, Asistencia*asis){

}


// --------------------------------------------------------------------------------------------------


//----------------------- FUNCIONES IMPRIMIR --------------------------------------------------------


void ImprimirClientes(Persona* clientes, int acum) {
    for (int i = 0; i < acum; ++i) {
        cout << "ID Cliente: " << clientes[i].idCliente << endl;
        cout << "Nombre: " << clientes[i].nombre << endl;
        cout << "Apellido: " << clientes[i].apellido << endl;
        cout << "Email: " << clientes[i].email << endl;
        cout << "Teléfono: " << clientes[i].telefono << endl;
        cout << "Fecha de Nacimiento: " << clientes[i].fechaNac << endl;
        cout << "Estado: " << clientes[i].estado << endl << endl;


    }
    cout << "el total de clientes es: " << acum << endl << endl;
}


//imprime el vector asistencias
void imprimirAsistencia(const Asistencia& asistencia) {
    cout << "ID Cliente: " << asistencia.idCliente << "\n";
    cout << "Cantidad de inscriptos: " << asistencia.cantInscriptos << "\n";
    for (int i = 0; i < asistencia.cantInscriptos; ++i) {
        cout << "Inscripcion " << i + 1 << ":\n";
        cout << "  - ID Curso: " << asistencia.CursosInscriptos[i].idCurso << "\n";
        cout << "  - Fecha de inscripcion: " << asctime(localtime(&asistencia.CursosInscriptos[i].fechaInscripcion));
    }
}

//-------------------------------------------------------------------------------------------

//verifica que la persona no este inscripta en la estrutura asistencias[]
bool clienterepetido(Persona* clientes, Clases* clas,Asistencia* Asistencias, Inscripcion* Inscrip, int indiceAleatorioclase, int indiceAleatoriocliente) {

    int tamano = sizeof(Asistencias) / sizeof(Asistencias[0]);

    for (int i = 0; i < tamano; i++)//tenemos que ver como sacamos esa cantidad de clientes en la estructura de asistencias
    {
        if (clientes[indiceAleatoriocliente].idCliente == Asistencias[i].idCliente &&
            clas[indiceAleatorioclase].idClase ==Asistencias[i].CursosInscriptos->idCurso) {//compara el id que se asigno con los id que se encuentra y tambien que la clase asignada coincida
            return true;
        }
    }
    return false;
}

void resize(Asistencia*& vector, int& tam) {
    tam++;
    Asistencia* aux = new Asistencia[tam];
    for (int i = 0; i < tam; i++)
    {
        aux[i] =vector[i];
    }
    delete[] vector;
    vector = aux;
}


//-----------------------------------------DUDAS--------------------------------------------------------------


//-----------METODO 1: HACER VECTOR AUXILIAR, VERIFICAR QUE ESE VECTOR CUMPLE LAS CONDICIONES Y GUARDAR----------

//Metodo para hacer reservas:  1) Hacer la reserva (generar idClase y un idCliente random) y guardarla en un vector auxiliar
//                                2) otra funcion: comparar ese vector auxiliar con la lista de asistencias (para ver si el cliente se repite)
//                              3) si pasa las verificaciones, agrego el auxiliar a la ultima posicion de asistencias.
/*
Asistencia GenerarReservaAleatoria(Clases* clas, int cantClases, Persona* clientes, int tamanio) {
    srand(time(0)); // Inicializar la semilla de rand() con el tiempo actual

    // Generar índices aleatorios para clases y clientes
    int indiceClase = rand() % cantClases; // Obtener un índice de clase aleatorio
    int indiceCliente = rand() % tamanio; // Obtener un índice de cliente aleatorio

    // Crear una estructura de Inscripcion para la reserva aleatoria
    Inscripcion nuevaInscripcion;
    nuevaInscripcion.idCurso = clas[indiceClase].idClase; // guardo el idClase generado aleatoriamente en la nueva estructura auxiliar
    nuevaInscripcion.fechaInscripcion = time(nullptr); // Obtener la fecha actual como la fecha de inscripción

    // Crear una estructura de Asistencia para la reserva generada
    Asistencia nuevaAsistencia;
    nuevaAsistencia.idCliente = clientes[indiceCliente].idCliente; // guardo el idCliente generado aleatoriamente
    nuevaAsistencia.cantInscriptos= //1? ; // --------------a que deberia ser igual???--------------
    nuevaAsistencia.CursosInscriptos = new Inscripcion[1]; // Reservar memoria para una única Inscripcion
    nuevaAsistencia.CursosInscriptos[0] = nuevaInscripcion; // Almacenar la inscripción en la reserva

    return nuevaAsistencia; //me devuelve todos los datos de una inscripción en esta estructura auxiliar "nuevaAsistencia"
}*/
//----------------------------------------------------------------------------------------------------------------
//METODO 2: ---------TODO EN UNA FUNCION-----------------
//Hace la reserva, verifica y guarda en el archivo binario
int agregar(const string& archivobinario, Persona* cliente, Clases* clases, int cantClases, int cantClientes, Asistencia*& Asistencias, Inscripcion*& Inscrip) {//---------------cantAsistencia va con & o con * ?---------------------------

    int i;
    int cupomaximo[7]={45, 25, 15, 40, 50, 30, 35};
    int cantAsis=0;

    ofstream bi(archivobinario, ios::binary);
    if (!bi) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Semilla para el generador de números aleatorios
    srand(time(nullptr));

    for (i = 0; i < cantClientes; i++)
    {
        int indiceAleatorioclase = rand() % cantClases;//indice aleatorio de clases, longitud debe ser la cantidad de clases
        int indiceAleatoriocliente = rand() % cantClientes;

        if(clienterepetido(cliente,clases,Asistencias,Inscrip, indiceAleatorioclase, indiceAleatoriocliente)==false &&
haycupo(clases, indiceAleatorioclase, indiceAleatoriocliente, cupomaximo)==true){//necesito que la funcion reciba los parametros bien pero no se como hacer sjhkajskd ayuda tomi
                resize(Asistencias, cantAsis);
                Asistencias[i].idCliente = indiceAleatoriocliente;
                bi.write((char*)&Asistencias[i].idCliente, sizeof(int));
                Asistencias[i].CursosInscriptos[i].idCurso =indiceAleatorioclase;
                bi.write((char*)Asistencias[i].CursosInscriptos[i].idCurso, sizeof(int));
                Asistencias[i].cantInscriptos++;
                //contarAsistencia()//actualizamos la cantidad de asistencia, va a ser la funcion que devuelve cantasistencias
        }
    }

    return 0;
}
/*
int cantAsistencia(Asistencia* asis){//---------------------como la hacemos???-------------------------------
    int cont = 0;
    for (int i = 0; i < sizeof(asis) / sizeof(asis[0]); i++) {
        cont++;
    }

    return cont;
}
*/
bool haycupo(Clases* clas, int indiceAleatorioclase, int indiceAleatoriocliente, int cupomaximo[7]) {
    if(clas[indiceAleatorioclase].idClase<=5){//spinning
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[1]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=6 && clas[indiceAleatorioclase].idClase<=11 ) {//yoga
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[2]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=12 && clas[indiceAleatorioclase].idClase<=17 ) {//pilates
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[3]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=18 && clas[indiceAleatorioclase].idClase<=23 ) {//streching
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[4]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=24 && clas[indiceAleatorioclase].idClase<=29 ) {//zumba
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[5]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=30 && clas[indiceAleatorioclase].idClase<=33 ) {//boxeo
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[6]){
                return false;
        }
    }
    if (clas[indiceAleatorioclase].idClase >=34 && clas[indiceAleatorioclase].idClase<=60 ) {//musculacion
        if(clas[indiceAleatorioclase].cupoactual>cupomaximo[7]){
                return false;
        }
    }

    return true;
}

Libreria::Libreria()
{

}




