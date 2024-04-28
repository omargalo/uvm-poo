#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

// Forward declarations necesarias
class Profesor;
class Materia;
class Alumno;

// Clase abstracta Persona
class Persona {
protected:
    string nombreCompleto;
    int edad;
    string email;

public:
    Persona(const string& nombreCompleto, int edad, const string& email)
        : nombreCompleto(nombreCompleto), edad(edad), email(email) {}

    virtual void registro() = 0;

    string getNombreCompleto() const {
        return nombreCompleto;
    }
};

// Definición completa de la clase Profesor
class Profesor : public Persona {
private:
    int empleadoId;
    list<Materia*> materias;

public:
    Profesor(const string& nombreCompleto, int edad, const string& email, int empleadoId)
        : Persona(nombreCompleto, edad, email), empleadoId(empleadoId) {}

    void registro() override {
        cout << "Profesor registrado: " << nombreCompleto << endl;
    }

    void asignarMateria(Materia* materia);
    void listarMaterias();
};

// Definición completa de la clase Materia
class Materia {
private:
    int materiaId;
    string nombreMateria;
    Profesor* profesor;

public:
    Materia(int materiaId, const string& nombreMateria)
        : materiaId(materiaId), nombreMateria(nombreMateria), profesor(nullptr) {}

    void asignarProfesor(Profesor* prof) {
        profesor = prof;
        prof->asignarMateria(this);
    }

    void registro() {
        cout << "Materia registrada: " << nombreMateria << endl;
    }

    string getNombreMateria() const {
        return nombreMateria;
    }
};

// Definición completa de la clase Alumno
class Alumno : public Persona {
private:
    int matricula;
    list<Materia*> materias;

public:
    Alumno(const string& nombreCompleto, int edad, const string& email, int matricula)
        : Persona(nombreCompleto, edad, email), matricula(matricula) {}

    void registro() override {
        cout << "Alumno registrado: " << nombreCompleto << endl;
    }

    void asignarMateria(Materia* materia) {
        materias.push_back(materia);
    }

    void listarMaterias();
};

// Implementación de funciones de Profesor y Alumno
void Profesor::asignarMateria(Materia* materia) {
    materias.push_back(materia);
}

void Profesor::listarMaterias() {
    cout << "Materias enseñadas por " << nombreCompleto << ":" << endl;
    for (auto& materia : materias) {
        cout << materia->getNombreMateria() << endl;
    }
}

void Alumno::listarMaterias() {
    cout << "Materias inscritas por " << nombreCompleto << ":" << endl;
    for (auto& materia : materias) {
        cout << materia->getNombreMateria() << endl;
    }
}
// Prototipos de funciones
void capturarProfesor(map<int, Profesor*>& profesores) {
    string nombre, email;
    int edad, empleadoId;

    cout << "Ingrese nombre completo del profesor: ";
    getline(cin, nombre);
    cout << "Ingrese email del profesor: ";
    getline(cin, email);
    cout << "Ingrese edad del profesor: ";
    cin >> edad;
    cout << "Ingrese ID de empleado del profesor: ";
    cin >> empleadoId;
    cin.ignore(); // Limpiar el buffer después de la entrada.

    Profesor* profesor = new Profesor(nombre, edad, email, empleadoId);
    profesores[empleadoId] = profesor;
    profesor->registro();
}

void capturarMateria(map<int, Materia*>& materias, map<int, Profesor*>& profesores) {
    string nombre;
    int materiaId, profesorId;

    cout << "Ingrese ID de la materia: ";
    cin >> materiaId;
    cout << "Ingrese nombre de la materia: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese ID del profesor para esta materia: ";
    cin >> profesorId;
    cin.ignore();

    Materia* materia = new Materia(materiaId, nombre);
    if (profesores.count(profesorId) > 0) {
        materia->asignarProfesor(profesores[profesorId]);
    }
    materias[materiaId] = materia;
    materia->registro();
}

void capturarAlumno(map<int, Alumno*>& alumnos) {
    string nombre, email;
    int edad, matricula;

    cout << "Ingrese nombre completo del alumno: ";
    getline(cin, nombre);
    cout << "Ingrese email del alumno: ";
    getline(cin, email);
    cout << "Ingrese edad del alumno: ";
    cin >> edad;
    cout << "Ingrese matricula del alumno: ";
    cin >> matricula;
    cin.ignore();

    Alumno* alumno = new Alumno(nombre, edad, email, matricula);
    alumnos[matricula] = alumno;
    alumno->registro();
}

void asignarMateriasAAlumnos(map<int, Alumno*>& alumnos, map<int, Materia*>& materias) {
    for (auto& [matricula, alumno] : alumnos) {
        cout << "Asignando materias a " << alumno->getNombreCompleto() << endl;
        int count = 0;
        for (auto& [materiaId, materia] : materias) {
            if (count < 2) { // Asigna solo dos materias a cada alumno
                alumno->asignarMateria(materia);
                count++;
            }
        }
        alumno->listarMaterias();
    }
}

int main() {
    map<int, Profesor*> profesores;
    map<int, Materia*> materias;
    map<int, Alumno*> alumnos;

    // Captura de Profesores, Materias y Alumnos
    for (int i = 0; i < 3; i++) {
        capturarProfesor(profesores);
    }

    for (int i = 0; i < 4; i++) {
        capturarMateria(materias, profesores);
    }

    for (int i = 0; i < 3; i++) {
        capturarAlumno(alumnos);
    }

    asignarMateriasAAlumnos(alumnos, materias);

    // Limpieza de memoria
    for (auto& [key, prof] : profesores) delete prof;
    for (auto& [key, mat] : materias) delete mat;
    for (auto& [key, alu] : alumnos) delete alu;

    return 0;
}
