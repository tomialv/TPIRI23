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

struct Inscripcion {
    uint idCurso;
    time_t fechaInscripcion;
};

struct Asistencia {
    uint idCliente;
    uint cantInscriptos;
    Inscripcion* CursosInscriptos;
};
Persona cargarpersona(Asistencia* Asistencias);
int LeerClientes(const string& archivocliente, Persona* clientes);
int contarClientes(const string& archivocliente);
int contarClases(const string& archivoclases);

void cupomaximo ();


class LIBRERIA_EXPORT Libreria
{
public:
    Libreria();
};

#endif // LIBRERIA_H
