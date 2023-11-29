#include "libreria.h"
#include <sstream>


void leerBinario(const char* nombreArchivo, Asistencia*& asistencias, int& cantAsistencias) {
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    archivo.read((char*)&cantAsistencias, sizeof(int));

    asistencias = new Asistencia[cantAsistencias];

    for (int i = 0; i < cantAsistencias; ++i) {
        archivo.read((char*)&asistencias[i].idCliente, sizeof(int));
        archivo.read((char*)&asistencias[i].cantInscriptos, sizeof(int));

        asistencias[i].CursosInscriptos = new Inscripcion[asistencias[i].cantInscriptos];

        for (int j = 0; j < asistencias[i].cantInscriptos; ++j) {
            archivo.read((char*)&asistencias[i].CursosInscriptos[j].idCurso, sizeof(int));
            archivo.read((char*)&asistencias[i].CursosInscriptos[j].fechaInscripcion, sizeof(time_t));
        }
    }

    archivo.close();
}




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
        cout << "Error al abrir el archivo." << endl;
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
            cout << "Error al abrir archivo" << endl;
    }

}

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
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
}

    int LeerClases(const string& archivoclase, Clases* clas){
        ifstream archiCla(archivoclase);
        string linea;
        char delimitador= ',';
        if (archiCla.is_open()) {
            getline(archiCla, linea); //leo encabezado
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


int agregar(const string& archivobinario, Persona* cliente, Clases* clases, int cantClases, int cantClientes, Asistencia* Asistencias, Inscripcion* Inscrip) {

    int i;
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

        if(clienterepetido(Persona* clientes,Clases* clas,Asistencia* Asistencias, Inscripcion* Inscrip, indiceAleatorioclase, indiceAleatoriocliente)==false){//necesito que la funcion reciba los parametros bien pero no se como hacer sjhkajskd ayuda tomi
                Asistencias[i].idCliente = cliente[indiceAleatoriocliente].idCliente;
                bi.write((char*)&Asistencias[i].idCliente, sizeof(int));
                Asistencias[i].CursosInscriptos->idCurso = clases[indiceAleatorioclase].idClase;
                bi.write((char*)Asistencias[i].CursosInscriptos->idCurso, sizeof(int));
        }
    }

    return 0;
}


bool clienterepetido(Persona* clientes, Clases* clas,Asistencia* Asistencias, Inscripcion* Inscrip, indiceAleatorioclase, indiceAleatoriocliente) {
    for (int i = 0; i < /*cant clientes en asistencias*/; i++)//tenemos que ver como sacamos esa cantidad de clientes en la estructura de asistencias
    {
        if (clientes[indiceAleatoriocliente].idCliente == Asistencias[i].idCliente && clas[indiceAleatorioclase]->idClase ==Asistencias[i].CursosInscriptos->idCurso) {//compara el id que se asigno con los id que se encuentra y tambien que la clase asignada coincida
                return true;
        }
    }
    return false;
}

void resize(string*& vector, int& tam) {
    tam++;
    string* aux = new string[tam];
    for (int i = 0; i < tam; i++)
    {
        *(aux + i) = *(vector + i);
    }
    delete[] vector;
    vector = aux;
}

Libreria::Libreria()
{

}




