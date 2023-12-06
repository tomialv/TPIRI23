#include "libreria.h"
#include <libreria.cpp>
#include <iostream>
using namespace std;

int main() {
    int cupomaximo[7]={45, 25, 15, 40, 50, 30, 35};
    string archivocliente= "/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/iriClientesGYM.csv";
    string archivoclases= "/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/iriClasesGYM.csv";
    string archivobinario= "/Users/tomialvarez/Desktop/Tp IRI 2023/Dataset TP/asistencias_1697673600000.dat";
    int tamanio = contarClientes(archivocliente);
    int cantclases = contarClases(archivoclases);
    //int cantAsistencias=cantAsistencias();//----------------¿como contamos cantidad de asistencias?--------------------
    int cantAsis=0;

    Asistencia* Asistencias = new Asistencia[cantAsis];//?
    Inscripcion* Inscrip= new Inscripcion[tamanio];//-------¿Que tamaño?-¿Tambien cantAsistencias?--------------
    Clases* clas= new Clases[cantclases];
    Persona* clientes = new Persona[tamanio];


    LeerClientes(archivocliente, clientes);//leo clientes y los guardo en clientes{}
    LeerClases(archivoclases, clas);//leo clases y los guardo en su clas{}
    //como seguimos?
    agregar(archivobinario, clientes, clas, cantclases, tamanio, Asistencias, Inscrip);
    //aca deberia ir las funciones para generar reserva nueva, verificarla y agregarla como una nueva asistencias[].



    //Por ultimo, escribir toda la lista de asistencias[] en el binario

    //--------------LIBERO ESPACIO DE MEMORIA RESERVADA-------------------------------
    delete[] clientes;
    delete[] clas;
    delete[] Asistencias;
    delete[] Inscrip;

    return 0;
}


