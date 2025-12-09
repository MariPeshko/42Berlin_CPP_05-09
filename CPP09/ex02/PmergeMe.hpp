/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/09 15:04:31 by mpeshko          ###   ########.fr       */
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
#define DEBUG_PART1 0
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
		void	createPairs(std::deque<Pair> &pairs, const std::deque<int> &vec, 
					int &unpaired_element, bool &has_unpaired);
		// Step 2: Extract larger elements (in fordJohnsonSort() )
		// Step 3: Sort recursively. Call fordJohnsonSort()
		// Step 4: Reorder pairs based on sorted larger elements
		template  < typename PairContainer, typename ElementContainer >
		void	reorderPairs(PairContainer &pairs, ElementContainer &larger_elements)
		{
			PairContainer reordered_pairs;
			for (size_t i = 0; i < larger_elements.size(); ++i)	{
				for (typename PairContainer::iterator it = pairs.begin(); it != pairs.end(); ++it)
				{
					if (it->larger == larger_elements[i]) {
						reordered_pairs.push_back(*it);
						pairs.erase(it); // Delete the pair found
						break;
					}
				}
			}
			pairs = reordered_pairs;
		}

		// Step 5: Build final result
		void	buildSortedVector(std::vector<int>& vec, const std::vector<Pair>& pairs, 
					int unpaired_element, bool has_unpaired);
		void	buildSortedDeq(std::deque<int> &deq, const std::deque<Pair> &pairs,
					int unpaired_element, bool has_unpaired);
		
		// Utility functions
		std::vector<size_t>	generateJacobsthalSequence(size_t n);
		std::vector<size_t>	generateInsertionOrder(size_t pend_size);
		// Binary search for insertion with a bound
		template<typename Container>
		void				insertInSortedContainer(Container &container, int value, size_t bound)
		{
			size_t left = 0;
			size_t right = bound;

			while (left < right) {
				size_t mid = left + (right - left) / 2;
				PmergeMe::nbr_of_comps++;
				if (container[mid] < value) {
					left = mid + 1;
				} else {
					right = mid;
				}
			}
			container.insert(container.begin() + left, value);
		}
		
		// µs (microsecond) is a unit of time equal to one-millionth of a second
		long	_totalUsVec;
		long	_totalUsDeq;
		unsigned int _vec_comparisons;
		unsigned int _deq_comparisons;
		
	public:
		PmergeMe(const std::vector<int> &parsed_numbers);
		PmergeMe(const std::deque<int> &parsed_numbers);
		~PmergeMe();
		
		static long long	fordJohnsonWorstCase(int n);
		static int			nbr_of_comps;
		static int			nbr_of_recur;
		
		void		VecFordJohnsonSort(std::vector<int>& vec);
		void		DeqFordJohnsonSort(std::deque<int>& vec);
		void		timeDiffVec(const struct timeval & begin, const struct timeval & end);
		void		timeDiffDeq(const struct timeval & begin, const struct timeval & end);
		void		VecDisplay();
		void		DeqDisplay();
		void		displayVecTime();
		void		displayDeqTime();
		void		displayVecComparisons();
		
		// Parsing
		static bool	isValidInput(const std::string & input);
		static bool	parseString(const std::string & inputstr, std::vector<int> & numbers);
		static bool	isDuplicates(const std::vector<int> & numbers);
		// Utils
		template  < typename Container >
		static bool	isSortedAscending(const Container& sorted_numbers)
		{
			if (sorted_numbers.size() < 2) return true;
			
			for (size_t i = 1; i < sorted_numbers.size(); ++i) {
				if (sorted_numbers[i - 1] > sorted_numbers[i]) return false;
			}
			return true;
		}
};

#endif
