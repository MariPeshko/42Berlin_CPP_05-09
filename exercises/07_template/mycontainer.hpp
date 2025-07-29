#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <iostream> 

// Forward declaration of a non-template helper function
// This function doesn't depend on T directly, but is used by the template's member function.
// It's the template provider's job to declare it.
void print_separator();

// --- MyContainer Class Template Definition ---
template <typename T>
class MyContainer {
public:
    MyContainer(const T& val1, const T& val2) : elem1(val1), elem2(val2) {}

    void print() const {
        std::cout << "Elements: "; // std::cout is a name that does NOT depend on T
        print_separator();         // print_separator() is a name that does NOT depend on T
        std::cout << elem1;        // elem1's type (T) DEPENDS on the template parameter
        print_separator();
        std::cout << elem2;        // elem2's type (T) DEPENDS on the template parameter
        std::cout << std::endl;
    }

private:
    T elem1;
    T elem2;
};

// --- Definition of the helper function ---
// This definition must also be in the header if it's used by an inline/template function
void print_separator() {
    std::cout << " | ";
}

#endif // MYCONTAINER_H