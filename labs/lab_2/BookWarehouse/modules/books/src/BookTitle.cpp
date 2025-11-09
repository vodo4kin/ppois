#include "BookTitle.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"

bool BookTitle::isValidTitle(const std::string& title) const{
    if (title.length() < BookConfig::BookTitle::MIN_LENGTH || title.length() > BookConfig::BookTitle::MAX_LENGTH) return false;
    bool hasNonSpace = false;
    for(char c : title){
        if(c == '\t' || c == '\n' || c == '\r') return false;
        if(c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

BookTitle::BookTitle(const std::string& title, const std::string& subtitle, const std::string& language){
    if(!isValidTitle(title)){
        throw DataValidationException("Invalid book title: '" + title + "'");
    }
    if (!subtitle.empty() && !isValidTitle(subtitle)) {
        throw DataValidationException("Invalid book subtitle: '" + subtitle + "'");
    }
    std::string newLanguage = StringValidation::normalizeLanguage(language);
    if (newLanguage.empty() || newLanguage.length() != 2){
        throw DataValidationException("Language must be 2 letters: '" + language + "'");
    }
    this->title = title;
    this->subtitle = subtitle;
    this->language = newLanguage;
}

std::string BookTitle::getTitle() const noexcept{
    return title;
}

std::string BookTitle::getSubtitle() const noexcept{
    return subtitle;
}

std::string BookTitle::getLanguage() const noexcept{
    return language;
}

std::string BookTitle::getFullTitle() const noexcept{
    return subtitle.empty()? title + " (" + language +
    ")":title + ": " + subtitle + " (" + language + ")";
}

bool BookTitle::operator==(const BookTitle& other) const noexcept{
    return title == other.title && 
           subtitle == other.subtitle && 
           language == other.language;
}

bool BookTitle::operator!=(const BookTitle& other) const noexcept{
    return !(*this == other);
}