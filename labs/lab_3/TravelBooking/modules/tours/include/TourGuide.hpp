#pragma once
#include <string>

class TourGuide {
private:
    std::string name;
    std::string language;
    int experienceYears;

public:
    TourGuide(const std::string& name,
              const std::string& language,
              int experienceYears);
    std::string getName() const;
    std::string getLanguage() const;
    int getExperienceYears() const;
    std::string getGuideInfo() const;
};
