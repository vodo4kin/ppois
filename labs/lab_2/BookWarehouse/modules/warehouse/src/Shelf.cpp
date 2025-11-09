#include "Shelf.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include <regex>

bool Shelf::isValidShelfId(const std::string& shelfId) const {
    std::regex pattern("^[A-Z]-\\d{2}$"); // Format: "A-01"
    return std::regex_match(shelfId, pattern) && !shelfId.empty();
}

bool Shelf::isValidMaxLocations(int maxLocations) const {
    return maxLocations >= WarehouseConfig::Shelf::MIN_LOCATIONS && 
           maxLocations <= WarehouseConfig::Shelf::MAX_LOCATIONS;
}

Shelf::Shelf(const std::string& shelfId, int maxLocations) {
    if (!isValidShelfId(shelfId)) {
        throw DataValidationException("Invalid shelf ID format: " + shelfId);
    }
    if (!isValidMaxLocations(maxLocations)) {
        throw DataValidationException("Invalid max locations: " + std::to_string(maxLocations));
    }
    this->shelfId = shelfId;
    this->maxLocations = maxLocations;
}

std::string Shelf::getShelfId() const noexcept {
    return shelfId;
}

int Shelf::getMaxLocations() const noexcept {
    return maxLocations;
}

int Shelf::getCurrentLocationsCount() const noexcept {
    return locations.size();
}

std::vector<std::shared_ptr<StorageLocation>> Shelf::getLocations() const noexcept {
    return locations;
}

void Shelf::addLocation(std::shared_ptr<StorageLocation> location) {
    if (!location) {
        throw DataValidationException("Cannot add null location to shelf");
    }
    if (locations.size() >= maxLocations) {
        throw WarehouseException("Shelf " + shelfId + " is full. Cannot add more locations");
    }
    if (containsLocation(location->getLocationId())) {
        throw DuplicateBookException("Location " + location->getLocationId() + " already exists on shelf " + shelfId);
    }
    locations.push_back(location);
}

void Shelf::removeLocation(const std::string& locationId) {
    auto it = std::find_if(locations.begin(), locations.end(),
        [&locationId](const std::shared_ptr<StorageLocation>& loc) {
            return loc->getLocationId() == locationId;
        });
    if (it != locations.end()) {
        locations.erase(it);
    }
}

std::shared_ptr<StorageLocation> Shelf::findLocation(const std::string& locationId) const noexcept {
    auto it = std::find_if(locations.begin(), locations.end(),
        [&locationId](const std::shared_ptr<StorageLocation>& loc) {
            return loc->getLocationId() == locationId;
        });
    return (it != locations.end()) ? *it : nullptr;
}

bool Shelf::containsLocation(const std::string& locationId) const noexcept {
    return findLocation(locationId) != nullptr;
}

std::vector<std::shared_ptr<StorageLocation>> Shelf::getAvailableLocations() const noexcept {
    std::vector<std::shared_ptr<StorageLocation>> available;
    std::copy_if(locations.begin(), locations.end(), std::back_inserter(available),
        [](const std::shared_ptr<StorageLocation>& loc) {
            return loc->getStatus() == StorageLocation::LocationStatus::FREE;
        });
    return available;
}

std::vector<std::shared_ptr<StorageLocation>> Shelf::getOccupiedLocations() const noexcept {
    std::vector<std::shared_ptr<StorageLocation>> occupied;
    std::copy_if(locations.begin(), locations.end(), std::back_inserter(occupied),
        [](const std::shared_ptr<StorageLocation>& loc) {
            return loc->getStatus() == StorageLocation::LocationStatus::OCCUPIED;
        });
    return occupied;
}

bool Shelf::hasAvailableSpace() const noexcept {
    return locations.size() < maxLocations;
}

int Shelf::getTotalCapacity() const noexcept {
    int total = 0;
    for (const auto& location : locations) {
        total += location->getCapacity();
    }
    return total;
}

int Shelf::getCurrentLoad() const noexcept {
    int total = 0;
    for (const auto& location : locations) {
        total += location->getCurrentLoad();
    }
    return total;
}

int Shelf::getAvailableSpace() const noexcept {
    return getTotalCapacity() - getCurrentLoad();
}

bool Shelf::isEmpty() const noexcept {
    return getCurrentLoad() == 0;
}

bool Shelf::isFull() const noexcept {
    return locations.size() >= maxLocations && getAvailableSpace() == 0;
}

std::string Shelf::getInfo() const noexcept {
    return "Shelf: " + shelfId + 
           " | Locations: " + std::to_string(locations.size()) + "/" + std::to_string(maxLocations) +
           " | Capacity: " + std::to_string(getTotalCapacity()) +
           " | Load: " + std::to_string(getCurrentLoad()) +
           " | Available: " + std::to_string(getAvailableSpace()) +
           " | Available Locations: " + std::to_string(getAvailableLocations().size());
}

bool Shelf::operator==(const Shelf& other) const noexcept {
    return shelfId == other.shelfId &&
           maxLocations == other.maxLocations &&
           locations == other.locations;
}

bool Shelf::operator!=(const Shelf& other) const noexcept {
    return !(*this == other);
}