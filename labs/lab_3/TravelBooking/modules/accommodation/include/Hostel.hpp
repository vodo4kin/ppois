#pragma once
#include "Accommodation.hpp"

class Hostel : public Accommodation {
private:
    bool isPrivateRoom;
    int bedsPerRoom;
    bool hasSharedKitchen;
    std::string bathroomType;
public:
    Hostel(const std::string& name, const std::string& location,
           double price, int capacity, double rating,
           bool privateRoom, int beds, bool sharedKitchen, const std::string& bathroom);
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    bool isPrivate() const;
    int getBedsPerRoom() const;
    bool hasCommonKitchen() const;
    std::string getBathroomType() const;
    bool isDormitory() const;
    double calculatePricePerBed() const;
    bool hasPrivateBathroom() const;
    std::string getHostelCategory() const;
    bool isSuitableForGroup(int groupSize) const;
};