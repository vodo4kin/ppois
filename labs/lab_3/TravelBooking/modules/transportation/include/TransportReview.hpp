#pragma once
#include <string>
#include <memory>
#include "Transport.hpp"

class TransportReview {
private:
    std::shared_ptr<Transport> transport;
    std::string reviewerName;
    std::string comment;
    int rating;
public:
    TransportReview(std::shared_ptr<Transport> transport,
                    const std::string& reviewerName,
                    const std::string& comment,
                    int rating);
    std::shared_ptr<Transport> getTransport() const;
    std::string getReviewerName() const;
    std::string getComment() const;
    int getRating() const;
    std::string getReviewSummary() const;
};
