#include "utils/DateTime.hpp"
#include <iomanip>
#include <sstream>
#include <ctime>
#include "exceptions/exceptions.hpp"

namespace Utils {

const std::string DateTime::dateFormat = "%d-%m-%Y";
const std::string DateTime::timeFormat = "%H:%M";
const std::string DateTime::dateTimeFormat = "%d-%m-%Y %H:%M";

bool DateTime::checkTmValidity(const std::tm& tmVal) noexcept {
    std::tm tempTm = tmVal;
    time_t time = std::mktime(&tempTm);
    if (time == -1) {
        return false;
    }
    return tmVal.tm_mday == tempTm.tm_mday &&
           tmVal.tm_mon == tempTm.tm_mon &&
           tmVal.tm_year == tempTm.tm_year &&
           tmVal.tm_hour == tempTm.tm_hour &&
           tmVal.tm_min == tempTm.tm_min;
}

DateTime::DateTime(const std::tm& tmStruct, bool isValid) noexcept
    : tmStruct_(tmStruct), isValid(isValid) {}

DateTime::DateTime() noexcept {
    *this = now();
}

DateTime DateTime::now() noexcept {
    auto nowChrono = std::chrono::system_clock::now();
    time_t currentTime = std::chrono::system_clock::to_time_t(nowChrono);
    std::tm tmStruct;
#ifdef _MSC_VER
    localtime_s(&tmStruct, &currentTime);
#else
    localtime_r(&currentTime, &tmStruct);
#endif
    return DateTime(tmStruct, true);
}

DateTime::DateTime(const std::string& dateString) {
    parseDate(dateString);
    tmStruct_.tm_hour = 0;
    tmStruct_.tm_min = 0;
    tmStruct_.tm_sec = 0;
    isValid = checkTmValidity(tmStruct_);
    if (!isValid) {
        throw InvalidInputFormatException("Invalid date: " + dateString);
    }
}

DateTime::DateTime(const std::string& dateString, const std::string& timeString) {
    parseDate(dateString);
    parseTime(timeString);
    tmStruct_.tm_sec = 0;
    isValid = checkTmValidity(tmStruct_);
    if (!isValid) {
        throw InvalidInputFormatException("Invalid date or time: " + dateString + " " + timeString);
    }
}

void DateTime::parseDate(const std::string& dateString) {
    std::istringstream ss(dateString);
    ss >> std::get_time(&tmStruct_, dateFormat.c_str());
    if (ss.fail() || !ss.eof()) {
        throw InvalidInputFormatException("Date string '" + dateString + "' does not match format " + dateFormat);
    }
    tmStruct_.tm_isdst = -1;
}

void DateTime::parseTime(const std::string& timeString) {
    std::istringstream ss(timeString);
    ss >> std::get_time(&tmStruct_, timeFormat.c_str());
    if (ss.fail() || !ss.eof()) {
        throw InvalidInputFormatException("Time string '" + timeString + "' does not match format " + timeFormat);
    }
    tmStruct_.tm_isdst = -1;
}

bool DateTime::isValidDate(const std::string& dateString) noexcept {
    std::tm tmVal = {};
    std::istringstream ss(dateString);
    ss >> std::get_time(&tmVal, dateFormat.c_str());
    tmVal.tm_isdst = -1;
    return !ss.fail() && ss.eof() && checkTmValidity(tmVal);
}

bool DateTime::isValidTime(const std::string& timeString) noexcept {
    std::tm tmVal = {};
    tmVal.tm_year = 100;
    tmVal.tm_mon = 0;
    tmVal.tm_mday = 1;
    std::istringstream ss(timeString);
    ss >> std::get_time(&tmVal, timeFormat.c_str());
    tmVal.tm_isdst = -1;
    return !ss.fail() && ss.eof() && checkTmValidity(tmVal);
}

bool DateTime::isValidDateTime(const std::string& dateTimeString) noexcept {
    std::tm tmVal = {};
    std::istringstream ss(dateTimeString);
    ss >> std::get_time(&tmVal, dateTimeFormat.c_str());
    tmVal.tm_isdst = -1;
    return !ss.fail() && ss.eof() && checkTmValidity(tmVal);
}

std::string DateTime::getDateString() const noexcept {
    std::ostringstream ss;
    ss << std::put_time(&tmStruct_, dateFormat.c_str());
    return ss.str();
}

std::string DateTime::getTimeString() const noexcept {
    std::ostringstream ss;
    ss << std::put_time(&tmStruct_, timeFormat.c_str());
    return ss.str();
}

std::string DateTime::getDateTimeString() const noexcept {
    std::ostringstream ss;
    ss << std::put_time(&tmStruct_, dateTimeFormat.c_str());
    return ss.str();
}

int DateTime::getDay() const noexcept { return tmStruct_.tm_mday; }
int DateTime::getMonth() const noexcept { return tmStruct_.tm_mon + 1; }
int DateTime::getYear() const noexcept { return tmStruct_.tm_year + 1900; }
int DateTime::getHour() const noexcept { return tmStruct_.tm_hour; }
int DateTime::getMinute() const noexcept { return tmStruct_.tm_min; }

bool DateTime::operator<(const DateTime& other) const noexcept {
    return toTimestamp() < other.toTimestamp();
}
bool DateTime::operator>(const DateTime& other) const noexcept {
    return toTimestamp() > other.toTimestamp();
}
bool DateTime::operator<=(const DateTime& other) const noexcept {
    return toTimestamp() <= other.toTimestamp();
}
bool DateTime::operator>=(const DateTime& other) const noexcept {
    return toTimestamp() >= other.toTimestamp();
}
bool DateTime::operator==(const DateTime& other) const noexcept {
    return toTimestamp() == other.toTimestamp();
}
bool DateTime::operator!=(const DateTime& other) const noexcept {
    return toTimestamp() != other.toTimestamp();
}

DateTime DateTime::addDays(int days) const {
    std::tm newTm = tmStruct_;
    newTm.tm_mday += days;
    newTm.tm_isdst = -1;
    time_t newTime = std::mktime(&newTm);
    if (newTime == -1 || !checkTmValidity(newTm)) {
        throw InvalidDateRangeException("Resulting date is out of representable range after adding days.");
    }
    std::tm resultTm;
#ifdef _MSC_VER
    localtime_s(&resultTm, &newTime);
#else
    localtime_r(&newTime, &resultTm);
#endif
    return DateTime(resultTm, true);
}

DateTime DateTime::addMinutes(int minutes) const {
    std::tm newTm = tmStruct_;
    newTm.tm_min += minutes;
    newTm.tm_isdst = -1;
    time_t newTime = std::mktime(&newTm);
    if (newTime == -1 || !checkTmValidity(newTm)) {
        throw InvalidDateRangeException("Resulting date/time is out of representable range after adding minutes.");
    }
    std::tm resultTm;
#ifdef _MSC_VER
    localtime_s(&resultTm, &newTime);
#else
    localtime_r(&newTime, &resultTm);
#endif
    return DateTime(resultTm, true);
}

long long DateTime::toTimestamp() const noexcept {
    std::tm tempTm = tmStruct_;
    tempTm.tm_isdst = -1;
    time_t timestamp = std::mktime(&tempTm);
    if (timestamp == -1) { 
        return 0;
    }
    return static_cast<long long>(timestamp);
}
}