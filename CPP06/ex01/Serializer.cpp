/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:53:31 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 12:27:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

Serializer::Serializer( void ) { }

Serializer::Serializer ( const Serializer & other ) {
	(void)other;
}

Serializer & Serializer::operator=( const Serializer &assign) {
	(void)assign;
	return *this;
}

Serializer::~Serializer( void ) {}

/**
 * It takes a pointer and converts it to the unsigned integer type uintptr_t.
 */
uintptr_t	Serializer::serialize(Data* ptr) {
	
	uintptr_t a = reinterpret_cast<uintptr_t>(ptr);
	return a;
	
}

/**
 * It takes an unsigned integer parameter and converts it to a pointer to Data.
 */
Data*		Serializer::deserialize(uintptr_t raw) {

	return reinterpret_cast<Data *>(raw);
	
}
