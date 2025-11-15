/**
 * @file TransportSchedule.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TransportSchedule class for transport scheduling
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
 * @class TransportSchedule
 * @brief Class representing transport schedule information
 * 
 * Manages transport schedules with departure dates, routes, and seat availability.
 * Provides functionality for seat reservation and schedule information retrieval.
 */
class TransportSchedule {
private:
    std::shared_ptr<Transport> transport;                   ///< Shared pointer to transport object
    std::string departureDate;                              ///< Date of departure
    std::string origin;                                     ///< Route origin location
    std::string destination;                                ///< Route destination location
    int availableSeats;                                     ///< Number of available seats

public:
    /**
     * @brief Construct a new TransportSchedule object
     * 
     * @param transport shared pointer to the Transport object
     * @param departureDate constant reference to the string containing departure date
     * @param origin constant reference to the string containing origin location
     * @param destination constant reference to the string containing destination location
     * @param availableSeats integer value containing available seat count
     */
    TransportSchedule(std::shared_ptr<Transport> transport,
                      const std::string& departureDate,
                      const std::string& origin,
                      const std::string& destination,
                      int availableSeats);
    
    /**
     * @brief Get the transport object
     * 
     * @return std::shared_ptr<Transport> containing transport object
     */
    std::shared_ptr<Transport> getTransport() const;
    
    /**
     * @brief Get the departure date
     * 
     * @return std::string containing departure date
     */
    std::string getDepartureDate() const;
    
    /**
     * @brief Get the origin location
     * 
     * @return std::string containing origin location
     */
    std::string getOrigin() const;
    
    /**
     * @brief Get the destination location
     * 
     * @return std::string containing destination location
     */
    std::string getDestination() const;
    
    /**
     * @brief Get the available seats count
     * 
     * @return int containing number of available seats
     */
    int getAvailableSeats() const;
    
    /**
     * @brief Reserve specified number of seats
     * 
     * @param count integer value containing number of seats to reserve
     */
    void reserveSeats(int count);
    
    /**
     * @brief Get comprehensive schedule information
     * 
     * @return std::string containing formatted schedule details
     */
    std::string getScheduleInfo() const;
};