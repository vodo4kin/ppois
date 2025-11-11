#include "TransportReview.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "utils/Utils.hpp"
#include "configs/TransportConfig.hpp"

TransportReview::TransportReview(std::shared_ptr<Transport> transport,
                                 const std::string& reviewerName,
                                 const std::string& comment,
                                 int rating)
    : transport(transport), reviewerName(reviewerName), comment(comment), rating(rating) {
    if (!transport) throw InvalidDataException("transport", "must be valid");
    if (!StringValidation::isValidName(reviewerName)) throw InvalidDataException("reviewerName", "must be valid");
    if (comment.empty()) throw InvalidDataException("comment", "cannot be empty");
    if (rating < TransportConfig::TransportReview::MIN_RATING || rating > TransportConfig::TransportReview::MAX_RATING) 
    throw InvalidDataException("rating", "must be in range \"" + std::to_string(TransportConfig::TransportReview::MIN_RATING) 
    + " - " + std::to_string(TransportConfig::TransportReview::MAX_RATING) + "\".");
}

std::shared_ptr<Transport> TransportReview::getTransport() const {
    return transport;
}

std::string TransportReview::getReviewerName() const {
    return reviewerName;
}

std::string TransportReview::getComment() const {
    return comment;
}

int TransportReview::getRating() const {
    return rating;
}

std::string TransportReview::getReviewSummary() const {
    return reviewerName + " rated " + std::to_string(rating) + "/5: " + comment;
}
