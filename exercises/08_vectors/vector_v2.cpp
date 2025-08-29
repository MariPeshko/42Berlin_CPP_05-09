#include <iostream>
#include <vector>

int main() {

	// Method 1: Using constructor with size and default value
	// Creates vector with 5 elements, all set to 0
/* 	std::vector<int> numbers(5, 0);  
	numbers[0] = 10;
	numbers[1] = 20;
	numbers[2] = 30;
	// ... assign other values
	std::cout << numbers.size() << std::endl;

	std::vector<int> numbers_more(10, 0);
	// assignment operator
	numbers = numbers_more;
	std::cout << numbers.size() << std::endl; */

	
	/* // Method 2: Using an array and vector constructor
	int arr[] = {10, 20, 30, 40, 50};
	// The vector constructor vector(first, last) expects:
	// Create vector from array
	// first: pointer to the beginning of the range
	// last: pointer to one past the end of the range
	std::vector<int> numbers(arr, arr + 5);   */

	// Method 3: Reserve space then push_back
	std::vector<int> numbers;
	numbers.reserve(5);  // Optional: pre-allocate memory for efficiency
	numbers.push_back(10);
	numbers.push_back(20);
	numbers.push_back(20);
	numbers.push_back(20);
	numbers.push_back(20);
	numbers.push_back(20);

	std::cout << numbers.size() << std::endl;
	// ... continue with other values

    return 0;
}

/**
 * C++98 doesn't support brace initialization.
 * 
 *  Create a vector with some initial values
    std::vector<int> numbers = {10, 20, 30, 40, 50};
 */