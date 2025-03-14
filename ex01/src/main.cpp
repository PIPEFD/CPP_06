/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:00:17 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/13 15:09:38 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"
#include "../inc/Data.hpp"
#include <iostream>

int main() {
    Data data;
    data.info = "Hello, Serialization!";
    data.value = 42;

    std::cout << "Dirección original de data: " << &data << "\n";
    std::cout << "data.info: " << data.info << "\n";
    std::cout << "data.value: " << data.value << "\n";

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Valor serializado: " << raw << "\n";

    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Dirección deserializada: " << deserializedData << "\n";

    if (deserializedData == &data) {
        std::cout << "¡La deserialización es correcta!\n";
    } else {
        std::cout << "Error: los punteros no coinciden.\n";
    }
    return (0);
}
