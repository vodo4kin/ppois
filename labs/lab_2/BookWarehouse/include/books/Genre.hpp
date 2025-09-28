#include <string>

class Genre{
    public:
    enum class Type{
        MYSTERY, THRILLER, FANTASY, SCIENCE_FICTION,
        ROMANCE, HISTORICAL_FICTION, HORROR, FOR_CHILDREN,
        AUTOBIOGRAPHY, DRAMA, POETRY, OTHER
    };
    private:
    Type genre;
    public:
    explicit Genre(Type genre) noexcept;
    std::string toString() const noexcept;
    Type getGenre() const noexcept;
    bool operator==(const Genre& other) const noexcept;
    bool operator!=(const Genre& other) const noexcept;
}; 