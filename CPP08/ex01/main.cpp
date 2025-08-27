/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:42 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/27 20:05:35 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <exception>

int	main( void )
{
	Span test(5);
	std::cout << test;

	Span def;
	std::cout << def;

	return 0;
}

