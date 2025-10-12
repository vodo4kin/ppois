#include "warehouse/WarehouseSection.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"
#include <regex>

bool WarehouseSection::isValidSectionId(const std::string& sectionId) const {
    std::regex pattern("^[A-Z]$");
    return std::regex_match(sectionId, pattern);
}

bool WarehouseSection::isValidTemperature(double temperature) const {
    return temperature >= WarehouseConfig::WarehouseSection::MIN_TEMPERATURE && 
           temperature <= WarehouseConfig::WarehouseSection::MAX_TEMPERATURE;
}

bool WarehouseSection::isValidHumidity(double humidity) const {
    return humidity >= WarehouseConfig::WarehouseSection::MIN_HUMIDITY && 
           humidity <= WarehouseConfig::WarehouseSection::MAX_HUMIDITY;
}

bool WarehouseSection::isValidName(const std::string& name) const {
    return StringValidation::isValidName(name, WarehouseConfig::WarehouseSection::MAX_NAME_LENGTH);
}

WarehouseSection::WarehouseSection(const std::string& sectionId, const std::string& name, 
                                 const std::string& description, SectionType sectionType,
                                 double temperature, double humidity) {
    if (!isValidSectionId(sectionId)) {
        throw DataValidationException("Invalid section ID: " + sectionId);
    }
    if (!isValidName(name)) {
        throw DataValidationException("Invalid section name: " + name);
    }
    if (!isValidTemperature(temperature)) {
        throw DataValidationException("Invalid temperature: " + std::to_string(temperature));
    }
    if (!isValidHumidity(humidity)) {
        throw DataValidationException("Invalid humidity: " + std::to_string(humidity));
    }
    this->sectionId = sectionId;
    this->name = name;
    this->description = description;
    this->sectionType = sectionType;
    this->temperature = temperature;
    this->humidity = humidity;
}

std::string WarehouseSection::getSectionId() const noexcept {
    return sectionId;
}

std::string WarehouseSection::getName() const noexcept {
    return name;
}

std::string WarehouseSection::getDescription() const noexcept {
    return description;
}

WarehouseSection::SectionType WarehouseSection::getSectionType() const noexcept {
    return sectionType;
}

double WarehouseSection::getTemperature() const noexcept {
    return temperature;
}

double WarehouseSection::getHumidity() const noexcept {
    return humidity;
}

std::vector<std::shared_ptr<Shelf>> WarehouseSection::getShelves() const noexcept {
    return shelves;
}

int WarehouseSection::getShelvesCount() const noexcept {
    return shelves.size();
}

void WarehouseSection::addShelf(std::shared_ptr<Shelf> shelf) {
    if (!shelf) {
        throw DataValidationException("Cannot add null shelf to section");
    }
    if (containsShelf(shelf->getShelfId())) {
        throw DataValidationException("Shelf " + shelf->getShelfId() + " already exists in section " + sectionId);
    }
    shelves.push_back(shelf);
}

void WarehouseSection::removeShelf(const std::string& shelfId) {
    auto it = std::find_if(shelves.begin(), shelves.end(),
        [&shelfId](const std::shared_ptr<Shelf>& shelf) {
            return shelf->getShelfId() == shelfId;
        });
    if (it != shelves.end()) {
        shelves.erase(it);
    }
}

std::shared_ptr<Shelf> WarehouseSection::findShelf(const std::string& shelfId) const noexcept {
    auto it = std::find_if(shelves.begin(), shelves.end(),
        [&shelfId](const std::shared_ptr<Shelf>& shelf) {
            return shelf->getShelfId() == shelfId;
        });
    return (it != shelves.end()) ? *it : nullptr;
}

bool WarehouseSection::containsShelf(const std::string& shelfId) const noexcept {
    return findShelf(shelfId) != nullptr;
}

std::vector<std::shared_ptr<StorageLocation>> WarehouseSection::findAvailableLocations() const noexcept {
    std::vector<std::shared_ptr<StorageLocation>> availableLocations;
    for (const auto& shelf : shelves) {
        auto shelfAvailable = shelf->getAvailableLocations();
        availableLocations.insert(availableLocations.end(), shelfAvailable.begin(), shelfAvailable.end());
    }
    return availableLocations;
}

std::shared_ptr<StorageLocation> WarehouseSection::findLocation(const std::string& locationId) const noexcept {
    //"A-01-B-05" where A is section, 01 is shelf
    for (const auto& shelf : shelves) {
        auto location = shelf->findLocation(locationId);
        if (location) {
            return location;
        }
    }
    return nullptr;
}

int WarehouseSection::getTotalCapacity() const noexcept {
    int total = 0;
    for (const auto& shelf : shelves) {
        total += shelf->getTotalCapacity();
    }
    return total;
}

int WarehouseSection::getCurrentLoad() const noexcept {
    int total = 0;
    for (const auto& shelf : shelves) {
        total += shelf->getCurrentLoad();
    }
    return total;
}

int WarehouseSection::getAvailableSpace() const noexcept {
    return getTotalCapacity() - getCurrentLoad();
}

bool WarehouseSection::isEmpty() const noexcept {
    return getCurrentLoad() == 0;
}

bool WarehouseSection::isFull() const noexcept {
    for (const auto& shelf : shelves) {
        if (!shelf->isFull()) {
            return false;
        }
    }
    return true;
}

void WarehouseSection::setTemperature(double temperature) {
    if (!isValidTemperature(temperature)) {
        throw DataValidationException("Invalid temperature: " + std::to_string(temperature));
    }
    this->temperature = temperature;
}

void WarehouseSection::setHumidity(double humidity) {
    if (!isValidHumidity(humidity)) {
        throw DataValidationException("Invalid humidity: " + std::to_string(humidity));
    }
    this->humidity = humidity;
}

std::string WarehouseSection::getInfo() const noexcept {
    return "Section: " + sectionId + " (" + name + ")" +
           " | Type: " + getSectionTypeString() +
           " | Shelves: " + std::to_string(shelves.size()) +
           " | Capacity: " + std::to_string(getTotalCapacity()) +
           " | Load: " + std::to_string(getCurrentLoad()) +
           " | Available: " + std::to_string(getAvailableSpace()) +
           " | Temp: " + std::to_string(temperature) + "°C" +
           " | Humidity: " + std::to_string(humidity) + "%";
}

std::string WarehouseSection::getSectionTypeString() const noexcept {
    switch (sectionType) {
        case SectionType::GENERAL: return "General";
        case SectionType::REFRIGERATED: return "Refrigerated";
        case SectionType::SECURE: return "Secure";
        case SectionType::BULK: return "Bulk";
        case SectionType::PICKING: return "Picking";
        default: return "Unknown";
    }
}

bool WarehouseSection::operator==(const WarehouseSection& other) const noexcept {
    return sectionId == other.sectionId &&
           name == other.name &&
           description == other.description &&
           sectionType == other.sectionType &&
           temperature == other.temperature &&
           humidity == other.humidity &&
           shelves == other.shelves;
}

bool WarehouseSection::operator!=(const WarehouseSection& other) const noexcept {
    return !(*this == other);
}