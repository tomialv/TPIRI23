#include "libreria.h"
#include <libreria.cpp>
#include <iostream>
using namespace std;

void MostrarAsistencia(const Asistencia& asistencia) {
    std::cout << "ID Cliente: " << asistencia.idCliente << "\n";
    std::cout << "Cantidad de inscriptos: " << asistencia.cantInscriptos << "\n";
    for (uint i = 0; i < asistencia.cantInscriptos; ++i) {
        std::cout << "Inscripcion " << i + 1 << ":\n";
        std::cout << "  - ID Curso: " << asistencia.CursosInscriptos[i].idCurso << "\n";
        std::cout << "  - Fecha de inscripcion: " << asctime(localtime(&asistencia.CursosInscriptos[i].fechaInscripcion));
    }
}
int cantAsistencias=0;
enum cupoMax { spinning =45, yoga =25, pilates=15, stretching =40, zumba=50, boxeo=30};

Persona cargarpersona(Asistencia* Asistencias);
int agregar(const string& archivobinario, Persona* cliente, Clases* clases, int cantClases, int cantClientes, Asistencia* Asistencias, Inscripcion* Inscrip);

Asistencia GenerarReservaAleatoria(Clases* clas, int cantClases, Persona* clientes, int tamanio) {
    srand(time(0)); // Inicializar la semilla de rand() con el tiempo actual

    // Generar índices aleatorios para clases y clientes
    int indiceClase = rand() % cantClases; // Obtener un índice de clase aleatorio
    int indiceCliente = rand() % tamanio; // Obtener un índice de cliente aleatorio

    // Crear una estructura de Inscripcion para la reserva aleatoria
    Inscripcion nuevaInscripcion;
    nuevaInscripcion.idCurso = clas[indiceClase].idClase; // Obtener el ID de la clase
    nuevaInscripcion.fechaInscripcion = time(nullptr); // Obtener la fecha actual como la fecha de inscripción

    // Crear una estructura de Asistencia para la reserva generada
    Asistencia nuevaAsistencia;
    nuevaAsistencia.idCliente = clientes[indiceCliente].idCliente;
    nuevaAsistencia.cantInscriptos = 1; // Una única inscripción en esta reserva
    nuevaAsistencia.CursosInscriptos = new Inscripcion[1]; // Reservar memoria para una única Inscripcion
    nuevaAsistencia.CursosInscriptos[0] = nuevaInscripcion; // Almacenar la inscripción en la reserva

    return nuevaAsistencia;
}

void imprimirAsistencias(Asistencia* asistencias, int cantAsistencias) {
    for (int i = 0; i < cantAsistencias; ++i) {
        cout << "Asistencia " << i + 1 << ":" << endl;
        cout << "ID Cliente: " << asistencias[i].idCliente << endl;
        cout << "Cantidad de inscriptos: " << asistencias[i].cantInscriptos << endl;

        for (int j = 0; j < asistencias[i].cantInscriptos; ++j) {
            cout << "Inscripcion " << j + 1 << ":" << endl;
            cout << "ID Curso: " << asistencias[i].CursosInscriptos[j].idCurso << endl;

            // Convertir la fecha a un formato legible
            char fecha[50];
            strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", localtime(&asistencias[i].CursosInscriptos[j].fechaInscripcion));
            cout << "Fecha de inscripcion: " << fecha << endl;
        }

        cout << endl;
    }
}

int main() {
    string archivocliente= "/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/iriClientesGYM.csv";
    string archivoclases= "/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/iriClasesGYM.csv";
    string archivobinario= "/Users/tomialvarez/Downloads/Dataset TP-1/asistencias_1697673600000.dat";
    int tamanio = contarClientes(archivocliente);
    int cantclases = contarClases(archivoclases);

    Asistencia* Asistencias = new Asistencia[900];
    Inscripcion* Inscrip= new Inscripcion[900];
    Clases* clas= new Clases[cantclases]; //aplicar sizeof
    Persona* clientes = new Persona[tamanio]; //aplicar funcion contar clientes;



    // Generar una reserva aleatoria
    Asistencia nuevaReserva = GenerarReservaAleatoria(clas, cantclases, clientes, tamanio);
    MostrarAsistencia(nuevaReserva);
    // Escribir la reserva en el archivo binario
    ofstream archibinwr("asistencias_1697673600000.dat", ios::binary | ios::app); // Abre el archivo en modo append
    if (archibinwr.is_open()) {
        // Escribir la reserva en el archivo binario
        archibinwr.write((char*)&nuevaReserva.idCliente, sizeof(uint));
        archibinwr.write((char*)&nuevaReserva.cantInscriptos, sizeof(uint));
        archibinwr.write((char*)nuevaReserva.CursosInscriptos, sizeof(Inscripcion) * nuevaReserva.cantInscriptos);

        archibinwr.close();
    } else {
        cout << "No se pudo abrir el archivo binario." << endl;
    }




    LeerClientes(archivocliente, clientes);
    // leerBinario("/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/asistencias_1697673600000.dat", asistencias, cantAsistencias);
    LeerClases(archivoclases, clas);
      //  ImprimirClientes(clientes, tamanio);
        //imprimirAsistencias(Asistencias, cantAsistencias);

    //agregar(archivobinario, clientes, clas, cantclases, tamanio, Asistencias, Inscrip);
     cout << "Cargue un cliente" << endl;


    delete[] clientes;
    delete[] clas;
    delete[] Asistencias;


    return 0;
}


