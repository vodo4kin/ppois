#pragma once
#include "Meal.hpp"

class DietarySpecificMeal : public Meal {
private:
    std::string dietType;
    bool nutritionistApproved;
    std::string portionControl;
    std::vector<std::string> allergensExcluded;
public:
    DietarySpecificMeal(const std::string& name, const std::string& description,
                        double price, int calories, const std::vector<std::string>& tags,
                        const std::string& dietType, bool approved, 
                        const std::string& portion, const std::vector<std::string>& allergens);
    std::string getType() const override;
    std::string getMealInfo() const override;
    std::string getDietType() const;
    bool isNutritionistApproved() const;
    std::string getPortionControl() const;
    std::vector<std::string> getAllergensExcluded() const;
    bool isStrictDiet() const;
    bool isAllergenFree() const;
    std::string getDietCategory() const;
};