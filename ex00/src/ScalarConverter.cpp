/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:57:48 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/08 23:08:47 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

#include <iostream>

// --------------------------- Princpio de las funciones de instanciar ---------------- //

ScalarConverter::ScalarConverter()
{
    std::cout << "Construtor for default" << std::endl;
    
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs)
{
    return (*this);
}

ScalarConverter::~ScalarConverter()
{
    std::cout << "Destroyer for default" << std::endl;   
}

// --------------------------- Final de las funciones de instanciar ---------------- //


void ScalarConverter::convert(const std::string &literal)
{
    eLiteralType type =  detectType(literal);

    

    
}
ScalarConverter::eLiteralType

ScalarConverter::detectType(const std::string &literal)
{
    
}