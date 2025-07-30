#include "mycontainer.hpp" // User includes the template definition

#include <string> // User needs std::string, so they include its header
#include <vector> // User needs std::vector, so they include its header

// A custom class that the user wants to put into MyContainer
class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}

    // User must provide an operator<< for Point if they want to print it
    // because MyContainer<Point>::print() will try to do std::cout << elem1;
    // This 'operator<<' DEPENDS on the template parameter 'Point'.
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x_ << ", " << p.y_ << ")";
    }

private:
    int x_;
    int y_;
};

int main() {
    // Instantiation 1: T is int
    MyContainer<int> int_container(10, 20);
    int_container.print(); // Works because int has operator<< (builtin)

    std::cout << "--------------------" << std::endl;

    // Instantiation 2: T is std::string
    MyContainer<std::string> string_container("hello", "world");
    string_container.print(); // Works because std::string has operator<< (from <string>)

    std::cout << "--------------------" << std::endl;

    // Instantiation 3: T is Point
    MyContainer<Point> point_container(Point(1, 2), Point(3, 4));
    point_container.print(); // Works because WE (the user) provided operator<< for Point

    // Instantiation 4: T is std::vector<int>

    // In C++98, you have to populate vectors element by element, 
    // or use helper functions.
    std::vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    std::vector<int> vec2;
    vec2.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);

    // This will FAIL to compile if operator<< for std::vector<int> is not visible
    // (std::vector does NOT have a default operator<<)

    MyContainer<std::vector<int> > vec_container(vec1, vec2);

    vec_container.print(); // COMPILE ERROR: No match for 'operator<<'
    // (operand types are 'std::ostream' and 'const std::vector<int>')

    return 0;
}