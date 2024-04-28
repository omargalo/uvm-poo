#include <iostream>
#include <string>

// Clase base
class Persona {
protected:
    std::string nombreCompleto;
    int edad;
    std::string email;

public:
    Persona(const std::string& nombreCompleto, int edad, const std::string& email)
        : nombreCompleto(nombreCompleto), edad(edad), email(email) {}
    // Método virtual puro para hacer la clase abstracta
    virtual void registro() = 0;
};

// Clase derivada: Cliente
class Cliente : public Persona {
private:
    int numeroCliente;
    std::string nombreCliente;
    std::string emailCliente;

public:
    Cliente(const std::string& nombreCompleto, int edad, const std::string& email,
        int numeroCliente, const std::string& nombreCliente, const std::string& emailCliente)
        : Persona(nombreCompleto, edad, email), numeroCliente(numeroCliente),
        nombreCliente(nombreCliente), emailCliente(emailCliente) {}

    void registro() override {
        std::cout << "Datos del Cliente:\n";
        std::cout << "Nombre Completo: " << nombreCompleto << "\n";
        std::cout << "Edad: " << edad << "\n";
        std::cout << "Email: " << emailCliente << "\n";
        std::cout << "Numero de Cliente: " << numeroCliente << "\n";
        std::cout << "Nombre Cliente: " << nombreCliente << "\n\n";
    }
};

// Clase derivada: Empleado
class Empleado : public Persona {
private:
    int numeroEmpleado;
    std::string nombreEmpleado;
    std::string puesto;

public:
    Empleado(const std::string& nombreCompleto, int edad, const std::string& email,
        int numeroEmpleado, const std::string& nombreEmpleado, const std::string& puesto)
        : Persona(nombreCompleto, edad, email), numeroEmpleado(numeroEmpleado),
        nombreEmpleado(nombreEmpleado), puesto(puesto) {}

    void registro() override {
        std::cout << "Datos del Empleado:\n";
        std::cout << "Nombre Completo: " << nombreCompleto << "\n";
        std::cout << "Edad: " << edad << "\n";
        std::cout << "Email: " << email << "\n";
        std::cout << "Numero de Empleado: " << numeroEmpleado << "\n";
        std::cout << "Nombre Empleado: " << nombreEmpleado << "\n";
        std::cout << "Puesto: " << puesto << "\n\n";
    }
};

int main() {
    // Solicitar datos del cliente
    std::string nombreCompletoC, emailC, nombreCliente;
    int edadC, numeroCliente;
    std::cout << "Ingrese los datos del cliente:\n";
    std::cout << "Nombre completo: ";
    std::getline(std::cin, nombreCompletoC);
    std::cout << "Edad: ";
    std::cin >> edadC;
    std::cin.ignore();
    std::cout << "Email: ";
    std::getline(std::cin, emailC);
    std::cout << "Numero de cliente: ";
    std::cin >> numeroCliente;
    std::cin.ignore();
    std::cout << "Nombre cliente: ";
    std::getline(std::cin, nombreCliente);
    Cliente cliente(nombreCompletoC, edadC, emailC, numeroCliente, nombreCliente, emailC);
    cliente.registro();

    // Solicitar datos del empleado
    std::string nombreCompletoE, emailE, nombreEmpleado, puesto;
    int edadE, numeroEmpleado;
    std::cout << "Ingrese los datos del empleado:\n";
    std::cout << "Nombre completo: ";
    std::getline(std::cin, nombreCompletoE);
    std::cout << "Edad: ";
    std::cin >> edadE;
    std::cin.ignore();
    std::cout << "Email: ";
    std::getline(std::cin, emailE);
    std::cout << "Numero de empleado: ";
    std::cin >> numeroEmpleado;
    std::cin.ignore();
    std::cout << "Nombre empleado: ";
    std::getline(std::cin, nombreEmpleado);
    std::cout << "Puesto: ";
    std::getline(std::cin, puesto);
    Empleado empleado(nombreCompletoE, edadE, emailE, numeroEmpleado, nombreEmpleado, puesto);
    empleado.registro();

    // Finalizar programa
    std::cout << "Presione Enter para salir...";
    std::cin.get();

    return 0;
}
