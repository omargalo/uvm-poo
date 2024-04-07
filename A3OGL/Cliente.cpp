#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Cliente {
private:
    int idCliente;
    string nombre;
    string apellidoPaterno;
    string email;
    string telefonoMovil;
    float saldo;

public:
    Cliente(int idCliente, const string& nombre, const string& apellidoPaterno, const string& email, const string& telefonoMovil, float saldo) {
        if (to_string(idCliente).length() != 4) {
            throw invalid_argument("El ID del cliente debe tener 4 digitos.");
        }
        if (nombre.length() > 20) {
            throw invalid_argument("El nombre debe tener maximo 20 caracteres.");
        }
        if (apellidoPaterno.length() > 20) {
            throw invalid_argument("El apellido paterno debe tener maximo 20 caracteres.");
        }
        if (email.find('@') == string::npos) {
            throw invalid_argument("El email debe contener el simbolo '@'.");
        }
        if (telefonoMovil.length() != 10 || !all_of(telefonoMovil.begin(), telefonoMovil.end(), ::isdigit)) {
            throw invalid_argument("El telefono movil debe tener 10 digitos.");
        }

        this->idCliente = idCliente;
        this->nombre = nombre;
        this->apellidoPaterno = apellidoPaterno;
        this->email = email;
        this->telefonoMovil = telefonoMovil;
        this->saldo = saldo;
    }

    int getIdCliente() const {
        return idCliente;
    }

    void mostrarInformacion() const {
        cout << "ID Cliente: " << idCliente << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido Paterno: " << apellidoPaterno << endl;
        cout << "Email: " << email << endl;
        cout << "Telefono Movil: " << telefonoMovil << endl;
        cout << "Saldo: " << saldo << endl;
    }

    void actualizarSaldo() {}
    void eliminarCuenta() {}
};

int main() {
    Cliente* clientes[3]{};
    int idCliente;
    string nombre, apellidoPaterno, email, telefonoMovil;
    float saldo;

    for (int i = 0; i < 3; i++) {
        try {
            cout << "Registro del cliente " << i + 1 << endl;
            cout << "ID Cliente (4 digitos): ";
            while (!(cin >> idCliente)) {
                cout << "Entrada invalida. Por favor, ingrese un numero de 4 digitos: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Nombre: ";
            getline(cin, nombre);

            cout << "Apellido Paterno: ";
            getline(cin, apellidoPaterno);

            cout << "Email: ";
            getline(cin, email);

            cout << "Telefono Movil: ";
            getline(cin, telefonoMovil);

            cout << "Saldo: ";
            while (!(cin >> saldo)) {
                cout << "Entrada invalida. Por favor, ingrese un numero valido para el saldo: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            clientes[i] = new Cliente(idCliente, nombre, apellidoPaterno, email, telefonoMovil, saldo);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            i--;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int opcion = 0;
    do {
        cout << "\nMenu de opciones:" << endl;
        cout << "1. Mostrar informacion de un cliente" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese el ID del cliente a buscar: ";
            cin >> idCliente;
            bool encontrado = false;
            for (int i = 0; i < 3; i++) {
                if (clientes[i]->getIdCliente() == idCliente) {
                    clientes[i]->mostrarInformacion();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Cliente no encontrado." << endl;
            }
        }
    } while (opcion != 2);

    for (int i = 0; i < 3; i++) {
        delete clientes[i];
    }

    return 0;
}


