#include <iostream>
#include <utility>
#include <algorithm>
#include "MultiSets.hpp"

bool MultiSet::isValid(const std::string& str) const {
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

int MultiSet::validateElement(const std::string& str, size_t start) const {
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

bool MultiSet::handleBracket(char c, int& balance, bool& expectElement, bool& afterComma) const {
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

bool MultiSet::handleComma(bool& expectElement, bool& afterComma) const {
    if (expectElement || afterComma) return false;
    expectElement = true;
    afterComma = true;
    return true;
}

std::vector<std::string> MultiSet::parseMultiSetString(const std::string& string){
    std::vector<std::string> elements;
    if (!isValid(string)) return elements; // проверка валидности
    std::string strWithoutSpace = removeSpaces(string);
    //избавляемся от скобочек
    if (strWithoutSpace.front() == '{' && strWithoutSpace.back() == '}') {
        strWithoutSpace = strWithoutSpace.substr(1, strWithoutSpace.size() - 2);
    }
    int balance = 0;
    std::string Element;
    for (char c : strWithoutSpace) {
        if (c == '{') {
            balance++;
            Element += c;
        } else if (c == '}') {
            balance--;
            Element += c;
        } else if (c == ',' && balance == 0) {
            // запятая разделяет элементы
            elements.push_back(Element);
            Element.clear();
        } else {
            Element += c;
        }
    }
    if (!Element.empty()) {
        elements.push_back(Element); // last элемент
    }
    return elements;
}

bool MultiSet::add(const std::string& element){
    if(!isValid(element)) return false;
    // Ищем элемент в мультимножестве
    for(auto& pair : elInMultiSet) {
        if(pair.first == element) {
            pair.second++; // увеличиваем счетчик
            return true;
        }
    }
    // Если элемент не найден, добавляем новый с счетчиком 1
    elInMultiSet.push_back(std::make_pair(element, 1));
    return true;
}

bool MultiSet::remove(const std::string& element){
    if(!isValid(element)) return false;
    for(auto it = elInMultiSet.begin(); it != elInMultiSet.end(); ++it){
        if(it->first == element){
            if(it->second > 1) {
                it->second--; // уменьшаем счетчик
            } else {
                elInMultiSet.erase(it); // удаляем элемент полностью
            }
            return true;
        }
    }
    return false;
}

int MultiSet::removeAll(const std::string& element){
    if(!isValid(element)) return 0;
    for(auto it = elInMultiSet.begin(); it != elInMultiSet.end(); ++it){
        if(it->first == element){
            int count = it->second;
            elInMultiSet.erase(it);
            return count;
        }
    }
    return 0;
}

void MultiSet::clear(){
    elInMultiSet.clear(); //чистим
}

int MultiSet::getCardinality() const{
    int total = 0;
    for(const auto& pair : elInMultiSet) {
        total += pair.second;
    }
    return total; // общее количество всех элементов
}

int MultiSet::getDistinctCount() const{
    return elInMultiSet.size(); // количество уникальных элементов
}

int MultiSet::getCount(const std::string& element) const{
    if(!isValid(element)) return 0;
    for(const auto& pair : elInMultiSet) {
        if(pair.first == element) {
            return pair.second;
        }
    }
    return 0;
}

bool MultiSet::isVoid() const{
    return elInMultiSet.empty(); //пусто
}

MultiSet MultiSet::getBoolean(){
    MultiSet newSet;
    int n = elInMultiSet.size();
    int total = 1 << n; // 2^n
    for (int mask = 0; mask < total; ++mask) {
        MultiSet subsetTemp; // множество-подможество
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subsetTemp.add(elInMultiSet[i].first); // элементы во множество-подмножество
            }
        }
        newSet.add(subsetTemp.toString()); // элемент в булеан
    }
    return newSet;
}

std::string MultiSet::toString() const {
    if (elInMultiSet.empty()) return "{}"; // возвращаем пустое
    std::string newStr = "{";
    for (size_t i = 0; i < elInMultiSet.size(); ++i) {
        // добавляем элемент столько раз, сколько он встречается
        for (int j = 0; j < elInMultiSet[i].second; ++j) {
            newStr += elInMultiSet[i].first;
            if (j < elInMultiSet[i].second - 1 || i < elInMultiSet.size() - 1) {
                newStr += ",";
            }
        }
        if (i != elInMultiSet.size() - 1 && elInMultiSet[i].second > 0) {
            // убираем лишнюю запятую, если она была добавлена
            if (newStr.back() == ',') {
                newStr.pop_back();
            }
            newStr += ",";
        }
    }
    if (newStr.back() == ',') {
        newStr.pop_back();
    }
    newStr += "}";
    return newStr;
}

std::string MultiSet::removeSpaces(const std::string& str) {
    std::string newStr;
    for (char c : str) {
        if (c != ' ') newStr += c;
    }
    return newStr;
}

const std::vector<std::pair<std::string, int>>& MultiSet::getElInMultiSet() const{
    return elInMultiSet;
}

MultiSet::MultiSet(const MultiSet& other){
    elInMultiSet = other.elInMultiSet;
}

MultiSet& MultiSet::operator = (const MultiSet& other){
    if(this != &other){ // при A=A или B=B не будет
        elInMultiSet = other.elInMultiSet;
    }
    return *this;
}

MultiSet& MultiSet::operator = (const std::string& elements){
    if(!isValid(elements)) return *this;
    clear(); // перед заданием множество чистим
    std::vector<std::string> parsed = parseMultiSetString(elements);
    for(const std::string& elem : parsed){
        add(elem);
    }
    return *this;
}

MultiSet& MultiSet::operator = (const char* elements){
    return *this = std::string(elements);
}

bool MultiSet::operator == (const MultiSet& other){
    if(other.getDistinctCount() != this->getDistinctCount()) return false;
    for(const auto& pair : other.getElInMultiSet()){
        if(this->getCount(pair.first) != pair.second) return false;
    }
    return true;
}

bool MultiSet::operator [] (const std::string& isHere) const{
    if(!isValid(isHere)) return false;
    return getCount(isHere) > 0;
}

bool MultiSet::operator [] (const char* isHere) const{
    return (*this)[std::string(isHere)];
}

MultiSet& MultiSet::operator += (const MultiSet& other){
    for(const auto& pair : other.getElInMultiSet()){
        for(int i = 0; i < pair.second; i++) {
            add(pair.first);
        }
    }
    return *this;
}

MultiSet& MultiSet::operator += (const std::string& string){
    if(!isValid(string)) return *this;
    std::vector<std::string> parsed = parseMultiSetString(string);
    for(const std::string& elem : parsed){
        add(elem);
    }
    return *this;
}

MultiSet& MultiSet::operator += (const char* elements){
    return *this += std::string(elements);
}

MultiSet MultiSet::operator + (const MultiSet& other){
    MultiSet newSet = *this;
    newSet += other;
    return newSet;
}

MultiSet MultiSet::operator * (const MultiSet& other){
    MultiSet newSet = *this;
    newSet *= other;
    return newSet;
}

MultiSet& MultiSet::operator *= (const MultiSet& other){
    std::vector<std::pair<std::string, int>> tempSet;
    for(const auto& pair : elInMultiSet){
        int otherCount = other.getCount(pair.first);
        if(otherCount > 0) {
            //минимум из двух счетчиков
            int minCount = std::min(pair.second, otherCount);
            tempSet.push_back(std::make_pair(pair.first, minCount));
        }
    }
    elInMultiSet = tempSet;
    return *this;
}

MultiSet& MultiSet::operator -= (const MultiSet& other){
    std::vector<std::pair<std::string, int>> tempSet;
    for(const auto& pair : elInMultiSet){
        int otherCount = other.getCount(pair.first);
        int newCount = pair.second - otherCount;
        if(newCount > 0) {
            tempSet.push_back(std::make_pair(pair.first, newCount));
        }
    }
    elInMultiSet = tempSet;
    return *this;
}

MultiSet MultiSet::operator - (const MultiSet& other){
    MultiSet newSet = *this;
    newSet -= other;
    return newSet;
}

std::ostream& operator<<(std::ostream& os, const MultiSet& set) {
    os << set.toString();
    return os;
}

std::istream& operator>>(std::istream& is, MultiSet& set) {
    std::string line;
    std::getline(is, line); // считываем
    if (!set.isValid(line)) { // проходит ли валидацию
        is.setstate(std::ios::failbit); // выбрасываем ошибку
        return is;
    }
    set = line;
    return is;
}

MultiSet::MultiSet() = default;
MultiSet::~MultiSet() = default;