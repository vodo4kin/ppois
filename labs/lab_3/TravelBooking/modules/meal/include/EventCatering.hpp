#pragma once
#include "Meal.hpp"

class EventCatering : public Meal {
private:
    int minimumGuests;
    std::string serviceType;
    bool includesServiceStaff;
    std::string eventType;
public:
    EventCatering(const std::string& name, const std::string& description,
                  double price, int calories, const std::vector<std::string>& tags,
                  int minGuests, const std::string& serviceType, bool staff, 
                  const std::string& eventType);
    std::string getType() const override;
    std::string getMealInfo() const override;
    int getMinimumGuests() const;
    std::string getServiceType() const;
    bool hasServiceStaff() const;
    std::string getEventType() const;
    bool isLargeEvent() const;
    bool isFormalService() const;
    std::string getCateringCategory() const;
};