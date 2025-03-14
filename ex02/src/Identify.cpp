/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:18:16 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/14 13:09:39 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/A.hpp"
#include "../inc/B.hpp"
#include "../inc/C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base()
{
}

enum		RealType
{
	TYPE_A,
	TYPE_B,
	TYPE_C,
	TYPE_UNKNOWN
};

const char	*realTypeToString(RealType type)
{
	switch (type)
	{
	case TYPE_A:
		return ("TYPE_A");
	case TYPE_B:
		return ("TYPE_B");
	case TYPE_C:
		return ("TYPE_C");
	default:
		return ("TYPE_UNKNOWN");
	}
}

RealType	identifyType(Base *p)
{
	if (dynamic_cast<A *>(p))
		return (TYPE_A);
	else if (dynamic_cast<B *>(p))
		return (TYPE_B);
	else if (dynamic_cast<C *>(p))
		return (TYPE_C);
	return (TYPE_UNKNOWN);
}

void	identify(Base *p)
{
	RealType	type;

	type = identifyType(p);
	std::cout << realTypeToString(type);
}

void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A";
		return ;
	}
	catch (...)
	{
		std::cerr << "Conversion to A failed.\n";
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B";
		return ;
	}
	catch (...)
	{
		std::cerr << "Conversion to B failed.\n";
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C";
		return ;
	}
	catch (...)
	{
		std::cerr << "Conversion to C failed.\n";
	}
	std::cout << "Unknown";
}

Base	*generate(void)
{
	int	r;

	r = std::rand() % 4;
	switch (r)
	{
	case 0:
		return (new A);
	case 1:
		return (new B);
	case 2:
		return (new C);
	default:
		return (NULL);
	}
}
