/**
 * @file BookCollection.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookCollection class for working with book collections
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <Book.hpp>

/**
 * @class BookCollection
 * @brief Class for working with book collections
 * 
 * Manages collections of books with name, description, and category.
 * Provides operations for adding, removing, and searching books in collections.
 */
class BookCollection {
private:
    std::string name;                           ///< Name of the collection
    std::string description;                    ///< Description of the collection
    std::string category;                       ///< Category of the collection
    std::vector<std::shared_ptr<Book>> books;   ///< Vector of books in the collection

    /**
     * @brief Private method to validate collection name
     * 
     * @param name constant reference to the string containing name to validate
     * 
     * @return true if name is valid
     * @return false if name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate collection description
     * 
     * @param desc constant reference to the string containing description to validate
     * 
     * @return true if description is valid
     * @return false if description is invalid
     */
    bool isValidDescription(const std::string& desc) const;

    /**
     * @brief Private method to validate collection category
     * 
     * @param category constant reference to the string containing category to validate
     * 
     * @return true if category is valid
     * @return false if category is invalid
     */
    bool isValidCategory(const std::string& category) const;

public:
    /**
     * @brief Construct a new BookCollection object
     * 
     * @param name constant reference to the string containing collection name
     * @param description constant reference to the string containing collection description
     * @param category constant reference to the string containing collection category
     */
    BookCollection(const std::string& name, const std::string& description = "",
                   const std::string& category = "General");

    /**
     * @brief Get the collection name
     * 
     * @return std::string containing collection name
     */
    std::string getName() const noexcept;

    /**
     * @brief Get the collection description
     * 
     * @return std::string containing collection description
     */
    std::string getDescription() const noexcept;

    /**
     * @brief Get the collection category
     * 
     * @return std::string containing collection category
     */
    std::string getCategory() const noexcept;

    /**
     * @brief Add book to collection
     * 
     * @param book shared pointer to the Book object to add
     */
    void addBook(std::shared_ptr<Book> book);

    /**
     * @brief Remove book from collection
     * 
     * @param book shared pointer to the Book object to remove
     */
    void removeBook(std::shared_ptr<Book> book);

    /**
     * @brief Get the number of books in collection
     * 
     * @return size_t containing book count
     */
    size_t getBookCount() const noexcept;

    /**
     * @brief Check if collection contains specific book
     * 
     * @param book shared pointer to the Book object to check
     * 
     * @return true if collection contains book
     * @return false if collection does not contain book
     */
    bool containsBook(std::shared_ptr<Book> book) const;

    /**
     * @brief Check if collection is empty
     * 
     * @return true if collection is empty
     * @return false if collection is not empty
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Get collection information
     * 
     * @return std::string containing formatted collection information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for book collections
     * 
     * @param other constant reference to the book collection to compare with
     * 
     * @return true if book collections are equal
     * @return false if book collections are not equal
     */
    bool operator==(const BookCollection& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book collections
     * 
     * @param other constant reference to the book collection to compare with
     * 
     * @return true if book collections are not equal
     * @return false if book collections are equal
     */
    bool operator!=(const BookCollection& other) const noexcept;
};