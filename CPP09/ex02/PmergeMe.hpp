/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/14 19:04:47 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
/* #include <sstream>
#include <stdexcept> */

class PmergeMe {
	private:
		std::vector<int>	_numbers;
		std::vector<int>	_sorted_numbers;
		int					_size;

		// Core algorithm functions
		// void fordJohnsonSort(std::vector<int>& vec);
		// void insertIntoMainChain(std::vector<int>& mainChain, int value);
		// std::vector<int> generateJacobsthalSequence(int n);
		
		// // Utility functions
		
		

	public:
		PmergeMe(const std::vector<int> & _numbers);
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& assign);
		
		void sort();
    	void display();

		static bool	isValidInput(const std::string & input);
		static bool parseString(const std::string & inputstr, std::vector<int> & numbers);
		static bool isDuplicates(const std::vector<int> & numbers);
};



#endif
