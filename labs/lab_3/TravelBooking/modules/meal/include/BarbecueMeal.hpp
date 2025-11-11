#pragma once
#include "Meal.hpp"

class BarbecueMeal : public Meal {
private:
    std::vector<std::string> meatTypes;
    bool vegetarianOptions;
    bool selfService;
    std::string locationType;
public:
    BarbecueMeal(const std::string& name, const std::string& description,
                 double price, int calories, const std::vector<std::string>& tags,
                 const std::vector<std::string>& meats, bool veggie, bool selfService, 
                 const std::string& location);
    std::string getType() const override;
    std::string getMealInfo() const override;
    std::vector<std::string> getMeatTypes() const;
    bool hasVegetarianOptions() const;
    bool isSelfService() const;
    std::string getLocationType() const;
    bool isOutdoorBarbecue() const;
    bool hasMultipleMeatOptions() const;
    std::string getBarbecueCategory() const;
};