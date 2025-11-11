#pragma once
#include <string>
#include <memory>
#include "Tour.hpp"

class TourSchedule {
private:
    std::shared_ptr<Tour> tour;
    std::string scheduledDate;
    int availableSlots;

public:
    TourSchedule(std::shared_ptr<Tour> tour,
                 const std::string& scheduledDate,
                 int availableSlots);

    std::shared_ptr<Tour> getTour() const;
    std::string getScheduledDate() const;
    int getAvailableSlots() const;
    void reduceSlots(int count);
    std::string getScheduleInfo() const;
};
