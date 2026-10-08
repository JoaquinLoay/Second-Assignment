// CMP-2102: Programación Avanzada en C++
// USFQ - Colegio de Ciencias e Ingeniería
// Ejercicio 2: Aritmética de Punteros y Matrices en RAM (6.5 Puntos)
// Estudiante: [Joaquin Loayza ]
// Profesor: Juan Diego Haro (jharo@asig.com.ec)

#include <iostream>
#include <cstddef>

const int FILAS = 3;
const int COLS = 4;

/**
 * @brief Suma todos los elementos que forman el borde o perímetro exterior de la matriz.
 * @param baseMatriz Puntero base al inicio de la matriz contigua (&matriz[0][0]).
 * @param filas Número total de filas de la cuadrícula.
 * @param columnas Número total de columnas de la cuadrícula.
 * @return Suma de las casillas en la primera fila, última fila, primera columna y última columna.
 * @warning Prohibido el uso de corchetes []. Debe usarse offset lineal: *(baseMatriz + fila * columnas + col).
 */
int sumarPerimetroMatriz(const int *baseMatriz, int filas, int columnas)
{
    // TODO [3.0 PUNTOS]: Suma del perimetro exterior mediante desplazamiento lineal
    // Si baseMatriz es nullptr, filas <= 0 o columnas <= 0, retorna 0.
    // Calcula la suma de todos los elementos que se ubican en el borde exterior
    // REGLA ESTRICTA: Queda prohibido usar corchetes [].
    //    Asegurate de no sumar las cuatro esquinas dos veces.
    // === TU CODIGO EMPIEZA AQUI ===
    if (!baseMatriz || filas <= 0 || columnas <= 0) {
        return 0;
    }

    int suma = 0;

    if (filas == 1 || columnas == 1) {
        for (int i = 0; i < filas * columnas; ++i) {
            suma += *(baseMatriz + i);
        }
        return suma;
    }

    for (int col = 0; col < columnas; ++col) {
        suma += *(baseMatriz + col);
        suma += *(baseMatriz + (filas - 1) * columnas + col);
    }

    for (int fila = 1; fila < filas - 1; ++fila) {
        suma += *(baseMatriz + fila * columnas);
        suma += *(baseMatriz + fila * columnas + columnas - 1);
    }

    return suma;
    // === TU CODIGO TERMINA AQUI ===
}

/**
 * @brief Recorre la matriz contigua con un puntero móvil, encuentra el valor máximo
 *        y deduce sus coordenadas (fila, col) mediante resta de punteros.
 * @param baseMatriz Puntero base al inicio del bloque de memoria continua.
 * @param totalElementos Cantidad total de elementos (filas * columnas).
 * @param columnas Número de columnas de la cuadrícula.
 * @param filaMax Puntero de salida donde se escribirá la fila del valor máximo.
 * @param colMax Puntero de salida donde se escribirá la columna del valor máximo.
 * @return El valor máximo encontrado en la matriz.
 * @warning Prohibido el uso de corchetes []. Debe usar puntero móvil (ptr++) y resta de punteros.
 */
int buscarMaximoYCoordenadas(const int *baseMatriz, int totalElementos, int columnas,
                             int *filaMax, int *colMax)
{
    // TODO [3.5 PUNTOS]: Busqueda de maximo y deduccion inversa de coordenadas con punteros
    // Si baseMatriz == nullptr, filaMax == nullptr, colMax == nullptr o totalElementos <= 0: retorna 0.
    // Recorre linealmente la memoria usando un puntero movil incremental:
    // const int* ptr = baseMatriz;
    // avanzando con ptr++ por cada uno de los totalElementos.
    // Localiza el valor maximo de la matriz. Calcula el desplazamiento relativo
    // al inicio mediante la resta de punteros: int offset = ptr - baseMatriz;
    // Al terminar el recorrido, deduce la fila y columna correspondientes:
    //    *filaMax = offset / columnas;
    //    *colMax = offset % columnas;
    // Retorna el valor maximo encontrado.
    // REGLA: Queda estrictamente prohibido usar corchetes [].
    // === TU CODIGO EMPIEZA AQUI ===
    
    if (!baseMatriz || !filaMax || !colMax || totalElementos <= 0) {
        return 0;
    }

    const int *ptr = baseMatriz;
    const int *maxPtr = baseMatriz;
    int maxValor = *baseMatriz;

    for (int i = 1; i < totalElementos; ++i) {
        ++ptr;
        if (*ptr > maxValor) {
            maxValor = *ptr;
            maxPtr = ptr;
        }
    }

    int offset = maxPtr - baseMatriz;
    *filaMax = offset / columnas;
    *colMax = offset % columnas;

    return maxValor;
    // === TU CODIGO TERMINA AQUI ===
}

// ============================================================================
// PROGRAMA PRINCIPAL
// El estudiante NO debe modificar esta función.
// ============================================================================
int main()
{
    std::cout << "=== EJERCICIO 2: ARITMETICA DE PUNTEROS Y MATRICES EN RAM ===\n";

    // Matriz de prueba (3 filas x 4 columnas):
    //  10, 20, 30, 40   -> fila 0 (borde)
    //  50, 99, 12, 60   -> fila 1 (borde: 50 y 60; interior: 99, 12)
    //  70, 80, 90, 15   -> fila 2 (borde)
    int matriz[FILAS][COLS] = {
        {10, 20, 30, 40},
        {50, 99, 12, 60},
        {70, 80, 90, 15}};

    // 1. Prueba de suma de perímetro exterior
    // Borde = 10 + 20 + 30 + 40 + 50 + 60 + 70 + 80 + 90 + 15 = 465
    int sumaPerimetro = sumarPerimetroMatriz(&matriz[0][0], FILAS, COLS);
    std::cout << "Suma del perimetro exterior: " << sumaPerimetro << " (Esperado: 465)\n";

    int sumaNull = sumarPerimetroMatriz(nullptr, FILAS, COLS);
    std::cout << "Suma con puntero nullptr: " << sumaNull << " (Esperado: 0)\n";

    // 2. Prueba de búsqueda de máximo y deducción de coordenadas
    int fMax = -1;
    int cMax = -1;
    int maxValor = buscarMaximoYCoordenadas(&matriz[0][0], FILAS * COLS, COLS, &fMax, &cMax);
    std::cout << "\nValor maximo encontrado: " << maxValor << " (Esperado: 99)\n";
    std::cout << "Coordenada fila maxima: " << fMax << " (Esperado: 1)\n";
    std::cout << "Coordenada col maxima:  " << cMax << " (Esperado: 1)\n";

    std::cout << "=== FIN EJERCICIO 2 ===\n";
    return 0;
}