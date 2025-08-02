#include <iostream>

void func1() { std::cout << "func1\n"; }
void func2() { std::cout << "func2\n"; }
int add(int a, int b) { return a + b; }

template <typename T> 
void fobj(T param1, T param2) {  // Functions convert to function pointers
    std::cout << "fobj: T = " << typeid(T).name() << std::endl;
    param1();  // Can call through function pointer
    param2();
}

template <typename T> 
void fref(const T& param1, const T& param2) {  // Functions keep their types
    std::cout << "fref: T = " << typeid(T).name() << std::endl;
    param1();  // Can still call
    param2();
}

int main() {
    // This works: function names convert to function pointers
    fobj(func1, func2);  // T deduced as void(*)()
    
    // This also works: both functions have same signature
    fref(func1, func2);  // T deduced as void()
    
    return 0;
}
