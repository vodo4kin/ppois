#pragma once

#include <string>
#include <vector>
#include <memory>

class Meal {
protected:
    std::string name;
    std::string description;
    double price;
    int calories;
    std::vector<std::string> dietaryTags;
public:
    Meal(const std::string& name, const std::string& description, 
         double price, int calories, const std::vector<std::string>& tags);
    virtual std::string getType() const = 0;
    virtual std::string getMealInfo() const;
    virtual ~Meal() = default;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getCalories() const;
    std::vector<std::string> getDietaryTags() const;
    void addDietaryTag(const std::string& tag);
    void setPrice(double newPrice);
    void setCalories(int newCalories);
    bool isSuitableForDiet(const std::string& diet) const;
    bool isWithinCalorieRange(int minCalories, int maxCalories) const;
    void validateMeal() const;
};