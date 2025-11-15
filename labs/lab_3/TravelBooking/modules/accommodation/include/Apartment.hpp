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
    
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    int getNumberOfRooms() const;
    bool hasFullKitchen() const;
    bool hasLaundry() const;
    double getArea() const;
    bool isSuitableForFamily() const;
    bool isStudio() const;
    double calculatePricePerPerson() const;
    std::string getApartmentCategory() const;
    bool hasFullAmenities() const;
};