/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:03:08 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 20:38:12 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
	
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	std::string	input = argv[1];
	RPN			process;
	process.Calculate(input);

	return 0;
}
