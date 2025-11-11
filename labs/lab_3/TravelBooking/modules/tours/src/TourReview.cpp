#include "TourReview.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "utils/Utils.hpp"
#include "configs/ToursConfig.hpp"

TourReview::TourReview(const std::string& reviewerName,
                       const std::string& comment,
                       int rating)
    : reviewerName(reviewerName), comment(comment), rating(rating) {
    if (!StringValidation::isValidName(reviewerName)) throw InvalidDataException("reviewerName", "must be valid");
    if (comment.empty() || comment.length() > ToursConfig::TourReview::MAX_REVIEW_LENGTH) throw InvalidDataException("comment", "cannot be empty or longer then" 
        + std::to_string(ToursConfig::TourReview::MAX_REVIEW_LENGTH));
    if (rating < ToursConfig::TourReview::MIN_RATING || rating > ToursConfig::TourReview::MAX_RATING) 
        throw InvalidDataException("rating", "must be between 1 and 5");
}

std::string TourReview::getReviewerName() const {
    return reviewerName;
}

std::string TourReview::getComment() const {
    return comment;
}

int TourReview::getRating() const {
    return rating;
}

std::string TourReview::getReviewSummary() const {
    return reviewerName + " rated " + std::to_string(rating) + "/5: " + comment;
}
