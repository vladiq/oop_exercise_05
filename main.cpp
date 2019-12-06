#include <iostream>
#include <algorithm>

#include "list.hpp"
#include "square.hpp"

int main() {
    container::list<Square<double>> list;
    int command, pos;

    while(true) {
        std::cout << std::endl;
        std::cout << "0 - quit" << std::endl;
        std::cout << "1 - add element to list by index or push front" << std::endl;
        std::cout << "2 - delete element from list (pop front / erase by index / erase by iterator)" << std::endl;
        std::cout << "3 - range-based for print" << std::endl;
        std::cout << "4 - count_if example" << std::endl;
        std::cout << "5 - print element by [index]" << std::endl;
        std::cin >> command;

        if(command == 0) {
            break;

        } else if(command == 1) {
            std::cout << "Enter coordinates" << std::endl;
            Square<double> square(std::cin);

            std::cout << "1 - PushFront" << std::endl;
            std::cout << "2 - insert by index" << std::endl;
            std::cin >> command;
            if(command == 1) {
                list.push(square);
                continue;
            } else if(command == 2) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                list.insert(pos, square);
                continue;
            } else {
                std::cout << "Wrong command" << std::endl;
                std::cin >> command;
                continue;
            }

        } else if(command == 2) {
            std::cout << "1 - erase by index" << std::endl;
            std::cout << "2 - erase by iterator" << std::endl;
            std::cout << "3 - pop front" << std::endl;
            std::cin >> command;
            if(command == 1) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                list.erase(pos);
                continue;
            } else if(command == 2) {
                std::cout << "Enter index" << std::endl;
                std::cin >> pos;
                auto temp = list.begin();
                for(int i = 0; i < pos; ++i) {
                    ++temp;
                }
                list.erase(temp);
                continue;

            } else if (command == 3) {
                try {
                    list.popFront();
                } catch(std::exception& e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
            } 
            else {
                std::cout << "Wrong command" << std::endl;
                std::cin >> command;
                continue;
            }

        } else if(command == 3) {
            for(const auto& item : list) {
                item.Print();
                continue;
            }

        } else if(command == 4) {
            std::cout << "Enter required area" << std::endl;
            std::cin >> pos;
            std::cout << "Number of squares with area less than " << pos << " equals ";
            std::cout << std::count_if(list.begin(), list.end(), [pos](Square<double> square) {return square.Area() < pos;}) << std::endl;
            continue;

        } else if (command == 5) {
            std::cout << "Enter index to print for" << std::endl;
            std::cin >> pos;
            try {
                list[pos].Print();
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            continue;

        } else {
            std::cout << "Wrong command" << std::endl;
            continue;
        }
    }

    return 0;
}

