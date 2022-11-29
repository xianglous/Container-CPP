// Container.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "vector.h"
#include "linked_list.h"

using namespace Containers;

template<typename T, template<typename...T> class V>
void printVector(const V<T>& vec) {
    std::cout << "Vector of size " << vec.size() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }
}

template<typename T, template<typename...T> class V>
void printIterate(const V<T>& iter) {
    std::cout << "Iterable of size " << iter.size() << std::endl;
    for (const T & val : iter) {
        std::cout << val << std::endl;
    }
}

int main()
{
    Vector<int> vec = { 4, 5, 6 };
    LinkedList<int> list{ 1, 2, 3 };
    printIterate(LinkedList<int>());
    vec.insert(vec.end(), vec.begin(), vec.end());
    printIterate(vec);
    list.insert(list.begin(), vec.begin(), vec.end());
    printIterate(list);
    list.erase(list.begin() + 2, list.begin() + 5);
    printIterate(list);
    vec.erase(vec.begin() + 1, vec.end() - 1);
    printIterate(vec);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
