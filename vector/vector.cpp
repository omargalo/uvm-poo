#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

class Materia;
class Profesor;

// IDs únicos para cada tipo de objeto
inline int nextAlumnoId = 1;
inline int nextProfesorId = 1;
inline int nextMateriaId = 1;

class Alumno {
public:
    int id;
    string nombre;
    string apellido;
    int noControl;
    int edad;
    char sexo;
    int semestre;
    list<Materia*> materias;

    Alumno() : Alumno("", "", 0, 0, ' ', 0) {
        cout << "Alumno default registrado." << endl;
    }

    Alumno(string nombre, string apellido, int noControl, int edad, char sexo, int semestre)
        : id(nextAlumnoId++), nombre(move(nombre)), apellido(move(apellido)), noControl(noControl), edad(edad), sexo(sexo), semestre(semestre) {
        cout << "Alumno " << id << " registrado." << endl;
    }
};

class Profesor {
public:
    int id;
    string nombre;
    string apellido;
    char sexo;
    int edad;
    string titulo;
    string cedulaProfesional;

    Profesor() : Profesor("", "", ' ', 0, "", "") {
        cout << "Profesor default registrado." << endl;
    }

    Profesor(string nombre, string apellido, char sexo, int edad, string titulo, string cedula)
        : id(nextProfesorId++), nombre(move(nombre)), apellido(move(apellido)), sexo(sexo), edad(edad), titulo(move(titulo)), cedulaProfesional(move(cedula)) {
        cout << "Profesor " << id << " registrado." << endl;
    }
};

class Materia {
public:
    int id;
    string nombre;
    int numeroCreditos;
    Profesor* profesor;

    Materia() : Materia("", 0, nullptr) {
        cout << "Materia default registrada." << endl;
    }

    Materia(string nombre, int creditos, Profesor* profesor = nullptr)
        : id(nextMateriaId++), nombre(move(nombre)), numeroCreditos(creditos), profesor(profesor) {
        cout << "Materia " << id << " registrada." << endl;
    }
};

void capturarDatos(const string& mensaje, string& destino) {
    cout << mensaje;
    getline(cin, destino);
}

template<typename T>
void capturarDatos(const string& mensaje, T& destino) {
    cout << mensaje;
    cin >> destino;
    cin.ignore();
}

void capturarProfesor(map<int, Profesor>& profesores) {
    string nombre, apellido, titulo, cedula;
    char sexo;
    int edad;

    capturarDatos("Introduzca el nombre del profesor: ", nombre);
    capturarDatos("Introduzca el apellido del profesor: ", apellido);
    capturarDatos("Introduzca el sexo del profesor (M/F): ", sexo);
    capturarDatos("Introduzca la edad del profesor: ", edad);
    capturarDatos("Introduzca el titulo del profesor: ", titulo);
    capturarDatos("Introduzca la cedula profesional del profesor: ", cedula);

    profesores.emplace(piecewise_construct, forward_as_tuple(nextProfesorId), forward_as_tuple(nombre, apellido, sexo, edad, titulo, cedula));
}

void capturarMateria(map<int, Materia>& materias, map<int, Profesor>& profesores) {
    string nombre;
    int creditos, profesorId;

    capturarDatos("Introduzca el nombre de la materia: ", nombre);
    capturarDatos("Introduzca los creditos de la materia: ", creditos);
    capturarDatos("Introduzca el ID del profesor asignado a la materia: ", profesorId);

    Profesor* profesor = profesores.find(profesorId) != profesores.end() ? &profesores[profesorId] : nullptr;
    materias.emplace(piecewise_construct, forward_as_tuple(nextMateriaId), forward_as_tuple(nombre, creditos, profesor));
}

void capturarAlumno(map<int, Alumno>& alumnos) {
    string nombre, apellido;
    int noControl, edad, semestre;
    char sexo;

    capturarDatos("Introduzca el nombre del alumno: ", nombre);
    capturarDatos("Introduzca el apellido del alumno: ", apellido);
    capturarDatos("Introduzca el numero de control del alumno: ", noControl);
    capturarDatos("Introduzca la edad del alumno: ", edad);
    capturarDatos("Introduzca el sexo del alumno (M/F): ", sexo);
    capturarDatos("Introduzca el semestre del alumno: ", semestre);

    alumnos.emplace(piecewise_construct, forward_as_tuple(nextAlumnoId), forward_as_tuple(nombre, apellido, noControl, edad, sexo, semestre));
}

int main() {
    map<int, Alumno> alumnos;
    map<int, Profesor> profesores;
    map<int, Materia> materias;

    for (int i = 0; i < 2; ++i) {
        capturarProfesor(profesores);
    }

    for (int i = 0; i < 3; ++i) {
        capturarMateria(materias, profesores);
    }

    for (int i = 0; i < 2; ++i) {
        capturarAlumno(alumnos);
    }

    return 0;
}
