#include <iostream>
#include <string>
using namespace std;

// Definición de la clase Persona
class Persona {
public:
    string nombre;
    int edad;
    char sexo;

    // Constructor
    Persona(string n, int e, char s) : nombre(n), edad(e), sexo(s) {}
};

// Función para imprimir los datos de una persona
void imprimir(Persona persona_imp) {
    cout << "Nombre: " << persona_imp.nombre << endl;
    cout << "Edad: " << persona_imp.edad << endl;
    cout << "Sexo: " << persona_imp.sexo << endl;
}

int main() {
    string nombre;
    int edad;
    char sexo;

    cout << "Ingrese nombre: ";
    cin >> nombre;
    cout << "Ingrese edad: ";
    cin >> edad;
    cout << "Ingrese sexo (M/F): ";
    cin >> sexo;

    Persona persona_imp(nombre, edad, sexo);
    imprimir(persona_imp);

    // Limpia el buffer de entrada y espera a que el usuario presione Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Presiona Enter para salir...";
    string dummy;
    getline(cin, dummy);

    return 0;
}
