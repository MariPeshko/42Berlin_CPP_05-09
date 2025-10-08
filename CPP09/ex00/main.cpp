/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:51 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/08 18:42:10 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>

/* 1. c_str()
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

int main(int argc, char **argv) {
    
	if (argc == 1 || argc > 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 0;
	}

    std::string		filename = argv[1];
	if (filename.empty())	{
		std::cerr << "<filename> is an empty string" << std::endl;
		return 1;
	}
    	if (is_directory(filename)) {
		std::cerr << filename << " is a directory" << std::endl;
		return 1;
	}
    std::ifstream	ifs(argv[1]);
	// check exist and permissions
	if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open file ";
		std::cerr << filename << std::endl;
        return 1;
    }

    BitcoinExchange exchange;
    
    
    return 0;

}