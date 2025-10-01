#pragma once
#include <string>

class ISBN{
    private:
    std::string code;
    bool isValidFormat(const std::string& str) const;
    std::string normalizeISBN(const std::string& str) const;
    char calculateCheckDigit(const std::string& str) const;

    public:
    explicit ISBN(const std::string& str);
    std::string getCode() const noexcept;
    std::string getFormattedCode() const noexcept;
    bool isISBNThirteen() const;
    bool operator==(const ISBN& other) const noexcept;
    bool operator!=(const ISBN& other) const noexcept;
};