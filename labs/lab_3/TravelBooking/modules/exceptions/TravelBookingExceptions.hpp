/**
 * @file TravelBookingExceptions.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with exception classes for travel booking management system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <exception>

/**
 * @class TravelBookingException
 * @brief Base exception class for travel booking management system
 * 
 * Provides common functionality for all travel booking-related exceptions
 * with formatted error messages and std::exception compatibility.
 */
class TravelBookingException : public std::exception {
protected:
    std::string message;                                      ///< Formatted error message

public:
    /**
     * @brief Construct a new TravelBookingException object
     * 
     * @param msg Basic error message without formatting
     */
    explicit TravelBookingException(const std::string& msg) : message(msg) {}
    
    /**
     * @brief Get error message as C-style string
     * 
     * @return const char* Formatted error message
     */
    const char* what() const noexcept override { return message.c_str(); }
};

/**
 * @class UnderageException
 * @brief Exception for age restriction violations
 * 
 * Thrown when user does not meet minimum age requirement for service
 */
class UnderageException : public TravelBookingException {
public:
    /**
     * @brief Construct a new UnderageException object
     * 
     * @param actualAge Current age of the user
     * @param requiredAge Minimum required age for service
     */
    explicit UnderageException(int actualAge, int requiredAge) 
        : TravelBookingException("Underage Restriction: User is " + std::to_string(actualAge) + 
                               " years old, but must be at least " + std::to_string(requiredAge) + 
                               " years old to use this service") {}
};

/**
 * @class TourCapacityExceededException
 * @brief Exception for tour capacity limitations
 * 
 * Thrown when requested tour slots exceed available capacity
 */
class TourCapacityExceededException : public TravelBookingException {
public:
    /**
     * @brief Construct a new TourCapacityExceededException object
     * 
     * @param tourName Name of the tour with capacity issue
     * @param requested Number of slots requested
     * @param available Number of slots available
     */
    explicit TourCapacityExceededException(const std::string& tourName, int requested, int available) 
        : TravelBookingException("Tour Capacity Exceeded: " + tourName + " - Requested: " + std::to_string(requested) + ", Available: " + std::to_string(available)) {}
};

/**
 * @class PaymentProcessingException
 * @brief Exception for payment processing failures
 * 
 * Thrown when payment gateway errors or invalid payment data detected
 */
class PaymentProcessingException : public TravelBookingException {
public:
    /**
     * @brief Construct a new PaymentProcessingException object
     * 
     * @param details Description of payment processing failure
     * @param code Optional error code from payment processor
     */
    explicit PaymentProcessingException(const std::string& details, const std::string& code = "") 
        : TravelBookingException("Payment Processing Failed: " + details + (code.empty() ? "" : " (Error: " + code + ")") + " - please verify payment details") {}
};

/**
 * @class SystemOverloadException
 * @brief Exception for system capacity limitations
 * 
 * Thrown when system resources are exceeded due to high concurrent usage
 */
class SystemOverloadException : public TravelBookingException {
public:
    /**
     * @brief Construct a new SystemOverloadException object
     * 
     * @param concurrentUsers Number of concurrent users causing overload
     * @param module Optional specific module experiencing overload
     */
    explicit SystemOverloadException(int concurrentUsers, const std::string& module = "") 
        : TravelBookingException("System Overload: Concurrent users: " + std::to_string(concurrentUsers) + (module.empty() ? "" : " in module: " + module) + " - please try again later") {}
};

/**
 * @class ResourceNotFoundException
 * @brief Exception for missing resources in system
 * 
 * Thrown when searching for non-existent resources in system catalog
 */
class ResourceNotFoundException : public TravelBookingException {
public:
    /**
     * @brief Construct a new ResourceNotFoundException object
     * 
     * @param resourceType Type of resource not found
     * @param identifier Unique identifier of missing resource
     */
    explicit ResourceNotFoundException(const std::string& resourceType, const std::string& identifier) 
        : TravelBookingException("Resource Not Found: " + resourceType + " with identifier: '" + identifier + "' - please verify the reference") {}
};

/**
 * @class InvalidDataException
 * @brief Exception for data validation failures
 * 
 * Thrown when business logic validation fails for system data
 */
class InvalidDataException : public TravelBookingException {
public:
    /**
     * @brief Construct a new InvalidDataException object
     * 
     * @param field Name of the field with invalid data
     * @param validationRule Description of validation rule violation
     */
    explicit InvalidDataException(const std::string& field, const std::string& validationRule) 
        : TravelBookingException("Invalid Data: Field '" + field + "' - " + validationRule + " - please correct and resubmit") {}
};

/**
 * @class InvalidDateException
 * @brief Exception for date format and value errors
 * 
 * Thrown when date validation fails due to format or logical errors
 */
class InvalidDateException : public TravelBookingException {
public:
    /**
     * @brief Construct a new InvalidDateException object
     * 
     * @param field Name of the date field with error
     */
    explicit InvalidDateException(const std::string& field) 
        : TravelBookingException("Invalid Date: Field '" + field + "' has incorrect format or value of date") {}
};

/**
 * @class TransportationSchedulingException
 * @brief Exception for transport scheduling conflicts
 * 
 * Thrown when transportation cannot be scheduled due to availability or routing issues
 */
