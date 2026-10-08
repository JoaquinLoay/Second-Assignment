// CMP-2102: Programación Avanzada en C++
// USFQ - Colegio de Ciencias e Ingeniería
// Ejercicio 3: POO, Encapsulamiento, Sobrecarga y Destructores (7.0 Puntos)
// Estudiante: [Joaquin Loayza]
// Profesor: Juan Diego Haro (jharo@asig.com.ec)

#include <iostream>

// ============================================================================
// FUNCIONES DEL SISTEMA PARA VERIFICACIÓN DE CICLO DE VIDA (NO MODIFICAR)
// ============================================================================
void notificarExito(int id, int x, int y)
{
    std::cout << "  -> [EXITO] Vector " << id << " procesado correctamente en coordenadas (" << x << ", " << y << ")\n";
}

void notificarFallo(int id, int x, int y)
{
    std::cout << "  -> [FALLO] Vector " << id << " descartado sin procesar en coordenadas (" << x << ", " << y << ")\n";
}

// ============================================================================
// CLASE VECTOR
// ============================================================================
class Vector
{
private:
    int id{0};
    int x{0};
    int y{0};
    bool procesado{false};

public:
    // ========================================================================
    // 1. CONSTRUCTOR CON LISTA DE INICIALIZACIÓN DE MIEMBROS [2.0 PUNTOS]
    // ========================================================================
    // TODO [2.0 PUNTOS]: Declara e implementa el constructor COMPLETO desde cero.
    // Debes escribir la firma, la lista de inicialización de miembros (usando ':') y el cuerpo.
    //
    // Requerimientos:
    // 1. Parámetros: Recibe tres enteros: un identificador numérico, la coordenada X inicial
    //    y la coordenada Y inicial.
    // 2. Lista de inicialización de miembros (Member Initializer List con sintaxis ':'):
    //    - 'id' debe inicializarse con el identificador recibido.
    //    - 'x' debe inicializarse con la coordenada X recibida.
    //    - 'y' debe inicializarse en 0.
    //    - 'procesado' debe inicializarse en false.
    // 3. Cuerpo del constructor (Realiza una única validación defensiva):
    //    - Si la coordenada Y recibida es menor a 0, 'y' se mantiene en 0.
    //    - Caso contrario, asigna a 'y' dicha coordenada Y recibida.
    //
    // === TU CODIGO EMPIEZA AQUI ===
    Vector(int identificador, int coordenadaX, int coordenadaY) : id(identificador), x(coordenadaX), y(0), procesado(false)
    {
        if (coordenadaY >= 0)
        {
            y = coordenadaY;
        }
    }   
    
    // === TU CODIGO TERMINA AQUI ===

    // ========================================================================
    // 2. MÉTODOS DE ACCESO: GETTERS Y SETTERS [1.5 PUNTOS]
    // ========================================================================
    // TODO [1.5 PUNTOS]: Declara e implementa los métodos de acceso para encapsular la clase:
    //
    // - Getters (Métodos de consulta inmutables):
    //   Deben calificarse con 'const' para asegurar que puedan ser llamados sobre instancias constantes:
    //   * getId(): retorna el identificador numérico 'id'.
    //   * getX(): retorna la coordenada entera 'x'.
    //   * getY(): retorna la coordenada entera 'y'.
    //
    // - Setters (Métodos de modificación):
    //   * setX: recibe un nuevo valor entero y lo asigna a la coordenada 'x'.
    //   * setY: recibe un nuevo valor entero y lo asigna a la coordenada 'y'.
    //     (Validación: si el nuevo valor recibido es menor a 0, 'y' se fija en 0; caso contrario toma el nuevo valor).
    //
    // === TU CODIGO EMPIEZA AQUI ===
    void setX(int nuevaX) { x = nuevaX; }

void setY(int nuevaY) {
    y = nuevaY >= 0 ? nuevaY : 0;
}

int multiplicar(const Vector *otro) const {
    if (otro == nullptr) {
        return 0;
    }

    return x * otro->x + y * otro->y;
}


    int getId() const { return id; }
    int getX() const { return x; }  
    int getY() const { return y; }  
    // === TU CODIGO TERMINA AQUI ===

    // ========================================================================
    // 3. SOBRECARGA DE MÉTODOS DE MULTIPLICACIÓN [2.0 PUNTOS]
    // ========================================================================
    // TODO [2.0 PUNTOS]: Declara e implementa dentro de la clase dos sobrecargas
    // para el método de multiplicación del vector con el nombre 'multiplicar',
    // ambos métodos deben llamarse multiplicar:
    //
    // - Sobrecarga 1 (Multiplicación por un escalar):
    //   Recibe un valor entero escalar y multiplica las coordenadas 'x' e 'y'
    //   del vector actual por dicho factor escalar (modificando las coordenadas del vector).
    //   Esta operación no retorna ningún valor.
    //
    // - Sobrecarga 2 (Multiplicación entre vectores (Producto punto)):
    //   Recibe un puntero a otro vector constante y calcula el producto escalar
    //   (producto punto) entre el vector actual y el vector recibido.
    //   Recordatorio: En matemáticas, si (x,y) son las componentes de un vector y (x',y')
    //   son las componentes de otro vector diferentes. Entonces la multiplicación entre
    //   vectores (producto punto) devuelve un número que es igual a:
    //                  x*x' + y*y'.
    //   Retorna el valor entero resultante. Si el puntero recibido es nulo (nullptr),
    //   debe retornar 0 de forma defensiva.
    //
    // Nota: Ambas sobrecargas deben compartir el mismo nombre ('multiplicar'), pero
    // difieren en sus parámetros y tipo de retorno.
    //
    // === TU CODIGO EMPIEZA AQUI ===
    void multiplicar(int escalar) {
        x *= escalar;
        y *= escalar;
    }   
    // === TU CODIGO TERMINA AQUI ===

