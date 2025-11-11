#pragma once
#include <string>
#include <exception>

class TravelBookingException : public std::exception {
protected:
    std::string message;
public:
    explicit TravelBookingException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class UnderageException : public TravelBookingException {
public:
    explicit UnderageException(int actualAge, int requiredAge) 
        : TravelBookingException("Underage Restriction: User is " + std::to_string(actualAge) + 
                               " years old, but must be at least " + std::to_string(requiredAge) + 
                               " years old to use this service") {}
};

class TourCapacityExceededException : public TravelBookingException {
public:
    explicit TourCapacityExceededException(const std::string& tourName, int requested, int available) 
        : TravelBookingException("Tour Capacity Exceeded: " + tourName + " - Requested: " + std::to_string(requested) + ", Available: " + std::to_string(available)) {}
};

class PaymentProcessingException : public TravelBookingException {
public:
    explicit PaymentProcessingException(const std::string& details, const std::string& code = "") 
        : TravelBookingException("Payment Processing Failed: " + details + (code.empty() ? "" : " (Error: " + code + ")") + " - please verify payment details") {}
};

class SystemOverloadException : public TravelBookingException {
public:
    explicit SystemOverloadException(int concurrentUsers, const std::string& module = "") 
        : TravelBookingException("System Overload: Concurrent users: " + std::to_string(concurrentUsers) + (module.empty() ? "" : " in module: " + module) + " - please try again later") {}
};

class ResourceNotFoundException : public TravelBookingException {
public:
    explicit ResourceNotFoundException(const std::string& resourceType, const std::string& identifier) 
        : TravelBookingException("Resource Not Found: " + resourceType + " with identifier: '" + identifier + "' - please verify the reference") {}
};

class InvalidDataException : public TravelBookingException {
public:
    explicit InvalidDataException(const std::string& field, const std::string& validationRule) 
        : TravelBookingException("Invalid Data: Field '" + field + "' - " + validationRule + " - please correct and resubmit") {}
};

class InvalidDateException : public TravelBookingException {
public:
    explicit InvalidDateException(const std::string& field) 
        : TravelBookingException("Invalid Date: Field '" + field + "' has incorrect format or value of date") {}
};

class TransportationSchedulingException : public TravelBookingException {
public:
    explicit TransportationSchedulingException(const std::string& transport, const std::string& reason) 
        : TravelBookingException("Transportation Scheduling Failed: " + transport + " - " + reason + " - no available routes for selected dates") {}
};

class InvalidBookingException : public TravelBookingException {
public:
    explicit InvalidBookingException(const std::string& reason)
        : TravelBookingException("Invalid Booking: " + reason + " - booking could not be created") {}
};

class AccommodationCapacityExceededException : public TravelBookingException {
public:
    explicit AccommodationCapacityExceededException(const std::string& accommodationName, int guests, int capacity) 
        : TravelBookingException("Accommodation Capacity Exceeded: " + accommodationName + 
                               " - Requested: " + std::to_string(guests) + " guests, Capacity: " + 
                               std::to_string(capacity) + " - please reduce guest count or choose different accommodation") {}
};

class AccommodationUnavailableException : public TravelBookingException {
public:
    explicit AccommodationUnavailableException(const std::string& accommodationName, const std::string& dates) 
        : TravelBookingException("Accommodation Unavailable: " + accommodationName + 
                               " is not available for dates: " + dates + 
                               " - please select different dates or accommodation") {}
};

class MealCompatibilityException : public TravelBookingException {
public:
    explicit MealCompatibilityException(const std::string& mealName, const std::string& conflict) 
        : TravelBookingException("Meal Compatibility Error: " + mealName + 
                               " - " + conflict + 
                               " - please review dietary tags and meal composition") {}
};

class MealPricingException : public TravelBookingException {
public:
    explicit MealPricingException(const std::string& mealName, double price, int calories, double maxPricePerCalorie) 
        : TravelBookingException("Meal Pricing Error: " + mealName + 
                               " - Price $" + std::to_string(static_cast<int>(price)) + 
                               " for " + std::to_string(calories) + " calories exceeds maximum value ratio of $" + 
                               std::to_string(maxPricePerCalorie) + " per calorie - please adjust pricing") {}
};

class DietaryRestrictionViolationException : public TravelBookingException {
public:
    explicit DietaryRestrictionViolationException(const std::string& mealName, const std::string& restriction) 
        : TravelBookingException("Dietary Restriction Violation: " + mealName + 
                               " conflicts with " + restriction + 
                               " dietary requirements - please select alternative meal") {}
};

class MealAllergyConflictException : public TravelBookingException {
public:
    explicit MealAllergyConflictException(const std::string& mealName, const std::string& allergen) 
        : TravelBookingException("Meal Allergy Conflict: " + mealName + 
                               " contains " + allergen + 
                               " which conflicts with guest allergies - meal substitution required") {}
};