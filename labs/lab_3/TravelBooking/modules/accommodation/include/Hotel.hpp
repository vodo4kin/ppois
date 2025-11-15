#pragma once
#include "Accommodation.hpp"

class Hotel : public Accommodation {
private:
    int starRating;
    bool hasPool;
    bool hasSpa;
    std::string roomType;
public:
    Hotel(const std::string& name, const std::string& location, 
          double price, int capacity, double rating,
          int stars, bool pool, bool spa, const std::string& roomType);
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    int getStarRating() const;
    bool hasSwimmingPool() const;
    bool hasSpaService() const;
    std::string getRoomType() const;
};