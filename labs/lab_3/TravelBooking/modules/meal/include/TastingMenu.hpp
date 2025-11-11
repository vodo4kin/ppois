#pragma once
#include "Meal.hpp"

class TastingMenu : public Meal {
private:
    int numberOfDishes;
    std::string chefSpecialty;
    bool includesWineTasting;
    std::string pairingNotes;
public:
    TastingMenu(const std::string& name, const std::string& description,
                double price, int calories, const std::vector<std::string>& tags,
                int dishes, const std::string& chefSpecialty, bool wineTasting, 
                const std::string& pairingNotes);
    std::string getType() const override;
    std::string getMealInfo() const override;
    int getNumberOfDishes() const;
    std::string getChefSpecialty() const;
    bool hasWineTasting() const;
    std::string getPairingNotes() const;
    bool isPremiumTasting() const;
    bool isWinePaired() const;
    std::string getTastingCategory() const;
};