    // ========================================================================
    // 4. DESTRUCTOR DE LA CLASE [1.5 PUNTOS]
    // ========================================================================
    // TODO [1.5 PUNTOS]: Declara e implementa el destructor de la clase Vector.
    // El estudiante debe conocer y escribir la sintaxis del destructor (~NombreClase).
    //
    // Comportamiento al destruirse el objeto (al abandonar el ámbito en la pila):
    // - Si 'procesado' es true: llama a notificarExito(id, x, y).
    // - Si 'procesado' es false: llama a notificarFallo(id, x, y).
    //
    // === TU CODIGO EMPIEZA AQUI ===
    ~Vector() {
        if (procesado) {
            notificarExito(id, x, y);
        } else {
            notificarFallo(id, x, y);
        }
    }   
    // === TU CODIGO TERMINA AQUI ===

    // ========================================================================
    // MÉTODO AUXILIAR DEL SISTEMA (NO MODIFICAR)
    // ========================================================================
    void procesar()
    {
        procesado = true;
    }
};

// ============================================================================
// PROGRAMA PRINCIPAL
// El estudiante NO debe modificar esta función.
// ============================================================================
int main()
{
    std::cout << "=== EJERCICIO 3: POO, ENCAPSULAMIENTO, SOBRECARGA Y DESTRUCTORES ===\n";

    // 1. Prueba de constructor con lista de inicializadores y validación defensiva
    std::cout << "\n--- 1. Constructor con lista de inicializadores y validacion ---\n";
    Vector v1(1, 3, 4);
    Vector v2(2, 2, -5); // Y es negativo: debe corregirse a 0
    std::cout << "Vector 1 Coordenadas: (" << v1.getX() << ", " << v1.getY() << ") (Esperado: (3, 4))\n";
    std::cout << "Vector 2 Coordenadas: (" << v2.getX() << ", " << v2.getY() << ") (Esperado: (2, 0))\n";

    // 2. Prueba de Getters y Setters (Encapsulamiento)
    std::cout << "\n--- 2. Getters y Setters ---\n";
    v2.setX(7);
    v2.setY(9);
    std::cout << "Vector 2 tras setX(7) y setY(9): (" << v2.getX() << ", " << v2.getY() << ") (Esperado: (7, 9))\n";

    v2.setY(-20); // Validación defensiva del setter
    std::cout << "Vector 2 tras setY(-20):         (" << v2.getX() << ", " << v2.getY() << ") (Esperado: (7, 0))\n";

    const Vector vConst(99, 15, 25);
    std::cout << "Vector constante id=" << vConst.getId() << ", (" << vConst.getX() << ", " << vConst.getY() << ") (Esperado: id=99, (15, 25))\n";

    // 3. Prueba de sobrecarga de métodos (multiplicar: escalar vs producto punto)
    std::cout << "\n--- 3. Sobrecarga de metodos (multiplicar) ---\n";
    Vector v3(3, 2, 5);
    int productoPunto = v1.multiplicar(&v3); // (3 * 2) + (4 * 5) = 6 + 20 = 26
    std::cout << "Producto punto V1 . V3: " << productoPunto << " (Esperado: 26)\n";

    int productoNull = v1.multiplicar(nullptr);
    std::cout << "Producto punto con nullptr: " << productoNull << " (Esperado: 0)\n";

    v1.multiplicar(2); // Multiplicación por escalar 2: (3 * 2, 4 * 2) = (6, 8)
    std::cout << "Vector 1 tras multiplicar(2): (" << v1.getX() << ", " << v1.getY() << ") (Esperado: (6, 8))\n";

    // 4. Prueba del ciclo de vida determinista del destructor RAII (Clase 10)
    std::cout << "\n--- 4. Destructor RAII en Stack ---\n";
    std::cout << "Iniciando bloque de objetos temporales...\n";
    {
        Vector vProcesado(101, 10, 20);
        vProcesado.procesar(); // Debe invocar notificarExito al destruirse

        Vector vInconcluso(102, 30, 40);
        // NO se procesa: debe invocar notificarFallo al destruirse
    }
    std::cout << "Bloque finalizado. Destructores ejecutados automaticamente.\n";

    std::cout << "\n=== FIN EJERCICIO 3 ===\n";
    return 0;
}