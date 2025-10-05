#include "warehouse/StorageLocation.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include <regex>

bool StorageLocation::isValidLocationId(const std::string& locationId) const {
    // "A-01-B-05" (Section-Shelf-Row-Cell)
    std::regex pattern("^[A-Z]-\\d{2}-[A-Z]-\\d{2}$");
    return std::regex_match(locationId, pattern) && !locationId.empty();
}

bool StorageLocation::isValidCapacity(int capacity) const {
    return capacity >= WarehouseConfig::StorageLocation::MIN_CAPACITY && 
           capacity <= WarehouseConfig::StorageLocation::MAX_CAPACITY;
}

bool StorageLocation::isValidLoad(int load, int capacity) const {
    return load >= 0 && load <= capacity;
}

StorageLocation::StorageLocation(const std::string& locationId, int capacity, 
                                int currentLoad, LocationStatus status) {
    if (!isValidLocationId(locationId)) {
        throw DataValidationException("Invalid location ID format: " + locationId);
    }
    if (!isValidCapacity(capacity)) {
        throw DataValidationException("Invalid capacity: " + std::to_string(capacity));
    }
    if (!isValidLoad(currentLoad, capacity)) {
        throw DataValidationException("Invalid current load: " + std::to_string(currentLoad));
    }
    this->locationId = locationId;
    this->capacity = capacity;
    this->currentLoad = currentLoad;
    this->status = status;
}

std::string StorageLocation::getLocationId() const noexcept {
    return locationId;
}

int StorageLocation::getCapacity() const noexcept {
    return capacity;
}

int StorageLocation::getCurrentLoad() const noexcept {
    return currentLoad;
}

int StorageLocation::getAvailableSpace() const noexcept {
    return capacity - currentLoad;
}

StorageLocation::LocationStatus StorageLocation::getStatus() const noexcept {
    return status;
}

bool StorageLocation::canAccommodate(int books) const noexcept {
    return status != LocationStatus::BLOCKED && 
           books >= 0 && 
           (currentLoad + books) <= capacity;
}

void StorageLocation::addBooks(int count) {
    if (status == LocationStatus::BLOCKED) {
        throw WarehouseException("Cannot add books to blocked location: " + locationId);
    }
    if (count < 0) {
        throw DataValidationException("Cannot add negative number of books: " + std::to_string(count));
    }
    if (!canAccommodate(count)) {
        throw WarehouseException("Cannot accommodate " + std::to_string(count) + 
                               " books in location: " + locationId + 
                               " (available: " + std::to_string(getAvailableSpace()) + ")");
    }
    currentLoad += count;
    if (currentLoad > 0) {
        status = LocationStatus::OCCUPIED;
    }
}

void StorageLocation::removeBooks(int count) {
    if (status == LocationStatus::BLOCKED) {
        throw WarehouseException("Cannot remove books from blocked location: " + locationId);
    }
    if (count < 0) {
        throw DataValidationException("Cannot remove negative number of books: " + std::to_string(count));
    }
    if (count > currentLoad) {
        throw WarehouseException("Cannot remove " + std::to_string(count) + 
                               " books from location: " + locationId + 
                               " (current: " + std::to_string(currentLoad) + ")");
    }
    currentLoad -= count;
    if (currentLoad == 0) {
        status = LocationStatus::FREE;
    }
}

void StorageLocation::setStatus(LocationStatus newStatus) noexcept {
    status = newStatus;
}

bool StorageLocation::isEmpty() const noexcept {
    return currentLoad == 0;
}

bool StorageLocation::isFull() const noexcept {
    return currentLoad >= capacity;
}

std::string StorageLocation::getInfo() const noexcept {
    std::string statusStr;
    switch (status) {
        case LocationStatus::FREE: statusStr = "Free"; break;
        case LocationStatus::OCCUPIED: statusStr = "Occupied"; break;
        case LocationStatus::BLOCKED: statusStr = "Blocked"; break;
    }
    return "Location: " + locationId + 
           " | Capacity: " + std::to_string(capacity) +
           " | Load: " + std::to_string(currentLoad) +
           " | Available: " + std::to_string(getAvailableSpace()) +
           " | Status: " + statusStr;
}

bool StorageLocation::operator==(const StorageLocation& other) const noexcept {
    return locationId == other.locationId &&
           capacity == other.capacity &&
           currentLoad == other.currentLoad &&
           status == other.status;
}

bool StorageLocation::operator!=(const StorageLocation& other) const noexcept {
    return !(*this == other);
}