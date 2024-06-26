#include <iostream>
#include <string>
#include <list>
#include <map>
#include <limits>

using namespace std;

// Declaraciones adelantadas de clases
class Profesor;
class Materia;
class Alumno;

// Clase abstracta Persona
class Persona {
protected:
    string nombreCompleto;
    int edad;
    string email;

// Constructor protegido para evitar instanciar objetos Persona
public:
    Persona(const string& nombreCompleto, int edad, const string& email)
        : nombreCompleto(nombreCompleto), edad(edad), email(email) {}

    // M�todo virtual puro
    virtual void registro() = 0;

	// M�todos de acceso
    string getNombreCompleto() const {
        return nombreCompleto;
    }
    string getEmail() const {
        return email;
    }
    int getEdad() const {
        return edad;
    }
};

// Herencia de la clase Persona
class Profesor : public Persona {
private:
    int empleadoId;
    list<Materia*> materias;

// Constructor de la clase Profesor
public:
    Profesor(const string& nombreCompleto, int edad, const string& email, int empleadoId)
        : Persona(nombreCompleto, edad, email), empleadoId(empleadoId) {}

	// M�todo virtual puro
    void registro() override {
        cout << "Profesor registrado: " << nombreCompleto << endl;
    }

    void asignarMateria(Materia* materia);
    void listarMaterias();
};

// Definici�n completa de la clase Materia
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
    Profesor* getProfesor() const {
        return profesor;
    }
};

// Herencia de la clase Persona
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

// Implementaci�n de funciones de Profesor y Alumno
void Profesor::asignarMateria(Materia* materia) {
    materias.push_back(materia);
}

void Profesor::listarMaterias() {
    cout << "Materias impartidas por " << nombreCompleto << ":" << endl;
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
    cin.ignore(); // Limpiar el buffer despu�s de la entrada.

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
            // Asigna solo dos materias a cada alumno
            if (count < 2) {
                alumno->asignarMateria(materia);
                count++;
            }
        }
        alumno->listarMaterias();
    }
}

void mostrarProfesor(const map<int, Profesor*>& profesores, int id) {
    auto it = profesores.find(id);
    if (it != profesores.end()) {
        Profesor* prof = it->second;
        cout << "Profesor ID: " << id << ", Nombre: " << prof->getNombreCompleto()
            << ", Email: " << prof->getEmail() << ", Edad: " << prof->getEdad() << endl;
        prof->listarMaterias();
    }
    else {
        cout << "Profesor no encontrado." << endl;
    }
}

void mostrarMateria(const map<int, Materia*>& materias, int id) {
    auto it = materias.find(id);
    if (it != materias.end()) {
        Materia* mat = it->second;
        Profesor* prof = mat->getProfesor();
        cout << "Materia ID: " << id << ", Nombre: " << mat->getNombreMateria()
            << ", Profesor: " << (prof ? prof->getNombreCompleto() : "Sin asignar") << endl;
    }
    else {
        cout << "Materia no encontrada." << endl;
    }
}

void mostrarAlumno(const map<int, Alumno*>& alumnos, int id) {
    auto it = alumnos.find(id);
    if (it != alumnos.end()) {
        Alumno* alu = it->second;
        cout << "Alumno ID: " << id << ", Nombre: " << alu->getNombreCompleto()
            << ", Email: " << alu->getEmail() << ", Edad: " << alu->getEdad() << endl;
        alu->listarMaterias();
    }
    else {
        cout << "Alumno no encontrado." << endl;
    }
}

void mostrarMenu(const map<int, Profesor*>& profesores, const map<int, Materia*>& materias, const map<int, Alumno*>& alumnos) {
    int opcion, id;
    do {
        cout << "\nMenu:\n1. Profesor\n2. Materia\n3. Alumno\n9. Salir\nSeleccione una opcion: ";
        cin >> opcion;

        if (opcion == 9) break;

        cout << "Ingrese el ID del registro: ";
        cin >> id;

        switch (opcion) {
        case 1:
            mostrarProfesor(profesores, id);
            break;
        case 2:
            mostrarMateria(materias, id);
            break;
        case 3:
            mostrarAlumno(alumnos, id);
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (opcion != 9);
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

    // Mostrar el men�
    mostrarMenu(profesores, materias, alumnos);

    // Limpieza de memoria
    for (auto& [key, prof] : profesores) delete prof;
    for (auto& [key, mat] : materias) delete mat;
    for (auto& [key, alu] : alumnos) delete alu;

    return 0;
}
