#include <iostream> // Libreria para entrada y salida de datos (como 'cout' y 'cin')
#include <vector>   // Libreria para usar el contenedor 'vector' (un arreglo dinamico)
#include <string>   // Libreria para usar el tipo de dato 'string' (cadenas de texto)
#include <stdexcept>// Libreria para usar excepciones, que nos ayudan a manejar errores
#include <limits>   // Libreria para manipular los limites de tipos de datos, util para limpiar 'cin'

// --- 1. Estructura de Datos (Representacion de la Cuenta) ---
// Una 'struct' (estructura) es como una plantilla para crear un tipo de dato complejo.
// Agrupa varias variables bajo un mismo nombre.
struct Cuenta {
    int id; // El ID de la cuenta (numero de identificacion)
    std::string nombre_titular; // El nombre de la persona dueña de la cuenta
    double saldo; // El dinero que tiene la cuenta
};

// --- 2. Base de Datos Simulada (Vector de Cuentas) ---
// Usamos un 'vector' (similar a un arreglo) para guardar todas las cuentas.
// Inicializamos el vector con tres cuentas de ejemplo (datos quemados o 'hardcoded').
std::vector<Cuenta> cuentas = {
    {1001, "Ana Garcia", 1500.50},    // Cuenta 1: ID 1001, saldo inicial $1500.50
    {1002, "Luis Perez", 450.00},     // Cuenta 2: ID 1002, saldo inicial $450.00
    {1003, "Sofia Martinez", 12000.75} // Cuenta 3: ID 1003, saldo inicial $12000.75
};

// Puntero para la cuenta que esta usando el cajero actualmente.
// Un 'puntero' guarda la direccion de memoria de una variable.
// 'nullptr' significa que no apunta a nada todavia.
Cuenta* cuenta_actual = nullptr;

// --- Funciones Auxiliares ---

/**
 * @brief Busca una cuenta en el vector usando su ID.
 * @param id El ID que queremos encontrar.
 * @return Un puntero a la cuenta encontrada o nullptr si no existe.
 */
Cuenta* buscarCuentaPorId(int id) {
    // Un bucle 'for' para recorrer (iterar) todo el vector 'cuentas'.
    for (size_t i = 0; i < cuentas.size(); ++i) {
        // Estructura de seleccion 'if': Si el ID de la cuenta actual es igual al ID buscado...
        if (cuentas[i].id == id) {
            // Devuelve la direccion de memoria (puntero) de la cuenta encontrada.
            return &cuentas[i];
        }
    }
    // Si el bucle termina y no se encontro la cuenta, devuelve nullptr.
    return nullptr;
}

/**
 * @brief Lee un monto (cantidad de dinero) y valida que sea positivo y numerico.
 * @return El valor doble (monto) leido y validado.
 */
double obtenerMontoValido() {
    double monto;
    // Bucle 'while' que se repite hasta que la entrada sea correcta.
    // std::cin >> monto: Intenta leer un numero. Devuelve 'false' si falla (ej. si se escribe texto).
    // || monto <= 0: O si el monto leido es cero o negativo.
    while (!(std::cin >> monto) || monto <= 0) {
        
        // --- Manejo de errores de entrada ---
        
        // 1. Limpia los 'flags' de error de std::cin (dice 'ya, reiniciamos la lectura').
        std::cin.clear(); 
        
        // 2. Ignora todo lo que este en el buffer de entrada hasta encontrar un salto de linea.
        // Esto previene que el bucle se repita infinitamente.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Muestra un mensaje de error al usuario.
        std::cout << "Error: Monto invalido. Por favor, ingrese una cantidad numerica positiva: ";
    }
    // Si el bucle termina, el monto es valido y lo devolvemos.
    return monto;
}

// --- 3. Funciones de Operaciones Basicas ---

/**
 * @brief Muestra el saldo actual de la cuenta logueada.
 */
