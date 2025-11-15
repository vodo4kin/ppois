#pragma once
#include "Accommodation.hpp"

class Villa : public Accommodation {
private:
    int numberOfFloors;
    bool hasPrivatePool;
    bool hasGarden;
    bool hasParking;
public:
    Villa(const std::string& name, const std::string& location,
          double price, int capacity, double rating,
          int floors, bool pool, bool garden, bool parking);
    
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    int getNumberOfFloors() const;
    bool hasPool() const;
    bool hasGardenArea() const;
    bool hasParkingSpace() const;
    bool isLuxuryVilla() const;
    bool hasFullPrivacy() const;
    double calculateLuxurySurcharge() const;
    std::string getVillaCategory() const;
    bool isSuitableForEvents() const;
};