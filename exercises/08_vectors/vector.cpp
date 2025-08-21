#include <iostream>
#include <vector>

int main() {
   

    // Create a vector and add elements using push_back (C++98 way)
    std::vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);
    
    // Access elements using subscript operator (0-based indexing)
    std::cout << "First element: " << numbers[0] << std::endl;   // 10
    std::cout << "Third element: " << numbers[2] << std::endl;   // 30
    
    // Modify elements using subscript operator
    numbers[1] = 99;
    std::cout << "Modified second element: " << numbers[1] << std::endl; // 99
    
    // You can also use it with variables as index
    int index = 4;
    std::cout << "Element at index 4: " << numbers[index] << std::endl; // 50
    
    // Safe access with bounds checking
    try {
        std::cout << numbers.at(10) << std::endl; // Throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "Index out of range!" << std::endl;
    }

    return 0;
}

/**
 * C++98 doesn't support brace initialization.
 * 
 *  Create a vector with some initial values
    std::vector<int> numbers = {10, 20, 30, 40, 50};
 */