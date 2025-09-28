#include "books/Genre.hpp"


Genre::Genre(Type genre) noexcept: genre(genre){}

std::string Genre::toString() const noexcept{
    switch(genre){
        case Type::AUTOBIOGRAPHY: return "Autobiography";
        case Type::MYSTERY: return "Mystery";
        case Type::THRILLER: return "Thriller";
        case Type::FANTASY: return "Fantasy";
        case Type::SCIENCE_FICTION: return "Science Fiction";
        case Type::ROMANCE: return "Romance";
        case Type::HISTORICAL_FICTION: return "Historical Fiction";
        case Type::HORROR: return "Horror";
        case Type::FOR_CHILDREN: return "For Children";
        case Type::DRAMA: return "Drama";
        case Type::POETRY: return "Poetry";
        case Type::OTHER: return "Other";
        default: return "Unknown Genre";
    }
}

Genre::Type Genre::getGenre() const noexcept{
    return genre;
}

bool Genre::operator==(const Genre& other) const noexcept{
    return genre == other.genre;
}

bool Genre::operator!=(const Genre& other) const noexcept{
    return !(*this == other);
}