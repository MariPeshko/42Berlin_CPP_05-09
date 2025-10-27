/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:52:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/27 18:28:00 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>

// ./PmergeMe 5 7 6 8 9 10 1 4 2 3

int main(int argc, char **argv) {
	
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int>	numbers;
	
	for (int i = 1; i < argc; i++) {
		std::string input = argv[i];
		if (!PmergeMe::isValidInput(input))
			return 1;
		if (!PmergeMe::parseString(input, numbers))
			return 1;
	}
	if (PmergeMe::isDuplicates(numbers)) // probably will be removed
		return 1;
	
	PmergeMe	SortObj(numbers);
	SortObj.sort(numbers);
	SortObj.display();

	return 0;
}
