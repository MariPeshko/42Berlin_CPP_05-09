/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:01:52 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/19 19:41:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <cstdint>

int	main( void ) {

	Data *d_ptr = new Data;

	std::cout << "Data *d_ptr: " << d_ptr << std::endl;
	std::cout << "Data *d_ptr string: " << d_ptr->name << std::endl;
	
	uintptr_t t = Serializer::serialize(d_ptr);
	std::cout << "uintptr_t t: " << t << std::endl;

	Data *ret = Serializer::deserialize(t);
	std::cout << "Data *ret:   " << ret << std::endl;

	std::cout << "Data *ret string: " << ret->name << std::endl;
	
	delete d_ptr;
	return 0;
	
}