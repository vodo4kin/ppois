/**
 * @file Transport.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Transport base class for transportation system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class Transport
 * @brief Base class for all types of transportation
 * 
 * Provides common interface and properties for various transport types
 * including flights, trains, buses, ships, and taxis. Implements core
 * functionality for route management and pricing.
 */
class Transport {
public:
    /**
     * @enum Type
     * @brief Enumeration of transportation types
     */
    enum class Type {
        FLIGHT,                                             ///< Air travel transport
        TRAIN,                                              ///< Rail transport
        BUS,                                                ///< Road bus transport
        SHIP,                                               ///< Sea transport
        TAXI                                                ///< Local taxi transport
    };

private:
    std::string company;                                    ///< Transport company name
    std::string departure;                                  ///< Departure location
    std::string arrival;                                    ///< Arrival location
    std::string departureTime;                              ///< Departure time
    std::string arrivalTime;                                ///< Arrival time
    double price;                                           ///< Ticket price
    Type transportType;                                     ///< Type of transport

public:
    /**
     * @brief Construct a new Transport object
     * 
     * @param company constant reference to the string containing company name
     * @param departure constant reference to the string containing departure location
     * @param arrival constant reference to the string containing arrival location
     * @param departureTime constant reference to the string containing departure time
     * @param arrivalTime constant reference to the string containing arrival time
     * @param price double value containing ticket price
     * @param type Type value containing transport type
     */
    Transport(const std::string& company,
              const std::string& departure,
              const std::string& arrival,
              const std::string& departureTime,
              const std::string& arrivalTime,
              double price,
              Type type);
    
    /**
     * @brief Get the transport identifier
     * 
     * @return int containing unique transport identifier
     */
    int getTransportId() const;
    
    /**
     * @brief Get the company name
     * 
     * @return std::string containing transport company name
     */
    std::string getCompany() const;
    
    /**
     * @brief Get the departure location
     * 
     * @return std::string containing departure location
     */
    std::string getDeparture() const;
    
    /**
     * @brief Get the arrival location
     * 
     * @return std::string containing arrival location
     */
    std::string getArrival() const;
    
    /**
     * @brief Get the departure time
     * 
     * @return std::string containing departure time
     */
    std::string getDepartureTime() const;
    
    /**
     * @brief Get the arrival time
     * 
     * @return std::string containing arrival time
     */
    std::string getArrivalTime() const;
    
    /**
     * @brief Get the ticket price
     * 
     * @return double containing ticket price
     */
    double getPrice() const;
    
    /**
     * @brief Get the transport type
     * 
     * @return Type containing transport type enum value
     */
    Type getTransportType() const;
    
    /**
     * @brief Get the transport type as string
     * 
     * @return std::string containing transport type description
     */
    std::string getTransportTypeStr() const;
    
    /**
     * @brief Get comprehensive transport information
     * 
     * @return std::string containing formatted transport details
     */
    std::string getTransportInfo() const;
};