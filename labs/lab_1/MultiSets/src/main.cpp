#include <iostream>
#include "MultiSets.hpp"

int main(){
    MultiSet set;
    std::cin >> set;
    std::cout << "Cardinality: " << set.getCardinality() << std::endl;
    std::cout << set << std::endl;
    return 0;
}