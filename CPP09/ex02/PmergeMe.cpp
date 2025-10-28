/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/28 13:58:54 by mpeshko          ###   ########.fr       */
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

// Знаходимо правильну позицію для вставки (binary search)
void PmergeMe::insertInSortedVector(std::vector<int>& vec, int value) {
    
    size_t left = 0;
    size_t right = vec.size();
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    // Вставляємо на знайдену позицію
    vec.insert(vec.begin() + left, value);
}

/* sortPairs(): Тільки сортує пари по larger елементах */
void PmergeMe::sortPairs(std::vector<Pair>& pairs, int unpaired, bool has_unpaired) {
    std::cout << "sortPairs() called with " << pairs.size() << " pairs";
	/* std::cout << "pairs[0] larger " << pairs[0].larger << std::endl;
	std::cout << "pairs[0] smaller " << pairs[0].smaller << std::endl; */
    if (has_unpaired) {
        std::cout << " + unpaired: " << unpaired;
    }
    std::cout << std::endl;

	// Debug output
    std::cout << "pairs: ";
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    }
    if (has_unpaired) {
        std::cout << " + unpaired: " << unpaired;
    }
    std::cout << std::endl;
	
	// Base cases for pair sorting
    if (pairs.empty()) {
        return;
    }
    
    if (pairs.size() == 1 && !has_unpaired) {
		std::cout << "sortPairs base case: size is 1 and no unpaired" << std::endl;
        return ; // Single pair, already sorted
    }
    
    if (pairs.size() == 2 && !has_unpaired) {
        if (pairs[0].larger > pairs[1].larger) {
            std::swap(pairs[0], pairs[1]);
        }
        return;
    }
    
    // Extract larger elements (a1, a2, a3, ...) for recursive sorting
    std::vector<int> larger_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger_elements.push_back(pairs[i].larger);
    }
    
    // Add unpaired element to the sorting process
    if (has_unpaired) {
        larger_elements.push_back(unpaired);
        std::cout << "Adding unpaired " << unpaired << " to larger elements" << std::endl;
    }
    
    std::cout << "Before recursive sort: ";
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        std::cout << larger_elements[i] << " ";
    }
    std::cout << std::endl;
    
    // РЕКУРСИВНО сортуємо larger elements як НОВІ ПАРИ
    // Створюємо пари з larger_elements і рекурсивно сортуємо їх
    if (larger_elements.size() > 1) {
        std::vector<Pair> sub_pairs;
        int sub_unpaired = 0;
        bool sub_has_unpaired = false;
        
        if (larger_elements.size() % 2 != 0) {
            sub_has_unpaired = true;
            sub_unpaired = larger_elements.back();
        }
        
        // Створюємо пари з larger_elements
        for (size_t i = 0; i < larger_elements.size() - (sub_has_unpaired ? 1 : 0); i += 2) {
            Pair p;
            if (larger_elements[i] > larger_elements[i + 1]) {
                p.larger = larger_elements[i];
                p.smaller = larger_elements[i + 1];
            } else {
                p.larger = larger_elements[i + 1];
                p.smaller = larger_elements[i];
            }
            sub_pairs.push_back(p);
        }

		//////
        
        // РЕКУРСИВНИЙ ВИКЛИК sortPairs()
        sortPairs(sub_pairs, sub_unpaired, sub_has_unpaired);

		// Debug output
    	std::cout << "sortPairs() after recursion. Sorted pairs: ";
    	for (size_t i = 0; i < sub_pairs.size(); ++i) {
      	  std::cout << "(" << sub_pairs[i].smaller << "," << sub_pairs[i].larger << ") ";
		}
    	if (sub_has_unpaired) {
        	std::cout << " + unpaired: " << sub_unpaired;
    	}
    	std::cout << std::endl;

		///////
		
		// Витягуємо відсортовані larger elements
        larger_elements.clear();
		// sub_pairs вже відсортовані по larger елементах після рекурсії
		// Створюємо main chain з larger елементів
		std::vector<int> main_chain;
		std::vector<int> pend_elements;

		for (size_t i = 0; i < sub_pairs.size(); ++i) {
    		main_chain.push_back(sub_pairs[i].larger);
    		pend_elements.push_back(sub_pairs[i].smaller);
		}

		// Початкова основа - main chain (вже відсортована)
	larger_elements = main_chain;

	// Вставляємо pend елементи ВРУЧНО (без std::lower_bound)
	for (size_t i = 0; i < pend_elements.size(); ++i) {
		insertInSortedVector(larger_elements, pend_elements[i]);
	}

	// Вставляємо unpaired елемент
	if (sub_has_unpaired) {
		insertInSortedVector(larger_elements, sub_unpaired);
	}
    
    std::cout << "After recursive sort: ";
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        std::cout << larger_elements[i] << " ";
    }
    std::cout << std::endl;
    
    // Reorder pairs based on sorted larger elements (excluding unpaired)
    // Reorder original pairs based on sorted larger elements
    std::vector<Pair> sorted_pairs;
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        if (has_unpaired && larger_elements[i] == unpaired) {
            continue;
        }
        
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].larger == larger_elements[i]) {
                sorted_pairs.push_back(pairs[j]);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }
	
    pairs = sorted_pairs;
}
}

void PmergeMe::sort(std::vector<int>& vec) {
    // Викликається ТІЛЬКИ ОДИН РАЗ на початку
    std::cout << "sort() called ONCE with: ";
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
    
    // Step 1: Create pairs and handle unpaired element
    std::vector<Pair> pairs;
    int unpaired_element = 0;
    bool has_unpaired = false;
    
    if (vec.size() % 2 != 0) {
        has_unpaired = true;
        unpaired_element = vec.back();
    }
    
    // Create pairs from adjacent elements
    for (std::vector<int>::const_iterator it = vec.begin();
         it != vec.end(); ) {
        if ((it + 1) == vec.end()) {
            break; // Odd number, last element handled above
        }
        
        Pair p;
        if (*it > *(it + 1)) {
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

	// Debug output
    std::cout << "Sort(). Sorted pair before sortPairs(): ";
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    }
    if (has_unpaired) {
        std::cout << " + unpaired: " << unpaired_element;
    }
    std::cout << std::endl;
    
    // Step 2: Sort pairs recursively
    sortPairs(pairs, unpaired_element, false);
    
	// Debug output
    std::cout << "Sort(). Sorted pairs: ";
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    }
    if (has_unpaired) {
        std::cout << " + unpaired: " << unpaired_element;
    }
    std::cout << std::endl;
	
    // Step 3: Build final result
    buildSortedVector(vec, pairs, unpaired_element, has_unpaired);
}

void PmergeMe::buildSortedVector(std::vector<int>& vec, std::vector<Pair>& pairs, int unpaired_element, bool has_unpaired) {
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
    
    if (has_unpaired) {
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
