/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/28 12:41:55 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>	// for std::istringstream
#include <cctype>	// for std::isdigit
#include <climits>  // INT_MAX
#include <set>

#include <algorithm>

PmergeMe::PmergeMe(const std::vector<int> & parsed_numbers)
	: _numbers(parsed_numbers) {
		_size = _numbers.size();
	}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy) :
	_numbers(copy._numbers) ,
	_sorted_numbers(copy._sorted_numbers)
	{}

PmergeMe& PmergeMe::operator=(const PmergeMe& assign) {
	if (this != &assign) {
		_numbers = assign._numbers;
		_sorted_numbers = assign._sorted_numbers;
	}
	return *this;
}

/* static void display_vector(const std::vector<int> & vct) {
	for (std::vector<int>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			std::cout << *it << " ";
} */

/* У Ford-Johnson алгоритмі непарні елементи треба додавати до larger_elements 
для рекурсивного сортування! */
void	PmergeMe::merge_sort(std::vector<Pair>& pairs, int & unpaired, bool has_unpaired) {
    // Base cases
 /*    if (pairs.size() <= 1) {
        return;
    }
    
    if (pairs.size() == 2) {
        if (pairs[0].larger > pairs[1].larger) {
            std::swap(pairs[0], pairs[1]);
        }
        return;
    }
     */
    // Extract larger elements for recursive Ford-Johnson sorting
    std::vector<int> larger_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger_elements.push_back(pairs[i].larger);
    }

	// Додай непарний елемент до сортування
    if (has_unpaired) {
        larger_elements.push_back(unpaired);
    }

	std::cout << "Before recursive sort: ";
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        std::cout << larger_elements[i] << " ";
    }
    std::cout << std::endl;
    
    // Recursively sort the larger elements using Ford-Johnson
    sort(larger_elements);

	std::cout << "After recursive sort: ";
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        std::cout << larger_elements[i] << " ";
    }
    std::cout << std::endl;
    
    // Reorder pairs based on sorted larger elements
    std::vector<Pair> sorted_pairs;
	
    for (size_t i = 0; i < larger_elements.size(); ++i) {
		bool found = false;
        // Find the pair with this larger element
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].larger == larger_elements[i]) {
                sorted_pairs.push_back(pairs[j]);
                pairs.erase(pairs.begin() + j);
				found = true;
                break;
            }
        }
		// Якщо не знайдено, це непарний елемент
        if (!found && has_unpaired && larger_elements[i] == unpaired) {
            unpaired_pos = i; // Запам'ятай позицію непарного в відсортованому масиві
        }
    }
    
    pairs = sorted_pairs;
}

void PmergeMe::sort(std::vector<int>& vec) {

	std::cout << "sort() called with: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "(size=" << vec.size() << ")" << std::endl;
	
	// Base cases
	if (vec.size() <= 1) {
		return;
	}
	if (vec.size() == 2) {
		if (vec[0] > vec[1]) {
			std::swap(vec[0], vec[1]);
		}
		return;
	}
	
	// Step 1: Create pairs. a and b parts
	std::vector<Pair> pairs;
	bool odd = false;
	int unpaired_element = 0;
	
	if (vec.size() % 2 != 0) {
		odd = true;
		unpaired_element = vec.back();
	}
	
	for (std::vector<int>::const_iterator it = vec.begin();
		it != vec.end(); ) {
			if ((it + 1) == vec.end())
				break ; // Odd number, last element handled above

			Pair p;
			if (*it > *(it + 1) || *it == *(it + 1)) {
				p.larger = *it;
				p.smaller = *(it + 1);
			} else {
				p.larger = *(it + 1);
				p.smaller = *it;
			}
			pairs.push_back(p);
			
			++it;
			if (it != vec.end()) {
            	++it;
        	}
		}
		
	// Step 2: Recursively sort pairs by larger elements
	merge_sort(pairs, unpaired_element, odd);

	// Debug output
    std::cout << "Sorted pairs: ";
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    }
    if (odd) {
        std::cout << " + unpaired: " << unpaired_element;
    }
    std::cout << std::endl;

	// Step 3: Build main chain
	// Main Chain = відсортовані більші елементи
	// Step 4: Insert remaining elements using Jacobsthal sequence
	/* Ключова ідея Ford-Johnson:
	Гарантія: Кожен smaller[i] ≤ larger[i] (з порівняння пар)
	Знання: smaller[0] ≤ 3, smaller[1] ≤ 4, smaller[2] ≤ 7, тощо
	Оптимізація: Знаючи ці межі, можемо вставляти елементи з 
	мінімальною кількістю порівнянь */
	
	// Temporary: copy results back to vec
    vec.clear();
	
  	 // Спочатку додаємо ВСІ larger елементи (вони вже відсортовані після merge_sort)
    for (size_t i = 0; i < pairs.size(); ++i) {
        vec.push_back(pairs[i].larger);
    }
    
    // Step 4: Потім вставляємо smaller елементи (це буде наступний 
	// крок Ford-Johnson)
    // Поки що просто додамо їх:
    for (size_t i = 0; i < pairs.size(); ++i) {
        // Знайти правильне місце для pairs[i].smaller
        // Поки що просто додамо на початок:
        vec.insert(vec.begin(), pairs[i].smaller);
    }
    
    if (odd) {
        vec.push_back(unpaired_element);
    }

	_sorted_numbers = vec;
}

void PmergeMe::display() {
	std::cout << "Before: ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _numbers.begin();
		it != _numbers.end(); ++it)
			std::cout << *it << " ";
	}
	else {
		std::vector<int>::const_iterator it = _numbers.begin();
		for (int i = 0; i < 4; i++) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << "[...]";
	}
	std::cout << std::endl;
	std::cout << "After:  ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _sorted_numbers.begin();
		it != _sorted_numbers.end(); ++it)
			std::cout << *it << " ";
	} else {
		std::vector<int>::const_iterator it = _sorted_numbers.begin();
		for (int i = 0; i < 4; i++, it++) {
			std::cout << *it << " ";
		}
		std::cout << "[...]";
	}
	/// to print last sorted elements (even for a list)
	// std::advance(it, size - 10);  
	
	std::cout << std::endl;
}

// static
bool	PmergeMe::isValidInput(const std::string & input) {
	if (input.empty()) {
		std::cerr << "Error: empty input" << std::endl;
		return false;
	}
	else if (input[0] == '-') {
		std::cerr << "Error" << std::endl; // negative integer
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(input[i])))
		{
			std::cerr << "Error: " << input[i] << " not a digit" << std::endl;
			return false;
		}
	}
	return true;
}

bool PmergeMe::parseString(const std::string & inputstr, std::vector<int> & numbers) {
	
	std::istringstream iss(inputstr);
	long number = 0;
	if (!(iss >> number) || !iss.eof()) {
		std::cerr << "Error: Invalid integer conversion." << std::endl;
		return false;
	}
	if (number > INT_MAX || number < 0) {
		std::cerr << "Error" << std::endl;
		return false;
	}
	numbers.push_back(static_cast<int>(number));
	
	return true;
}

bool PmergeMe::isDuplicates(const std::vector<int> & numbers) {
	std::set<int> seen;
    
    for (std::vector<int>::const_iterator it = numbers.begin(); 
         it != numbers.end(); ++it) {
        if (seen.find(*it) != seen.end()) {
			std::cerr << "Duplicate found" << std::endl;
            return true; 
        }
        seen.insert(*it);
    }
    return false;
}
