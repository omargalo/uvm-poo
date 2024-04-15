#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// M_PI es una constante que representa el valor de π (pi), y es
// comúnmente usada para cálculos matemáticos relacionados con
// círculos y otras formas geométricas.
#ifndef M_PI
// Define M_PI como una aproximación de pi, si no está definido.
#define M_PI 3.14159265358979323846
#endif


// Sobrecarga de funciones para calcular el área de diferentes figuras
double area(double lado) {
    // Área del cuadrado
    return lado * lado;
}

double area(double base, double altura) {
    //Área del triángulo
    return base * altura / 2;
}

double area(double radio, char) {
    // Área del círculo
    return M_PI * radio * radio;
}

double area(double baseMenor, double baseMayor, double altura) {
    // Área del trapecio
    return (baseMenor + baseMayor) * altura / 2;
}

int main() {
    int opcion;
    cout << "Menu para calcular areas:" << endl;
    cout << "1. Cuadrado" << endl;
    cout << "2. Triangulo" << endl;
    cout << "3. Circulo" << endl;
    cout << "4. Trapecio" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
        double lado;
        cout << "Ingrese el lado del cuadrado: ";
        cin >> lado;
        cout << "Area del cuadrado: " << area(lado) << endl;
        break;
    }
    case 2: {
        double base, altura;
        cout << "Ingrese la base y la altura del triangulo: ";
        cin >> base >> altura;
        cout << "Area del triangulo: " << area(base, altura) << endl;
        break;
    }
    case 3: {
        double radio;
        cout << "Ingrese el radio del circulo: ";
        cin >> radio;
        cout << "Area del circulo: " << area(radio, 'c') << endl;
        break;
    }
    case 4: {
        double baseMenor, baseMayor, altura;
        cout << "Ingrese la base menor, la base mayor y la altura del trapecio: ";
        cin >> baseMenor >> baseMayor >> altura;
        cout << "Area del trapecio: " << area(baseMenor, baseMayor, altura) << endl;
        break;
    }
    default:
        cout << "Opcion no valida" << endl;
    }

    // Limpia el buffer de entrada y espera a que el usuario presione Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Presiona Enter para salir...";
    string dummy;
    getline(cin, dummy);

    return 0;
}
