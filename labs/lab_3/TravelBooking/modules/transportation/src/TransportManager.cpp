#include "TransportManager.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "utils/Utils.hpp"
#include "configs/TransportConfig.hpp"

void TransportManager::addSchedule(const std::shared_ptr<TransportSchedule>& schedule) {
    if (!schedule) throw InvalidDataException("schedule", "must be valid");
    schedules.push_back(schedule);
}

void TransportManager::addReview(const std::shared_ptr<TransportReview>& review) {
    if (!review) throw InvalidDataException("review", "must be valid");
    reviews.push_back(review);
}

std::shared_ptr<TransportSchedule> TransportManager::findScheduleByRoute(const std::string& origin,
                                                                          const std::string& destination,
                                                                          const std::string& date) const {
    for (const auto& schedule : schedules) {
        if (schedule->getOrigin() == origin &&
            schedule->getDestination() == destination &&
            schedule->getDepartureDate() == date) {
            return schedule;
        }
    }
    throw ResourceNotFoundException("TransportSchedule", origin + " → " + destination + " on " + date);
}

void TransportManager::reserveSeats(const Transport::Type& transportType,
                                    const std::string& origin,
                                    const std::string& destination,
                                    const std::string& date,
                                    int count) {
    if (origin.length() > TransportConfig::Transport::MAX_COMPANY_NAME_LENGTH) throw InvalidDataException("length company", " cannnot be longer than" 
        + std::to_string(TransportConfig::Transport::MAX_COMPANY_NAME_LENGTH));
    if (!StringValidation::isValidDate(date)) {
        throw InvalidDateException("reserve seats date");
    }
    if (count < 1) {
        throw InvalidDataException("reserve seats count", "must be > 0");
    }
    auto schedule = findScheduleByRoute(origin, destination, date);
    schedule->reserveSeats(count);
}

std::vector<std::shared_ptr<TransportReview>> TransportManager::getReviewsForTransport(const std::string& transportType) const {
    std::vector<std::shared_ptr<TransportReview>> result;
    for (const auto& review : reviews) {
        if (review->getTransport()->getTransportTypeStr() == transportType) {
            result.push_back(review);
        }
    }
    return result;
}
