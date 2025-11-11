#pragma once
#include "Meal.hpp"

class PicnicLunch : public Meal {
private:
    bool isPrePackaged;
    bool needsHeating;
    std::vector<std::string> containerTypes;
public:
    PicnicLunch(const std::string& name, const std::string& description,
                double price, int calories, const std::vector<std::string>& tags,
                bool prePackaged, bool heating, const std::vector<std::string>& containers);
    std::string getType() const override;
    std::string getMealInfo() const override;
    bool isPrePackagedMeal() const;
    bool needsHeatings() const;
    std::vector<std::string> getContainerTypes() const;
    bool isReadyToEat() const;
    bool isOutdoorFriendly() const;
    std::string getPicnicCategory() const;
};