/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:06:13 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/08 20:00:46 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <string>

class ScalarConverter
{
  public:
	enum	eLiteralType
	{
		T_CHAR,
		T_INT,
		T_FLOAT,
		T_DOUBLE,
		T_PSEUDOF,
		T_PSEUDOD,
		T_INVALID
	};
    
    public:
	    static void convert(const std::string &literal);

  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &rhs);
	~ScalarConverter();

	static eLiteralType detectType(const std::string &literal);

	static void PrintFromChar(char c);
	static void PrintFromFloat(float f);

	static void PrintFromInt(int i);
	static void PrintFromDouble(double d);
};
#endif