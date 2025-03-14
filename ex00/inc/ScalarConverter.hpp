/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:06:13 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/14 12:26:02 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#define T_MINUS 0.0
#define T_MINUSF 0.0f



#include <string>
#include <iostream>
#include <cstdlib>  
#include <limits>
#include <cctype>    
#include <cstring>   
#include <cmath> 
#include <iostream>

class ScalarConverter
{
  public:
	enum eLiteralType {
        T_CHAR,        // literal de un caracter (no dígito)
        T_INT,         // número entero
        T_FLOAT,       // número float (termina en 'f')
        T_DOUBLE,      // número double
        T_PLUS_INF,    // +∞
        T_MINUS_INF,   // -∞
        T_NAN,         // NaN
        T_INVALID      // No se pudo determinar
    };
    private:
        ScalarConverter();
	    ScalarConverter(const ScalarConverter &other);
	    ScalarConverter &operator=(const ScalarConverter &rhs);
	    ~ScalarConverter();
    public:
	    static void convert(const std::string &literal);
        static eLiteralType detectType(const std::string &literal);

    private:        
        static  void printfFromChar(char c);
        static  void printFromFloat(float f);
        static  void PrintFromInt(int i);
        static  void printfFromDouble(double d);
        static  void printNan();
        static  void printInf(bool negative);

        static  bool myIsNan(double x);
        static  bool myIsInf(double x);   
};
#endif