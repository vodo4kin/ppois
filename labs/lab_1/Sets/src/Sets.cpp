#include <iostream>
#include "Sets.hpp"

bool Set::isValid(const std::string& str) const {
    int balance = 0;
    bool expectElement = true;
    bool afterComma = false;
    
    for (size_t i = 0; i < str.size(); ++i) {
        char tmp = str[i];
        if (tmp == ' ') continue;
        
        if (tmp == '{' || tmp == '}') {
            if (!handleBracket(tmp, balance, expectElement, afterComma)) {
                return false;
            }
        } 
        else if (tmp == ',') {
            if (!handleComma(expectElement, afterComma)) {
                return false;
            }
        }   
        else {
            if (!expectElement) return false;
            
            int endIndex = validateElement(str, i);
            if (endIndex == -1) return false;
            
            i = endIndex - 1;
            expectElement = false;
            afterComma = false;
        }
    }
    
    return (balance == 0) && !expectElement && !afterComma;
}

int Set::validateElement(const std::string& str, size_t start) const {
    size_t j = start;
    while (j < str.size() && str[j] != ' ' && str[j] != ',' && str[j] != '}') {
        char symbol = str[j];
        if (!(isdigit(symbol) || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))) {
            return -1;
        }
        j++;
    }
    return j;
}

bool Set::handleBracket(char c, int& balance, bool& expectElement, bool& afterComma) const {
    if (c == '{') {
        if (!expectElement) return false;
        balance++;
        expectElement = true;
        afterComma = false;
    } 
    else if (c == '}') {
        if (balance <= 0 || afterComma) return false;
        balance--;
        expectElement = false;
        afterComma = false;
    }
    return true;
}

bool Set::handleComma(bool& expectElement, bool& afterComma) const {
    if (expectElement || afterComma) return false;
    expectElement = true;
    afterComma = true;
    return true;
}

std::vector<std::string> Set::parseSetString(const std::string& string){
    std::vector<std::string> elements;
    if (!isValid(string)) return elements; // проверка валдиности
    std::string strWithoutSpace = removeSpaces(string);
    //избавляемся от скобочек
    if (strWithoutSpace.front() == '{' && strWithoutSpace.back() == '}') {
        strWithoutSpace = strWithoutSpace.substr(1, strWithoutSpace.size() - 2);
    }
    int balance = 0;
    std::string element;
    for (char c : strWithoutSpace) {
        if (c == '{') {
            balance++;
            element += c;
        } else if (c == '}') {
            balance--;
            element += c;
        } else if (c == ',' && balance == 0) {
            // запятая разделяет эелементы
            elements.push_back(element);
            element.clear();
        } else {
            element += c;
        }
    }
    if (!element.empty()) {
        elements.push_back(element); // last элемент
    }
    return elements;
}

bool Set::add(const std::string& element){
    if(!isValid(element)) return false;
    if((*this)[element]) return false;
    elInSet.push_back(element); //если нету - добавляем
    return true;
}

bool Set::remove(const std::string& element){
    if(!isValid(element)) return false;
    for(std::vector<std::string>::iterator it = elInSet.begin(); it!=elInSet.end(); ++it){
        if(*it == element){
            elInSet.erase(it); // обновлять вектор не надо, т.к. дальше выходим
            return true;
        }
    }
    return false;
}

void Set::clear(){
    elInSet.clear(); //чистим
}

int Set::getCardinality() const{
    return elInSet.size(); //мощность
}

bool Set::isVoid() const{
    return elInSet.empty(); //пусто
}

Set Set::getBoolean(){ // всего будет 2^n подможеств
    Set newSet;
    int n = elInSet.size();
    int total = 1 << n; // 2^n

    for (int mask = 0; mask < total; ++mask) {
        Set subsetTemp; // множество-подможество
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subsetTemp.add(elInSet[i]); // элементы во множество-подмножество
            }
        }
        std::string subsetTempStr = subsetTemp.toString(); // делаем в строку
        newSet.add(subsetTemp.toString()); // элемент в булеан
    }
    return newSet;
}

std::string Set::toString() const {
    if (elInSet.empty()) return "{}"; // возвращаем пустое
    std::string newStr = "{";
    for (size_t i = 0; i < elInSet.size(); ++i) {
        newStr += elInSet[i];
        if (i != elInSet.size() - 1) newStr += ",";
    }
    newStr += "}";
    return newStr;
}

std::string Set::removeSpaces(const std::string& str) {
    std::string newStr;
    for (char c : str) {
        if (c != ' ') newStr += c;
    }
    return newStr;
}

const std::vector<std::string>& Set::getElInSet() const{
    return elInSet;
}

Set::Set(const Set& other){
    elInSet = other.elInSet;
}

Set& Set::operator = (const Set& other){
    if(this != &other){ // при A=A или B=B не будет
        elInSet = other.elInSet;
    }
    return *this;
}

Set& Set::operator = (const std::string& elements){
    if(!isValid(elements)) return *this;
    clear(); // перед заданием множества чистим
    std::vector<std::string> parsed = parseSetString(elements);
    for(const std::string& elem : parsed){
        add(elem);
    }
    return *this;
}

Set& Set::operator = (const char* elements){
    return *this = std::string(elements);
}

bool Set::operator == (const Set& other){
    if(other.getCardinality() != this->getCardinality()) return false;
    for(const std::string& elem : other.getElInSet()){
        if(!(*this)[elem]) return false;
    }
    return true;
}

bool Set::operator [] (const std::string& isHere) const{
    if(!isValid(isHere)) return false;
    for(std::vector<std::string>::const_iterator it = elInSet.begin(); it != elInSet.end(); ++it){
        if(*it == isHere) return true;
    }
    return false;
}

bool Set::operator [] (const char* isHere) const{
    return (*this)[std::string(isHere)];
}

Set& Set::operator += (const Set& other){
    for(const std::string& elem : other.getElInSet()){
        add(elem);
    }
    return *this;
}

Set& Set::operator += (const std::string& string){
    if(!isValid(string)) return *this;
    std::vector<std::string> parsed = parseSetString(string);
    for(const std::string& elem : parsed){
        add(elem);
    }
    return *this;
}

Set& Set::operator += (const char* elements){
    return *this += std::string(elements);
}

Set Set::operator + (const Set& other){
    Set newSet = *this;
    newSet += other;
    return newSet;
}

Set Set::operator * (const Set& other){
    Set newSet = *this;
    newSet *= other;
    return newSet;
}

Set& Set::operator *= (const Set& other){
    std::vector<std::string> tempSet;
    for(const std::string& elem : elInSet){
        if(other[elem]){
            tempSet.push_back(elem);
        }
    }
    elInSet = tempSet;
    return *this;
}

Set& Set::operator -= (const Set& other){
    std::vector<std::string> tempSet;
    for(const std::string& elem : elInSet){
        if(!other[elem]){
            tempSet.push_back(elem);
        }
    }
    elInSet = tempSet;
    return *this;
}

Set Set::operator - (const Set& other){
    Set newSet = *this;
    newSet-= other;
    return newSet;
}

std::ostream& operator<<(std::ostream& os, const Set& set) {
    os << set.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Set& set) {
    std::string line;
    std::getline(is, line); // считываем
    
    if (!set.isValid(line)) { // проходит ли валидацию
        is.setstate(std::ios::failbit); // выбрасываем ошибку
        return is;
    }
    
    set = line;
    return is;
}

Set::Set(const std::string str){
    operator=(str);
}

Set::Set() = default;
Set::~Set() = default;