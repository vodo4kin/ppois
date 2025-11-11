#pragma once

#include <string>
#include <vector>
#include <memory>

class Accommodation {
protected:
    std::string name;
    std::string location;
    double pricePerNight;
    int capacity;
    double rating;
    std::vector<std::string> amenities;

public:
    Accommodation(const std::string& name, const std::string& location, 
                  double price, int capacity, double rating);
    
    virtual std::string getType() const = 0;
    virtual std::string getAccommodationInfo() const;
    virtual ~Accommodation() = default;
    std::string getName() const { return name; }
    std::string getLocation() const { return location; }
    double getPricePerNight() const { return pricePerNight; }
    int getCapacity() const { return capacity; }
    double getRating() const { return rating; }
    std::vector<std::string> getAmenities() const { return amenities; }
    void addAmenity(const std::string& amenity);
    void setPricePerNight(double price);
    void setRating(double newRating);
    bool canAccommodate(int guests) const;
    bool isAvailableForDates(const std::string& startDate, const std::string& endDate) const;
    void validateBooking(int guests, const std::string& startDate, const std::string& endDate) const;
};