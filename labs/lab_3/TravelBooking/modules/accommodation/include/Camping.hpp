#pragma once
#include "Accommodation.hpp"

class Camping : public Accommodation {
private:
    std::string accommodationType;
    bool hasSharedBathroom;
    bool hasElectricity;
    bool campfireAllowed;
public:
    Camping(const std::string& name, const std::string& location,
            double price, int capacity, double rating,
            const std::string& accType, bool sharedBath, bool electricity, bool campfire);
    std::string getType() const override { return "Camping"; }
    std::string getAccommodationInfo() const override;
    std::string getAccommodationType() const { return accommodationType; }
    bool hasSharedBathrooms() const { return hasSharedBathroom; }
    bool hasElectricalAccess() const { return hasElectricity; }
    bool isCampfireAllowed() const { return campfireAllowed; }
    bool isGlamping() const;
    bool isBasicCamping() const;
    bool hasEssentialAmenities() const;
    std::string getCampingCategory() const;
    bool isFamilyFriendly() const;
};