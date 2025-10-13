/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:52:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/13 14:58:42 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
	
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	std::string	input = argv[1];
	PmergeMe	process;
	process.Calculate(input);

	return 0;
}
