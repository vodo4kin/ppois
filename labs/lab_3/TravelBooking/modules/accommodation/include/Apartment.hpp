#pragma once
#include "Accommodation.hpp"

class Apartment : public Accommodation {
private:
    int numberOfRooms;
    bool hasKitchen;
    bool hasWashingMachine;
    double area;

public:
    Apartment(const std::string& name, const std::string& location,
              double price, int capacity, double rating,
              int rooms, bool kitchen, bool washingMachine, double area);
    
    std::string getType() const override { return "Apartment"; }
    std::string getAccommodationInfo() const override;
    int getNumberOfRooms() const { return numberOfRooms; }
    bool hasFullKitchen() const { return hasKitchen; }
    bool hasLaundry() const { return hasWashingMachine; }
    double getArea() const { return area; }
    bool isSuitableForFamily() const;
    bool isStudio() const;
    double calculatePricePerPerson() const;
    std::string getApartmentCategory() const;
    bool hasFullAmenities() const;
};