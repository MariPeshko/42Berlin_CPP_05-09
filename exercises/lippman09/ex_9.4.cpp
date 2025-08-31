#include <vector>
#include <algorithm>
#include <iostream>

// The function signature takes two iterators and the value
std::vector<int>::iterator easyfind(std::vector<int>::iterator begin, 
        std::vector<int>::iterator end, int value) {

    // std::find works directly on a range defined by two iterators
    return std::find(begin, end, value);

}

int main() {

    //std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7}; // c++11

    std::vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    numbers.push_back(7);

    // To call the function, pass the iterators from the container
    std::vector<int>::iterator it = easyfind(numbers.begin(), numbers.end(), 6);

    // Check if the value was found
    if (it != numbers.end()) {
        std::cout << "Value found at position: " << std::distance(numbers.begin(), it) << std::endl;
    } else {
        std::cout << "Value not found." << std::endl;
    }

    return 0;
}