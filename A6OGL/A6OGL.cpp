#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

// Declaración adelantada: permite referenciar las clases antes de su definición completa.
class Materia;
class Profesor;

// Variables estáticas para mantener un contador único de IDs para cada tipo de objeto.
static int nextAlumnoId = 1;
static int nextProfesorId = 1;
static int nextMateriaId = 1;

// Definición de la clase Alumno.
class Alumno {
public:
    int id; // ID único del alumno.
    string nombre;
    string apellido;
    int noControl;
    int edad;
    char sexo;
    int semestre;
    // Lista de materias en las que está inscrito el alumno.
    list<Materia*> materias;

    // Constructor por defecto para crear un alumno con valores iniciales.
    Alumno() : id(nextAlumnoId++), nombre(""), apellido(""), noControl(0), edad(0), sexo(' '), semestre(0) {
        cout << "Alumno default registrado." << endl;
    }

    // Constructor con parámetros para inicializar un alumno con datos específicos.
    Alumno(const string& nombre, const string& apellido, int noControl, int edad, char sexo, int semestre)
        : id(nextAlumnoId++), nombre(nombre), apellido(apellido), noControl(noControl), edad(edad), sexo(sexo), semestre(semestre) {
        cout << "Alumno " << id << " registrado." << endl;
    }
};

// Definición de la clase Profesor.
class Profesor {
public:
    int id; // ID único del profesor.
    string nombre;
    string apellido;
    char sexo;
    int edad;
    string titulo;
    string cedulaProfesional;

    // Constructor por defecto para crear un profesor con valores iniciales.
    Profesor() : id(nextProfesorId++), nombre(""), apellido(""), sexo(' '), edad(0), titulo(""), cedulaProfesional("") {
        cout << "Profesor default registrado." << endl;
    }

    // Constructor con parámetros para inicializar un profesor con datos específicos.
    Profesor(const string& nombre, const string& apellido, char sexo, int edad, const string& titulo, const string& cedula)
        : id(nextProfesorId++), nombre(nombre), apellido(apellido), sexo(sexo), edad(edad), titulo(titulo), cedulaProfesional(cedula) {
        cout << "Profesor " << id << " registrado." << endl;
    }
};

// Definición de la clase Materia.
class Materia {
public:
    int id; // ID único de la materia.
    string nombre;
    int numeroCreditos;
    // Puntero al profesor que imparte la materia.
    Profesor* profesor;

    // Constructor por defecto para crear una materia con valores iniciales.
    Materia() : id(nextMateriaId++), nombre(""), numeroCreditos(0), profesor(nullptr) {
        cout << "Materia default registrada." << endl;
    }

    // Constructor con parámetros para inicializar una materia con datos específicos.
    Materia(const string& nombre, int creditos, Profesor* profesor = nullptr)
        : id(nextMateriaId++), nombre(nombre), numeroCreditos(creditos), profesor(profesor) {
        cout << "Materia " << id << " registrada." << endl;
    }
};

// Funciones para capturar información de los objetos desde la consola.
// Cada función solicita datos específicos al usuario y utiliza estos
// datos para crear y almacenar los objetos en mapas.
void capturarProfesor(map<int, Profesor>& profesores) {
    string nombre, apellido, titulo, cedula;
    char sexo;
    int edad;

    // Solicita datos del profesor y los captura usando cin.
    // Crea un objeto Profesor y lo almacena en un mapa usando un ID único.
    cout << "Introduzca el nombre del profesor: ";
    getline(cin, nombre);
    cout << "Introduzca el apellido del profesor: ";
    getline(cin, apellido);
    cout << "Introduzca el sexo del profesor (M/F): ";
    cin >> sexo;
    cin.ignore(); // Ignora el '\n' restante en el buffer después de cin
    cout << "Introduzca la edad del profesor: ";
    cin >> edad;
    cin.ignore(); // Limpiar buffer
    cout << "Introduzca el titulo del profesor: ";
    getline(cin, titulo);
    cout << "Introduzca la cedula profesional del profesor: ";
    getline(cin, cedula);
    // Instanciar un nuevo objeto Profesor en el mapa usando un ID único.
    profesores.emplace(piecewise_construct, forward_as_tuple(nextProfesorId), forward_as_tuple(nombre, apellido, sexo, edad, titulo, cedula));
}

