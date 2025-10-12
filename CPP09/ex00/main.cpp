/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:51 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 13:37:49 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>  // For std::pair

int main(int argc, char **argv) {
	
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	
	BitcoinExchange	exchange;
	if (exchange.processInputFile(argv[1]) == false)
		return 1;
		
	return 0;

}