void consultarSaldo() {
    std::cout << "\nOperacion: Consulta de Saldo\n";
    std::cout << "----------------------------------\n";
    // Usamos el puntero 'cuenta_actual' para acceder a sus propiedades (->).
    std::cout << "Titular: " << cuenta_actual->nombre_titular << "\n";
    std::cout << "ID Cuenta: " << cuenta_actual->id << "\n";
    std::cout << "Saldo Actual: $" << cuenta_actual->saldo << "\n";
    std::cout << "----------------------------------\n";
}

/**
 * @brief Permite al usuario retirar dinero de su cuenta.
 */
void realizarRetiro() {
    // Bloque 'try-catch': Intentamos hacer algo y si hay un error, lo 'atrapamos' (catch).
    try {
        std::cout << "\nOperacion: Retiro\n";
        std::cout << "Saldo disponible: $" << cuenta_actual->saldo << "\n";
        std::cout << "Ingrese el monto a retirar: ";
        
        double monto = obtenerMontoValido(); // Reutilizacion de codigo

        // Validacion: Si el monto solicitado es mayor al saldo que tiene la cuenta...
        if (monto > cuenta_actual->saldo) {
            // Lanzamos una 'excepcion' (error) indicando saldo insuficiente.
            throw std::runtime_error("Saldo insuficiente para realizar este retiro.");
        }
        
        // Si hay saldo, actualizamos el saldo restando el monto.
        cuenta_actual->saldo -= monto;
        
        std::cout << "\nRetiro exitoso de $" << monto << ".\n";
        consultarSaldo(); // Reutilizacion de codigo
        
    } catch (const std::runtime_error& e) {
        // El bloque 'catch' atrapa el error lanzado en el 'try'.
        // e.what() contiene el mensaje que pasamos a la excepcion.
        std::cout << "\nERROR: " << e.what() << "\n";
    }
}

/**
 * @brief Permite al usuario depositar dinero en su cuenta.
 */
void realizarDeposito() {
    std::cout << "\nOperacion: Deposito\n";
    std::cout << "Ingrese el monto a depositar: ";
    
    double monto = obtenerMontoValido(); // Reutilizacion de codigo

    // Actualizamos el saldo sumando el monto.
    cuenta_actual->saldo += monto;
    
    std::cout << "\nDeposito exitoso de $" << monto << ".\n";
    consultarSaldo(); // Reutilizacion de codigo
}

/**
 * @brief Permite transferir dinero de la cuenta actual a otra cuenta.
 */
void realizarTransferencia() {
    try {
        std::cout << "\nOperacion: Transferencia\n";
        std::cout << "Ingrese el ID de la cuenta destino: ";
        int id_destino;
        
        // Bucle para asegurar que el ID de destino sea un numero valido.
        while (!(std::cin >> id_destino)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: ID invalido. Por favor, ingrese un numero entero: ";
        }

        // Buscamos la cuenta destino con la funcion auxiliar.
        Cuenta* cuenta_destino = buscarCuentaPorId(id_destino);

        // Validacion: Si la cuenta destino no existe (es nullptr)...
        if (cuenta_destino == nullptr) {
            throw std::runtime_error("Cuenta destino no encontrada.");
        }
        
        // Validacion: Si la cuenta destino es la misma que la cuenta actual...
        if (cuenta_destino->id == cuenta_actual->id) {
            throw std::runtime_error("No se puede transferir a la misma cuenta.");
        }

        std::cout << "Ingrese el monto a transferir: ";
        double monto = obtenerMontoValido(); // Reutilizacion de codigo

        // Validacion: Si el saldo de la cuenta origen es insuficiente...
        if (monto > cuenta_actual->saldo) {
            throw std::runtime_error("Saldo insuficiente para realizar la transferencia.");
        }

        // --- Logica de la Transferencia ---
        // 1. Restamos el monto de la cuenta origen (la actual).
        cuenta_actual->saldo -= monto;
        // 2. Sumamos el monto a la cuenta destino.
        cuenta_destino->saldo += monto;

        std::cout << "\nTransferencia de $" << monto << " a la cuenta " << cuenta_destino->nombre_titular << " exitosa.\n";
        consultarSaldo(); // Reutilizacion de codigo
        
    } catch (const std::runtime_error& e) {
        std::cout << "\nERROR: " << e.what() << "\n";
    }
}

