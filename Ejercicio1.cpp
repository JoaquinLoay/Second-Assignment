// CMP-2102: Programación Avanzada en C++
// USFQ - Colegio de Ciencias e Ingeniería
// Ejercicio 1: Cadenas Estilo C y Búferes Seguros (6.5 Puntos)
// Estudiante: [Joaquin Loayza ]
// Profesor: Juan Diego Haro (jharo@asig.com.ec)

#include <iostream>

/**
 * @brief Cuenta cuántas veces aparece un carácter objetivo dentro de una cadena estilo C,
 *        inspeccionando como máximo maxLectura caracteres antes de encontrar '\0'.
 * @param cadena Puntero constante a la cadena estilo C delimitada por '\0'.
 * @param objetivo Carácter a contabilizar.
 * @param maxLectura Límite defensivo máximo de caracteres a inspeccionar en memoria.
 * @return Número de ocurrencias de 'objetivo', o 0 si cadena es nullptr o maxLectura <= 0.
 * @note Prohibido el uso de <cstring> o funciones de biblioteca estándar (strlen, etc.).
 */
int contarCaracteresAcotado(const char *cadena, char objetivo, int maxLectura)
{
    // TODO [2.5 PUNTOS]: Conteo acotado de caracteres con punteros
    // Si cadena es nullptr o maxLectura <= 0, retorna 0.
    // Recorre la cadena usando aritmética de punteros.
    // Detén el recorrido al encontrar '\0' o al alcanzar maxLectura caracteres.
    // Cuenta y retorna cuántas veces coincide el carácter actual con 'objetivo'.
    // === TU CODIGO EMPIEZA AQUI ===
    if (!cadena || maxLectura <= 0) {
        return 0;
    }

    int conteo = 0;
    const char *p = cadena;
    for (int i = 0; i < maxLectura && *p != '\0'; i++) {
        if (*p == objetivo) {
            conteo++;
        }
        p++;
    }

    return conteo;
    // === TU CODIGO TERMINA AQUI ===
}

/**
 * @brief Concatena de forma segura una cadena 'sufijo' al final de la cadena 'destino'.
 * @param destino Búfer de caracteres que ya contiene una cadena terminada en '\0'.
 * @param capDestino Capacidad física total del arreglo destino.
 * @param sufijo Cadena a anexar al final de destino.
 * @return true si todo el sufijo alcanzó completo sin recortarse;
 *         false si fue truncado o si algún puntero es nullptr o capDestino <= 0.
 * @note REGLA: Debe garantizar que destino SIEMPRE termine con '\0'.
 *       Queda estrictamente prohibido el uso de <cstring>.
 */
bool concatenarSeguro(char *destino, int capDestino, const char *sufijo)
{
    // TODO [4.0 PUNTOS]: Concatenacion segura en memoria contigua
    // Si alguna condición falla, retorna false inmediatamente.
    // Valida que destino != nullptr, sufijo != nullptr y capDestino > 0.
    // Encuentra la posición del primer '\0' en destino sin exceder capDestino.
    // Si destino no contiene un terminador '\0' dentro del rango [0, capDestino - 1], retorna false.
    // A partir de esa posición de fin, copia los caracteres de sufijo uno a uno sin escribir
    // más allá del índice (capDestino - 1) para reservar la última casilla física.
    // Escribe SIEMPRE el carácter '\0' en la posición de cierre resultante.
    // Retorna true si todo el sufijo cupo completo sin recortarse; false si fue truncado.
    // === TU CODIGO EMPIEZA AQUI ===
    if (!destino || !sufijo || capDestino <= 0) {
        return false;
    }

    char *fin = destino;
    while (*fin != '\0' && fin - destino < capDestino - 1) {
        fin++;
    }

    if (*fin != '\0') {
        return false;
    }

    while (*sufijo != '\0' && fin - destino < capDestino - 1) {
        *fin = *sufijo;
        fin++;
        sufijo++;
    }

    *fin = '\0';

    return true;
    // === TU CODIGO TERMINA AQUI ===
}

// ============================================================================
// PROGRAMA PRINCIPAL
// El estudiante NO debe modificar esta función.
// ============================================================================
int main()
{
    std::cout << "=== EJERCICIO 1: CADENAS ESTILO C Y BUFERES SEGUROS ===\n";

    // 1. Prueba de conteo acotado
    const char trama[] = "item:402;sensor:A1;temp:85;status:OK";
    int cuentaSeparador = contarCaracteresAcotado(trama, ';', 64);
    std::cout << "Ocurrencias de ';' en trama completa: " << cuentaSeparador << " (Esperado: 3)\n";

    int cuentaAcotada = contarCaracteresAcotado(trama, ';', 15);
    std::cout << "Ocurrencias de ';' inspeccionando max 15 caracteres: " << cuentaAcotada << " (Esperado: 1)\n";

    int cuentaNull = contarCaracteresAcotado(nullptr, ';', 20);
    std::cout << "Conteo sobre puntero nullptr: " << cuentaNull << " (Esperado: 0)\n";

    // 2. Prueba de concatenación segura
    char buffer[20] = "DATA_";
    bool exito1 = concatenarSeguro(buffer, 20, "2026");
    std::cout << "\nConcatenacion 1 cupo completo: " << (exito1 ? "SI" : "NO") << " (Esperado: SI)\n";
    std::cout << "Resultado buffer: [" << buffer << "] (Esperado: [DATA_2026])\n";

    char bufferPequeno[10] = "ID:";
    bool exito2 = concatenarSeguro(bufferPequeno, 10, "ABCDEFGHIJKL");
    std::cout << "\nConcatenacion 2 con truncamiento seguro: " << (!exito2 ? "SI" : "NO") << " (Esperado: SI)\n";
    std::cout << "Resultado truncado seguro: [" << bufferPequeno << "]\n";

    bool exitoNull = concatenarSeguro(nullptr, 10, "TEST");
    std::cout << "Concatenacion con puntero nulo rechazada: " << (!exitoNull ? "SI" : "NO") << " (Esperado: SI)\n";

    std::cout << "=== FIN EJERCICIO 1 ===\n";
    return 0;
}