/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:28 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/31 13:42:59 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <climits>

// Default constructor
Span::Span( void ) :  _N(1) {
	_numbers.reserve(1);
}

// Parameterized constructor
Span::Span( unsigned int N ) : _N(N) {
	_numbers.reserve(N);
};

// Copy Constructor
Span::Span ( Span const & src ) :
	_N(src.getN()),
	_numbers(src._numbers)
{ }

// Assignment operator 
// Capacity check to maintain class consistency.
Span &	Span::operator=( Span const &assign ) {

	std::cout << "Assignment operator" << std::endl;
	if (this != &assign) {
		if (this->_N < assign._numbers.size()) {
			throw std::runtime_error("Cannot assign: not enough capacity");
		}
		this->_numbers = assign._numbers;
	}
	return *this;
	
}

Span::~Span() { };

unsigned int	Span::getN() const {
	return this->_N;
}

void	Span::addNumber(int number) {
	if (_numbers.size() >= _N) {
		throw std::length_error("Exception: Span is full");
	}
	_numbers.push_back(number);
}

/* find out the longest span (or distance, if you prefer) 
between all the numbers stored, and return it.
It works for INT_MAX and INT_MIN */
unsigned long	Span::longestSpan() const {

	if (this->_numbers.size() < 2)
		throw std::runtime_error("Exception: less than 2 numbers stored");
	int min_elem = *std::min_element(_numbers.begin(), _numbers.end());
    int max_elem = *std::max_element(_numbers.begin(), _numbers.end());
	unsigned long result = static_cast<unsigned long>(max_elem) - static_cast<unsigned long>(min_elem);
	return result;
}

/* find out the shortest span (or distance, if you prefer) 
between all the numbers stored, and return it */
unsigned long	Span::shortestSpan() const {
	
	if (this->_numbers.size() < 2)
		throw std::runtime_error("Exception: less than 2 numbers stored");
	
	std::vector<int> copy = this->_numbers;
	sort(copy.begin(), copy.end());

	/* for (std::vector<int>::const_iterator it = copy.begin(); 
			it != copy.end(); ++it)
				std::cout << *it << " ";
	std::cout << std::endl; */

	unsigned long shortSpan = ULONG_MAX;
	for (std::vector<int>::const_iterator it = copy.begin(); 
		it != copy.end() - 1; ++it)				// Stop before last element
	{
		unsigned long current_span = static_cast<unsigned long>(*(it + 1)) - 
									static_cast<unsigned long>(*it);
		if (current_span < shortSpan)
			shortSpan = *(it + 1) - *it;
	}
	return shortSpan;
}

void	Span::print() const {
	std::cout << "Span object of " << this->getN() << " elements: ";
	for (std::vector<int>::const_iterator it = _numbers.begin(); 
			it != _numbers.end(); ++it)
				std::cout << *it << " ";
	std::cout << std::endl;
}

void	Span::addManyNumbers(std::vector<int> & v) {
	
	// this->_numbers = v; // copy approach

	// check it later
/* 	if (_numbers.size() + std::distance(first, last) > _N)
        throw std::length_error("Not enough space in Span"); */
	
	// range of iterators
	// insert copies all elements into _numbers.
	//iterator insert(iterator position, InputIterator first, InputIterator last);
	_numbers.clear(); // removes all existing numbers
	_numbers.insert(_numbers.begin(), v.begin(), v.end());
	
	return ;
}

/* // version 2
void Span::addManyNumbers(const std::vector<int>& v) {
    if (v.size() > _N)
        throw std::length_error("Too many numbers for Span");

    _numbers.assign(v.begin(), v.end());
} */

std::ostream &	operator<<(std::ostream &o, Span const &i) {

    o << "Span object of " << i.getN() << " maximum elements.";
	o << std::endl;
    return o;

}
