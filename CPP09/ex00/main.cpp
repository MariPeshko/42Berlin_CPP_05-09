/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:51 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/09 17:01:59 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>  // For std::pair


int main(int argc, char **argv) {
	
	if (argc == 1 || argc > 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

    BitcoinExchange exchange;
	if (exchange.processInputFile(argv[1]) == false)
		return 1;
    //std::string		filename = argv[1];
	
	// print database 1
    /* std::map<std::string, double>::const_iterator it;
    for (it = exchange.getBase().begin(); it != exchange.getBase().end(); ++it) {
        std::cout << "Date: " << it->first 
                  << " Rate: " << it->second << std::endl;
    } */
	
    return 0;

}
