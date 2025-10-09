/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:29:56 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/09 18:35:22 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  // for std::istringstream
#include <cstdlib>  // for std::atof
#include <sys/stat.h>


BitcoinExchange::BitcoinExchange() {
    if (!loadDatabase("data.csv")) {
        std::cerr << "Error: Cannot load database file data.csv" << std::endl;
    }
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
		std::cerr << "Error: Cannot open file ";
		std::cerr << filename << std::endl;
        return false;
    }
    
    std::string	line;
    std::getline(file, line); // skipping the header "date,exchange_rate"
    
    while (std::getline(file, line)) {
		std::istringstream	iss(line);
		std::string	date, rate_str;
		
		if (std::getline(iss, date, ',') && std::getline(iss, rate_str)) {
			double rate = std::atof(rate_str.c_str());
			_database[date] = rate;
		}
	}
	if (_database.empty())
		std::cerr << "Warning: data.csv is empty" << std::endl;
	file.close();
	return true;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) :
	_database(copy.getBase()) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& assign) {
	if (this != &assign) {
		_database = assign.getBase();
	}
	return *this;
}

std::map<std::string, double>	BitcoinExchange::getBase() const {
	return _database;
}

std::map<std::string, double> &	BitcoinExchange::getBase() {
	return _database;
}

/*  1. c_str()
	stat() requires a const char* 
	and .c_str() converts std::string → const char*
    2. S_ISDIR(path_stat.st_mode) is a macro that 
	checks whether the mode indicates a directory.
    3. if (stat(path.c_str(), &path_stat) != 0)
	stat failed — possibly file doesn't exist or no permission. */
static bool is_directory(const std::string& path) {
    struct stat	path_stat;
	if (stat(path.c_str(), &path_stat) != 0) {
        return false;
    }
    return S_ISDIR(path_stat.st_mode);
}


bool BitcoinExchange::processInputFile(const std::string& filename) {
	if (filename.empty())	{
		std::cerr << "<filename> is an empty string" << std::endl;
		return false;
	}
	if (is_directory(filename)) {
		std::cerr << filename << " is a directory" << std::endl;
		return false;
	}
    std::ifstream	file(filename.c_str());
	if (!file.is_open()) {
        std::cerr << "Error: Cannot open file ";
		std::cerr << filename << std::endl;
        return false;
    }

	std::string	line;
	std::getline(file, line); // skipping the header
	while(std::getline(file, line)) {
		std::istringstream	iss(line);
		std::string			date, pipe, value_str;
		if (iss >> date >> pipe >> value_str && pipe == "|") {
			double value = std::atof(value_str.c_str());
			// is it valid value wrapper
			if (value < 0 || value > 1000) std::cerr << "Error: not a positive number." << std::endl;
			else if (value > 1000) std::cerr << "Error: too large number." << std::endl;
			else {
				if (isValidDate(date))
					std::cout << date << " => " << value << " = " << CalcAmount(date, value) << std::endl;
				}
		} else {
        	std::cerr << "Error: bad input => " << line << std::endl;
    	}
	}
	file.close();
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	
	if (date.empty())
		return false;
	
	std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
    
    // Target date is before all dates in database
    if (it == _database.begin()) {
        std::cerr << "Warning: date " << date << " is earlier than earliest available date " 
                  << _database.begin()->first << "\nI use a rate of the earliest date" << std::endl;
        return true;
    }

	/// TO DO
	/// check if the format is valid - year range, month range, days range with - in between
	// return false;
	return true;
}

double BitcoinExchange::CalcAmount(const std::string & date, double value) {

	std::map<std::string, double>::const_iterator it;
	it = _database.find(date);
	if(it != _database.end()) {
		return it->second * value;
	}
	else {
		//  TO DO
		// to make i more concise - method findClosestRate - return it->second
		std::string date_lower = findClosestDate(date);
		
		//std::cout << date_lower << std::endl;
		std::map<std::string, double>::const_iterator it;
		it = _database.find(date_lower);
		return it->second * value;
	}
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
	// Find the first date that is greater than the target date
    std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
    
    // Target date is before all dates in database
    if (it == _database.begin()) {
		return it->first; // Use earliest rate
    }
	// Move to the previous element (closest earlier date)
    --it;
    return it->first;
}
