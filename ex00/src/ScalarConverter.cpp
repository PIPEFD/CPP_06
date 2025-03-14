/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:57:48 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/14 12:30:44 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

#include <cmath>

ScalarConverter::ScalarConverter()
{
	std::cout << "Construtor for default" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &)
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &)
{
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "Destroyer for default" << std::endl;
}
bool ScalarConverter::myIsNan(double x)
{
	return (x != x);
}

bool ScalarConverter::myIsInf(double x)
{
	return (x == HUGE_VAL || x == -HUGE_VAL);
}

ScalarConverter::eLiteralType ScalarConverter::detectType(const std::string &literal)
{
	char	*end;
	double	val;
	char	*end2;
	double	val2;

	if (literal.size() == 1 && !std::isdigit(literal[0]))
		return (T_CHAR);
	end = NULL;
	val = std::strtod(literal.c_str(), &end);
	if (*end != '\0')
	{
		if (literal.size() > 1 && literal.find('f') >= 1)
		{
			std::string tmp = literal.substr(0, literal.size() - 1);
			end2 = NULL;
			val2 = std::strtod(tmp.c_str(), &end2);
			if (*end2 == '\0')
				return (T_FLOAT);
		}
		return (T_INVALID);
	}
	if (myIsNan(val))
		return (T_NAN);
	if (myIsInf(val))
	{
		if (val < T_MINUS)
			return (T_MINUS_INF);
		else
			return (T_PLUS_INF);
	}
	if (literal.find('.') != std::string::npos
		|| literal.find('e') != std::string::npos
		|| literal.find('E') != std::string::npos)
		return (T_DOUBLE);
	return (T_INT);
}

void ScalarConverter::convert(const std::string &literal)
{
	eLiteralType	type;

	type = detectType(literal);
	switch (type)
	{
	case T_CHAR:
		printfFromChar(literal[0]);
		break ;
	case T_INT:
	{
		PrintFromInt(std::strtol(literal.c_str(), NULL, 10));
		break ;
	}
	case T_FLOAT:
	{
		printFromFloat(std::strtof(literal.substr(0, literal.size()
					- 1).c_str(), NULL));
		break ;
	}
	case T_DOUBLE:
	{
		printfFromDouble(std::strtod(literal.c_str(), NULL));
		break ;
	}
	case T_PLUS_INF:
	{
		printInf(false);
		break ;
	}
	case T_MINUS_INF:
	{
		printInf(true);
		break ;
	}
	case T_NAN:
	{
		printNan();
		break ;
	}
	default:
	{
		std::cout << "char impossible\n"
					<< "int impossible\n"
					<< "float impossible\n"
					<< "double impossible\n";
		break ;
	}
	}
}
void ScalarConverter::printfFromChar(char c)
{
	int		i;
	float	f;
	double	d;

	std::cout << "char: '" << c << "'\n";
	i = static_cast<int>(c);
	std::cout << "int: '" << i << "'\n";
	f = static_cast<float>(c);
	std::cout << "float: '" << f << "f\n";
	d = static_cast<double>(c);
	std::cout << "double: " << d << "\n";
}

void ScalarConverter::PrintFromInt(int l)
{
	if (l < std::numeric_limits<int>::min()
		|| l > std::numeric_limits<int>::max())
	{
		std::cout << "char impossible\n"
					<< "int impossible\n"
					<< "float impossible\n"
					<< "double impossible\n";
		return ;
	}
	if (static_cast<int>(l) >= 32 && static_cast<int>(l) <= 126)
	{
		std::cout << "char :'" << static_cast<char>(l) << "'\n";
	}
	else if (static_cast<int>(l) >= 0 && static_cast<int>(l) <= 32)
		std::cout << "char:  Non displayable\n";
	else
		std::cout << "char: Impossible\n";
	std::cout << "int: " << static_cast<int>(l) << "\n";
	std::cout << "float:  " << static_cast<float>(l) << ".0f\n";
	std::cout << "double: " << static_cast<double>(l) << ".0\n";
}

void ScalarConverter::printFromFloat(float f)
{
	if (myIsNan(f))
		printNan();
	return ;
	if (myIsInf(f))
	{
		printInf((f < T_MINUSF));
		return ;
	}
	if (f >= static_cast<float>(std::numeric_limits<char>::min())
		&& f <= static_cast<float>(std::numeric_limits<char>::max()))
	{
		if (std::isprint(static_cast<unsigned char>(f)))
			std::cout << "Char: '" << static_cast<char>(f) << "'\n";
		else
			std::cout << "char: Non displayable\n";
	}
	else
	{
		std::cout << "char: impossible\n";
	}
	if (f >= static_cast<float>(std::numeric_limits<int>::min())
		&& f <= static_cast<float>(std::numeric_limits<int>::max()))
	{
		std::cout << "int: " << static_cast<int>(f) << "\n";
	}
	else
	{
		std::cout << " int impossible";
	}
	std::cout << "float: " << f << "f\n";
	std::cout << "double: " << static_cast<double>(f) << "\n";
}

void ScalarConverter::printfFromDouble(double d)
{
	if (myIsNan(d))
	{
		printNan();
		return ;
	}
	if (myIsInf(d))
	{
		printInf((d < T_MINUS));
		return ;
	}
	if (d >= static_cast<double>(std::numeric_limits<char>::min())
		&& d <= static_cast<double>(std::numeric_limits<char>::max()))
	{
		if (std::isprint(static_cast<unsigned char>(d)))
			std::cout << "char: '" << static_cast<char>(d) << "' \n";
		else
			std::cout << "char: Non displayable \n";
	}
	else
		std::cout << "char: imposiible \n";
	if (d >= static_cast<double>(std::numeric_limits<int>::min())
		&& d <= static_cast<double>(std::numeric_limits<int>::max()))
	{
		std::cout << " int " << static_cast<int>(d) << "\n";
	}
	else
		std::cout << " int impossible\n";
	std::cout << "float " << static_cast<float>(d) << "f\n";
	std::cout << "double: " << d << "\n";
}
void ScalarConverter::printInf(bool negative)
{
	std::cout << "char: impossible\n";
	std::cout << "char: impossible\n";
	if (negative)
	{
		std::cout << "float: -inff\n";
		std::cout << "double: -inf\n";
	}
	else
	{
		std::cout << "float: +inff\n";
		std::cout << "double: +inf\n";
	}
}

void ScalarConverter::printNan()
{
	std::cout << "char: impossible\n";
	std::cout << "int impossible \n";
	std::cout << "float: +nanf\n";
	std::cout << "double: +nan\n";
}