#pragma once
#include "Accommodation.hpp"

class CruiseCabin : public Accommodation {
private:
    std::string cabinType;
    int deckNumber;
    bool hasWindow;
    std::string shipName;
public:
    CruiseCabin(const std::string& name, const std::string& location,
                double price, int capacity, double rating,
                const std::string& cabinType, int deck, bool window, const std::string& ship);
    std::string getType() const override;
    std::string getAccommodationInfo() const override;
    std::string getCabinType() const;
    int getDeckNumber() const;
    bool hasOceanView() const;
    std::string getShipName() const;
    bool isPremiumCabin() const;
    bool isInteriorCabin() const;
    bool hasView() const;
    std::string getCabinCategory() const;
    bool isOnUpperDeck() const;
};