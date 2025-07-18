/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:02:14 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/18 18:33:22 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <string>

int	main (int argc, char **argv) {

	if (argc == 1 || argc > 2) {
		std::cout << "Usage: ./convert <string literal>" << std::endl;
		return 0;
	}
	return ScalarConverter::convert(argv[1]);;
}