#pragma once
#include "Accommodation.hpp"

class MountainLodge : public Accommodation {
private:
    int altitude;
    bool hasHeating;
    bool hasFireplace;
    std::string accessibility;
public:
    MountainLodge(const std::string& name, const std::string& location,
                  double price, int capacity, double rating,
                  int altitude, bool heating, bool fireplace, const std::string& accessibility);
    std::string getType() const override { return "Mountain Lodge"; }
    std::string getAccommodationInfo() const override;
    int getAltitude() const { return altitude; }
    bool hasHeatingSystem() const { return hasHeating; }
    bool hasFireplaceFeature() const { return hasFireplace; }
    std::string getAccessibilityLevel() const { return accessibility; }
    bool isHighAltitude() const;
    bool isWinterReady() const;
    std::string getLodgeCategory() const;
    bool isRemoteLocation() const;
    bool requiresExperience() const;
};