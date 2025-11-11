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
    std::string getType() const override { return "Hotel"; }
    std::string getAccommodationInfo() const override;
    int getStarRating() const { return starRating; }
    bool hasSwimmingPool() const { return hasPool; }
    bool hasSpaService() const { return hasSpa; }
    std::string getRoomType() const { return roomType; }
};