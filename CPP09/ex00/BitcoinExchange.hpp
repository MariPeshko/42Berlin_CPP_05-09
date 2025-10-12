/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:29:59 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 13:09:06 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;  // date -> exchange_rate
	bool	loadDatabase(const std::string& filename);
    bool	isValidDate(const std::string& date) const;
	bool	isValidValue(const std::string& value_str) const;
    bool	isValidValue(double value) const;
    double	findClosestRate(const std::string& date) const;
	double	CalcAmount(const std::string & date, double value) const;
    
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange& operator=(const BitcoinExchange& assign);
	
	const std::map<std::string, double>& getBase() const;
	std::map<std::string, double>& getBase();
	
	bool processInputFile(const std::string& filename);
	void processLine(const std::string& line);
};

#endif
