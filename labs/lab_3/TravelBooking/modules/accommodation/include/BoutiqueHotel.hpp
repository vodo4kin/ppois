#pragma once
#include "Accommodation.hpp"

class BoutiqueHotel : public Accommodation {
private:
    std::string theme;
    int yearBuilt;
    bool hasConcierge;
    std::string architecturalStyle;
public:
    BoutiqueHotel(const std::string& name, const std::string& location,
                  double price, int capacity, double rating,
                  const std::string& theme, int year, bool concierge, const std::string& style);
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    std::string getTheme() const;
    int getYearBuilt() const;
    bool hasConciergeService() const;
    std::string getArchitecturalStyle() const;
    bool isHistoric() const;
    bool isDesignHotel() const;
    bool hasPremiumServices() const;
    std::string getBoutiqueCategory() const;
    int calculateHotelAge() const;
};