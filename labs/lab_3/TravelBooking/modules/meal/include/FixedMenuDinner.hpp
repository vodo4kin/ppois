#pragma once
#include "Meal.hpp"

class FixedMenuDinner : public Meal {
private:
    std::vector<std::string> menuItems;
    bool includesWinePairing;
    std::string ambiance;
public:
    FixedMenuDinner(const std::string& name, const std::string& description,
                    double price, int calories, const std::vector<std::string>& tags,
                    const std::vector<std::string>& items, bool wine, const std::string& ambiance);
    
    std::string getType() const override;
    std::string getMealInfo() const override;
    std::vector<std::string> getMenuItems() const;
    bool hasWinePairing() const;
    std::string getAmbiance() const;
    bool isFineDining() const;
    bool hasMultipleCourses() const;
    std::string getDinnerCategory() const;
};