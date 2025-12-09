/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:52:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/09 15:05:20 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sys/time.h>

int main(int argc, char **argv) {
	
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int>	numbersVec;
	std::deque<int>		numbersDeq;
	
	for (int i = 1; i < argc; i++) {
		std::string input = argv[i];
		if (!PmergeMe::isValidInput(input))
			return 1;
		if (!PmergeMe::parseString(input, numbersVec))
			return 1;
	}
	if (PmergeMe::isDuplicates(numbersVec))
		return 1;
	numbersDeq.assign(numbersVec.begin(), numbersVec.end());
	
	// Vector sorting
	struct timeval begin;
	struct timeval end;
	gettimeofday(&begin, NULL);
	PmergeMe	SortVec(numbersVec);
	SortVec.VecFordJohnsonSort(numbersVec);
	gettimeofday(&end, NULL);
	SortVec.timeDiffVec(begin, end);
	
	PmergeMe::nbr_of_comps = 0;

	// Deque sorting
	gettimeofday(&begin, NULL);
	PmergeMe	SortDeque(numbersDeq);
	SortDeque.DeqFordJohnsonSort(numbersDeq);
	gettimeofday(&end, NULL);
	SortDeque.timeDiffDeq(begin, end);

	// Displaying
	SortVec.VecDisplay();
	SortVec.displayVecTime();
	SortDeque.displayDeqTime();
	SortVec.displayVecComparisons();

	return 0;
}
