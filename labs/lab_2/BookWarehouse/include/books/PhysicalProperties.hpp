#pragma once
#include <string>

class PhysicalProperties {
public:
    enum class CoverType {
        HARDCOVER,
        PAPERBACK
    };
private:
    static constexpr int MAX_WEIGHT = 5000;
    static constexpr int MAX_PAGES = 5000;
    static constexpr int MAX_DIMENSION = 500;
    int weight;           // вес в граммах
    int height;           // высота в мм
    int width;            // ширина в мм  
    int thickness;        // толщина в мм
    int pageCount;        // количество страниц
    CoverType coverType;  // тип обложки
    std::string material; // материал обложки
    bool isValidWeight(int weight) const;
    bool isValidDimension(int dimension) const;
    bool isValidPageCount(int pages) const;
public:
    PhysicalProperties(int weight, int height, int width, int thickness, 
                      int pageCount, CoverType coverType, const std::string& material);
    int getWeight() const noexcept;
    int getHeight() const noexcept;
    int getWidth() const noexcept;
    int getThickness() const noexcept;
    int getPageCount() const noexcept;
    CoverType getCoverType() const noexcept;
    std::string getMaterial() const noexcept;
    double getVolume() const noexcept;        // объем в см³
    double getDensity() const noexcept;       // плотность (г/см³)
    std::string getCoverTypeString() const noexcept;
    bool operator==(const PhysicalProperties& other) const noexcept;
    bool operator!=(const PhysicalProperties& other) const noexcept;
};