#include <vector>
#include <algorithm>
#include <iostream>

// The function signature takes two iterators and the value
bool	findInt(std::vector<int>::iterator begin, 
        std::vector<int>::iterator end, int value) {
    
    std::vector<int>::iterator it = std::find(begin, end, value);
    bool res = false;
    if (it != end)
            res = true;
    return res;

}

int	main() {
	
	//std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7}; // c++11

    std::vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    numbers.push_back(7);

	int nmbToFind = 8;

    // To call the function, pass the iterators from the container
    bool finder = findInt(numbers.begin(), numbers.end(), nmbToFind);
	if (finder == true)
		std::cout << nmbToFind << " is in this vector" << std::endl;
	else
		std::cout << nmbToFind << " is NOT in this vector" << std::endl;

    return 0;
}