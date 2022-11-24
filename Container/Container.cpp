// Container.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "vector.h"

using namespace Containers;

template<typename T>
void printVector(const Vector<T>& vec) {
    std::cout << "Vector of size " << vec.size() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }
}

int main()
{
    Vector<int> vec{ 1, 2, 3 };
    printVector(vec);
    for (int i = 4; i < 10; ++i)
        vec.push_back(i);
    printVector(vec);
    while (!vec.empty())
        vec.pop_back();
    printVector(vec);
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
