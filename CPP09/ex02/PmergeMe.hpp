/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/09 10:42:12 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>

#define DEBUG_RECURSION 0
#define DEBUG_PART2 0
#define FULL_DEBUG 0
#define Jacobsthal 0
#define SORTED 0

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define ORANGE "\033[38;5;208m"

struct	Pair {
	int	smaller;
	int	larger;
};

class PmergeMe {
	
	private:
		PmergeMe(const PmergeMe& copy);
		PmergeMe&	operator=(const PmergeMe& assign);

		std::vector<int>	_numbers_vec;
		std::deque<int>		_numbers_deque;
		std::vector<int>	_sorted_numbers_vec;
		std::deque<int>		_sorted_numbers_deque;
		int					_size;

		// Core algorithm functions
		// Step 1: 
		void	createPairs(std::vector<Pair> &pairs, const std::vector<int> &vec, 
					int &unpaired_element, bool &has_unpaired);
		// Step 2: Extract larger elements (in fordJohnsonSort() )
		// Step 3: Sort recursively. Call fordJohnsonSort()
		// Step 4: Reorder pairs based on sorted larger elements
		void	reorderPairs(std::vector<Pair> & pairs,
					const std::vector<int> &larger_elements);
		// Step 5: Build final result
		void	buildSortedVector(std::vector<int>& vec, const std::vector<Pair>& pairs, 
					int unpaired_element, bool has_unpaired);
		
		// Utility functions
		std::vector<size_t>	generateJacobsthalSequence(size_t n);
		std::vector<size_t>	generateInsertionOrder(size_t pend_size);
		void				insertInSortedVector(std::vector<int>& vec, int value, size_t bound);
	
		// µs (microsecond) is a unit of time equal to one-millionth of a second
		long	_totalUsVec;
		long	_totalUsDeq;
		
	public:
		PmergeMe(const std::vector<int> &parsed_numbers);
		PmergeMe(const std::deque<int> &parsed_numbers);
		~PmergeMe();
		
		static long long	fordJohnsonWorstCase(int n);
		static int			nbr_of_comps;
		static int			nbr_of_recur;
		
		void		fordJohnsonSort(std::vector<int>& vec);
		void		timeDiffVec(const struct timeval & begin, const struct timeval & end);
		void		timeDiffDeq(const struct timeval & begin, const struct timeval & end);
		void		displayVec();
		void		displayVecTime();
		void		displayDeqTime();
		void		displayVecComparisons();
		
		// Parsing
		static bool	isValidInput(const std::string & input);
		static bool	parseString(const std::string & inputstr, std::vector<int> & numbers);
		static bool	isDuplicates(const std::vector<int> & numbers);
		// Utils
		static bool	isSortedAscending(const std::vector<int>& vec);
};

#endif
