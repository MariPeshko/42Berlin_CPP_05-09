/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/27 18:35:10 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>	// for std::istringstream
#include <cctype>	// for std::isdigit
#include <climits>  // INT_MAX
#include <set>

PmergeMe::PmergeMe(const std::vector<int> & parsed_numbers)
	: _numbers(parsed_numbers) {
		_size = _numbers.size();
	}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy) :
	_numbers(copy._numbers) ,
	_sorted_numbers(copy._sorted_numbers)
	{}

PmergeMe& PmergeMe::operator=(const PmergeMe& assign) {
	if (this != &assign) {
		_numbers = assign._numbers;
		_sorted_numbers = assign._sorted_numbers;
	}
	return *this;
}

static void display_vector(const std::vector<int> & vct) {
	for (std::vector<int>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			std::cout << *it << " ";
}

void PmergeMe::sort(std::vector<int>& vec) {
	_sorted_numbers = _numbers;
	// Base case
	if (vec.size() <= 1) {
		return;
	}
	if (vec.size() == 2) {
		if (vec[0] > vec[1]) {
			std::swap(vec[0], vec[1]);
		}
		return;
	}
	
	// Step 1: Create pairs. a and b parts
	bool odd = false;
	std::vector<int> larg;	// a's in Knuth's notation
	std::vector<int> small;	// b's in Knuth's notation
	int unpaired_element = 0;
	int size = vec.size();
	
	if (size % 2 != 0) {
		odd = true;
		unpaired_element = vec.back();
	}
	
	for (std::vector<int>::const_iterator it = vec.begin();
		it != vec.end(); ) {
			if ((it + 1) == vec.end())
				break ;
			if (*it > *(it + 1) || *it == *(it + 1)) {
				larg.push_back(*it);
				small.push_back(*(it + 1));
			} else {
				larg.push_back(*(it + 1));
				small.push_back(*it);
			}
			++it;
			if (it != vec.end()) {
            	++it;
        	}
		}
		
		// Step 2: RECURSIVELY sort larger elements using Ford-Johnson
		sort(larg);
		
		std::cout << "small: ";
		display_vector(small);
		std::cout << "large: ";
		display_vector(larg);
		if (odd == true) {
			std::cout << "unpaired_element: " << unpaired_element;
			
		}
		std::cout << std::endl;

		// Step 3: Build main chain
		// Step 4: Insert remaining elements using Jacobsthal sequence
		_sorted_numbers = _numbers;
}

void PmergeMe::display() {
	std::cout << "Before: ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _numbers.begin();
		it != _numbers.end(); ++it)
			std::cout << *it << " ";
	}
	else {
		std::vector<int>::const_iterator it = _numbers.begin();
		for (int i = 0; i < 4; i++) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << "[...]";
	}
	std::cout << std::endl;
	std::cout << "After:  ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _sorted_numbers.begin();
		it != _sorted_numbers.end(); ++it)
			std::cout << *it << " ";
	} else {
		std::vector<int>::const_iterator it = _sorted_numbers.begin();
		for (int i = 0; i < 4; i++, it++) {
			std::cout << *it << " ";
		}
		std::cout << "[...]";
	}
	/// to print last sorted elements (even for a list)
	// std::advance(it, size - 10);  
	
	std::cout << std::endl;
}

// static
bool	PmergeMe::isValidInput(const std::string & input) {
	if (input.empty()) {
		std::cerr << "Error: empty input" << std::endl;
		return false;
	}
	else if (input[0] == '-') {
		std::cerr << "Error" << std::endl; // negative integer
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(input[i])))
		{
			std::cerr << "Error: " << input[i] << " not a digit" << std::endl;
			return false;
		}
	}
	return true;
}

bool PmergeMe::parseString(const std::string & inputstr, std::vector<int> & numbers) {
	
	std::istringstream iss(inputstr);
	long number = 0;
	if (!(iss >> number) || !iss.eof()) {
		std::cerr << "Error: Invalid integer conversion." << std::endl;
		return false;
	}
	if (number > INT_MAX || number < 0) {
		std::cerr << "Error" << std::endl;
		return false;
	}
	numbers.push_back(static_cast<int>(number));
	
	return true;
}

bool PmergeMe::isDuplicates(const std::vector<int> & numbers) {
	std::set<int> seen;
    
    for (std::vector<int>::const_iterator it = numbers.begin(); 
         it != numbers.end(); ++it) {
        if (seen.find(*it) != seen.end()) {
			std::cerr << "Duplicate found" << std::endl;
            return true; 
        }
        seen.insert(*it);
    }
    return false;
}