// --- Funcion Principal del Menu ---

/**
 * @brief Muestra el menu de opciones y maneja la seleccion del usuario.
 */
void mostrarMenu() {
    int opcion;
    // Bucle 'do-while': Ejecuta el codigo una vez (do) y luego repite mientras la condicion sea verdadera (while).
    do {
        std::cout << "\n\n=== CAJERO AUTOMATICO SIMULADO ===\n";
        std::cout << "Usuario: " << cuenta_actual->nombre_titular << " (ID: " << cuenta_actual->id << ")\n";
        std::cout << "1. Consultar Saldo\n";
        std::cout << "2. Realizar Retiro\n";
        std::cout << "3. Realizar Deposito\n";
        std::cout << "4. Realizar Transferencia\n";
        std::cout << "5. Cerrar Sesion (Salir)\n";
        std::cout << "Seleccione una opcion: ";

        // Si la lectura de la opcion falla (ej. se escribe texto)...
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Intente de nuevo.\n";
            continue; // 'continue' salta al inicio de la siguiente repeticion del bucle 'do-while'.
        }

        std::cout << "==================================\n";

        // Estructura de seleccion 'switch': Ejecuta el codigo segun el valor de 'opcion'.
        switch (opcion) {
            case 1: // Si opcion es 1
                consultarSaldo();
                break; // 'break' sale del 'switch'.
            case 2: // Si opcion es 2
                realizarRetiro();
                break;
            case 3: // Si opcion es 3
                realizarDeposito();
                break;
            case 4: // Si opcion es 4
                realizarTransferencia();
                break;
            case 5: // Si opcion es 5 (Salir)
                std::cout << "Gracias por usar el Cajero Automatico. Sesion cerrada.\n";
                // No hay 'break' despues de este mensaje, el bucle terminara porque la condicion 'opcion != 5' sera falsa.
                break;
            default: // Si opcion no es 1, 2, 3, 4, o 5
                std::cout << "Opcion no valida. Por favor, elija un numero del 1 al 5.\n";
                break;
        }
    } while (opcion != 5); // La condicion de repeticion: Repetir mientras la opcion NO sea 5.
}

/**
 * @brief Funcion principal donde empieza la ejecucion del programa.
 */
int main() {
    // std::cout: Muestra texto en la consola.
    std::cout << "--- BIENVENIDO AL CAJERO AUTOMATICO ---\n";
    std::cout << "Cuentas Disponibles (Solo para prueba): 1001, 1002, 1003\n";
    
    int id_ingresado;
    
    // Bucle para simular el inicio de sesion. Se repite hasta que el ID sea correcto.
    while (cuenta_actual == nullptr) { // Repetir mientras no haya una cuenta logueada (nullptr).
        std::cout << "\nPor favor, ingrese su ID de cuenta: ";
        
        // Si la lectura del ID falla (error de tipo de dato)...
        if (!(std::cin >> id_ingresado)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, ingrese un ID numerico.\n";
            continue; // Salta al inicio de la siguiente repeticion del bucle 'while'.
        }

        // Intentamos buscar la cuenta con el ID ingresado.
        cuenta_actual = buscarCuentaPorId(id_ingresado);

        // Estructura de seleccion 'if/else'
        if (cuenta_actual != nullptr) {
            // Si la cuenta existe, saludamos y llamamos a la funcion del menu.
            std::cout << "¡Bienvenido, " << cuenta_actual->nombre_titular << "!\n";
            mostrarMenu(); // Llama a la funcion que ejecuta el menu.
        } else {
            // Si la cuenta no existe.
            std::cout << "ID de cuenta incorrecto. Intente de nuevo.\n";
        }
    }

    // Un 'return 0' indica que el programa termino correctamente.
    return 0; 
}