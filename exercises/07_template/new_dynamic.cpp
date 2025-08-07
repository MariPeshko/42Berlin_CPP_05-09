#include <iostream>
#include <vector>

int main() {

    int *arr = new int[5](); // Creates array: {0, 0, 0, 0, 0}
                //  ^  ^  ^
                //  |  |  |
                //  |  |  +-- Parentheses for value initialization
                //  |  +-- Array size (n elements)
                //  +-- Type of elements
	//int arr[] = {10, 20, 30, 40, 50};
    std::cout << "First element: " << arr[0] << std::endl; 
    delete[] arr;


    // Without parentheses:
    // Creates array with UNINITIALIZED values (garbage)
	int	*arr2 = new int[5];  
    std::cout << "First element: " << arr2[0] << std::endl; 
	delete[] arr2;     

    return 0;
}

