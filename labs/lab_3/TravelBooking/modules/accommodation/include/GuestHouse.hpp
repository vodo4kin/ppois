#pragma once
#include "Accommodation.hpp"

class GuestHouse : public Accommodation {
private:
    bool isFamilyOwned;
    int totalRooms;
    std::string hostLanguage;
    bool hasCommonArea;
public:
    GuestHouse(const std::string& name, const std::string& location,
               double price, int capacity, double rating,
               bool familyOwned, int totalRooms, const std::string& language, bool commonArea);
    std::string getType() const override { return "Guest House"; }
    std::string getAccommodationInfo() const override;
    bool isFamilyBusiness() const { return isFamilyOwned; }
    int getTotalRooms() const { return totalRooms; }
    std::string getHostLanguage() const { return hostLanguage; }
    bool hasCommonSpace() const { return hasCommonArea; }
    bool isSmallGuestHouse() const;
    bool offersPersonalService() const;
    std::string getGuestHouseType() const;
    bool isSuitableForLongStay() const;
    bool hasCommunityAtmosphere() const;
};