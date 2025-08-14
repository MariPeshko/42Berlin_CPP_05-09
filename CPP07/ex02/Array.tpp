/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:30:06 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/14 12:56:23 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>
#include <stdexcept>

// Default constructor
// Construction with no parameter: Creates an empty array
template <typename T>
Array<T>::Array( void ) :
	_array(NULL), _size(0)
{ };

/**
 * Parametrized constructor.
 * Construction with an unsigned int n as a parameter:
 * Creates an array of n elements initialized by default.
 */
template <typename T>
Array<T>::Array( unsigned int n ) :
	_array(new T[n]() ), _size(n)
{ };

// Copy Constructor
template <typename T>
Array<T>::Array ( Array const & src ) :
	_array(new T[src._size]()), _size(src._size)
{ 
	for (unsigned int i = 0; i < _size; i++) {
		_array[i] = src._array[i];
	}
}

// Assignment operator 
template <typename T>
Array<T> &	Array<T>::operator=( Array const &assign ) {
	
	if (this != &assign) {
		delete[] this->_array;
		this->_size = assign._size;
		this->_array = new T[this->_size]();
		for (unsigned int i = 0; i < this->_size; i++) {
			this->_array[i] = assign._array[i];
		}
	}
    return *this;
}

// Destructor
template <typename T>
Array<T>::~Array() { 

	delete[] _array;
	
};

template <typename T>
T &	Array<T>::operator[](const unsigned int &index) {
	
	if (index >= this->_size)
		throw std::out_of_range("Array index out of range");
	return this->_array[index];
	
}

/**
 * const version
 * to handle const objects and const references
 */
template <typename T>
const T & Array<T>::operator[](const unsigned int &index) const {

    if (index >= this->_size)
        throw std::out_of_range("Array index out of range");
    return this->_array[index];
	
}

/**
 *  A member function size() that returns the number of 
 * elements in the array. This member function takes 
 * no parameters and must not modify the current instance.
 */
template <typename T>
const unsigned int	Array<T>::size( ) const {

	return this->_size;
	
}
