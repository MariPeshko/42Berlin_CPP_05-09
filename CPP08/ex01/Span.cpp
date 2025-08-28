/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:28 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/28 22:11:13 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "Span.hpp"

Span::Span( void ) :  _N(1)
{ std::cout << "Span Default Constructor" << std::endl; }

Span::Span( unsigned int N ) : _N(N) { };

// Copy Constructor
Span::Span ( Span const & src ) : _N(src.getN()) { }

// Assignment operator 
Span &	Span::operator=( Span const &assign ) {
	
	if (this != &assign) {
		this->_N = assign._N;
	}
    return *this;
}

Span::~Span() { };

unsigned int Span::getN() const {
	return this->_N;
}

std::ostream &	operator<<(std::ostream &o, Span const &i) {

    o << "Span object of " << i.getN() << " maximum elements.";
	o << std::endl;
    return o;

}
