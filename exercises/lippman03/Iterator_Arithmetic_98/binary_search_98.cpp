
#include <iostream>

#include <vector>

#include <string>

/**
 * TO run a program:
 * 
 * ./binary_search_98 < ../data/sorted_list
 * 
 */

int main(void)
{
    std::vector<std::string> text;
    std::string line;

    while (std::getline(std::cin, line))
        text.push_back(line);

    std::string sought = "f";

    // beg and end will denote the range we’re searching
    std::vector<std::string>::iterator beg = text.begin();
    std::vector<std::string>::iterator end = text.end();

    std::vector<std::string>::iterator mid = beg + (end - beg) / 2; // original midpoint

    // while there are still elements to look at and we haven’t yet found sought
    while (mid != end && *mid != sought) {
        if (sought < *mid) // is the element we want in the first half?
            end = mid;     // if so, adjust the range to ignore the second half
        else               // the element we want is in the second half
            beg = mid + 1; // start looking with the element just after mid
        mid = beg + (end - beg) / 2; // new midpoint
    }

    if (mid != text.end() && *mid == sought)
        std::cout << "It is found on the line " << (mid - text.begin()) + 1 << std::endl;
    else
        std::cout << "There is no " << sought << " in the text." << std::endl;

    return 0;
}
