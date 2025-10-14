/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:52:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/14 16:54:46 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>



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
	if (PmergeMe::isDuplicates(numbers))
		return 1;
	
	PmergeMe	SortObj(numbers);
	SortObj.sort();
	SortObj.display();

	return 0;
}
