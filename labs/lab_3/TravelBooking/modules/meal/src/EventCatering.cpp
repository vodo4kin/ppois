#include "EventCatering.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

EventCatering::EventCatering(const std::string& name, const std::string& description,
                             double price, int calories, const std::vector<std::string>& tags,
                             int minGuests, const std::string& serviceType, bool staff, 
                             const std::string& eventType)
    : Meal(name, description, price, calories, tags),
      minimumGuests(minGuests), serviceType(serviceType), 
      includesServiceStaff(staff), eventType(eventType) {
    if (calories < MealConfig::EventCatering::MIN_CALORIES || 
        calories > MealConfig::EventCatering::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::EventCatering::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::EventCatering::MAX_CALORIES));
    }
    if (minimumGuests < MealConfig::EventCatering::MIN_GUESTS || 
        minimumGuests > MealConfig::EventCatering::MAX_GUESTS) {
        throw InvalidDataException("minimumGuests", "must be between " + 
            std::to_string(MealConfig::EventCatering::MIN_GUESTS) + " and " + 
            std::to_string(MealConfig::EventCatering::MAX_GUESTS));
    }
    if (!StringValidation::isValidName(serviceType) || 
        serviceType.length() > MealConfig::EventCatering::MAX_SERVICE_TYPE_LENGTH) {
        throw InvalidDataException("serviceType", "must be valid and not longer than " + 
            std::to_string(MealConfig::EventCatering::MAX_SERVICE_TYPE_LENGTH));
    }
    if (!StringValidation::isValidName(eventType) || 
        eventType.length() > MealConfig::EventCatering::MAX_EVENT_TYPE_LENGTH) {
        throw InvalidDataException("eventType", "must be valid and not longer than " + 
            std::to_string(MealConfig::EventCatering::MAX_EVENT_TYPE_LENGTH));
    }
    if (includesServiceStaff) addDietaryTag("service-staff");
    if (minimumGuests >= MealConfig::EventCatering::LARGE_EVENT_THRESHOLD) addDietaryTag("large-event");
    addDietaryTag(eventType + "-catering");
}

std::string EventCatering::getType() const {
    return "Event Catering";
}

std::string EventCatering::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Minimum Guests: " + std::to_string(minimumGuests) + "\n" +
           "Service Type: " + serviceType + "\n" +
           "Service Staff: " + std::string(includesServiceStaff ? "Yes" : "No") + "\n" +
           "Event Type: " + eventType + "\n";
    return info;
}

int EventCatering::getMinimumGuests() const {
    return minimumGuests;
}

std::string EventCatering::getServiceType() const {
    return serviceType;
}

bool EventCatering::hasServiceStaff() const {
    return includesServiceStaff;
}

std::string EventCatering::getEventType() const {
    return eventType;
}

bool EventCatering::isLargeEvent() const {
    return minimumGuests >= MealConfig::EventCatering::LARGE_EVENT_THRESHOLD;
}

bool EventCatering::isFormalService() const {
    return serviceType == "served" && includesServiceStaff;
}

std::string EventCatering::getCateringCategory() const {
    if (isLargeEvent() && isFormalService()) return "Premium Event Catering";
    else if (isLargeEvent()) return "Large Event Catering";
    else return "Standard Event Catering";
}