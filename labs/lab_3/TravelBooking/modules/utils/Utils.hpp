#pragma once
#include <string>
#include <cctype>
#include <chrono>
#include <iomanip>

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

class DateUtils {
public:
    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
        return ss.str();
    }
    static int calculateAge(const std::string& birthDate) {
        std::string currentDate = getCurrentDate();
        int currentYear = std::stoi(currentDate.substr(0, 4));
        int currentMonth = std::stoi(currentDate.substr(5, 2));
        int currentDay = std::stoi(currentDate.substr(8, 2));
        int birthYear = std::stoi(birthDate.substr(0, 4));
        int birthMonth = std::stoi(birthDate.substr(5, 2));
        int birthDay = std::stoi(birthDate.substr(8, 2));
        int age = currentYear - birthYear;
        if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
            age--;
        }
        return age;
    }
};