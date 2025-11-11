#include "TourSchedule.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"

TourSchedule::TourSchedule(std::shared_ptr<Tour> tour,
                           const std::string& scheduledDate,
                           int availableSlots)
    : tour(tour), scheduledDate(scheduledDate), availableSlots(availableSlots) {
    if (!tour) throw InvalidDataException("tour", "must be valid");
    if (!StringValidation::isValidDate(scheduledDate)) throw InvalidDateException("scheduledDate");
    if (availableSlots < 0) throw InvalidDataException("availableSlots", "must be non-negative");
}

std::shared_ptr<Tour> TourSchedule::getTour() const {
    return tour;
}

std::string TourSchedule::getScheduledDate() const {
    return scheduledDate;
}

int TourSchedule::getAvailableSlots() const {
    return availableSlots;
}

void TourSchedule::reduceSlots(int count) {
    if (count > availableSlots) {
        throw TourCapacityExceededException(tour->getTitle(), count, availableSlots);
    }
    availableSlots -= count;
}

std::string TourSchedule::getScheduleInfo() const {
    return "Tour: " + tour->getTitle() + "\n"
         + "Date: " + scheduledDate + "\n"
         + "Available Slots: " + std::to_string(availableSlots);
}
