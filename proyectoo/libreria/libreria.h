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
    int cupoactual=0;
    string nombre;
    float horario;
};

struct Inscripcion {//-------como debemos usarla?-------------
    uint idCurso;
    time_t fechaInscripcion;
};

struct Asistencia {
    uint idCliente;
    uint cantInscriptos;//en la posicion que esta idCliente, es la cantidad de personas que hay ahi? de donde sacamos ese dato?
    Inscripcion* CursosInscriptos;
};

int LeerClientes(const string& archivocliente, Persona* clientes);
int contarClientes(const string& archivocliente);
int contarClases(const string& archivoclases);
int agregar(const string& archivobinario, Persona* cliente, Clases* clases, int cantClases, int cantClientes, Asistencia*& Asistencias, Inscripcion*& Inscrip);
int LeerClases(const string& archivoclase, Clases* clas);
bool clienterepetido(Persona* clientes, Clases* clas,Asistencia* Asistencias, Inscripcion* Inscrip, int indiceAleatorioclase, int indiceAleatoriocliente);
void resize(string*& vector, int& tam);
bool haycupo(Clases* clas, int indiceAleatorioclase, int indiceAleatoriocliente, int cupomaximo[7]);
int leerAsistencia(const string&archivobinario, Asistencia*asis);

void ImprimirClientes(Persona* clientes, int acum);
void imprimirAsistencia(const Asistencia& asistencia);

class LIBRERIA_EXPORT Libreria
{
public:
    Libreria();
};

#endif // LIBRERIA_H


/*
// no entendemos como funciona la cantidad de inscriptos.... va variando en cada posicion de Asistencia?
y tampoco entendemos la propia estructura de inscripción, CursosInscriptos, que deberiamos meter ahi?

Lo entendemos asi..por ejemplo la reserva 1 sería:
Asistencias[1].idcliente
    Asistencias[1].cantInscriptos
            Asistencias[1].CursosInscriptos[1].idcurso
            Asistencias[1].CursosInscriptos[1].fechainscripcion


Esto va a ir variando en cada reserva para Asistencias[1][2][3], etc...


Hablando de las reservas.., tenemos dudas de que método deberiamos usar para crearlas. En libreria.cpp detallamos las dudas
*/


