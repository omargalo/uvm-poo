#include <iostream>
#include <string>
#include <list>

using namespace std;

class Profesor;
class Materia;

class Alumno {
public:
    string nombre;
    string apellido;
    int noControl;
    int edad;
    char sexo;
    int semestre;
    list<Materia*> materias;

    Alumno() {
        cout << "Clase Alumno lista. Metodos listos para agregar funcionalidad." << endl;
    }

    Alumno(const string& nombre, const string& apellido, int noControl, int edad, char sexo, int semestre)
        : nombre(nombre), apellido(apellido), noControl(noControl), edad(edad), sexo(sexo), semestre(semestre) {
        cout << "Clase Alumno instanciada con datos. Metodos listos para agregar funcionalidad." << endl;
    }

    void registrarAlumno() {}
    void eliminarAlumno() {}
    void agregarMateria(Materia* materia) {}
    void eliminarMateria(Materia* materia) {}
};

class Profesor {
public:
    string nombre;
    string apellido;
    char sexo;
    int edad;
    string titulo;
    string cedulaProfesional;

    Profesor() {
        cout << "Clase Profesor lista. Metodos listos para agregar funcionalidad." << endl;
    }

    Profesor(const string& nombre, const string& apellido, const char sexo, int edad, const string& titulo, const string& cedula)
        : nombre(nombre), apellido(apellido), sexo(sexo), edad(edad), titulo(titulo), cedulaProfesional(cedula) {
        cout << "Clase Profesor instanciada con datos. Metodos listos para agregar funcionalidad." << endl;
    }

    void Contratar() {}
    void Despedir() {}
};

class Materia {
public:
    string nombre;
    int numeroCreditos;
    Profesor* profesor;

    Materia() {
        cout << "Clase Materia lista. Metodos listos para agregar funcionalidad." << endl;
    }

    Materia(const string& nombre, int creditos, Profesor* profesor = nullptr)
        : nombre(nombre), numeroCreditos(creditos), profesor(profesor) {
        cout << "Clase Materia instanciada con datos. Metodos listos para agregar funcionalidad." << endl;
    }

    void AsignarProfesor(Profesor* p) {
        profesor = p;
    }

    void Eliminar() {}
};

int main() {
    Alumno alumno;
    Materia materia;
    Profesor profesor;

	cout << "Press Enter to exit the application" << endl;
    cin.get();

    return 0;
}
