/**
 * @file TourGuide.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TourGuide class for tour guide management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class TourGuide
 * @brief Class representing tour guide information
 * 
 * Manages tour guide details including language skills and experience.
 * Provides functionality for guide information retrieval and presentation.
 */
class TourGuide {
private:
    std::string name;                                       ///< Guide name
    std::string language;                                   ///< Primary language spoken
    int experienceYears;                                    ///< Years of experience

public:
    /**
     * @brief Construct a new TourGuide object
     * 
     * @param name constant reference to the string containing guide name
     * @param language constant reference to the string containing primary language
     * @param experienceYears integer value containing years of experience
     */
    TourGuide(const std::string& name,
              const std::string& language,
              int experienceYears);
    
    /**
     * @brief Get the guide name
     * 
     * @return std::string containing guide name
     */
    std::string getName() const;
    
    /**
     * @brief Get the primary language
     * 
     * @return std::string containing primary language
     */
    std::string getLanguage() const;
    
    /**
     * @brief Get the experience years
     * 
     * @return int containing years of experience
     */
    int getExperienceYears() const;
    
    /**
     * @brief Get comprehensive guide information
     * 
     * @return std::string containing formatted guide details
     */
    std::string getGuideInfo() const;
};