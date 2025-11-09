#pragma once

#include <string>
#include <ctime>
#include "exceptions/exceptions.hpp"

namespace Utils {

class DateTime {
public:
    static const std::string dateFormat;      // "DD-MM-YYYY"
    static const std::string timeFormat;      // "HH:MM"
    static const std::string dateTimeFormat;  // "DD-MM-YYYY HH:MM"

    DateTime() noexcept;
    explicit DateTime(const std::string& dateString);
    DateTime(const std::string& dateString, const std::string& timeString);
    static DateTime now() noexcept;
    static bool isValidDate(const std::string& dateString) noexcept;
    static bool isValidTime(const std::string& timeString) noexcept;
    static bool isValidDateTime(const std::string& dateTimeString) noexcept;
    std::string getDateString() const noexcept;
    std::string getTimeString() const noexcept;
    std::string getDateTimeString() const noexcept;
    int getDay() const noexcept;
    int getMonth() const noexcept;
    int getYear() const noexcept;
    int getHour() const noexcept;
    int getMinute() const noexcept;
    bool operator<(const DateTime& other) const noexcept;
    bool operator>(const DateTime& other) const noexcept;
    bool operator<=(const DateTime& other) const noexcept;
    bool operator>=(const DateTime& other) const noexcept;
    bool operator==(const DateTime& other) const noexcept;
    bool operator!=(const DateTime& other) const noexcept;
    DateTime addDays(int days) const;
    DateTime addMinutes(int minutes) const;
    long long toTimestamp() const noexcept;
private:
    std::tm tmStruct_;
    bool isValid = false;
    explicit DateTime(const std::tm& tmStruct, bool isValid = true) noexcept;
    void parseDateManual(const std::string& dateString);
    void parseTimeManual(const std::string& timeString);
    std::string formatDateManual() const noexcept;
    std::string formatTimeManual() const noexcept;

    static bool checkTmValidity(const std::tm& tmVal) noexcept;
};
}