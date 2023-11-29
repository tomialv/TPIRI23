#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <string.h>
#include "libreria_global.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Persona{
    int idCliente;
    string nombre;
    string apellido;
    string email;
    string telefono;
    string fechaNac;
    float estado;
};

struct Clases {
    int idClase;
    string nombre;
    float horario;
};

struct Inscripcion {//-------como funciona??-------------
    uint idCurso;
    time_t fechaInscripcion;
};

struct Asistencia {
    uint idCliente;
    uint cantInscriptos;//en la posicion que esta idcurso, es la cantidad de personas que hay ahi
    Inscripcion* CursosInscriptos;
};

int LeerClientes(const string& archivocliente, Persona* clientes);
int contarClientes(const string& archivocliente);
int contarClases(const string& archivoclases);
int agregar(const string& archivobinario, Persona* cliente, Clases* clases, int cantClases, int cantClientes, Asistencia* Asistencias, Inscripcion* Inscrip,int& cantAsistencia);
int LeerClases(const string& archivoclase, Clases* clas);
bool clienterepetido(Persona* clientes, Clases* clas,Asistencia* Asistencias, Inscripcion* Inscrip, int indiceAleatorioclase, int indiceAleatoriocliente);
void resize(string*& vector, int& tam);

void ImprimirClientes(Persona* clientes, int acum);
void imprimirAsistencia(const Asistencia& asistencia);

class LIBRERIA_EXPORT Libreria
{
public:
    Libreria();
};

#endif // LIBRERIA_H


/*
// no entendemos como funciona la cantidad de inscriptos
Asistencias[1].idcliente
    Asistencias[1].cantInscriptos
            Asistencias[1].CursosInscriptos[1].idcurso
            Asistencias[1].CursosInscriptos[1].fechainscripcion



*/

enum cupoMax { spinning =45, yoga =25, pilates=15, stretching =40, zumba=50, boxeo=30};

