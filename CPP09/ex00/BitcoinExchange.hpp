/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:29:59 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/08 18:43:35 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;  // date -> exchange_rate
	bool loadDatabase(const std::string& filename);
   /*  bool isValidDate(const std::string& date) const;
    bool isValidValue(double value) const;
    std::string findClosestDate(const std::string& date) const; */
    
public:
    BitcoinExchange();
    ~BitcoinExchange();
    /* BitcoinExchange(const BitcoinExchange& copy);
    BitcoinExchange& operator=(const BitcoinExchange& assign); */
    
   /*  bool processInputFile(const std::string& filename);
    void processLine(const std::string& line); */
};

#endif
