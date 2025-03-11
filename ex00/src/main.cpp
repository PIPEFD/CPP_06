/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:08:20 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/11 16:36:07 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"
#include "../inc/ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <exception>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX
#include <vector>
#include <iomanip>   // std::fixed, std::setprecision


// -----------------------------------------------------------------------------
// Función auxiliar para convertir el enum a string (para visualización)
const char* typeToString(ScalarConverter::eLiteralType t)
{
    switch (t) {
        case ScalarConverter::T_CHAR:       return "T_CHAR";
        case ScalarConverter::T_INT:        return "T_INT";
        case ScalarConverter::T_FLOAT:      return "T_FLOAT";
        case ScalarConverter::T_DOUBLE:     return "T_DOUBLE";
        case ScalarConverter::T_PLUS_INF:   return "T_PLUS_INF";
        case ScalarConverter::T_MINUS_INF:  return "T_MINUS_INF";
        case ScalarConverter::T_NAN:        return "T_NAN";
        case ScalarConverter::T_INVALID:    return "T_INVALID";
    }
    return "UNKNOWN";
}

// -----------------------------------------------------------------------------
// Función auxiliar para imprimir el resultado en color: verde [OK] y rojo [FAIL]
// -----------------------------------------------------------------------------
static void printResult(bool ok)
{
    if (ok)
        std::cout << " \033[32m[OK]\033[0m";    // verde
    else
        std::cout << " \033[31m[FAIL]\033[0m";   // rojo
}

// -----------------------------------------------------------------------------
// Función auxiliar para testear una literal con el tipo esperado
// Si detectType es privado, se debe disponer de un método público de depuración
// (por ejemplo, debugDetectType) que retorne el mismo enum.
// -----------------------------------------------------------------------------
static void testLiteralWithExpected(const std::string &literal,
                                    ScalarConverter::eLiteralType expected)
{
    // Utilizamos el wrapper de depuración; si no existe, temporalmente
    // se puede hacer detectType público para testeo.
    ScalarConverter::eLiteralType detected = ScalarConverter::detectType(literal);
    
    std::cout << "[ Literal: \"" << literal << "\" ]\n";
    std::cout << "  Detected: " << typeToString(detected)
              << " | Expected: " << typeToString(expected);
    
    bool ok = (detected == expected);
    printResult(ok);
    std::cout << "\n";

    // También invocamos convert() para ver la salida completa
    try {
        ScalarConverter::convert(literal);
    }
    catch (const std::exception &e) {
        std::cerr << "Exception in convert(): " << e.what() << "\n";
    }
    std::cout << "-------------------------------------\n";
}

// -----------------------------------------------------------------------------
// 1) Generar un int aleatorio en [minVal, maxVal] y testearlo (se espera T_INT)
// -----------------------------------------------------------------------------
static void testRandomInts(int nTests, int minVal, int maxVal)
{
    std::cout << "=== Test random INT between ["
              << minVal << ", " << maxVal << "] ("
              << nTests << " samples) ===\n";
    for (int i = 0; i < nTests; i++)
    {
        long range = static_cast<long>(maxVal) - static_cast<long>(minVal) + 1;
        long r = minVal + (std::rand() % range);
        std::ostringstream oss;
        oss << r;
        testLiteralWithExpected(oss.str(), ScalarConverter::T_INT);
    }
}

// -----------------------------------------------------------------------------
// 2) Generar un float aleatorio en [minF, maxF], y testearlo con sufijo 'f'
//    Se espera T_FLOAT (salvo que el valor sea tan extremo que se convierta en ±inf o nan)
// -----------------------------------------------------------------------------
static void testRandomFloats(int nTests, float minF, float maxF)
{
    std::cout << "=== Test random FLOAT between ["
              << minF << ", " << maxF << "] ("
              << nTests << " samples) ===\n";
    for (int i = 0; i < nTests; i++)
    {
        float scale = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        float fVal = minF + scale * (maxF - minF);
        std::ostringstream oss;
        oss << fVal << 'f';
        testLiteralWithExpected(oss.str(), ScalarConverter::T_FLOAT);
    }
}

// -----------------------------------------------------------------------------
// 3) Generar un double aleatorio en [minD, maxD], sin sufijo
//    Se espera T_DOUBLE (salvo casos especiales)
// -----------------------------------------------------------------------------
static void testRandomDoubles(int nTests, double minD, double maxD)
{
    std::cout << "=== Test random DOUBLE between ["
              << minD << ", " << maxD << "] ("
              << nTests << " samples) ===\n";
    for (int i = 0; i < nTests; i++)
    {
        double scale = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
        double dVal = minD + scale / (maxD - minD);
        
        std::ostringstream oss;
        std::cout << "DVAL   "<<  dVal << std::endl;
        // Usamos std::fixed y std::setprecision para asegurar que el literal tenga punto decimal
        oss << std::fixed << std::setprecision(6) << dVal;
        testLiteralWithExpected(oss.str(), ScalarConverter::T_DOUBLE);
    }
}

// -----------------------------------------------------------------------------
// 4) Test específico para validar casos del enum (casos fijos)
// -----------------------------------------------------------------------------
static void testEnumCases()
{
    std::cout << "=== Test de casos específicos del enum ===\n";
    struct TestCase {
        std::string literal;
        ScalarConverter::eLiteralType expected;
    };

    TestCase cases[] = {
        {"a",      ScalarConverter::T_CHAR},
        {"Z",      ScalarConverter::T_CHAR},
        {"42",     ScalarConverter::T_INT},
        {"-100",   ScalarConverter::T_INT},
        {"42.0f",  ScalarConverter::T_FLOAT},
        {"-3.14f", ScalarConverter::T_FLOAT},
        {"42.0",   ScalarConverter::T_DOUBLE},
        {"-3.14",  ScalarConverter::T_DOUBLE},
        {"+inf",   ScalarConverter::T_PLUS_INF},
        {"-inf",   ScalarConverter::T_MINUS_INF},
        {"nan",    ScalarConverter::T_NAN},
        {"42abc",  ScalarConverter::T_INVALID}
    };

    const size_t nCases = sizeof(cases) / sizeof(cases[0]);
    for (size_t i = 0; i < nCases; i++) {
        testLiteralWithExpected(cases[i].literal, cases[i].expected);
    }
}

// -----------------------------------------------------------------------------
// main de prueba
// -----------------------------------------------------------------------------
int main()
{
    // Inicializamos la semilla de rand()
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    try {
        // 1) Test de casos específicos (enum)
        testEnumCases();

        // 2) Test aleatorios
        testRandomInts(20, -100, 100);
        testRandomFloats(10, -1000.0f, 1000.0f);
        testRandomDoubles(10, -1.0e6, 1.0e6);

        // 3) Pruebas de rangos extremos
        testRandomFloats(5, -FLT_MAX, FLT_MAX);
        testRandomDoubles(5, -DBL_MAX, DBL_MAX);
        testRandomInts(5, INT_MIN, INT_MAX);
    }
    catch (const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << "\n";
    }
    return 0;
}
