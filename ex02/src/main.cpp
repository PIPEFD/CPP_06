/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:34:12 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/14 12:51:13 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/A.hpp"
#include "../inc/B.hpp"
#include "../inc/Base.hpp"
#include "../inc/C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>


Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    Base* instance = NULL;
    instance = generate();

    if (!instance) {
        std::cerr << "Error: generate() returned NULL." << std::endl;
        return (1);
    }

    std::cout << "Identificación usando puntero: ";
    identify(instance);
    std::cout << "\n";

    std::cout << "Identificación usando referencia: ";
    identify(*instance);
    std::cout << "\n";

    delete instance;
    instance = NULL;

    return (0);
}
