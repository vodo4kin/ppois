#pragma once
#include <string>

class BookCondition {
public:
    enum class Condition {
        NEW,        // новая
        LIKE_NEW,   // как новая
        VERY_GOOD,  // очень хорошее
        GOOD,       // хорошее
        FAIR,       // удовлетворительное  
        POOR        // плохое
    };
private:
    Condition condition;
public:
    explicit BookCondition(Condition condition) noexcept;
    Condition getCondition() const noexcept;
    std::string toString() const noexcept;
    bool isNew() const noexcept;
    bool isUsed() const noexcept;
    bool needsReplacement() const noexcept; // POOR - требует замены
    bool operator==(const BookCondition& other) const noexcept;
    bool operator!=(const BookCondition& other) const noexcept;
};