/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:29:56 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/08 18:49:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>  // for std::istringstream
#include <cstdlib>  // for std::atof

BitcoinExchange::BitcoinExchange() {
    if (!loadDatabase("data.csv")) {
        std::cerr << "Error: Cannot load database" << std::endl;
    }
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
		std::cerr << "Error: Cannot open file ";
		std::cerr << filename << std::endl;
        return false;
    }
    
    std::string line;
    std::getline(file, line); // skipping the header "date,exchange_rate"
    
    while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, rate_str;
		
		if (std::getline(iss, date, ',') && std::getline(iss, rate_str)) {
			double rate = std::atof(rate_str.c_str());  // C++98
			_database[date] = rate;
		}
	}
	file.close();
	return true;
}

BitcoinExchange::~BitcoinExchange() {}

// copy
// copy assignment
