#include "BookCondition.hpp"

BookCondition::BookCondition(Condition condition) noexcept 
    : condition(condition) {}

BookCondition::Condition BookCondition::getCondition() const noexcept {
    return condition;
}

std::string BookCondition::toString() const noexcept {
    switch(condition) {
        case Condition::NEW: return "New";
        case Condition::LIKE_NEW: return "Like New";
        case Condition::VERY_GOOD: return "Very Good";
        case Condition::GOOD: return "Good";
        case Condition::FAIR: return "Fair";
        case Condition::POOR: return "Poor";
        default: return "Unknown";
    }
}

bool BookCondition::isNew() const noexcept {
    return condition == Condition::NEW;
}

bool BookCondition::isUsed() const noexcept {
    return condition != Condition::NEW;
}

bool BookCondition::needsReplacement() const noexcept {
    return condition == Condition::POOR;
}

bool BookCondition::operator==(const BookCondition& other) const noexcept {
    return condition == other.condition;
}

bool BookCondition::operator!=(const BookCondition& other) const noexcept {
    return condition != other.condition;
}