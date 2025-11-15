/**
 * @file TourReview.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TourReview class for tour reviews
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class TourReview
 * @brief Class representing tour reviews and ratings
 * 
 * Manages customer reviews for tours with ratings and comments.
 * Provides functionality for review summary generation and data retrieval.
 */
class TourReview {
private:
    std::string reviewerName;                               ///< Name of the reviewer
    std::string comment;                                    ///< Review comment text
    int rating;                                             ///< Rating value (typically 1-5)

public:
    /**
     * @brief Construct a new TourReview object
     * 
     * @param reviewerName constant reference to the string containing reviewer name
     * @param comment constant reference to the string containing review comment
     * @param rating integer value containing rating value
     */
    TourReview(const std::string& reviewerName,
               const std::string& comment,
               int rating);
    
    /**
     * @brief Get the reviewer name
     * 
     * @return std::string containing reviewer name
     */
    std::string getReviewerName() const;
    
    /**
     * @brief Get the review comment
     * 
     * @return std::string containing review comment text
     */
    std::string getComment() const;
    
    /**
     * @brief Get the rating value
     * 
     * @return int containing rating value
     */
    int getRating() const;
    
    /**
     * @brief Get review summary
     * 
     * @return std::string containing formatted review summary
     */
    std::string getReviewSummary() const;
};