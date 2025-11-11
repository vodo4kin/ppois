#pragma once
#include <vector>
#include <memory>
#include <string>
#include "TransportSchedule.hpp"
#include "TransportReview.hpp"

class TransportManager {
private:
    std::vector<std::shared_ptr<TransportSchedule>> schedules;
    std::vector<std::shared_ptr<TransportReview>> reviews;
public:
    void addSchedule(const std::shared_ptr<TransportSchedule>& schedule);
    void addReview(const std::shared_ptr<TransportReview>& review);
    std::shared_ptr<TransportSchedule> findScheduleByRoute(const std::string& origin,
                                                            const std::string& destination,
                                                            const std::string& date) const;
    void reserveSeats(const Transport::Type& transportType,
                      const std::string& origin,
                      const std::string& destination,
                      const std::string& date,
                      int count);
    std::vector<std::shared_ptr<TransportReview>> getReviewsForTransport(const std::string& transportType) const;
};
