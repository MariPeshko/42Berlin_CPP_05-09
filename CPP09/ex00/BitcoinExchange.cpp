/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:29:56 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 13:39:18 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  // for std::istringstream
#include <cstdlib>  // for std::atof
#include <sys/stat.h>
#include <cctype> // for std::isdigit(


BitcoinExchange::BitcoinExchange() {
	if (!loadDatabase("data.csv")) {
		std::cerr << "Error: Cannot load database file data.csv" << std::endl;
	}
}

bool	BitcoinExchange::loadDatabase(const std::string& filename) {
	
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

const std::map<std::string, double> &	BitcoinExchange::getBase() const {
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
		processLine(line);
	}
	file.close();
	return true;
}

void	BitcoinExchange::processLine(const std::string& line) {
	
	std::istringstream	iss(line);
	std::string			date, pipe, value_str;
	if (iss >> date >> pipe >> value_str && pipe == "|") {
		if (!isValidValue(value_str)) {
			std::cerr << "Error: value is not valid number => " << line << std::endl;
			return ;
		}
		double value = std::atof(value_str.c_str());
		if (!isValidValue(value)) {
			return ;
		} else if (isValidDate(date)) {
			std::cout << date << " => " << value << " = " << CalcAmount(date, value) << std::endl;
		} else {
			std::cerr << "Error: bad input => " << line << std::endl;
		}
	} else {
		std::cerr << "Error: bad input => " << line << std::endl;
	}
}

bool	BitcoinExchange::isValidValue(const std::string& value_str) const {
	
	if (value_str.empty())
		return false;
	if (value_str == "-" || value_str == ".")
		return false;

	bool dot = false;
	for (size_t i = 0; i < value_str.length(); ++i) {
		char c = value_str[i];
		if (i == 0 && value_str[i] == '-') {
			continue ;	
		}
		else if (i > 0 && value_str[i] == '-') {
			return false;
		}
		else if (c == '.') {
			if (dot) return false;
			dot = true;
		} else if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool	BitcoinExchange::isValidValue(double value) const {
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	} else if (value > 1000) {
	std::cerr << "Error: too large number." << std::endl;
			return false;
		
	} else {
		return true;
	}
}

bool	BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.length() != 10) 
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.length(); ++i) {
		if (i == 4 || i == 7) continue; // skip hyphens
		if (!std::isdigit(date[i])) {
			return false;
		}
	}
	std::string	year_s = date.substr(0, 4);
	std::string	month_s = date.substr(5, 2);
	std::string	day_s = date.substr(8, 2);
	
	int year = std::atoi(year_s.c_str());
	int month = std::atoi(month_s.c_str());
	int day = std::atoi(day_s.c_str());
	if (year < 2008 || year > 2025) return false;
	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;
	
	std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
	// Target date is before all dates in database
	if (it == _database.begin()) {
		std::cerr << "Warning: date " << date << " is earlier than earliest available date " 
			<< _database.begin()->first << "\nI use a rate of the earliest date" << std::endl;
		}
	return true;
}

double	BitcoinExchange::CalcAmount(const std::string & date, double value) const {

	std::map<std::string, double>::const_iterator it;
	it = _database.find(date);
	if (it != _database.end()) {
		return it->second * value;
	}
	else {
		double rate_lower = findClosestRate(date);
		return rate_lower * value;
	}
}

double	BitcoinExchange::findClosestRate(const std::string& date) const {
	// Find the first date that is greater than the target date
	std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
	if (it == _database.begin())
		return it->second;
	--it; // closest earlier date
	return it->second;
}
