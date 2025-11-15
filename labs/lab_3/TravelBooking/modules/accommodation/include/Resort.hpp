#pragma once
#include "Accommodation.hpp"

class Resort : public Accommodation {
private:
    bool hasPrivateBeach;
    int numberOfRestaurants;
    bool hasSpa;
    std::vector<std::string> activities;
public:
    Resort(const std::string& name, const std::string& location,
           double price, int capacity, double rating,
           bool beach, int restaurants, bool spa, const std::vector<std::string>& activities);
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    bool hasBeachAccess() const;
    int getRestaurantCount() const;
    bool hasSpaServices() const;
    std::vector<std::string> getActivities() const;
    bool isLuxuryResort() const;
    bool hasComprehensiveAmenities() const;
    int getActivityCount() const;
    std::string getResortCategory() const;
    bool isBeachResort() const;
};