/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/13 16:17:14 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <iostream>
/* #include <sstream>
#include <stdexcept> */

class PmergeMe {
	private:
		std::vector<int> _numbers;

		// Core algorithm functions
		// void fordJohnsonSort(std::vector<int>& vec);
		// void insertIntoMainChain(std::vector<int>& mainChain, int value);
		// std::vector<int> generateJacobsthalSequence(int n);
		
		// // Utility functions
		// bool	isValidInput(const std::string & input);
		// void parse(int argc, char** argv);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& assign);
		
		/* void sort(int argc, char** argv);
    	void display(); */
};

#endif
