#include <iostream>
#include "Sets.hpp"

int main(){
    Set set;
    std::cin >> set;
    std::cout << "Cardinality: " << set.getCardinality() << std::endl;
    std::cout << set << std::endl;
    return 0;
}