class TransportationSchedulingException : public TravelBookingException {
public:
    /**
     * @brief Construct a new TransportationSchedulingException object
     * 
     * @param transport Type or name of transportation
     * @param reason Detailed reason for scheduling failure
     */
    explicit TransportationSchedulingException(const std::string& transport, const std::string& reason) 
        : TravelBookingException("Transportation Scheduling Failed: " + transport + " - " + reason + " - no available routes for selected dates") {}
};

/**
 * @class InvalidBookingException
 * @brief Exception for booking creation failures
 * 
 * Thrown when booking cannot be created due to business rule violations
 */
class InvalidBookingException : public TravelBookingException {
public:
    /**
     * @brief Construct a new InvalidBookingException object
     * 
     * @param reason Detailed reason for booking creation failure
     */
    explicit InvalidBookingException(const std::string& reason)
        : TravelBookingException("Invalid Booking: " + reason + " - booking could not be created") {}
};

/**
 * @class AccommodationCapacityExceededException
 * @brief Exception for accommodation guest capacity limitations
 * 
 * Thrown when requested guest count exceeds accommodation capacity
 */
class AccommodationCapacityExceededException : public TravelBookingException {
public:
    /**
     * @brief Construct a new AccommodationCapacityExceededException object
     * 
     * @param accommodationName Name of the accommodation with capacity issue
     * @param guests Number of guests requested
     * @param capacity Maximum guest capacity of accommodation
     */
    explicit AccommodationCapacityExceededException(const std::string& accommodationName, int guests, int capacity) 
        : TravelBookingException("Accommodation Capacity Exceeded: " + accommodationName + 
                               " - Requested: " + std::to_string(guests) + " guests, Capacity: " + 
                               std::to_string(capacity) + " - please reduce guest count or choose different accommodation") {}
};

/**
 * @class AccommodationUnavailableException
 * @brief Exception for accommodation availability conflicts
 * 
 * Thrown when accommodation is not available for requested dates
 */
class AccommodationUnavailableException : public TravelBookingException {
public:
    /**
     * @brief Construct a new AccommodationUnavailableException object
     * 
     * @param accommodationName Name of the unavailable accommodation
     * @param dates Requested dates for accommodation
     */
    explicit AccommodationUnavailableException(const std::string& accommodationName, const std::string& dates) 
        : TravelBookingException("Accommodation Unavailable: " + accommodationName + 
                               " is not available for dates: " + dates + 
                               " - please select different dates or accommodation") {}
};

/**
 * @class MealCompatibilityException
 * @brief Exception for meal composition conflicts
 * 
 * Thrown when meal components conflict with each other or service requirements
 */
class MealCompatibilityException : public TravelBookingException {
public:
    /**
     * @brief Construct a new MealCompatibilityException object
     * 
     * @param mealName Name of the meal with compatibility issue
     * @param conflict Description of the compatibility conflict
     */
    explicit MealCompatibilityException(const std::string& mealName, const std::string& conflict) 
        : TravelBookingException("Meal Compatibility Error: " + mealName + 
                               " - " + conflict + 
                               " - please review dietary tags and meal composition") {}
};

/**
 * @class MealPricingException
 * @brief Exception for meal pricing policy violations
 * 
 * Thrown when meal price exceeds maximum allowed price per calorie ratio
 */
class MealPricingException : public TravelBookingException {
public:
    /**
     * @brief Construct a new MealPricingException object
     * 
     * @param mealName Name of the meal with pricing issue
     * @param price Current price of the meal
     * @param calories Calorie count of the meal
     * @param maxPricePerCalorie Maximum allowed price per calorie
     */
    explicit MealPricingException(const std::string& mealName, double price, int calories, double maxPricePerCalorie) 
        : TravelBookingException("Meal Pricing Error: " + mealName + 
                               " - Price $" + std::to_string(static_cast<int>(price)) + 
                               " for " + std::to_string(calories) + " calories exceeds maximum value ratio of $" + 
                               std::to_string(maxPricePerCalorie) + " per calorie - please adjust pricing") {}
};

/**
 * @class DietaryRestrictionViolationException
 * @brief Exception for dietary requirement violations
 * 
 * Thrown when meal conflicts with specific dietary restrictions
 */
class DietaryRestrictionViolationException : public TravelBookingException {
public:
    /**
     * @brief Construct a new DietaryRestrictionViolationException object
     * 
     * @param mealName Name of the meal with restriction violation
     * @param restriction Type of dietary restriction violated
     */
    explicit DietaryRestrictionViolationException(const std::string& mealName, const std::string& restriction) 
        : TravelBookingException("Dietary Restriction Violation: " + mealName + 
                               " conflicts with " + restriction + 
                               " dietary requirements - please select alternative meal") {}
};

/**
 * @class MealAllergyConflictException
 * @brief Exception for meal allergen conflicts
 * 
 * Thrown when meal contains allergens that conflict with guest allergies
 */
class MealAllergyConflictException : public TravelBookingException {
public:
    /**
     * @brief Construct a new MealAllergyConflictException object
     * 
     * @param mealName Name of the meal with allergen conflict
     * @param allergen Specific allergen causing conflict
     */
    explicit MealAllergyConflictException(const std::string& mealName, const std::string& allergen) 
        : TravelBookingException("Meal Allergy Conflict: " + mealName + 
                               " contains " + allergen + 
                               " which conflicts with guest allergies - meal substitution required") {}
};