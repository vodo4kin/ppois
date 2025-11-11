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
    
    std::string getType() const override { return "Villa"; }
    std::string getAccommodationInfo() const override;
    int getNumberOfFloors() const { return numberOfFloors; }
    bool hasPool() const { return hasPrivatePool; }
    bool hasGardenArea() const { return hasGarden; }
    bool hasParkingSpace() const { return hasParking; }
    bool isLuxuryVilla() const;
    bool hasFullPrivacy() const;
    double calculateLuxurySurcharge() const;
    std::string getVillaCategory() const;
    bool isSuitableForEvents() const;
};