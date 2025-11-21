/**
 * @file TransportReview.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TransportReview class for transport reviews
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Transport.hpp"

/**
 * @class TransportReview
 * @brief Class representing transport service reviews
 * 
 * Manages customer reviews for transport services with ratings and comments.
 * Provides functionality for review summary generation and data retrieval.
 */
class TransportReview {
private:
    std::shared_ptr<Transport> transport;                   ///< Shared pointer to reviewed transport
    std::string reviewerName;                               ///< Name of the reviewer
    std::string comment;                                    ///< Review comment text
    int rating;                                             ///< Rating value (typically 1-5)

public:
    /**
     * @brief Construct a new TransportReview object
     * 
     * @param transport shared pointer to the Transport object being reviewed
     * @param reviewerName constant reference to the string containing reviewer name
     * @param comment constant reference to the string containing review comment
     * @param rating integer value containing rating value
     */
    TransportReview(std::shared_ptr<Transport> transport,
                    const std::string& reviewerName,
                    const std::string& comment,
                    int rating);
    
    /**
     * @brief Get the transport object
     * 
     * @return std::shared_ptr<Transport> containing reviewed transport object
     */
    std::shared_ptr<Transport> getTransport() const;
    
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