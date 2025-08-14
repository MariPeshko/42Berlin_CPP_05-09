/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:21:59 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/14 12:55:26 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ARRAY_HPP
# define ARRAY_HPP

#include <iostream>


template <typename T>
class Array {
	
private:
	T *				_array;
	unsigned int	_size;

public:
    // Orthodox Canonical Form
    Array();
    Array(unsigned int n);
	~Array();
	Array(const Array& copy);
	Array&		operator=(const Array& assign);

	// Subscript Operator Overloading 
	T&			operator[](const unsigned int &index);
	const T&	operator[](const unsigned int &index) const;
	
	const unsigned int	size() const;
};

// Include the template implementation at the end
#include "Array.tpp"  

#endif
