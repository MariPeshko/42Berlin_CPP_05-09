/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/13 16:10:54 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
//#include <cctype> // for std::isdigit

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy) :
	_numbers(copy._numbers) 
	{}

PmergeMe& PmergeMe::operator=(const PmergeMe& assign) {
	if (this != &assign) {
		_numbers = assign._numbers;
	}
	return *this;
}
