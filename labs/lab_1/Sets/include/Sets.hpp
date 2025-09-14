/**
 * @file Sets.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Set class for working with sets
 * @version 0.1
 * @date 2025-09-09
 * 
 * 
 */

#include <vector>
#include <string>

/**
 * @class Set
 * @brief Class for working with sets
 * 
 * Stores elements as strings.
 * Supports set operations: union, 
 * intersection, difference, membership testing, 
 * and boolean creation
 */
class Set{
    std::vector<std::string> elInSet;
    /**
     * @brief Private method to add one element to a set
     * 
     * @param &element constant reference of the string containing 
     * the element to add to the set
     * 
     * @return true
     * @return false
     */
    bool add(const std::string& element);

    /**
     * @brief Private method for parsing a string to bring it to the desired form
     * 
     * @param &string constant reference of the string to parse
     * @return std::vector<std::string> 
     */
    std::vector<std::string> parseSetString(const std::string& string);

    /**
     * @brief Private method to check if a string is valid
     * 
     * @param &string constant reference of the string being checked
     * @return true 
     * @return false 
     */
    bool isValid(const std::string& string) const;

    /**
     * @brief Private constant method to convert a class set to a string
     * 
     * @return std::string
     */
    std::string toString() const;

    /**
     * @brief Private intermediate method to remove all 
     * spaces in a string
     * 
     * @param &str constant reference of the image string to form the output 
     * prototype string after removing spaces
     * @return std::string 
     */
    std::string removeSpaces(const std::string& str);
    
    /**
     * @brief Private method to validate element content (letters and digits only)
     * 
     * @param str string to validate
     * @param start starting index of the element
     * @return int end index of the element
     */
    int validateElement(const std::string& str, size_t start) const;
    
    /**
     * @brief Private method to handle bracket characters
     * 
     * @param c current character
     * @param balance reference to bracket balance counter
     * @param expectElement reference to element expectation flag
     * @param afterComma reference to comma flag
     * @return bool true if valid, false otherwise
     */
    bool handleBracket(char c, int& balance, bool& expectElement, bool& afterComma) const;
    
    /**
     * @brief Private method to handle comma character
     * 
     * @param expectElement reference to element expectation flag
     * @param afterComma reference to comma flag
     * @return bool true if valid, false otherwise
     */
    bool handleComma(bool& expectElement, bool& afterComma) const;
    
    public:
    /**
     * @brief Construct a new Set object
     * 
     */
    Set();

    /**
     * @brief Destroy the Set object
     * 
     */
    ~Set();

    /**
     * @brief Public method to remove an element from a set
     * 
     * @param &element constant reference of the string to remove element from set
     * @return true 
     * @return false 
     */
    bool remove(const std::string& element);

    /**
     * @brief Public method to clear the entire set
     * 
     */
    void clear();

    /**
     * @brief Public method for getting the cardinality of a set
     * 
     * @return int 
     */
    int getCardinality() const;

    /**
     * @brief Public constant method for determining whether a set is empty
     * 
     * @return true 
     * @return false 
     */
    bool isVoid() const;

    /**
     * @brief Public method for creating a boolean from a set
     * 
     * @return Set 
     */
    Set getBoolean();

    /**
     * @brief Constant method to get a constant reference to a string vector 
     * of elements in a set
     * 
     * @return const std::vector<std::string>& 
     */
    const std::vector<std::string>& getElInSet() const;

    /**
     * @brief Copy constructor
     * 
     * @param other constant reference to the set being copied
     */
    Set(const Set& other);

    /**
     * @brief Assignment operator
     * 
     * @param other constant reference to the set being copied
     * @return Set& 
     */
    Set& operator = (const Set& other);

    /**
     * @brief Public operator for filling a set with a string
     * 
     * @param elements constant reference to a set string
     * @return Set& 
     */
    Set& operator = (const std::string& elements);

    /**
     * @brief Analogue of the operator fill a set with a string for working with the data type char
     * 
     * @param elements constant pointer of type char
     * @return Set& 
     */
    Set& operator =( const char* elements);

    /**
     * @brief Public operator for comparing two sets
     * 
     * @param other constant reference to the set being compared
     * @return true 
     * @return false 
     */
    bool operator == (const Set& other);

    /**
     * @brief Constant public operator for checking whether an element is in a set
     * 
     * @param isHere constant reference to the string containing the element being checked
     * @return true 
     * @return false 
     */
    bool operator [] (const std::string& isHere) const;

    /**
     * @brief Analog operator checks if an element is present in a set for working with a constant char data type
     * 
     * @param isHere constant pointer of type char
     * @return true 
     * @return false 
     */
    bool operator [] (const char* isHere) const;

    /**
     * @brief Public operator for adding elements from another set to the current set (union operation)
     * 
     * @param other constant reference to the set whose elements are being added
     * @return Set&
     */
    Set& operator += (const Set& other);

    /**
     * @brief Public operator for adding a single element represented as a string to the current set
     * 
     * @param string constant reference to the string containing the element to add
     * @return Set&
     */
    Set& operator += (const std::string& string);

    /**
     * @brief Public operator for adding a single element represented as a character array to the current set
     * 
     * @param elements constant pointer of type char containing the element to add
     * @return Set&
     */
    Set& operator += (const char* elements);

    /**
     * @brief Public operator for union of two sets
     * 
     * @param other constant reference to the set to unite with
     * @return Set
     */
    Set operator + (const Set& other);

    /**
     * @brief Public operator for intersection of two sets
     * 
     * @param other constant reference to the set to intersect with
     * @return Set
     */
    Set operator * (const Set& other);

    /**
     * @brief Public operator for intersection with assignment
     * 
     * @param other constant reference to the set to intersect with
     * @return Set&
     */
    Set& operator *= (const Set& other);

    /**
     * @brief Public operator for difference with assignment
     * 
     * @param other constant reference to the set to subtract
     * @return Set&
     */
    Set& operator -= (const Set& other);

    /**
     * @brief Public operator for difference of two sets
     * 
     * @param other constant reference to the set to subtract
     * @return Set
     */
    Set operator - (const Set& other);

    /**
     * @brief Friend operator for outputting set to output stream
     * 
     * @param os reference to output stream
     * @param set constant reference to the set to output
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Set& set);
    
    /**
     * @brief Friend operator for inputting set from input stream
     * 
     * @param is reference to input stream
     * @param set reference to the set to input data into
     * @return std::istream&
     */
    friend std::istream& operator>>(std::istream& is, Set& set);
};