void capturarMateria(map<int, Materia>& materias, map<int, Profesor>& profesores) {
    string nombre;
    int creditos, profesorId;

    // Solicita datos de la materia y captura relaciones con profesores.
    // Crea un objeto Materia y lo almacena en un mapa,
    // asociando a un profesor existente.
    cout << "Introduzca el nombre de la materia: ";
    getline(cin, nombre);
    cout << "Introduzca los creditos de la materia: ";
    cin >> creditos;
    cout << "Introduzca el ID del profesor asignado a la materia: ";
    cin >> profesorId;
    cin.ignore(); // Limpiar buffer
    // Buscar el profesor en el mapa de profesores y asignarlo a la materia.
    Profesor* profesor = profesores.find(profesorId) != profesores.end() ? &profesores[profesorId] : nullptr;
    materias.emplace(piecewise_construct, forward_as_tuple(nextMateriaId), forward_as_tuple(nombre, creditos, profesor));
}

void capturarAlumno(map<int, Alumno>& alumnos) {
    string nombre, apellido;
    int noControl, edad, semestre;
    char sexo;

    // Solicita datos del alumno y los captura usando cin.
    // Crea un objeto Alumno y lo almacena en un mapa usando un ID único.
    cout << "Introduzca el nombre del alumno: ";
    getline(cin, nombre);
    cout << "Introduzca el apellido del alumno: ";
    getline(cin, apellido);
    cout << "Introduzca el numero de control del alumno: ";
    cin >> noControl;
    cout << "Introduzca la edad del alumno: ";
    cin >> edad;
    cout << "Introduzca el sexo del alumno (M/F): ";
    cin >> sexo;
    cin.ignore(); // Limpiar buffer
    cout << "Introduzca el semestre del alumno: ";
    cin >> semestre;
    cin.ignore(); // Limpiar buffer al final
    // Instanciar un nuevo objeto Alumno en el mapa usando un ID único.
    alumnos.emplace(piecewise_construct, forward_as_tuple(nextAlumnoId), forward_as_tuple(nombre, apellido, noControl, edad, sexo, semestre));
}

// Función para mostrar información de los objetos almacenados en los mapas.
void mostrarInformacion(map<int, Alumno>& alumnos, map<int, Profesor>& profesores, map<int, Materia>& materias) {
    int opcion, id;
    cout << "Desea visualizar:\n1. Profesor\n2. Materia\n3. Alumno\n";
    cin >> opcion;
    cout << "Ingrese el ID del registro: ";
    cin >> id;

    // Mostrar información del objeto seleccionado según la opción y el ID.
    switch (opcion) {
    case 1:
        if (profesores.find(id) != profesores.end()) { // Verifica si el ID existe en el mapa de profesores.
            Profesor& p = profesores[id];
            cout << "Nombre: " << p.nombre << ", Apellido: " << p.apellido << ", Edad: " << p.edad << ", Titulo: " << p.titulo << endl;
        }
        else {
            cout << "Profesor no encontrado." << endl;
        }
        break;
    case 2:
        if (materias.find(id) != materias.end()) { // Verifica si el ID existe en el mapa de materias.
            Materia& m = materias[id];
            cout << "Nombre: " << m.nombre << ", Creditos: " << m.numeroCreditos << ", Profesor: " << (m.profesor ? m.profesor->nombre : "Sin asignar") << endl;
        }
        else {
            cout << "Materia no encontrada." << endl;
        }
        break;
    case 3:
        if (alumnos.find(id) != alumnos.end()) { // Verifica si el ID existe en el mapa de alumnos.
            Alumno& a = alumnos[id];
            cout << "Nombre: " << a.nombre << ", Apellido: " << a.apellido << ", Edad: " << a.edad << ", Semestre: " << a.semestre << endl;
        }
        else {
            cout << "Alumno no encontrado." << endl;
        }
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}

// Función principal que orquesta la creación y manejo de objetos.
int main() {
    map<int, Alumno> alumnos;
    map<int, Profesor> profesores;
    map<int, Materia> materias;

    // Captura de 2 Profesores
    for (int i = 0; i < 2; ++i) {
        capturarProfesor(profesores);
    }

    // Captura de 3 Materias
    for (int i = 0; i < 3; ++i) {
        capturarMateria(materias, profesores);
    }

    // Captura de 2 Alumnos
    for (int i = 0; i < 2; ++i) {
        capturarAlumno(alumnos);
    }

    // Función para mostrar información
    mostrarInformacion(alumnos, profesores, materias);

    // Limpia el buffer de entrada y espera a que el usuario presione Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Presiona Enter para salir...";
    string dummy;
    getline(cin, dummy);

    return 0;
}
