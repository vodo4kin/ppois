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
    std::string getType() const override { return "Cruise Cabin"; }
    std::string getAccommodationInfo() const override;
    std::string getCabinType() const { return cabinType; }
    int getDeckNumber() const { return deckNumber; }
    bool hasOceanView() const { return hasWindow; }
    std::string getShipName() const { return shipName; }
    bool isPremiumCabin() const;
    bool isInteriorCabin() const;
    bool hasView() const;
    std::string getCabinCategory() const;
    bool isOnUpperDeck() const;
};