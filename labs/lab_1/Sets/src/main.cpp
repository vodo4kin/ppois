#include <iostream>
#include "Sets.hpp"
using namespace std;

int main(){
    Set set;
    set = "{a, b, c    , {{{}}}}";
    Set setTwo;
    setTwo = "{b}";
    set-=setTwo;
    cout << set << endl;
    return 0;
}