#include "books/PhysicalProperties.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"

bool PhysicalProperties::isValidWeight(int weight) const {
    return weight > 0 && weight <= MAX_WEIGHT;
}

bool PhysicalProperties::isValidDimension(int dimension) const {
    return dimension > 0 && dimension <= MAX_DIMENSION;
}

bool PhysicalProperties::isValidPageCount(int pages) const {
    return pages > 0 && pages <= MAX_PAGES;
}

PhysicalProperties::PhysicalProperties(int weight, int height, int width, 
    int thickness, int pageCount, CoverType coverType, const std::string& material) {
    
    if (!isValidWeight(weight)) {
        throw DataValidationException("Invalid weight: " + std::to_string(weight) + "g");
    }
    if (!isValidDimension(height)) {
        throw DataValidationException("Invalid height: " + std::to_string(height) + "mm");
    }
    if (!isValidDimension(width)) {
        throw DataValidationException("Invalid width: " + std::to_string(width) + "mm");
    }
    if (!isValidDimension(thickness)) {
        throw DataValidationException("Invalid thickness: " + std::to_string(thickness) + "mm");
    }
    if (!isValidPageCount(pageCount)) {
        throw DataValidationException("Invalid page count: " + std::to_string(pageCount));
    }
    if (!StringValidation::isValidName(material)) {
        throw DataValidationException("Invalid material: '" + material + "'");
    }
    
    this->weight = weight;
    this->height = height;
    this->width = width;
    this->thickness = thickness;
    this->pageCount = pageCount;
    this->coverType = coverType;
    this->material = material;
}

int PhysicalProperties::getWeight() const noexcept {
    return weight;
}

int PhysicalProperties::getHeight() const noexcept {
    return height;
}

int PhysicalProperties::getWidth() const noexcept {
    return width;
}

int PhysicalProperties::getThickness() const noexcept {
    return thickness;
}

int PhysicalProperties::getPageCount() const noexcept {
    return pageCount;
}

PhysicalProperties::CoverType PhysicalProperties::getCoverType() const noexcept {
    return coverType;
}

std::string PhysicalProperties::getMaterial() const noexcept {
    return material;
}

double PhysicalProperties::getVolume() const noexcept {
    // Объем в см³ (переводим мм в см)
    return (height / 10.0) * (width / 10.0) * (thickness / 10.0);
}

double PhysicalProperties::getDensity() const noexcept {
    double volume = getVolume();
    if (volume == 0) return 0;
    return weight / volume; // г/см³
}

std::string PhysicalProperties::getCoverTypeString() const noexcept {
    switch(coverType) {
        case CoverType::HARDCOVER: return "Hardcover";
        case CoverType::PAPERBACK: return "Paperback";
        default: return "Unknown";
    }
}

bool PhysicalProperties::operator==(const PhysicalProperties& other) const noexcept {
    return weight == other.weight &&
           height == other.height &&
           width == other.width &&
           thickness == other.thickness &&
           pageCount == other.pageCount &&
           coverType == other.coverType &&
           material == other.material;
}

bool PhysicalProperties::operator!=(const PhysicalProperties& other) const noexcept {
    return !(*this == other);
}