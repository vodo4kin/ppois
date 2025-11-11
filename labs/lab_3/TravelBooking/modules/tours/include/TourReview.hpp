#pragma once
#include <string>

class TourReview {
private:
    std::string reviewerName;
    std::string comment;
    int rating;
public:
    TourReview(const std::string& reviewerName,
               const std::string& comment,
               int rating);
    std::string getReviewerName() const;
    std::string getComment() const;
    int getRating() const;
    std::string getReviewSummary() const;
};
