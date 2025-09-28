#include "books/ISBN.hpp"
#include "exceptions/WarehouseExceptions.hpp"

bool ISBN::isValidFormat(const std::string& str) const{
    std::string normalized = normalizeISBN(str);
    size_t len = normalized.length();
    if(len != 10 && len != 13) return false;
    for (size_t i = 0; i < len - 1; ++i) {
        if (!std::isdigit(normalized[i])) return false;
    }
    char lastChar = normalized[len - 1];
    return std::isdigit(lastChar) || (len == 10 && lastChar == 'X');
}

std::string ISBN::normalizeISBN(const std::string& str) const{
    std::string result;
    for(char c : str){
        if(std::isdigit(c) || c == 'X' || c == 'x'){
            result += std::toupper(c);
        }
    }
    return result;
}

char ISBN::calculateCheckDigit(const std::string& str) const{
    bool isThirteen = (str.length() == 13);
    int sum = 0;
    if (isThirteen) {
        for (size_t i = 0; i < 12; ++i) {
            int digit = str[i] - '0';
            int weight = (i % 2 == 0) ? 1 : 3;
            sum += digit * weight;
        }
    } 
    else {
        for (size_t i = 0; i < 9; ++i) {
            int digit = str[i] - '0';
            sum += digit * (10 - i);
        }
    }

    int remainder = sum % (isThirteen ? 10 : 11);
    int checkDigit = (remainder == 0) ? 0 : 
                    (isThirteen ? 10 - remainder : 11 - remainder);
    
    if (!isThirteen && checkDigit == 10) {
        return 'X';
    }
    
    return '0' + checkDigit;
}


ISBN::ISBN(const std::string& str) {
    std::string normalized = normalizeISBN(str);
    if (!isValidFormat(normalized)) {
        throw InvalidISBNException("Invalid format: " + str);
    }
    char actualCheckDigit = normalized.back();
    char calculatedCheckDigit = calculateCheckDigit(normalized);
    if (actualCheckDigit != calculatedCheckDigit) {
        throw InvalidISBNException("Check digit mismatch: " + str);
    }
    code = normalized;
}

std::string ISBN::getCode() const noexcept{
    return code;
}

std::string ISBN::getFormattedCode() const noexcept{
    if (!isISBNThirteen()) {
        return code.substr(0, 1) + "-" + code.substr(1, 3) + "-" + 
               code.substr(4, 5) + "-" + code.substr(9, 1);
    } 
    else {
        return code.substr(0, 3) + "-" + code.substr(3, 1) + "-" + 
               code.substr(4, 3) + "-" + code.substr(7, 5) + "-" + 
               code.substr(12, 1);
    }
}

bool ISBN::isISBNThirteen() const{
    return code.length() == 13;
}

bool ISBN::operator==(const ISBN& other) const noexcept{
    return code == other.code;
}

bool ISBN::operator!=(const ISBN& other) const noexcept{
    return !(*this == other);
}