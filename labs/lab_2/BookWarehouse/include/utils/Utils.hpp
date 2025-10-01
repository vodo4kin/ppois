#pragma once
#include <string>
#include <cctype>

class StringValidation {
public:
    static bool isValidName(const std::string& str) {
        if (str.empty()) return false;
        bool hasNonSpace = false;
        for (char c : str) {
            if (c == '\t' || c == '\n' || c == '\r') return false;
            if (c != ' ') hasNonSpace = true;
        }
        return hasNonSpace;
    }
    
    static bool isValidName(const std::string& str, size_t maxLength) {
        return str.length() <= maxLength && isValidName(str);
    }

    static std::string normalizeLanguage(const std::string& language) {
        std::string result;
        for(char c : language){
            result += std::toupper(static_cast<unsigned char>(c));
        }
        return result;
    }

    static bool isValidDate(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        
        for (int i = 0; i < 10; i++) {
            if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i]))) {
                return false;
            }
        }
        return true;
    }
};